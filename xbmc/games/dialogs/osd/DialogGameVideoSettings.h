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

#include "settings/dialogs/GUIDialogSettingsManualBase.h"

namespace KODI
{
namespace GAME
{
  class CDialogGameVideoSettings : public CGUIDialogSettingsManualBase
  {
  public:
    CDialogGameVideoSettings();
    virtual ~CDialogGameVideoSettings() = default;

    // implementation of CGUIControl via CGUIDialogSlider
    virtual bool OnAction(const CAction &action) override;

  protected:
    // implementation of ISettingCallback via CGUIDialogSettingsManualBase
    virtual void OnSettingChanged(std::shared_ptr<const CSetting> setting) override;
    virtual void OnSettingAction(std::shared_ptr<const CSetting> setting) override;

    // specialization of CGUIDialogSettingsBase via CGUIDialogSettingsManualBase
    virtual bool AllowResettingSettings() const override { return false; }
    virtual void Save() override;
    virtual void SetupView() override;

    // specialization of CGUIDialogSettingsManualBase
    virtual void InitializeSettings() override;
  };
}
}
