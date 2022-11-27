/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
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
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_And         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)
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
  MACRO_MOUSE_NORMAL,
  MACRO_MOUSE_SLOW,
};

enum {
  QWERTY,
  SYMBOL,
  NUMBER,
  PAREN,
  MOUSE,
  MOUSE_WARP,
  PLAIN,
};

// clang-format off
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B         ,Key_Delete
      ,Key_Lang1,Key_Tab ,Key_LeftGui ,Key_Backtick  ,Key_Space     ,Key_Backspace

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_Lang1    ,Key_Enter ,Key_Esc    ,Key_Minus ,Key_Quote  ,Key_F14
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
                ,Key_LeftArrow ,Key_DownArrow       ,Key_UpArrow     ,Key_RightArrow ,Key_LeftShift
      ,___      ,Key_F11       ,Key_F12             ,Key_F13         ,Key_F14        ,Key_Quote
      ,___      ,___           ,___                 ,___             ,___            ,___
   ),

   [PAREN] = KEYMAP_STACKED
   (
       Key_Home        ,Key_End          ,Key_PrintScreen,___    ,___
      ,Key_LessThan    ,Key_GreaterThan  ,Key_Insert ,___    ,___
      ,Key_PageUp      ,Key_PageDown     ,Key_Pause  ,___    ,___       ,___
      ,___             ,___              ,___        ,___    ,___       ,___

             ,___   ,Key_LeftCurl    ,Key_RightCurl   ,___   ,___
             ,___   ,Key_LeftParen   ,Key_RightParen  ,___   ,___
       ,___  ,___   ,Key_LeftBracket ,Key_RightBracket,___   ,___
       ,___  ,___   ,___      ,___   ,___   ,___
   ),

   [MOUSE] = KEYMAP_STACKED
   (
       Key_mouseScrollUp ,Key_mouseScrollL,Key_mouseUp ,Key_mouseScrollR ,___
      ,Key_mouseScrollDn ,Key_mouseL      ,Key_mouseDn ,Key_mouseR       ,___
      ,___               ,___             ,___         ,___              ,___            ,___
      ,___               ,___             ,___         ,___              ,Key_mouseBtnL  ,Key_mouseBtnM

                     ,___           ,___              ,___ ,___ ,___
                     ,___           ,___ ,M(MACRO_MOUSE_FAST) ,M(MACRO_MOUSE_NORMAL) ,M(MACRO_MOUSE_SLOW)
       ,___          ,___           ,___              ,___ ,___ ,___
       ,Key_mouseBtnM,Key_mouseBtnR ,Key_mouseWarpEnd ,___ ,___ ,___
   ),

   [MOUSE_WARP] = KEYMAP_STACKED
   (
    ___, Key_mouseWarpNW, Key_mouseWarpN, Key_mouseWarpNE, ___,
    Key_mouseWarpEnd, Key_mouseWarpW, Key_mouseWarpIn, Key_mouseWarpE, ___,
    ___, Key_mouseWarpSW, Key_mouseWarpS, Key_mouseWarpSE, ___, ___,
    ___, ___, ___, ___, ___, ___,

         ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___
   ),


  [PLAIN] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B         ,Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_Backtick  ,Key_Space     ,Key_Backspace

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_Lang1,    Key_Enter ,Key_Esc    ,Key_Minus ,Key_Quote  ,Key_Enter
  )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
                          //  EscapeOneShot,
                          EEPROMSettings,
                          //                          EEPROMKeymap,
                          //                          Focus,
                          //                          FocusEEPROMCommand,
                          //                          FocusSettingsCommand,
  Qukeys,
  //  SpaceCadet,
  OneShot,
  Macros,
  DynamicMacros,
  MouseKeys,
  //  EscapeOneShotConfig,
  FirmwareVersion
                          //                          LayerNames,
  //  SpaceCadetConfig,
                          //  OneShotConfig,
                          //  MouseKeysConfig
                          );

int lastPressedMouseMacro = 0;

void updateMouseSpeed(int pressedSpeed) {
  switch (pressedSpeed) {
    case MACRO_MOUSE_FAST:
      MouseKeys.setCursorInitSpeed(30);
      MouseKeys.setCursorAccelDuration(200); // 6
      MouseKeys.setCursorBaseSpeed(127);
      MouseKeys.setScrollInterval(50);
      //      MouseKeys.wheelSpeed(20);
      break;
    case MACRO_MOUSE_NORMAL:
      MouseKeys.setCursorInitSpeed(10);
      MouseKeys.setCursorAccelDuration(600); // 2
      MouseKeys.setCursorBaseSpeed(40);
      MouseKeys.setScrollInterval(50);
      //      MouseKeys.wheelSpeed = 1;
      break;
    case MACRO_MOUSE_SLOW:
      MouseKeys.setCursorInitSpeed(1);
      MouseKeys.setCursorAccelDuration(800); // 4
      MouseKeys.setCursorBaseSpeed(20);
      MouseKeys.setScrollInterval(200);
      //      MouseKeys.wheelSpeed = 1;
      break;
    default:
      break;
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
    default:
      break;
    }
  }

  switch (macro_id) {
    case MACRO_MOUSE_FAST:
      if (keyToggledOn(event.state)) {
        lastPressedMouseMacro = MACRO_MOUSE_FAST;
        updateMouseSpeed(lastPressedMouseMacro);
      } else if (keyToggledOff(event.state)) {
        if (lastPressedMouseMacro == MACRO_MOUSE_FAST) {
          lastPressedMouseMacro = MACRO_MOUSE_NORMAL;
          updateMouseSpeed(lastPressedMouseMacro);
        }
      }
      break;
    case MACRO_MOUSE_NORMAL:
      if (keyToggledOn(event.state)) {
        lastPressedMouseMacro = MACRO_MOUSE_NORMAL;
        updateMouseSpeed(lastPressedMouseMacro);
      }
      break;
    case MACRO_MOUSE_SLOW:
      if (keyToggledOn(event.state)) {
        lastPressedMouseMacro = MACRO_MOUSE_SLOW;
        updateMouseSpeed(lastPressedMouseMacro);
      } else if (keyToggledOff(event.state)) {
        if (lastPressedMouseMacro == MACRO_MOUSE_SLOW) {
          lastPressedMouseMacro = MACRO_MOUSE_NORMAL;
          updateMouseSpeed(lastPressedMouseMacro);
        }
      }
      break;
    default:
      break;
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup();
  //  EEPROMKeymap.setup(10);

  DynamicMacros.reserve_storage(48);

  LayerNames.reserve_storage(63);


  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  //  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();

  QUKEYS(
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 0), Key_LeftControl),      // A
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 11), Key_LeftControl),      // ;

      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 1), Key_LeftAlt),      // s
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 10), Key_LeftAlt),      // l

      kaleidoscope::plugin::Qukey(0, KeyAddr(2, 0), Key_LeftShift),    // pinky
      kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), Key_LeftGui),    // pinky

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 5), Key_LeftShift),    // thumb outer
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 6), Key_LeftGui),    // thumb outer

      kaleidoscope::plugin::Qukey(0, KeyAddr(2, 5), ShiftToLayer(PLAIN)),    // between

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 4), ShiftToLayer(SYMBOL)),    // thumb fun
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 7), ShiftToLayer(NUMBER)),    // thumb fun

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 3), Key_LeftGui),    // thumb inner
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 8), Key_LeftShift),    // thumb inner

      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 3), ShiftToLayer(PAREN)),    // index fun
      kaleidoscope::plugin::Qukey(0, KeyAddr(1, 8), ShiftToLayer(MOUSE)),    // index fun

      kaleidoscope::plugin::Qukey(MOUSE, KeyAddr(3, 8), ShiftToLayer(MOUSE_WARP)),    // thumb inner
  )

  updateMouseSpeed(MACRO_MOUSE_NORMAL);
  MouseKeys.setWarpGridSize(MOUSE_WARP_GRID_3X3);
}

void loop() {
  Kaleidoscope.loop();
}


