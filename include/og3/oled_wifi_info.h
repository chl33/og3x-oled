// Copyright (c) 2026 Chris Lee and contributors.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#pragma once

#include <og3/compiler_definitions.h>
#include <og3/dependencies.h>
#include <og3/ha_dependencies.h>
#include <og3/wifi_manager.h>

#include <functional>

#include "og3/oled_display_ring.h"

namespace og3 {

/**
 * @brief A module that automatically adds WiFi status info to an OledDisplayRing.
 *
 * OledWifiInfo monitors the WiFi state and registers a callback with the
 * OledDisplayRing to display the current IP address or AP mode credentials.
 */
class OledWifiInfo : public Module {
 public:
  static const char kName[];  ///< @brief "oled-wifi"

  /** @brief Constructs an OledWifiInfo module. */
  explicit OledWifiInfo(Tasks* tasks);

 private:
  HADependenciesArray<2> m_dependencies{{WifiManager::kName, OledDisplayRing::kName}};
  WifiManager* m_wifi = nullptr;
  OledDisplayRing* m_oled = nullptr;
};

}  // namespace og3
