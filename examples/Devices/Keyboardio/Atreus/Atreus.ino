/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-TapDance.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At LSHIFT(Key_2)
#define Key_Hash LSHIFT(Key_3)
#define Key_Dollar LSHIFT(Key_4)
#define Key_Percent LSHIFT(Key_5)
#define Key_Caret LSHIFT(Key_6)
#define Key_And LSHIFT(Key_7)
#define Key_Star LSHIFT(Key_8)
#define Key_Plus LSHIFT(Key_Equals)
#define Key_Underscore LSHIFT(Key_Minus)
#define Key_Tilde LSHIFT(Key_Backtick)
#define Key_Colon LSHIFT(Key_Semicolon)
#define Key_DBLQuote LSHIFT(Key_Quote)
#define Key_Pipe LSHIFT(Key_Backslash)
#define Key_LeftCurl LSHIFT(Key_LeftBracket)
#define Key_RightCurl LSHIFT(Key_RightBracket)
#define Key_LessThan  LSHIFT(Key_Comma)
#define Key_GreaterThan LSHIFT(Key_Period)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO,
  MACRO_DBL_BQ,
  MACRO_MOUSE_FAST,
  MACRO_MOUSE_SLOW,
};

enum {
  QWERTY,
  SYMBOL,
  NUMBER,
  PAREN,
  MOUSE,
  PLAIN,
};

enum {
  COMBO_EMACS_HANGUL,
  COMBO_JK_COLON
};

enum {
  TD_P_QUOTE, // semicolon and quote
};

void macroEmacsHangul(uint8_t combo_index) {

  /*
   *       return MACRO(I(25),
                   D(LeftShift), T(M), U(LeftShift), T(O), T(D), T(E), T(L),
                   T(Spacebar),
                   W(100),
                   T(0), T(1) );
   */

  Macros.play(MACRO(T(F14)));
}

void jkColon(uint8_t combo_index) {
  Macros.type(PSTR("juhyung"));
}

// jk :
// vb hangul
USE_MAGIC_COMBOS(
  [COMBO_EMACS_HANGUL] = {
    .action = macroEmacsHangul,
    .keys = { R1C8, R2C8 }
  },
  [COMBO_JK_COLON] = {
    .action = jkColon,
    .keys = { R1C8, R1C9 }
  }
);



/* *INDENT-OFF* */
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B         ,Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_Backtick  ,Key_Space     ,Key_Backspace

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,TD(TD_P_QUOTE)
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_Lang1,    Key_Enter ,Key_Esc    ,Key_Minus ,Key_Quote  ,Key_Enter
  ),

  [SYMBOL] = KEYMAP_STACKED
  (
       Key_Exclamation ,Key_At           ,Key_Underscore   ,Key_Tab     ,LSHIFT(Key_Tab)
      ,Key_Hash        ,Key_Dollar       ,Key_Minus        ,Key_Esc     ,LSHIFT(Key_Esc)
      ,Key_Percent     ,Key_Caret        ,Key_Tilde        ,Key_Colon   ,___                ,___
      ,___             ,___              ,___              ,___         ,___                ,___

                   ,M(MACRO_DBL_BQ),Key_Tilde ,Key_DBLQuote    ,Key_Pipe  ,Key_Backslash
                   ,Key_Plus       ,Key_Minus ,Key_Slash       ,Key_Star  ,Key_Quote
      ,___         ,Key_And        ,Key_Equals,Key_Comma       ,Key_Period,Key_Semicolon
      ,___         ,___            ,___       ,___             ,___       ,___
   ),

  [NUMBER] = KEYMAP_STACKED
  (
       Key_1               ,Key_2                 ,Key_3   ,Key_4        ,Key_5
      ,Key_F1              ,Key_F2                ,Key_F3  ,Key_F4       ,Key_F5
      ,Key_F6              ,Key_F7                ,Key_F8  ,Key_F9       ,Key_F10 ,___
      ,MoveToLayer(QWERTY) ,M(MACRO_VERSION_INFO) ,___     ,___          ,___     ,___

                ,Key_6         ,Key_7               ,Key_8           ,Key_9          ,Key_0
                ,Key_LeftArrow ,Key_DownArrow       ,Key_UpArrow     ,Key_RightArrow ,Key_F10
      ,___      ,Key_F11       ,Key_F12             ,Key_F13         ,Key_F14        ,Key_F15
      ,___      ,___           ,___                 ,___             ,___            ,___
   ),

   [PAREN] = KEYMAP_STACKED
   (
       Key_Home        ,Key_End          ,___   ,___    ,___
      ,Key_LessThan    ,Key_GreaterThan  ,___   ,___    ,___
      ,Key_PageUp      ,Key_PageDown     ,___   ,___    ,___       ,___
      ,___             ,___              ,___   ,___    ,___       ,___

             ,___   ,Key_LeftCurl    ,Key_RightCurl   ,___   ,___
             ,___   ,Key_LeftParen   ,Key_RightParen  ,___   ,___
       ,___  ,___   ,Key_LeftBracket ,Key_RightBracket,___   ,___
       ,___  ,___   ,___      ,___   ,___   ,___
   ),

   [MOUSE] = KEYMAP_STACKED
   (
       Key_mouseScrollUp ,Key_mouseScrollL,Key_mouseUp ,Key_mouseScrollR ,___
      ,Key_mouseScrollDn ,Key_mouseL      ,Key_mouseDn ,Key_mouseR       ,___
      ,M(MACRO_MOUSE_SLOW),M(MACRO_MOUSE_FAST),___     ,___              ,___          ,___
      ,___               ,___             ,___         ,M(MACRO_MOUSE_SLOW),Key_mouseBtnL,___

                     ,___           ,___              ,Key_mouseWarpNW ,Key_mouseWarpN  ,Key_mouseWarpNE
                     ,___           ,___              ,Key_mouseWarpW  ,Key_mouseWarpIn ,Key_mouseWarpE
       ,___          ,___           ,___              ,Key_mouseWarpSW ,Key_mouseWarpS  ,Key_mouseWarpSE
       ,Key_mouseBtnM,Key_mouseBtnR ,M(MACRO_MOUSE_FAST),___             ,___             ,___
   ),

  [PLAIN] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B         ,Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_Backtick  ,Key_Space     ,Key_Backspace

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,TD(TD_P_QUOTE)
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_Lang1,    Key_Enter ,Key_Esc    ,Key_Minus ,Key_Quote  ,Key_Enter
  )
)

/*


    Key_mouseWarpNW, Key_mouseWarpNE, Key_mouseWarpSW, Key_mouseWarpSE: Warp towards the north-west, north-east, south-west, or south-east quadrants, respectively.

    Key_mouseWarpEnd: End the warping sequence, resetting it to the default state. Using any of the warping keys after this will start from the whole screen again.


    Key_mouseWarpN, Key_mouseWarpE, Key_mouseWarpS, Key_mouseWarpW: Warp towards the north, east, south, and west sectors, respectively.

    Key_mouseWarpIn: Warp to the center sector of the grid. The plugin will continue to “zoom” into center of the current cell with each consecutive press of this key.

 *
 */


/* *INDENT-ON* */

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusEEPROMCommand,
  FocusSettingsCommand,
  Qukeys,
  SpaceCadet,
  OneShot,
  Macros,
  MouseKeys,
  MagicCombo,
  TapDance
);

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
    case TD_P_QUOTE:
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_P, Key_Quote);
  }
}

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_QWERTY:
      // This macro is currently unused, but is kept around for compatibility
      // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
      // longer do. We keep it so that if someone still has the old layout with
      // the macro in EEPROM, it will keep working after a firmware update.
      Layer.move(QWERTY);
      break;
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    case MACRO_DBL_BQ:
      Macros.type(PSTR("``"));
      break;
    case MACRO_MOUSE_FAST:
      MouseKeys.speed = 10;
      MouseKeys.accelSpeed = 3;
      MouseKeys.setSpeedLimit(127);
      MouseKeys.wheelSpeed = 1;
      break;
    case MACRO_MOUSE_SLOW:
      MouseKeys.speed = 3;
      MouseKeys.accelSpeed = 1;
      MouseKeys.setSpeedLimit(20);
      MouseKeys.wheelSpeed = 10;
      break;
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup();
  SpaceCadet.disable();
  EEPROMKeymap.setup(10);

  QUKEYS(
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 0), Key_LeftControl),      // A
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 11), Key_LeftControl),      // ;

      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 1), Key_LeftAlt),      // s
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 10), Key_LeftAlt),      // l

      kaleidoscope::plugin::Qukey(0, KeyAddr(2, 0), Key_LeftShift),    // pinky
      kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), Key_LeftGui),    // pinky

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 5), Key_LeftShift),    // thumb outer
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 6), Key_LeftGui),    // thumb outer

      kaleidoscope::plugin::Qukey(0, KeyAddr(2, 5), ShiftToLayer(PLAIN)),    // thumb fun

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 4), ShiftToLayer(SYMBOL)),    // thumb fun
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 7), ShiftToLayer(NUMBER)),    // thumb fun

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 3), Key_LeftGui),    // thumb inner
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 8), Key_LeftShift),    // thumb inner

      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 3), ShiftToLayer(PAREN)),    // index fun
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 8), ShiftToLayer(MOUSE)),    // index fun
  )

  MouseKeys.speed = 7;
  MouseKeys.accelSpeed = 3;
  MouseKeys.setWarpGridSize(MOUSE_WARP_GRID_3X3);
}

void loop() {
  Kaleidoscope.loop();
}


