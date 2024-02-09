// Copyright (c) 2024 Chris Lee and contibuters.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#pragma once

#include <og3/compiler_definitions.h>
#include <og3/dependencies.h>
#include <og3/wifi_manager.h>

#include <functional>

#include "og3/oled_display_ring.h"

namespace og3 {

class OledWifiInfo : public Module {
 public:
  static const char kName[];

  explicit OledWifiInfo(Tasks* tasks) RT3_NONNULL();

 private:
  DependenciesArray<2> m_dependencies{{WifiManager::kName, OledDisplayRing::kName}};
  WifiManager* m_wifi = nullptr;
  OledDisplayRing* m_oled = nullptr;
};

}  // namespace og3
