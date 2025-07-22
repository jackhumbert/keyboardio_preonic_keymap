/* keyboardio_preonic_keymap -- Jack's personal keymap for the Preonic
 * Copyright 2018-2025 Keyboard.io, inc.
 *                2025 Jack Humbert
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
#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"

#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
// #include "Kaleidoscope-OneShot.h"
// #include "Kaleidoscope-Qukeys.h"
// #include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Keyclick.h"
#include "Kaleidoscope-MagicCombo.h"

#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-PreonicColormap.h"


// Support for setting and saving the default LED mode
#include "Kaleidoscope-DefaultLEDModeConfig.h"

// Support for changing the brightness of the LEDs
#include "Kaleidoscope-LEDBrightnessConfig.h"

// Support for showing device status with the LED Indicators
#include "Kaleidoscope-LEDIndicators.h"

#include "helpers.h"

/** This 'enum' is a list of all the macros used by the firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum {
  MACRO_SHIFT,
  MACRO_BOOTLOADER,
  MACRO_VERSION_INFO,
  MACRO_ANY,
  MACRO_TOGGLE_MODE,
  MACRO_BT_SELECT_1,  // Select slot 1
  MACRO_BT_SELECT_2,  // Select slot 2
  MACRO_BT_SELECT_3,  // Select slot 3
  MACRO_BT_SELECT_4,  // Select slot 4
  MACRO_BT_PAIR,      // Start pairing for selected slot
  MACRO_BT_OFF,
  MACRO_BATTERY_LEVEL  // Report current battery level
};

// Define our magic combo
enum {
  COMBO_ENTER_TEST_MODE
};

// Configure the magic combo
USE_MAGIC_COMBOS(
  [COMBO_ENTER_TEST_MODE] = {
    .action = [](uint8_t combo_index) {
      //  PreonicHardwareTestMode.enterTestMode();
    },
    .keys = {
      R1C0,  // `
      R5C0,  // Hyper
      R5C11  // Right arrow
    }});

enum {
  BASE,
  SSHIFT,
  LOWER,
  RAISE,
  NAV,
  FUN
};

// clang-format off
KEYMAPS(
  [BASE] = KEYMAP(
    Consumer_VolumeDecrement, Consumer_VolumeIncrement, 
    M(MACRO_ANY), ShiftToLayer(FUN), Consumer_PlaySlashPause,

    Key_Bt, Key_1,  Key_2,  Key_3,  Key_4,  Key_5,  Key_6,  Key_7,  Key_8,  Key_9,  Key_0,  Key_Mn,
    Key_Tab,Key_Q,  Key_W,  Key_F,  Key_P,  Key_G,  Key_J,  Key_L,  Key_U,  Key_Y,  Key_Sc, Key_Bp,
    Key_Mn, Key_A,  Key_R,  Key_S,  Key_T,  Key_D,  Key_H,  Key_N,  Key_E,  Key_I,  Key_O,  Key_Qu,
    Key_Es, Key_Z,  Key_X,  Key_C,  Key_V,  Key_B,  Key_K,  Key_M,  Key_Cm, Key_Pr, Key_Sl, Key_Enter,
    Key_RS, Key_LG, Key_LA, Key_LC, ShiftToLayer(LOWER),  
                                            M(MACRO_SHIFT), 
                                                    Key_Sp, ShiftToLayer(RAISE),       
                                                                    ShiftToLayer(NAV), XXX, XXX, XXX
  ),

  [SSHIFT] = KEYMAP(
    ___, ___, 
    ___, ___, ___,

    SH(Bt), SH(1),  SH(2),  SH(3),  SH(4),  SH(5),  SH(6),  SH(7),  SH(8),  SH(9),  SH(0),  SH(Mn),
    SH(Tab),SH(Q),  SH(W),  SH(F),  SH(P),  SH(G),  SH(J),  SH(L),  SH(U),  SH(Y),  SH(Sc), SH(Bp),
    SH(Mn), SH(A),  SH(R),  SH(S),  SH(T),  SH(D),  SH(H),  SH(N),  SH(E),  SH(I),  SH(O),  Key_Bt,
    SH(Es), SH(Z),  SH(X),  SH(C),  SH(V),  SH(B),  SH(K),  SH(M),  SH(1),  SH(2),  SH(Sl), SH(Enter),
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______
  ),

  [LOWER] = KEYMAP(
    ___, ___, 
    ___, ___, ___,

    // ______, ______, Key_A,  Key_B,  Key_C,  ______, ______, ______, ______, ______, ______, ______,
    // Key_Bp, ______, Key_7,  Key_8,  Key_9,  ______, ______, Key_F9, Key_F10,Key_F11,Key_F12,______,
    // Key_De, ______, Key_4,  Key_5,  Key_6,  ______, ______, Key_F5, Key_F6, Key_F7, Key_F8, ______,
    // ______, Key_0,  Key_1,  Key_2,  Key_3,  ______, ______, Key_F1, Key_F2, Key_F3, Key_F4, ______,
    ______, Key_C,  Key_D,  Key_E,  Key_F,  ______, ______, Key_F13,Key_F14,Key_F15,Key_F16,______,
    Key_Bp, Key_8,  Key_9,  Key_A,  Key_B,  ______, ______, Key_F9, Key_F10,Key_F11,Key_F12,______,
    Key_De, Key_4,  Key_5,  Key_6,  Key_7,  ______, ______, Key_F5, Key_F6, Key_F7, Key_F8, ______,
    ______, Key_0,  Key_1,  Key_2,  Key_3,  ______, ______, Key_F1, Key_F2, Key_F3, Key_F4, ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______
  ),

  [RAISE] = KEYMAP(
    ___, ___, 
    ___, ___, ___,

    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
    ______, ______, SH(Cm), SH(4),  SH(Pr), ______, ______, Key_Lb, SH(Mn), Key_Rb, ______, ______,
    ______, Key_Bl, SH(9),  SH(Qu), SH(0),  SH(3),  SH(5),  SH(Lb), Key_Eq, SH(Rb), SH(Bl), ______,
    ______, ______, SH(Sc), SH(8),  SH(Eq), ______, ______, SH(7),  SH(6),  SH(Bt), ______, ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______
  ),

  [NAV] = KEYMAP(
    ___, ___, 
    ___, ___, ___,

    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
    ______, ______, ______, ______, ______, ______, ______, Key_Hm, Key_Pd, Key_Pu, Key_En, ______,
    ______, ______, ______, ______, ______, ______, ______, Key_Lf, Key_Dn, Key_Up, Key_Rt, ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______
  ),

  [FUN] = KEYMAP(
    ___, ___, 
    ___, ___, M(MACRO_BOOTLOADER),
    
    Key_BLEOff, Key_BLESelectDevice1, Key_BLESelectDevice2, Key_BLESelectDevice3, Key_BLESelectDevice4, Key_BLEStartPairing, ___, ___, ___, ___, ___, M(MACRO_VERSION_INFO),
    Key_LEDEffectNext,___,Consumer_VolumeIncrement,___, ___,  ___,  ___,  ___,  ___,  ___,  ___,  ___,
    ___, Consumer_ScanPreviousTrack,Consumer_VolumeDecrement,Consumer_ScanNextTrack,___,  ___,  ___,  ___,  ___,  ___,  ___,  ___,
    Key_ToggleKeyclick,___,  Consumer_Mute,   ___,         ___,  ___,  ___,  ___,  ___,  ___,  ___,  ___,
    M(MACRO_BATTERY_LEVEL), ___,        ___,  ___,         ___,  ___,  ___,  ___,  ___,  ___,  ___,   ___
  )
);


// Colors names of the EGA palette, for convenient use in colormaps. Should
// match the palette definition below. Optional, one can just use the indexes
// directly, too.
enum {
  BLACK,
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  LIGHT_GRAY,
  DARK_GRAY,
  BRIGHT_BLUE,
  BRIGHT_GREEN,
  BRIGHT_CYAN,
  BRIGHT_RED,
  BRIGHT_MAGENTA,
  YELLOW,
  WHITE
};

// Define an EGA palette. Conveniently, that's exactly 16 colors, just like the
// limit of LEDPaletteTheme.
PALETTE(
    CRGB(0x00, 0x00, 0x00),  // [0x0] black
    CRGB(0x00, 0x00, 0xaa),  // [0x1] blue
    CRGB(0x00, 0xaa, 0x00),  // [0x2] green
    CRGB(0x00, 0xaa, 0xaa),  // [0x3] cyan
    CRGB(0xaa, 0x00, 0x00),  // [0x4] red
    CRGB(0xaa, 0x00, 0xaa),  // [0x5] magenta
    CRGB(0xaa, 0x55, 0x00),  // [0x6] brown
    CRGB(0xaa, 0xaa, 0xaa),  // [0x7] light gray
    CRGB(0x55, 0x55, 0x55),  // [0x8] dark gray
    CRGB(0x55, 0x55, 0xff),  // [0x9] bright blue
    CRGB(0x55, 0xff, 0x55),  // [0xa] bright green
    CRGB(0x55, 0xff, 0xff),  // [0xb] bright cyan
    CRGB(0xff, 0x55, 0x55),  // [0xc] bright red
    CRGB(0xff, 0x55, 0xff),  // [0xd] bright magenta
    CRGB(0xff, 0xff, 0x55),  // [0xe] yellow
    CRGB(0xff, 0xff, 0xff)   // [0xf] white
)

COLORMAPS(
    [0] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [1] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [2] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [3] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [4] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [5] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [6] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [7] = COLORMAP (BLACK,  BLACK, BLACK, BLACK),
    [8] = COLORMAP (BLACK,  BLACK, BLACK, BLACK)  
)

namespace kaleidoscope {
namespace plugin {


// When activated, this plugin will suppress any `Shift` key (including modifier
// combos with `Shift`) before it's added to the HID report.
class Shifter : public Plugin {

 public:
  // EventHandlerResult onAddToReport(Key key) {
  //   if (active_)
  //     key.setFlags(SHIFT_HELD);
  //   return EventHandlerResult::OK;
  // }

  EventHandlerResult onKeyEvent(KeyEvent &event) {
    if ((event.state & INJECTED) != 0)
      return EventHandlerResult::OK;

    if (active) {
      if ((keyToggledOn(event.state) && event.key.isKeyboardShift()) || keyToggledOff(event.state) && !event.key.isKeyboardShift() && !shifted) {
        KeyEvent new_event = KeyEvent(KeyAddr::none(), INJECTED | IS_PRESSED, Key_LeftShift);
        Runtime.handleKeyEvent(new_event);
        shifted = true;
      } else if ((keyToggledOn(event.state) && !event.key.isKeyboardShift()) || keyToggledOff(event.state) && !event.key.isKeyboardShift() && shifted) {
        KeyEvent new_event = KeyEvent(KeyAddr::none(), INJECTED | WAS_PRESSED, Key_LeftShift);
        Runtime.handleKeyEvent(new_event);
        shifted = false;
      }
    }
    if (!active && shifted)  {
      KeyEvent new_event = KeyEvent(KeyAddr::none(), INJECTED | WAS_PRESSED, Key_LeftShift);
      Runtime.handleKeyEvent(new_event);
      shifted = false;
    }
    return EventHandlerResult::OK;
  }

  void enable(KeyEvent &event) {
    active = true;
    // event.key.setKeyCode(Key_LS.getKeyCode());
    // event.key.setFlags(0);
    // event.state |= INJECTED;
    // shifted = true;
    Layer.move(SSHIFT);
  }

  void disable(KeyEvent &event) {
    active = false;
    // event.key.setKeyCode(Key_LS.getKeyCode());
    // event.key.setFlags(0);
    // event.state |= INJECTED;
    // shifted = false;
    Layer.move(BASE);
  }

 private:
  bool active {false};
  bool shifted {false};
};
}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::Shifter Shifter;

// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  // Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  // SpaceCadet,
  // SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  // OneShot,
  // OneShotConfig,
  // EscapeOneShot,
  // EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the same time.
  MagicCombo,

  // LEDControl provides support for other LED modes
  LEDControl,

  // Enables setting, saving (via Chrysalis), and restoring (on boot) the
  // default LED mode.
  DefaultLEDModeConfig,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  PreonicColormapEffect,
  DefaultPreonicColormap,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  // HostPowerManagement,

  LEDBrightnessConfig,
  LEDRainbowEffect,

  // The Keyclick plugin for audible feedback
  Keyclick,
  // LEDIndicators shows device status indicators using the LEDs
  // It should be listed after all other LED plugins
  LEDIndicators,
  Shifter
);

void configureIndicators() {
  // Configure LED mapping to use our four LEDs
  static const KeyAddr indicator_leds[] = {
    KeyAddr(0, 0),
    KeyAddr(0, 1),
    KeyAddr(0, 2),
    KeyAddr(0, 3)};
  LEDIndicators.setSlots(4, indicator_leds);
}

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Preonic - Firmware version "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
    event.key.setFlags(0);
  }
}

// Helper function to report battery level
static void batteryLevelMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    // Get the battery level
    uint8_t battery_level = kaleidoscope::Runtime.device().batteryGauge().getBatteryLevel();

    // Report battery level with a message
    Macros.type(PSTR("Battery Status:\n"));

    // Battery percentage
    char percentage[5];
    snprintf(percentage, sizeof(percentage), "%d%%", battery_level);
    Macros.type(PSTR("Level: "));
    Macros.type(percentage);
    Macros.type(PSTR("\n"));

    // Raw battery level
    char raw_level[5];
    snprintf(raw_level, sizeof(raw_level), "%d", kaleidoscope::Runtime.device().batteryGauge().getRawBatteryLevel());
    Macros.type(PSTR("Raw Level: "));
    Macros.type(raw_level);
    Macros.type(PSTR("\n"));

    // Battery voltage
    char voltage[8];
    snprintf(voltage, sizeof(voltage), "%.2fV", kaleidoscope::Runtime.device().batteryGauge().getVoltage() / 1000.0f);
    Macros.type(PSTR("Voltage: "));
    Macros.type(voltage);
    Macros.type(PSTR("\n"));

    // Charge rate
    int16_t charge_rate = kaleidoscope::Runtime.device().batteryGauge().getChargeRate();
    char rate[8];
    snprintf(rate, sizeof(rate), "%.2f%%/hr", charge_rate * 0.208f);
    Macros.type(PSTR("Charge Rate: "));
    Macros.type(rate);
    Macros.type(PSTR("\n"));

    // Charging status
    Macros.type(PSTR("Power Source: "));
    if (kaleidoscope::Runtime.device().batteryCharger().hasPower()) {
      Macros.type(PSTR("Connected\n"));

      Macros.type(PSTR("Charging Status: "));
      uint8_t charging_state = kaleidoscope::Runtime.device().batteryCharger().getChargingState();

      // Using defined enum values from BQ24075
      typedef kaleidoscope::driver::battery_charger::BQ24075<kaleidoscope::device::keyboardio::PreonicBatteryChargerProps> BQ24075;

      switch (charging_state) {
      case BQ24075::CHARGING:
        Macros.type(PSTR("Charging\n"));
        break;
      case BQ24075::CHARGE_COMPLETE:
        Macros.type(PSTR("Charge Complete\n"));
        break;
      case BQ24075::CHARGE_FAULT:
        Macros.type(PSTR("Fault Detected\n"));
        break;
      case BQ24075::NO_BATTERY:
        Macros.type(PSTR("No Battery\n"));
        break;
      case BQ24075::BATTERY_DISCONNECTED:
        Macros.type(PSTR("Battery Disconnected\n"));
        break;
      default:
        Macros.type(PSTR("Not Charging\n"));
        break;
      }

      // No need to print static configuration values in the status report
    } else {
      Macros.type(PSTR("Battery\n"));
    }

    // Alert status
    Macros.type(PSTR("Alerts: "));
    if (kaleidoscope::Runtime.device().batteryGauge().hasLowBatteryAlert()) {
      Macros.type(PSTR("Low Battery "));
    }
    if (kaleidoscope::Runtime.device().batteryGauge().hasChangeAlert()) {
      Macros.type(PSTR("Level Changed "));
    }
    if (kaleidoscope::Runtime.device().batteryGauge().hasLowVoltageAlert()) {
      Macros.type(PSTR("Low Voltage "));
    }
    if (kaleidoscope::Runtime.device().batteryGauge().hasHighVoltageAlert()) {
      Macros.type(PSTR("High Voltage "));
    }
    if (!kaleidoscope::Runtime.device().batteryGauge().hasLowBatteryAlert() &&
        !kaleidoscope::Runtime.device().batteryGauge().hasChangeAlert() &&
        !kaleidoscope::Runtime.device().batteryGauge().hasLowVoltageAlert() &&
        !kaleidoscope::Runtime.device().batteryGauge().hasHighVoltageAlert()) {
      Macros.type(PSTR("None"));
    }
    Macros.type(PSTR("\n"));

    // Hibernate status
    if (kaleidoscope::Runtime.device().batteryGauge().isHibernating()) {
      Macros.type(PSTR("Status: Hibernating\n"));
    } else {
      Macros.type(PSTR("Status: Active\n"));
    }

    // Firmware version
    char version[6];
    snprintf(version, sizeof(version), "0x%04X", kaleidoscope::Runtime.device().batteryGauge().getVersion());
    Macros.type(PSTR("Gauge IC: "));
    Macros.type(version);
    Macros.type(PSTR("\n"));
  }
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {
  case MACRO_SHIFT: {
    if (keyToggledOn(event.state)) {
      Shifter.enable(event);
    } else if (keyToggledOff(event.state)) {
      Shifter.disable(event);
    }
  } break;
  case MACRO_BOOTLOADER: {
    NVIC_SystemReset();
  } break;
  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;
  case MACRO_ANY:
    anyKeyMacro(event);
    break;
  case MACRO_TOGGLE_MODE:
    if (keyToggledOn(event.state)) {
      kaleidoscope::Runtime.device().toggleHostConnectionMode();
    }
    break;
  case MACRO_BT_SELECT_1:
    if (keyToggledOn(event.state)) {
      kaleidoscope::Runtime.device().ble().selectDevice(1);
      kaleidoscope::Runtime.device().setHostConnectionMode(MODE_BLE);
    }
    break;
  case MACRO_BT_SELECT_2:
    if (keyToggledOn(event.state)) {
      kaleidoscope::Runtime.device().ble().selectDevice(2);
      kaleidoscope::Runtime.device().setHostConnectionMode(MODE_BLE);
    }
    break;
  case MACRO_BT_SELECT_3:
    if (keyToggledOn(event.state)) {
      kaleidoscope::Runtime.device().ble().selectDevice(3);
      kaleidoscope::Runtime.device().setHostConnectionMode(MODE_BLE);
    }
    break;
  case MACRO_BT_SELECT_4:
    if (keyToggledOn(event.state)) {
      kaleidoscope::Runtime.device().ble().selectDevice(4);
      kaleidoscope::Runtime.device().setHostConnectionMode(MODE_BLE);
    }
    break;
  case MACRO_BT_PAIR:
    if (keyToggledOn(event.state)) {
      kaleidoscope::Runtime.device().ble().startDiscoverableAdvertising();
    }
    break;
  case MACRO_BT_OFF:
    if (keyToggledOn(event.state)) {
      kaleidoscope::Runtime.device().ble().stopAdvertising();
      kaleidoscope::Runtime.device().ble().disconnect();
      kaleidoscope::Runtime.device().setHostConnectionMode(MODE_USB);
    }
    break;
  case MACRO_BATTERY_LEVEL:
    batteryLevelMacro(event.state);
    break;
  }
  return MACRO_NONE;
}


void setup() {
  Kaleidoscope.setup();
  // kaleidoscope::Runtime.device().speaker().playTone(440, 400);
  // kaleidoscope::Runtime.device().speaker().playTone(880, 200);
  configureIndicators();

  PreonicColormapEffect.max_layers(9);
  LEDRainbowEffect.brightness(25);

  // Disable Keyclick by default
  Keyclick.disable();

  //  DefaultLEDModeConfig.activateLEDModeIfUnconfigured(&LEDRainbowEffect);

  DefaultLEDModeConfig.activateLEDModeIfUnconfigured(&LEDOff);

  // kaleidoscope::Runtime.device().speaker().playTune(
  //   {440, 880,  440,  880}, 
  //   {50,  50,   200,  50}
  // );

  //kaleidoscope::Runtime.device().ble().selectDevice(1);
  //kaleidoscope::Runtime.device().setHostConnectionMode(MODE_BLE);
}

void loop() {
  Kaleidoscope.loop();
}
