// Copyright (c) 2024 Chris Lee and contibuters.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include "og3/oled_wifi_info.h"

#include <og3/wifi_manager.h>

#include "og3/oled_display_ring.h"

namespace og3 {

const char OledWifiInfo::kName[] = "oled-wifi";

OledWifiInfo::OledWifiInfo(Tasks* tasks) : Module(OledWifiInfo::kName, tasks->module_system()) {
  setDependencies(&m_dependencies);
  add_link_fn([this](og3::NameToModule& name_to_module) -> bool {
    m_oled = OledDisplayRing::get(name_to_module);
    m_wifi = WifiManager::get(name_to_module);
    return m_oled && m_wifi;
  });
  add_init_fn([this]() {
    if (m_oled && m_wifi) {
      m_oled->addDisplayFn([this]() {
        if (m_wifi->apMode()) {
          m_oled->display("AP mode");
        } else if (m_wifi->wasConnected()) {
          char buf[80];
          snprintf(buf, sizeof(buf), "IP: %s", m_wifi->ipAddress().c_str());
          m_oled->display(buf);
        } else {
          m_oled->display("WiFi is off");
        }
      });
    }
  });
}

}  // namespace og3
