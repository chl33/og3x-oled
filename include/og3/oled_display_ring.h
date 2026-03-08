// Copyright (c) 2026 Chris Lee and contributors.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#pragma once

#include <og3/tasks.h>

#include <functional>
#include <vector>

#include "og3/oled.h"

namespace og3 {

/**
 * @brief An OLED controller that cycles through multiple display functions.
 *
 * OledDisplayRing allows multiple modules to register display callbacks.
 * It periodically rotates through these callbacks, showing each one's output
 * for a fixed amount of time.
 */
class OledDisplayRing : public Oled {
 public:
  static const char* kName;  ///< @brief "oled_ring"

  /**
   * @brief Constructs an OledDisplayRing.
   * @param updater The ModuleSystem to register with.
   * @param initial_txt Default text shown if no callbacks are registered.
   * @param switch_time_msec Time in milliseconds to show each registered page.
   * @param font_size Default font size.
   * @param orientation Screen orientation.
   */
  OledDisplayRing(ModuleSystem* updater, const char* initial_txt, unsigned switch_time_msec,
                  FontSize font_size = kSixteenPt,
                  Orientation orientation = Orientation::kFlipVertical);

  /** @brief Type for display update callbacks. */
  using CallbackFn = std::function<void()>;

  /**
   * @brief Registers a function to be called when its turn comes in the ring.
   * @param fn The callback function which should call display() or similar.
   */
  void addDisplayFn(const CallbackFn& fn);

  /** @return Pointer to the OledDisplayRing module instance. */
  static OledDisplayRing* get(const NameToModule& n2m) {
    return GetModule<OledDisplayRing>(n2m, kName);
  }

 private:
  /** @brief Internal callback for the periodic timer. */
  void timerCallback();

  std::vector<CallbackFn> m_callbacks;
  const unsigned m_switch_time_msec;
  unsigned m_callback_index = 0;
  PeriodicTaskScheduler m_scheduler;
};

}  // namespace og3
