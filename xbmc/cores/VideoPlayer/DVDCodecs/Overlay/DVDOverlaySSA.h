#pragma once

/*
 *      Copyright (C) 2005-2013 Team XBMC
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "system.h" // for SAFE_RELEASE
#include "DVDOverlay.h"
#include "../../DVDSubtitles/DVDSubtitlesLibass.h"

class CDVDOverlaySSA : public CDVDOverlay
{
public:

  CDVDSubtitlesLibass* m_libass;

  explicit CDVDOverlaySSA(CDVDSubtitlesLibass* libass) : CDVDOverlay(DVDOVERLAY_TYPE_SSA)
  {
    replace = true;
    m_libass = libass;
    libass->Acquire();
  }

  CDVDOverlaySSA(CDVDOverlaySSA& src)
    : CDVDOverlay(src)
    , m_libass(src.m_libass)
  {
    m_libass->Acquire();
  }

  ~CDVDOverlaySSA() override
  {
    if(m_libass)
      SAFE_RELEASE(m_libass);
  }

  CDVDOverlaySSA* Clone() override
  {
    return new CDVDOverlaySSA(*this);
  }
};
