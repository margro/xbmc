/*
 *      Copyright (C) 2012-2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "RetroPlayerAudio.h"
#include "cores/AudioEngine/Interfaces/AE.h"
#include "cores/AudioEngine/Interfaces/AEStream.h"
#include "cores/AudioEngine/Utils/AEChannelInfo.h"
#include "cores/AudioEngine/Utils/AEUtil.h"
#include "cores/RetroPlayer/audio/AudioTranslator.h"
#include "cores/RetroPlayer/process/RPProcessInfo.h"
#include "utils/log.h"
#include "ServiceBroker.h"

#include <cmath>

using namespace KODI;
using namespace RETRO;

const double MAX_DELAY = 0.3; // seconds

CRetroPlayerAudio::CRetroPlayerAudio(CRPProcessInfo& processInfo) :
  m_processInfo(processInfo),
  m_pAudioStream(nullptr),
  m_bAudioEnabled(true)
{
  CLog::Log(LOGDEBUG, "RetroPlayer[AUDIO]: Initializing audio");
}

CRetroPlayerAudio::~CRetroPlayerAudio()
{
  CLog::Log(LOGDEBUG, "RetroPlayer[AUDIO]: Deinitializing audio");

  CloseStream();
}

bool CRetroPlayerAudio::OpenStream(const StreamProperties& properties)
{
  const AudioStreamProperties& audioProperties = reinterpret_cast<const AudioStreamProperties&>(properties);

  const AEDataFormat pcmFormat = CAudioTranslator::TranslatePCMFormat(audioProperties.format);
  if (pcmFormat == AE_FMT_INVALID)
  {
    CLog::Log(LOGERROR, "RetroPlayer[AUDIO]: Unknown PCM format: %d", static_cast<int>(audioProperties.format));
    return false;
  }

  unsigned int iSampleRate = static_cast<unsigned int>(std::round(audioProperties.sampleRate));
  if (iSampleRate == 0)
  {
    CLog::Log(LOGERROR, "RetroPlayer[AUDIO]: Invalid samplerate: %f", audioProperties.sampleRate);
    return false;
  }

  CAEChannelInfo channelLayout;
  for (auto it = audioProperties.channelMap.begin(); it != audioProperties.channelMap.end(); ++it)
  {
    AEChannel channel = CAudioTranslator::TranslateAudioChannel(*it);
    if (channel == AE_CH_NULL)
      break;

    channelLayout += channel;
  }

  if (!channelLayout.IsLayoutValid())
  {
    CLog::Log(LOGERROR, "RetroPlayer[AUDIO]: Empty channel layout");
    return false;
  }

  if (m_pAudioStream != nullptr)
    CloseStream();


  IAE* audioEngine = CServiceBroker::GetActiveAE();
  if (audioEngine == nullptr)
    return false;

  CLog::Log(LOGINFO, "RetroPlayer[AUDIO]: Creating audio stream, format = %s, sample rate = %d, channels = %d",
             CAEUtil::DataFormatToStr(pcmFormat)
             , iSampleRate
             , channelLayout.Count());

  AEAudioFormat audioFormat;
  audioFormat.m_dataFormat = pcmFormat;
  audioFormat.m_sampleRate = iSampleRate;
  audioFormat.m_channelLayout = channelLayout;
  m_pAudioStream = audioEngine->MakeStream(audioFormat);

  if (m_pAudioStream == nullptr)
  {
    CLog::Log(LOGERROR, "RetroPlayer[AUDIO]: Failed to create audio stream");
    return false;
  }

  m_processInfo.SetAudioChannels(audioFormat.m_channelLayout);
  m_processInfo.SetAudioSampleRate(audioFormat.m_sampleRate);
  m_processInfo.SetAudioBitsPerSample(CAEUtil::DataFormatToUsedBits(audioFormat.m_dataFormat));

  return true;
}

void CRetroPlayerAudio::AddStreamData(const StreamPacket &packet)
{
  const AudioStreamPacket& audioPacket = reinterpret_cast<const AudioStreamPacket&>(packet);

  if (m_bAudioEnabled)
  {
    if (m_pAudioStream)
    {
      const double delaySecs = m_pAudioStream->GetDelay();

      const size_t frameSize = m_pAudioStream->GetChannelCount() * (CAEUtil::DataFormatToBits(m_pAudioStream->GetDataFormat()) >> 3);

      const unsigned int frameCount = static_cast<unsigned int>(audioPacket.size / frameSize);

      if (delaySecs > MAX_DELAY)
      {
        m_pAudioStream->Flush();
        CLog::Log(LOGDEBUG, "RetroPlayer[AUDIO]: Audio delay (%0.2f ms) is too high - flushing", delaySecs * 1000);
      }

      m_pAudioStream->AddData(&audioPacket.data, 0, frameCount);
    }
  }
}

void CRetroPlayerAudio::CloseStream()
{
  if (m_pAudioStream)
  {
    CLog::Log(LOGDEBUG, "RetroPlayer[AUDIO]: Closing audio stream");

    CServiceBroker::GetActiveAE()->FreeStream(m_pAudioStream, true);
    m_pAudioStream = nullptr;
  }
}
