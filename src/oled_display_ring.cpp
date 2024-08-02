// Copyright (c) 2024 Chris Lee and contibuters.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include "og3/oled_display_ring.h"

namespace og3 {

const char* OledDisplayRing::kName = "oled_ring";

OledDisplayRing::OledDisplayRing(ModuleSystem* modules, const char* initial_txt,
                                 unsigned switch_time_msec, FontSize font_size,
                                 Orientation orientation)
    : Oled(kName, modules, initial_txt, font_size, orientation),
      m_switch_time_msec(switch_time_msec),
      m_scheduler(
          1, m_switch_time_msec, [this]() { timerCallback(); }, nullptr) {
  add_link_fn([this](const NameToModule& name_to_module) -> bool {
    m_scheduler.setTasks(Tasks::get(name_to_module));
    return true;
  });
}

void OledDisplayRing::addDisplayFn(const CallbackFn& fn) { m_callbacks.push_back(fn); }

void OledDisplayRing::timerCallback() {
  if (m_callbacks.empty()) {
    return;
  }
  m_callbacks[m_callback_index]();
  m_callback_index = (m_callback_index + 1) % m_callbacks.size();
}

}  // namespace og3
