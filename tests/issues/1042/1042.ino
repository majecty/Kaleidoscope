/* -*- mode: c++ -*-
 * Kaleidoscope-Leader -- VIM-style leader keys
 * Copyright (C) 2016, 2017, 2018  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <Kaleidoscope.h>
#include <Kaleidoscope-Leader.h>
#include <Kaleidoscope-MacroSupport.h>

#include <Kaleidoscope-Ranges.h>
#include "kaleidoscope/KeyEventTracker.h"
#include "kaleidoscope/LiveKeys.h"
#include "kaleidoscope/plugin.h"

#include <Kaleidoscope-Devel-ArduinoTrace.h>

// *INDENT-OFF*
KEYMAPS(
  [0] = KEYMAP_STACKED
  (LEAD(0),      Key_1, Key_2, Key_3, Key_4, Key_5, Key_NoKey,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,

   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   LEAD(0),

   Key_skip,  Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_skip,
   Key_Enter, Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
              Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   Key_skip,  Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

   Key_RightShift, Key_RightAlt, Key_Spacebar, Key_RightControl,
   LEAD(0)),
)
// *INDENT-ON*

namespace kaleidoscope {
namespace plugin {

class LeaderPrefix : public Plugin {
 public:
  EventHandlerResult onKeyswitchEvent(KeyEvent &event) {
    // DUMP(int(event.id()));
    // DUMP(int(event.key.getRaw()));
    if (event_tracker_.shouldIgnore(event))
      return EventHandlerResult::OK;

    if (!active_) {
      if (keyToggledOn(event.state) && isLeaderKey(event.key)) {
        active_ = true;
        leader_arg_ = 0;
      }
      return EventHandlerResult::OK;
    }

    if (keyToggledOn(event.state)) {
      for (uint8_t i{0}; i < 10; ++i) {
        if (digit_keys_[i] == event.key) {
          leader_arg_ *= 10;
          leader_arg_ += i;
          live_keys.mask(event.addr);
          return EventHandlerResult::ABORT;
        }
      }
      // DUMP(active_);
      active_ = false;
    }
    if (keyToggledOff(event.state) && event.key == Key_Masked)
      return EventHandlerResult::ABORT;
    return EventHandlerResult::OK;
  }

  EventHandlerResult afterEachCycle() {
    // int timestamp = Runtime.millisAtCycleStart();
    // DUMP(timestamp);
    return EventHandlerResult::OK;
  }

  uint16_t arg() const {
    return leader_arg_;
  }

 private:
  Key digit_keys_[10] = {
    Key_P, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Y, Key_U, Key_I, Key_O,
  };

  KeyEventTracker event_tracker_;
  bool active_{false};
  uint16_t leader_arg_{0};
  bool isLeaderKey(Key key) {
    return (key >= ranges::LEAD_FIRST && key <= ranges::LEAD_LAST);
  }
};

} // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::LeaderPrefix LeaderPrefix;

auto &serial_port = Kaleidoscope.serialPort();

static void leaderTestX(uint8_t seq_index) {
  MacroSupport.tap(Key_A);
}

static void leaderTestXX(uint8_t seq_index) {
  MacroSupport.tap(Key_B);
}

void leaderTestPrefix(uint8_t seq_index) {
  uint8_t prefix_arg = LeaderPrefix.arg();
  // DUMP(prefix_arg);
  MacroSupport.tap(Key_Y);
  while (prefix_arg-- > 0)
    MacroSupport.tap(Key_X);
}

static const kaleidoscope::plugin::Leader::dictionary_t leader_dictionary[] PROGMEM =
LEADER_DICT({LEADER_SEQ(LEAD(0), Key_X), leaderTestX},
{LEADER_SEQ(LEAD(0), Key_X, Key_X), leaderTestXX},
{LEADER_SEQ(LEAD(0), Key_Z), leaderTestPrefix});

KALEIDOSCOPE_INIT_PLUGINS(LeaderPrefix, Leader);

void setup() {
  Kaleidoscope.setup();

  Leader.dictionary = leader_dictionary;
}

void loop() {
  Kaleidoscope.loop();
}
