/*
 *      Copyright (C) 2016-2017 Team Kodi
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

#include "GameClientTranslator.h"

using namespace KODI;
using namespace GAME;

const char* CGameClientTranslator::ToString(GAME_ERROR error)
{
  switch (error)
  {
  case GAME_ERROR_NO_ERROR:           return "no error";
  case GAME_ERROR_NOT_IMPLEMENTED:    return "not implemented";
  case GAME_ERROR_REJECTED:           return "rejected by the client";
  case GAME_ERROR_INVALID_PARAMETERS: return "invalid parameters for this method";
  case GAME_ERROR_FAILED:             return "the command failed";
  case GAME_ERROR_NOT_LOADED:         return "no game is loaded";
  case GAME_ERROR_RESTRICTED:         return "the required resources are restricted";
  default:
    break;
  }
  return "unknown error";
}

const char* CGameClientTranslator::ToString(GAME_MEMORY memory)
{
  switch (memory)
  {
  case GAME_MEMORY_SAVE_RAM:                return "save ram";
  case GAME_MEMORY_RTC:                     return "rtc";
  case GAME_MEMORY_SYSTEM_RAM:              return "system ram";
  case GAME_MEMORY_VIDEO_RAM:               return "video ram";
  case GAME_MEMORY_SNES_BSX_RAM:            return "snes bsx ram";
  case GAME_MEMORY_SNES_SUFAMI_TURBO_A_RAM: return "snes sufami turbo a ram";
  case GAME_MEMORY_SNES_SUFAMI_TURBO_B_RAM: return "snes sufami turbo b ram";
  case GAME_MEMORY_SNES_GAME_BOY_RAM:       return "snes game boy ram";
  case GAME_MEMORY_SNES_GAME_BOY_RTC:       return "snes game boy rtc";
  default:
    break;
  }
  return "unknown memory";
}

bool CGameClientTranslator::TranslateStreamType(GAME_STREAM_TYPE gameType, RETRO::StreamType &retroType)
{
  switch (gameType)
  {
  case GAME_STREAM_AUDIO:
    retroType = RETRO::StreamType::AUDIO;
    return true;
  case GAME_STREAM_VIDEO:
    retroType = RETRO::StreamType::VIDEO;
    return true;
  case GAME_STREAM_SW_FRAMEBUFFER:
    retroType = RETRO::StreamType::SW_BUFFER;
    return true;
  case GAME_STREAM_HW_FRAMEBUFFER:
    retroType = RETRO::StreamType::HW_BUFFER;
    return true;
  default:
    break;
  }
  return false;
}

AVPixelFormat CGameClientTranslator::TranslatePixelFormat(GAME_PIXEL_FORMAT format)
{
  switch (format)
  {
  case GAME_PIXEL_FORMAT_0RGB8888: return AV_PIX_FMT_0RGB32;
  case GAME_PIXEL_FORMAT_RGB565:   return AV_PIX_FMT_RGB565;
  case GAME_PIXEL_FORMAT_0RGB1555: return AV_PIX_FMT_RGB555;
  default:
    break;
  }
  return AV_PIX_FMT_NONE;
}

RETRO::PCMFormat CGameClientTranslator::TranslatePCMFormat(GAME_PCM_FORMAT format)
{
  switch (format)
  {
  case GAME_PCM_FORMAT_S16NE: return RETRO::PCMFormat::FMT_S16NE;
  default:
    break;
  }
  return RETRO::PCMFormat::FMT_UNKNOWN;
}

RETRO::AudioChannel CGameClientTranslator::TranslateAudioChannel(GAME_AUDIO_CHANNEL channel)
{
  switch (channel)
  {
  case GAME_CH_FL:   return RETRO::AudioChannel::CH_FL;
  case GAME_CH_FR:   return RETRO::AudioChannel::CH_FR;
  case GAME_CH_FC:   return RETRO::AudioChannel::CH_FC;
  case GAME_CH_LFE:  return RETRO::AudioChannel::CH_LFE;
  case GAME_CH_BL:   return RETRO::AudioChannel::CH_BL;
  case GAME_CH_BR:   return RETRO::AudioChannel::CH_BR;
  case GAME_CH_FLOC: return RETRO::AudioChannel::CH_FLOC;
  case GAME_CH_FROC: return RETRO::AudioChannel::CH_FROC;
  case GAME_CH_BC:   return RETRO::AudioChannel::CH_BC;
  case GAME_CH_SL:   return RETRO::AudioChannel::CH_SL;
  case GAME_CH_SR:   return RETRO::AudioChannel::CH_SR;
  case GAME_CH_TFL:  return RETRO::AudioChannel::CH_TFL;
  case GAME_CH_TFR:  return RETRO::AudioChannel::CH_TFR;
  case GAME_CH_TFC:  return RETRO::AudioChannel::CH_TFC;
  case GAME_CH_TC:   return RETRO::AudioChannel::CH_TC;
  case GAME_CH_TBL:  return RETRO::AudioChannel::CH_TBL;
  case GAME_CH_TBR:  return RETRO::AudioChannel::CH_TBR;
  case GAME_CH_TBC:  return RETRO::AudioChannel::CH_TBC;
  case GAME_CH_BLOC: return RETRO::AudioChannel::CH_BLOC;
  case GAME_CH_BROC: return RETRO::AudioChannel::CH_BROC;
  default:
    break;
  }
  return RETRO::AudioChannel::CH_NULL;
}

RETRO::VideoRotation CGameClientTranslator::TranslateRotation(GAME_VIDEO_ROTATION rotation)
{
  switch (rotation)
  {
  case GAME_VIDEO_ROTATION_90_CCW:
    return RETRO::VideoRotation::ROTATION_90_CCW;
  case GAME_VIDEO_ROTATION_180_CCW:
    return RETRO::VideoRotation::ROTATION_180_CCW;
  case GAME_VIDEO_ROTATION_270_CCW:
    return RETRO::VideoRotation::ROTATION_270_CCW;
  default:
    break;
  }
  return RETRO::VideoRotation::ROTATION_0;
}

GAME_KEY_MOD CGameClientTranslator::GetModifiers(KEYBOARD::Modifier modifier)
{
  using namespace KEYBOARD;

  unsigned int mods = GAME_KEY_MOD_NONE;

  if (modifier & Modifier::MODIFIER_CTRL)  mods |= GAME_KEY_MOD_CTRL;
  if (modifier & Modifier::MODIFIER_SHIFT) mods |= GAME_KEY_MOD_SHIFT;
  if (modifier & Modifier::MODIFIER_ALT)   mods |= GAME_KEY_MOD_ALT;
  if (modifier & Modifier::MODIFIER_RALT)  mods |= GAME_KEY_MOD_ALT;
  if (modifier & Modifier::MODIFIER_META)  mods |= GAME_KEY_MOD_META;
  if (modifier & Modifier::MODIFIER_SUPER) mods |= GAME_KEY_MOD_SUPER;
  if (modifier & Modifier::MODIFIER_NUMLOCK) mods |= GAME_KEY_MOD_NUMLOCK;
  if (modifier & Modifier::MODIFIER_CAPSLOCK) mods |= GAME_KEY_MOD_CAPSLOCK;
  if (modifier & Modifier::MODIFIER_SCROLLLOCK) mods |= GAME_KEY_MOD_SCROLLOCK;

  return static_cast<GAME_KEY_MOD>(mods);
}

const char* CGameClientTranslator::TranslateRegion(GAME_REGION region)
{
  switch (region)
  {
  case GAME_REGION_NTSC: return "NTSC";
  case GAME_REGION_PAL:  return "PAL";
  default:
    break;
  }
  return "Unknown";
}

PORT_TYPE CGameClientTranslator::TranslatePortType(GAME_PORT_TYPE portType)
{
  switch (portType)
  {
    case GAME_PORT_KEYBOARD:    return PORT_TYPE::KEYBOARD;
    case GAME_PORT_MOUSE:       return PORT_TYPE::MOUSE;
    case GAME_PORT_CONTROLLER:  return PORT_TYPE::CONTROLLER;
    default:
      break;
  }

  return PORT_TYPE::UNKNOWN;
}
