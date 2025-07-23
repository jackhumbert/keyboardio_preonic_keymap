/* Kaleidoscope-Shifter
 * Copyright 2025 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * Additional Permissions:
 * As an additional permission under Section 7 of the GNU General Public
 * License Version 3, you may link this software against a Vendor-provided
 * Hardware Specific Software Module under the terms of the MCU Vendor
 * Firmware Library Additional Permission Version 1.0.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "kaleidoscope/plugin/Shifter.h"

namespace kaleidoscope {
namespace plugin {

EventHandlerResult Shifter::onKeyEvent(KeyEvent &event) {
  if ((event.state & INJECTED) != 0)
    return EventHandlerResult::OK;

  if (active) {
    if ((event.key != Layer.getKeyFromPROGMEM(layer, event.addr)) &&
        event.key.isKeyboardKey()) {
      Key key = event.key;
      key.setFlags(key.getFlags() | SHIFT_HELD);

      KeyEvent new_event = KeyEvent(event.addr, INJECTED | event.state, key);
      Runtime.handleKeyEvent(new_event);
      return EventHandlerResult::EVENT_CONSUMED;
    }
  }
  return EventHandlerResult::OK;
}

} // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::Shifter Shifter;