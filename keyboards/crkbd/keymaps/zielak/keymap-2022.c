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

#define _COLEMAKDH 0
#define _GAME1 1
#define _GAME2 2
#define _SYMB 3
#define _NAV 4
#define _ADJUST 5
#define _REST 6

enum custom_keycodes {
  APP_NXT = SAFE_RANGE,
  APP_PRV,
  K_PRSCR, // print region of screen
  K_QUIT,
  K_CLOSE,
  K_FIND,
  K_UNDO,
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
static bool isSwappingApps = false;
static bool isCapsWordUp = false;
static uint16_t ctrlKey = KC_LCTL;

// Shortcuts to make keymap more readable
#define SYM_L   MO(_SYMB)
#define NAV_L   TT(_NAV)
#define ADJ_L   MO(_ADJUST) // LT(_ADJUST, KC_ESC)
#define RST_L   MO(_REST)
#define GM2_L   MO(_GAME2)

// Which key do you use to enter a layer
# define _ENTRY_ _______

#define DEF_COL DF(_COLEMAKDH)
#define DEF_GAM DF(_GAME1)

// My usage
// ctrl 0.3  0.0 = 0.3
// alt  0.4  0.2 = 0.6
// shft 0.8  3.0 = 3.8
// gui  7.2  0.0 = 7.2

#define _LGUI LGUI_T(KC_Z)
#define _LALT RALT_T(KC_X) // RALT_T on left side - because I type PL letters on windows
#define _LSFT LSFT_T(KC_C)
#define _LCTL LCTL_T(KC_D)

#define _RCTL RCTL_T(KC_H)
#define _RSFT RSFT_T(KC_COMM)
#define _RALT RALT_T(KC_DOT)
#define _RGUI RGUI_T(KC_SLASH)

// Home row for nav layer
#define NA_LGUI LGUI_T(KC_P7)
#define NA_LALT RALT_T(KC_P8) // RALT_T on left side - because I type PL letters on windows
#define NA_LSFT LSFT_T(KC_P9)
#define NA_LCTL LCTL_T(KC_PSLS)

#define OSM_CTL OSM(MOD_RCTL)
#define OSM_ALT OSM(MOD_RALT)
#define OSM_SFT OSM(MOD_RSFT)
#define OSM_GUI OSM(MOD_RGUI)

// #define ENT_SFT MT(MOD_LSFT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDH] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.          ,-----------------------------------------------------.
       KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,           KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSPC ,
    //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
       KC_LCTL ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G    ,           KC_M    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT ,
    //|--------+--------+--------+--------+--------+--------|          |--------+--------+--------+--------+--------+--------|
       KC_LSFT ,_LGUI   ,_LALT   ,_LSFT   ,_LCTL   ,KC_V    ,           KC_K    ,_RCTL   ,_RSFT   ,_RALT   ,_RGUI   ,ADJ_L   ,
    //|--------+--------+--------+--------+--------+--------+---|  |---+--------+--------+--------+--------+--------+--------|
                                      KC_LALT ,NAV_L   ,KC_SPC  ,   KC_LSFT ,SYM_L   ,KC_ENT
                                   //`--------------------------'  `--------------------------'
  ),

  [_GAME1] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,            KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,            KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,            KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLASH,ADJ_L   ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      KC_LALT ,GM2_L   ,KC_SPC  ,   KC_LSFT ,SYM_L   ,KC_ENT
                                   //`--------------------------'  `--------------------------'
  ),

  [_GAME2] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,KC_1    ,KC_2    ,KC_3    ,KC_I    ,KC_ESC  ,            KC_HOME ,KC_END  ,KC_UP   ,KC_WH_U ,KC_INS  ,KC_BSPC ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_4    ,KC_5    ,KC_6    ,KC_MINS ,KC_ENT  ,            KC_PGUP ,KC_LEFT ,KC_DOWN ,KC_RIGHT,APP_PRV ,APP_NXT ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_7    ,KC_8    ,KC_9    ,KC_EQL  ,KC_M    ,            KC_PGDN ,KC_WH_D ,K_INDEL ,K_INDER ,XXXXXXX ,ADJ_L   ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                        KC_0  ,_ENTRY_ ,_______ ,    _______, RST_L  ,_______
                                   //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       K_TERMI ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PPLS ,KC_ESC  ,            KC_HOME ,KC_END  ,KC_UP   ,KC_WH_D ,KC_DEL  ,KC_BSPC ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       KC_DOT  ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PMNS ,KC_ENT  ,            KC_PGUP ,KC_LEFT ,KC_DOWN ,KC_RIGHT,APP_PRV ,APP_NXT ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       KC_P0   ,NA_LGUI ,NA_LALT ,NA_LSFT ,NA_LCTL ,KC_PAST ,            KC_PGDN ,KC_WH_U ,K_INDEL ,K_INDER ,XXXXXXX ,ADJ_L   ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      KC_COLN ,_ENTRY_ ,_______ ,   _______ , RST_L  ,_______
                                   //`--------------------------'  `--------------------------'
  ),

  [_SYMB] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,KC_QUES ,KC_EXLM ,K_ARROW ,KC_PPLS ,KC_PERC ,            XXXXXXX ,KC_TILD ,KC_UNDS ,KC_GRV  ,KC_COLN ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_AT   ,KC_DLR  ,KC_AMPR ,KC_PMNS ,KC_PEQL ,            KC_LPRN ,KC_RPRN ,KC_LBRC ,KC_RBRC ,KC_PIPE ,KC_DQUO ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,XXXXXXX ,KC_HASH ,KC_CIRC ,KC_PSLS ,KC_PAST ,            KC_LCBR ,KC_RCBR ,KC_LABK ,KC_RABK ,KC_BSLS ,_______ ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      _______ ,RST_L   ,_______ ,   _______ ,_ENTRY_ ,_______
                                   //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       XXXXXXX ,CG_SWAP ,CG_NORM ,XXXXXXX ,XXXXXXX ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,KC_VOLD ,KC_VOLU ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,DEF_COL ,DEF_GAM ,XXXXXXX ,DB_TOGG ,XXXXXXX ,            K_PRSCR ,XXXXXXX ,KC_MPRV ,KC_MNXT ,XXXXXXX ,_ENTRY_ ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,XXXXXXX ,XXXXXXX ,   KC_MPLY ,XXXXXXX ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),

  [_REST] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,XXXXXXX ,            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,XXXXXXX ,            XXXXXXX ,OSM_CTL ,OSM_SFT ,OSM_ALT ,OSM_GUI ,ADJ_L   ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,_ENTRY_ ,XXXXXXX ,   XXXXXXX ,_ENTRY_ ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  )
};

bool tap_ctrl_and_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code(ctrlKey);
        tap_code(keycode);
        unregister_code(ctrlKey);
    }
    return false;
}

void caps_word_set_user(bool active) {
    isCapsWordUp = active;
}

// OLED stuff

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
//   if (!is_keyboard_master()) {
//     return OLED_ROTATION_90;  // flips the display 180 degrees if offhand
//   }
//   return OLED_ROTATION_270;
}

// #define L_COLEMAKDH 0
// #define L_GAME1 2
// #define L_GAME2 4
// #define L_SYMB 8
// #define L_NAV 16
// #define L_ADJUST 32
// #define L_REST 64

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);

    // if(default_layer_state == _COLEMAKDH) {
    //     oled_write_ln_P(PSTR("Colemak"), false);
    // }else if(default_layer_state == _GAME1){
    //     oled_write_ln_P(PSTR("Game"), false);
    // }

    switch (get_highest_layer(layer_state)) {
        case _COLEMAKDH:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case _GAME1:
            oled_write_ln_P(PSTR("Game"), false);
            break;
        case _GAME2:
            oled_write_ln_P(PSTR("Game Two"), false);
            break;
        case _SYMB:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        case _REST:
            oled_write_ln_P(PSTR("Rest / FK"), false);
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
    if(isSwappingApps){
        oled_write_P(PSTR(" APPswap "), true);
    }
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
        case APP_NXT:
        case APP_PRV:
            // Only accept while help RALT
            if (get_mods() & MOD_BIT(KC_RALT) || isSwappingApps) {
                dprint("+KC_RALT");
                if (record->event.pressed) {
                    isSwappingApps = true;
                    unregister_code(KC_RALT);

                    register_code(isOnMac ? KC_LGUI : KC_LALT);
                    if(keycode == APP_PRV) {
                        register_code(KC_LSFT);
                    }
                    tap_code(KC_TAB);
                    if(keycode == APP_PRV) {
                        unregister_code(KC_LSFT);
                    }
                } else {
                    unregister_code(KC_TAB);
                }
                return true;
            } else {
                if (record->event.pressed) {
                    register_code(KC_LCTL);
                    if(keycode == APP_PRV) {
                        register_code(KC_LSFT);
                    }
                    tap_code(KC_TAB);
                    if(keycode == APP_PRV) {
                        unregister_code(KC_LSFT);
                    }
                    unregister_code(KC_LCTL);
                }
            }
        case KC_RALT:
            if(!record->event.pressed && isSwappingApps) {
                isSwappingApps = false;
                unregister_code(isOnMac ? KC_LGUI : KC_LALT);
                unregister_code(KC_TAB);
            }
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
