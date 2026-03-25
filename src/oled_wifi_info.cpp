// Copyright (c) 2026 Chris Lee and contributors.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include "og3/oled_wifi_info.h"

#include <og3/wifi_manager.h>

#include "og3/oled_display_ring.h"

namespace og3 {

const char OledWifiInfo::kName[] = "oled-wifi";

OledWifiInfo::OledWifiInfo(Tasks* tasks) : Module(OledWifiInfo::kName, tasks->module_system()) {
  require(OledDisplayRing::kName, &m_oled);
  require(WifiManager::kName, &m_wifi);
  add_init_fn([this]() {
    if (m_oled && m_wifi) {
      m_oled->addDisplayFn([this]() {
        static char s_buf[80];
        if (m_wifi->apMode()) {
          static bool s_show_password = false;
          if (s_show_password && m_wifi->apPassword()) {
            snprintf(s_buf, sizeof(s_buf), "PW: %s", m_wifi->apPassword());
          } else {
            snprintf(s_buf, sizeof(s_buf), "AP: %s", m_wifi->board().c_str());
          }
          m_oled->display(s_buf);
          s_show_password = !s_show_password;
        } else if (m_wifi->wasConnected()) {
          snprintf(s_buf, sizeof(s_buf), "IP: %s", m_wifi->ipAddr().c_str());
          m_oled->display(s_buf);
        } else {
          m_oled->display("WiFi is off");
        }
      });
    }
  });
}

}  // namespace og3
