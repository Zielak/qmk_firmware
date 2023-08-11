/* Copyright 2021 weteor
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#ifdef COMBO_ENABLE
#   include "combos.h"
#endif

#define _BASE 0
#define _NAV 1
#define _NUM 2
#define _SML 3
#define _SMR 4
#define _FUN 5
#define _FNK 6

enum custom_keycodes {
  K_PRSCR = SAFE_RANGE, // print region of screen
  K_QUIT,
  K_CLOSE,
  K_FIND,
  K_UNDO,
  K_REDO,
  K_CUT,
  K_COPY,
  K_PASTE,
  K_INDEL,
  K_INDER,
  K_ARROW,
  K_TERMI,
};

// App swapping and Print screen are different on Mac...
static bool isOnMac = true;
// static bool isSwappingApps = false;
static bool isCapsWordUp = false;
static uint16_t ctrlKey = KC_LGUI;

// Aliases to make keymap more readable
#define FUN_L   LT(_FUN, KC_Q)
#define NAV_L   MO(_NAV)
#define NUM_L   MO(_NUM)
#define FNK_L   OSL(_FNK)
#define SML_L   MO(_SML)
#define SMR_L   MO(_SMR)

// Which key do you use to enter a layer
# define _ENTRY_ _______

// My usage
// ctrl 0.3  0.0 = 0.3
// alt  0.4  0.2 = 0.6
// shft 0.8  3.0 = 3.8
// gui  7.2  0.0 = 7.2

#define _LGUI LGUI_T(KC_A)
#define _LALT LALT_T(KC_R)
#define _LSFT LSFT_T(KC_S)
#define _LCTL LCTL_T(KC_T)

#define _RCTL RCTL_T(KC_N)
#define _RSFT RSFT_T(KC_E)
#define _RALT RALT_T(KC_I)
#define _RGUI RGUI_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
    //,--------------------------------------------.           ,--------------------------------------------.
       FUN_L   ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,            KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_BSPC ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       _LGUI   ,_LALT   ,_LSFT   ,_LCTL   ,KC_G    ,            KC_M    ,_RCTL   ,_RSFT   ,_RALT   ,_RGUI   ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,            KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLASH,
    //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                             NAV_L   ,SMR_L   ,KC_SPACE,   NUM_L   ,SML_L   ,XXXXXXX // Trackball
                          //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT(
    //,--------------------------------------------.           ,--------------------------------------------.
       XXXXXXX ,XXXXXXX ,CW_TOGG ,XXXXXXX ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_DEL  ,KC_BSPC ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_LGUI ,KC_LALT ,KC_LSFT ,KC_LCTL ,XXXXXXX ,            XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGH ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       K_UNDO  ,K_CUT   ,K_COPY  ,K_REDO  ,K_PASTE ,            KC_INS  ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,
    //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                             _ENTRY_ ,XXXXXXX ,XXXXXXX ,   XXXXXXX ,XXXXXXX ,XXXXXXX
                          //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT(
    //,--------------------------------------------.           ,--------------------------------------------.
       FNK_L   ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,            XXXXXXX ,XXXXXXX ,CW_TOGG ,KC_DEL  ,KC_BSPC ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_P0   ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PMNS ,            XXXXXXX ,KC_RCTL ,KC_RSFT ,KC_RALT ,KC_RGUI ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_COLN ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PSLS ,            K_PASTE ,K_REDO  ,K_COPY  ,K_CUT   ,K_UNDO  ,
    //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                             KC_PAST ,KC_DOT  ,KC_PEQL ,   _ENTRY_ ,XXXXXXX ,XXXXXXX
                          //`--------------------------'  `--------------------------'
  ),

  [_SML] = LAYOUT(
    //,--------------------------------------------.           ,--------------------------------------------.
       KC_AMPR ,KC_EXLM ,K_ARROW ,KC_PPLS ,KC_PERC ,            XXXXXXX ,XXXXXXX ,CW_TOGG ,KC_DEL  ,KC_BSPC ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_AT   ,KC_DLR  ,KC_UNDS ,KC_PMNS ,KC_EQL  ,            XXXXXXX ,KC_RCTL ,KC_RSFT ,KC_RALT ,KC_RGUI ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_TILD ,KC_HASH ,KC_CIRC ,KC_PSLS ,KC_PAST ,            K_PASTE ,K_REDO  ,K_COPY  ,K_CUT   ,K_UNDO  ,
    //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                             XXXXXXX ,XXXXXXX ,XXXXXXX ,   XXXXXXX ,_ENTRY_ ,XXXXXXX
                          //`--------------------------'  `--------------------------'
  ),

  [_SMR] = LAYOUT(
    //,--------------------------------------------.           ,--------------------------------------------.
       XXXXXXX ,XXXXXXX ,CW_TOGG ,XXXXXXX ,XXXXXXX ,            KC_PIPE ,KC_LPRN ,KC_LCBR ,KC_LBRC ,KC_DQUO ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_LGUI ,KC_LALT ,KC_LSFT ,KC_LCTL ,XXXXXXX ,            KC_SCLN ,KC_RPRN ,KC_RCBR ,KC_RBRC ,KC_QUOT ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       K_UNDO  ,K_CUT   ,K_COPY  ,K_REDO  ,K_PASTE ,            KC_COLN ,KC_GRV  ,KC_LT   ,KC_GT   ,KC_BSLS ,
    //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                             XXXXXXX ,_ENTRY_ ,XXXXXXX ,   XXXXXXX ,XXXXXXX ,XXXXXXX
                          //`--------------------------'  `--------------------------'
  ),

  [_FUN] = LAYOUT(
    //,--------------------------------------------.           ,--------------------------------------------.
       _ENTRY_ ,XXXXXXX ,CW_TOGG ,XXXXXXX ,K_PRSCR ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       KC_LGUI ,KC_LALT ,KC_LSFT ,KC_LCTL ,XXXXXXX ,            XXXXXXX ,KC_MPRV ,KC_VOLD ,KC_VOLU ,KC_MNXT ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       K_UNDO  ,K_CUT   ,K_COPY  ,K_REDO  ,K_PASTE ,            XXXXXXX ,XXXXXXX ,KC_BRID ,KC_BRIU ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                             XXXXXXX ,CG_SWAP ,CG_NORM ,   KC_MPLY ,KC_MUTE ,XXXXXXX
                          //`--------------------------'  `--------------------------'
  ),

  [_FNK] = LAYOUT(
    //,--------------------------------------------.           ,--------------------------------------------.
       _ENTRY_ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,            XXXXXXX ,XXXXXXX ,CW_TOGG ,KC_DEL  ,KC_BSPC ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       XXXXXXX, KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,            XXXXXXX ,KC_RCTL ,KC_RSFT ,KC_RALT ,KC_RGUI ,
    //|--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------|
       XXXXXXX ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,            K_PASTE ,K_REDO  ,K_COPY  ,K_CUT   ,K_UNDO  ,
    //|--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------|
                             XXXXXXX ,XXXXXXX ,XXXXXXX ,   XXXXXXX ,XXXXXXX ,XXXXXXX
                          //`--------------------------'  `--------------------------'
  ),

};

bool tap_ctrl_and_key(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    register_code(ctrlKey);
    tap_code_delay(keycode, 20);
    unregister_code(ctrlKey);
  }
  return false;
}

void caps_word_set_user(bool active) {
  isCapsWordUp = active;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CG_NORM:
      if (record->event.pressed) {
        isOnMac = false;
        ctrlKey = KC_LCTL;
      }
      return true;
    case CG_SWAP:
      if (record->event.pressed) {
        isOnMac = true;
        ctrlKey = KC_LGUI;
      }
      return true;
    case K_PRSCR:
      if (record->event.pressed) {
        if(isOnMac){
          register_code(KC_LGUI);
          register_code(KC_LSFT);
          tap_code(KC_4);
          unregister_code(KC_LGUI);
          unregister_code(KC_LSFT);
        }else{
          register_code(KC_LGUI);
          register_code(KC_LSFT);
          tap_code(KC_S);
          unregister_code(KC_LGUI);
          unregister_code(KC_LSFT);
        }
      }else{
        if(isOnMac){
          unregister_code(KC_LGUI);
          unregister_code(KC_LSFT);
        }else{
          unregister_code(KC_LGUI);
          unregister_code(KC_LSFT);
        }
      }
      return false;
    case K_UNDO:
      return tap_ctrl_and_key(KC_Z, record);
    case K_REDO:
      return tap_ctrl_and_key(KC_Y, record);
    case K_CUT:
      return tap_ctrl_and_key(KC_X, record);
    case K_COPY:
      return tap_ctrl_and_key(KC_C, record);
    case K_PASTE:
      return tap_ctrl_and_key(KC_V, record);
    case K_FIND:
      return tap_ctrl_and_key(KC_F, record);
    case K_CLOSE:
      return tap_ctrl_and_key(KC_W, record);
    case K_ARROW:
      if (record->event.pressed) {
        SEND_STRING("=>");
      }
      return false;
    case K_INDEL:
      return tap_ctrl_and_key(KC_LBRC, record);
    case K_INDER:
      return tap_ctrl_and_key(KC_RBRC, record);
    case K_TERMI:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_GRAVE);
        unregister_code(KC_LCTL);
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }

  return true;
}
