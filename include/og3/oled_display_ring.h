// Copyright (c) 2024 Chris Lee and contibuters.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#pragma once

#include <og3/tasks.h>

#include <functional>
#include <vector>

#include "og3/oled.h"

namespace og3 {

// Control OLED to show one of a list of messages.
// A module can register a funciton for controlling the display.
// This module will call those in a cyclic order.
class OledDisplayRing : public Oled {
 public:
  static const char* kName;

  OledDisplayRing(ModuleSystem* updater, const char* initial_txt, unsigned switch_time_msec,
                  FontSize font_size = kSixteenPt);

  // Add the callback which will be called when it is its turn.
  using CallbackFn = std::function<void()>;
  void addDisplayFn(const CallbackFn& fn);

  static OledDisplayRing* get(const NameToModule& n2m) {
    return GetModule<OledDisplayRing>(n2m, kName);
  }

 private:
  void timerCallback();

  std::vector<CallbackFn> m_callbacks;
  const unsigned m_switch_time_msec;
  unsigned m_callback_index = 0;
  PeriodicTaskScheduler m_scheduler;
};

}  // namespace og3
