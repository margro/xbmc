#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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

#include "utils/StdString.h"

class CFileItem;
class CURL;

namespace PLAYLIST
{
  class CPlayList;

  class CPlayListFactory
  {
  public:
    static CPlayList* Create(const CStdString& filename);
    static CPlayList* Create(const CFileItem& item);
    static bool IsPlaylist(const CURL& url);
    static bool IsPlaylist(const CStdString& filename);
    static bool IsPlaylist(const CFileItem& item);
  };
}
