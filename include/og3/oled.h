// Copyright (c) 2026 Chris Lee and contibuters.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#pragma once

#ifndef NATIVE
#include <SSD1306Wire.h>
#include <Wire.h>
#endif

#include <og3/module.h>

namespace og3 {

/**
 * @brief Base class for controlling an SSD1306 OLED display via I2C.
 *
 * This module wraps the SSD1306Wire library and provides basic drawing
 * and font management integration with the og3 Module system.
 */
class Oled : public Module {
 public:
  /** @brief Supported font sizes. */
  enum FontSize {
    kTenPt = 0,      ///< 10pt font (Plain MT 10)
    kSixteenPt = 1,  ///< 16pt font (Plain MT 16)
  };

  /** @brief Screen orientation modes. */
  enum class Orientation {
    kDefault = 0,       ///< Standard orientation.
    kFlipVertical = 1,  ///< Upside down (often needed for certain board layouts).
  };

  /**
   * @brief Constructs an Oled module.
   * @param name Unique module name.
   * @param updater The ModuleSystem to register with.
   * @param initial_txt Text to display immediately after initialization.
   * @param font_size Starting font size.
   * @param orientation Starting orientation.
   */
  Oled(const char* name, ModuleSystem* updater, const char* initial_txt,
       FontSize font_size = kSixteenPt, Orientation orientation = Orientation::kFlipVertical);

  /** @brief Initializes the hardware. Called automatically by the Module system. */
  void setup();

  /** @brief Clears the screen and immediately updates the display. */
  void clear();

  /**
   * @brief Displays a message on the screen.
   * @param msg The C-string to display.
   */
  void display(const char* msg);

  /** @brief Updates the font size for subsequent drawing calls. */
  void setFontSize(FontSize font_size) { m_font_size = font_size; }

#ifndef NATIVE
  /** @return Reference to the underlying SSD1306Wire driver object. */
  SSD1306Wire& screen() { return m_display; }
#endif

 private:
  void _sendFontSize(bool force = false);
#ifndef NATIVE
  SSD1306Wire m_display;
#endif
  const char* m_initial_txt;
  const Orientation m_orientation;
  FontSize m_font_size;
  FontSize m_sent_font_size;
  int m_start = 0;
  bool m_ok = false;
};

}  // namespace og3
