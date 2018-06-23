/*
 *      Copyright (C) 2017 Team Kodi
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

#pragma once

#include "cores/GameSettings.h"

#include <string>

namespace KODI
{
namespace RETRO
{
  /*!
   * \brief Video settings provided by the rendering system
   */
  class CRenderVideoSettings
  {
  public:
    CRenderVideoSettings() { Reset(); }

    void Reset();

    bool operator==(const CRenderVideoSettings &rhs) const;
    bool operator!=(const CRenderVideoSettings &rhs) const { return !(*this == rhs); }
    bool operator<(const CRenderVideoSettings &rhs) const;
    bool operator>(const CRenderVideoSettings &rhs) const { return !(*this == rhs || *this < rhs); }

    /*!
     * \brief Get a string representation of the video filter parameters
     */
    std::string GetVideoFilter() const;
    void SetVideoFilter(const std::string &videoFilter);

    SCALINGMETHOD GetScalingMethod() const { return m_scalingMethod; }
    void SetScalingMethod(SCALINGMETHOD method) { m_scalingMethod = method; }

    VIEWMODE GetRenderViewMode() const { return m_viewMode; }
    void SetRenderViewMode(VIEWMODE mode) { m_viewMode = mode; }

    unsigned int GetRenderRotation() const { return m_rotationDegCCW; }
    void SetRenderRotation(unsigned int rotationDegCCW) { m_rotationDegCCW = rotationDegCCW; }

  private:
    SCALINGMETHOD m_scalingMethod;
    VIEWMODE m_viewMode;
    unsigned int m_rotationDegCCW;
  };
}
}
