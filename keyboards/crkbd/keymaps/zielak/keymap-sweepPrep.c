/*
    Copyright 2019 @foostan
    Copyright 2020 Drashna Jaelre <@drashna>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

#define _BASE 0
#define _NAV 1
#define _NUM 2
#define _SYM 3
#define _FUN 4
#define _FNK 5

enum custom_keycodes {
//   APP_NXT,
//   APP_PRV,
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

// Shortcuts to make keymap more readable
#define FUN_L   LT(_FUN, KC_Q)
#define NAV_L   LT(_NAV, KC_SPACE) // TT(_NAV)
#define NUM_L   LT(_NUM, KC_ENTER) // MO(_ADJUST)
#define FNK_L   OSL(_FNK)
#define SYM_L   LT(_SYM, KC_QUOT)

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
  [_BASE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       XXXXXXX ,FUN_L   ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,            KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_BSPC ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,_LGUI   ,_LALT   ,_LSFT   ,_LCTL   ,KC_G    ,            KC_M    ,_RCTL   ,_RSFT   ,_RALT   ,_RGUI   ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,            KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLASH,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,KC_LSFT ,NAV_L   ,   NUM_L   ,SYM_L   ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),                                        // Tab     , Space     , Enter  , Backspace

  [_FUN] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       XXXXXXX ,_ENTRY_ ,CG_SWAP ,CG_NORM ,XXXXXXX ,K_PRSCR ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_LGUI ,KC_LALT ,KC_LSFT ,KC_LCTL ,XXXXXXX ,            XXXXXXX ,KC_MPRV ,KC_VOLD ,KC_VOLU ,KC_MNXT ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,KC_BRID ,KC_BRIU ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,K_TERMI ,XXXXXXX ,   KC_MPLY ,KC_MUTE ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),
  [_NAV] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_DEL  ,KC_BSPC ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_LGUI ,KC_LALT ,KC_LSFT ,KC_LCTL ,XXXXXXX ,            XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,            KC_INS  ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,XXXXXXX ,_ENTRY_ ,   KC_ENT  ,XXXXXXX ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),

  // keypad part focused on IP/port entry
  [_NUM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       XXXXXXX ,FNK_L   ,KC_P4   ,KC_P5   ,KC_P6   ,KC_COLN ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_DEL  ,KC_BSPC ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_P0   ,KC_P1   ,KC_P2   ,KC_P3   ,KC_DOT  ,            XXXXXXX ,KC_RCTL ,KC_RSFT ,KC_RALT ,KC_RGUI ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_PMNS ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PSLS ,            KC_PEQL ,KC_PPLS ,KC_PMNS ,KC_PAST ,KC_PSLS ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,KC_LSFT ,KC_SPC  ,   _ENTRY_ ,XXXXXXX ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),

  // sub layer of NUM for F keys
  [_FNK] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       XXXXXXX ,_ENTRY_ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_DEL  ,KC_BSPC ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,XXXXXXX, KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,            XXXXXXX ,KC_RCTL ,KC_RSFT ,KC_RALT ,KC_RGUI ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,XXXXXXX ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,XXXXXXX ,XXXXXXX ,   XXXXXXX ,XXXXXXX ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),

// TODO:
  [_SYM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,----------------------------------------------------.
       XXXXXXX ,KC_AMPR ,KC_EXLM ,K_ARROW ,KC_PPLS ,KC_PERC ,            KC_PIPE ,KC_LPRN ,KC_LCBR ,KC_LBRC ,KC_BSPC ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_AT   ,KC_DLR  ,KC_UNDS ,KC_PMNS ,KC_EQL  ,            KC_SCLN ,KC_RCTL ,KC_RSFT ,KC_RALT ,KC_RGUI ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_TILD ,KC_HASH ,KC_CIRC ,KC_PSLS ,KC_PAST ,            KC_COLN ,KC_RPRN ,KC_RCBR ,KC_RBRC ,KC_BSLS ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,KC_GRV  ,KC_SPC  ,   XXXXXXX ,_ENTRY_ ,XXXXXXX
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

// Combo stuff

const uint16_t PROGMEM combo_enter[] = {KC_COMM ,KC_DOT , COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_X, KC_C, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_enter, KC_ENT),
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_tab, KC_TAB),
    // COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};

// OLED stuff

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);

    // if(default_layer_state == _BASE) {
    //     oled_write_ln_P(PSTR("Colemak"), false);
    // }else if(default_layer_state == _GAME1){
    //     oled_write_ln_P(PSTR("Game"), false);
    // }

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("base"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("NAV igation"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("NUM bers"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("SYM bols"), false);
            break;
        case _FUN:
            oled_write_ln_P(PSTR("FUN ctions"), false);
            break;
        case _FNK:
            oled_write_ln_P(PSTR("F1 - F12"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?"), false);
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (
        (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)
    ) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(
        keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
        record->event.key.row, record->event.key.col,
        keycode, name
    );
}

void oled_render_keylog(void) {
    // oled_write(keylog_str, false);
}

void oled_render_caps_status(void) {
    oled_write_P(PSTR("\n- "), false);
    oled_write_P(isOnMac ? PSTR(" Mac ") : PSTR(" Win "), false);

    if(isCapsWordUp){
        oled_write_P(PSTR(" CAPS "), true);
    }
    // if(isSwappingApps){
    //     oled_write_P(PSTR(" APPswap "), true);
    // }
    oled_advance_page(true);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
        oled_render_caps_status();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    #ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    #endif // OLED_ENABLE

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
            // TODO: mac/win, for grabbing screen region!
            if (record->event.pressed) {
                if(isOnMac){
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    tap_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }else{

                }
            }else{
                if(isOnMac){
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }else{

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
        // case APP_NXT:
        // case APP_PRV:
        //     // Only accept while help RALT
        //     if (get_mods() & MOD_BIT(KC_RALT) || isSwappingApps) {
        //         dprint("+KC_RALT");
        //         if (record->event.pressed) {
        //             isSwappingApps = true;
        //             unregister_code(KC_RALT);

        //             register_code(isOnMac ? KC_LGUI : KC_LALT);
        //             if(keycode == APP_PRV) {
        //                 register_code(KC_LSFT);
        //             }
        //             tap_code(KC_TAB);
        //             if(keycode == APP_PRV) {
        //                 unregister_code(KC_LSFT);
        //             }
        //         } else {
        //             unregister_code(KC_TAB);
        //         }
        //         return true;
        //     } else {
        //         if (record->event.pressed) {
        //             register_code(KC_LCTL);
        //             if(keycode == APP_PRV) {
        //                 register_code(KC_LSFT);
        //             }
        //             tap_code(KC_TAB);
        //             if(keycode == APP_PRV) {
        //                 unregister_code(KC_LSFT);
        //             }
        //             unregister_code(KC_LCTL);
        //         }
        //     }
        // case KC_RALT:
        //     if(!record->event.pressed && isSwappingApps) {
        //         isSwappingApps = false;
        //         unregister_code(isOnMac ? KC_LGUI : KC_LALT);
        //         unregister_code(KC_TAB);
        //         return false;
        //     }
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
