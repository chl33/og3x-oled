// Copyright (c) 2024 Chris Lee and contibuters.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include "og3/oled.h"

namespace og3 {

Oled::Oled(const char* name, ModuleSystem* modules, const char* initial_txt,
           Oled::FontSize font_size, Oled::Orientation orientation)
    : Module(name, modules),
#ifndef NATIVE
      m_display(0x3c, SDA, SCL, GEOMETRY_128_32),
#endif
      m_initial_txt(initial_txt),
      m_orientation(orientation),
      m_font_size(font_size),
      m_sent_font_size(font_size) {
  add_init_fn([this]() { setup(); });
}

void Oled::_sendFontSize(bool force) {
#ifndef NATIVE
  if (!force && (m_font_size == m_sent_font_size)) {
    return;
  }
  switch (m_font_size) {
    case kTenPt:
      m_display.setFont(ArialMT_Plain_10);
      break;
    case kSixteenPt:
      m_display.setFont(ArialMT_Plain_16);
      break;
  }
  m_sent_font_size = m_font_size;
#endif
}

void Oled::setup() {
#ifndef NATIVE
  m_ok = m_display.init();
#else
  m_ok = true;
#endif
  if (!m_ok) {
    return;
  }
#ifndef NATIVE
  m_display.clear();
  if (m_orientation == Orientation::kFlipVertical) {
    m_display.flipScreenVertically();
  }
  m_display.setTextAlignment(TEXT_ALIGN_LEFT);
  _sendFontSize(true);
  m_display.drawString(0, 0, m_initial_txt);
  m_display.display();
#endif
  m_start = 1;
}

void Oled::clear() {
  if (!m_ok) {
    return;
  }
#ifndef NATIVE
  m_display.clear();
  m_display.display();
#endif
}

void Oled::display(const char* msg) {
  if (!m_ok) {
    return;
  }
#ifndef NATIVE
  m_display.clear();
  _sendFontSize();
  m_display.drawString(0, 0, msg);
  m_display.display();
#endif
}

}  // namespace og3
