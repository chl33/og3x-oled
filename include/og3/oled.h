// Copyright (c) 2024 Chris Lee and contibuters.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#pragma once

#ifndef NATIVE
#include <SSD1306Wire.h>
#include <Wire.h>
#endif

#include <og3/module.h>

namespace og3 {

class Oled : public Module {
 public:
  enum FontSize {
    kTenPt = 0,
    kSixteenPt = 1,
  };
  enum class Orientation {
    kDefault = 0,
    kFlipVertical = 1,
  };

  Oled(const char* name, ModuleSystem* updater, const char* initial_txt,
       FontSize font_size = kSixteenPt, Orientation orientation = Orientation::kFlipVertical);

  void setup();
  void clear();
  void display(const char* msg);
  void setFontSize(FontSize font_size) { m_font_size = font_size; }

  SSD1306Wire& screen() { return m_display; }

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
