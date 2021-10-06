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



#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO,
  MACRO_DBL_BQ,
};

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

enum {
  QWERTY,
  FUN,
  UPPER
};

/* *INDENT-OFF* */
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B         ,Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_Backtick  ,Key_Space     ,Key_Backspace

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_Lang1,    Key_Enter ,Key_Esc    ,Key_Minus ,Key_Quote  ,Key_Enter
  ),

  [FUN] = KEYMAP_STACKED
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

  [UPPER] = KEYMAP_STACKED
  (
       Key_Insert            ,Key_Home                 ,Key_UpArrow   ,Key_End        ,Key_PageUp
      ,Key_Delete            ,Key_LeftArrow            ,Key_DownArrow ,Key_RightArrow ,Key_PageDown
      ,M(MACRO_VERSION_INFO) ,Consumer_VolumeIncrement ,XXX           ,XXX            ,___ ,___
      ,MoveToLayer(QWERTY)   ,Consumer_VolumeDecrement ,___           ,___            ,___ ,___

                ,Key_UpArrow   ,Key_F7              ,Key_F8          ,Key_F9         ,Key_F10
                ,Key_DownArrow ,Key_F4              ,Key_F5          ,Key_F6         ,Key_F11
      ,___      ,XXX           ,Key_F1              ,Key_F2          ,Key_F3         ,Key_F12
      ,___      ,___           ,MoveToLayer(QWERTY) ,Key_PrintScreen ,Key_ScrollLock ,Consumer_PlaySlashPause
   )
)
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
  MouseKeys
);

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

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 5), Key_LeftShift),    // thumb outer
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 6), Key_LeftShift),    // thumb outer

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 4), ShiftToLayer(UPPER)),    // thumb fun
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 7), ShiftToLayer(FUN)),    // thumb fun

      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 3), Key_LeftGui),    // thumb fun
      kaleidoscope::plugin::Qukey(0, KeyAddr(3, 8), Key_LeftGui),    // thumb fun
  )
}

void loop() {
  Kaleidoscope.loop();
}


