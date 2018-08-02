 /*
 *  Copyright (C) 2012-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "SavestateDatabase.h"
#include "Savestate.h"
#include "SavestateDefines.h"
#include "SavestateUtils.h"
#include "ServiceBroker.h"
#include "addons/AddonManager.h"
#include "games/GameTypes.h"
#include "games/tags/GameInfoTag.h"
#include "utils/StringUtils.h"
#include "utils/Variant.h"
#include "FileItem.h"

using namespace KODI;
using namespace GAME;

CSavestateDatabase::CSavestateDatabase() = default;

bool CSavestateDatabase::AddSavestate(const CSavestate& save)
{
  return save.Serialize(CSavestateUtils::MakeMetadataPath(save.GamePath()));
}

bool CSavestateDatabase::GetSavestate(const std::string& path, CSavestate& save)
{
  return save.Deserialize(path);
}

bool CSavestateDatabase::GetSavestatesNav(CFileItemList& items, const std::string& gamePath, const std::string& gameClient /* = "" */)
{
  //! @todo
  return false;
}

bool CSavestateDatabase::RenameSavestate(const std::string& path, const std::string& label)
{
  //! @todo
  return false;
}

bool CSavestateDatabase::DeleteSavestate(const std::string& path)
{
  //! @todo
  return false;
}

bool CSavestateDatabase::ClearSavestatesOfGame(const std::string& gamePath, const std::string& gameClient /* = "" */)
{
  //! @todo
  return false;
}

CFileItem* CSavestateDatabase::CreateFileItem(const CVariant& object) const
{
  using namespace ADDON;

  CSavestate save;
  save.Deserialize(object);
  CFileItem* item = new CFileItem(save.Label());

  item->SetPath(save.Path());
  if (!save.Thumbnail().empty())
    item->SetArt("thumb", save.Thumbnail());
  else
  {
    AddonPtr addon;
    if (CServiceBroker::GetAddonMgr().GetAddon(save.GameClient(), addon, ADDON_GAMEDLL))
      item->SetArt("thumb", addon->Icon());
  }

  // Use the slot number as the second label
  if (save.Type() == SAVETYPE::SLOT)
    item->SetLabel2(StringUtils::Format("%u", save.Slot()));

  item->m_dateTime = save.Timestamp();
  item->SetProperty(FILEITEM_PROPERTY_SAVESTATE_DURATION, static_cast<uint64_t>(save.PlaytimeWallClock()));
  item->GetGameInfoTag()->SetGameClient(save.GameClient());
  item->m_dwSize = save.Size();
  item->m_bIsFolder = false;

  return item;
}
