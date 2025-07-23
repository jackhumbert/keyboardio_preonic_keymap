#pragma once

#include "Kaleidoscope-Ranges.h"               // for KEYCLICK_TOGGLE
#include "kaleidoscope/KeyEvent.h"             // for KeyEvent
#include "kaleidoscope/Runtime.h"              // for Runtime
#include "kaleidoscope/event_handler_result.h" // for EventHandlerResult
#include "kaleidoscope/key_defs.h"             // for Key
#include "kaleidoscope/plugin.h"               // for Plugin
#include <stdint.h>                            // for uint8_t, uint16_t

namespace kaleidoscope {
namespace plugin {

// When activated, this plugin will use a custom layer to override an otherwise
// normal shift key
class Shifter : public Plugin {

public:
  EventHandlerResult onKeyEvent(KeyEvent &event);

  void enable(KeyEvent &event) {
    active = true;
    Layer.insert(1, layer);
  }

  void disable(KeyEvent &event) {
    active = false;
    Layer.deactivate(layer);
  }
  uint8_t layer{0};

private:
  bool active{false};
};
} // namespace plugin
} // namespace kaleidoscope

extern kaleidoscope::plugin::Shifter Shifter;