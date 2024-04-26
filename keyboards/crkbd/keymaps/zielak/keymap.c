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
#define _QWERTY 1
#define _NAV 2
#define _NUM 3
#define _NUM_PAD 4
#define _FNK 5
#define _SYM 6

enum custom_keycodes {
    K_QUIT = SAFE_RANGE,
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
    APP_NXT,
    APP_PRV,
    NUM_L,
    NUMPD_L,
};

// App swapping and Print screen are different on Mac...
static uint16_t ctrlKey        = KC_LGUI;
static bool     isOnMac        = true;
static bool     isSwappingApps = false;
static bool     isCapsLockOn   = false;

static bool     numActive    = false;
static bool     numLocked    = false;
static uint16_t numLayer     = _NUM;
static uint16_t numTimestamp = 0;
static uint16_t numTapCount  = 0;

// Aliases to make keymap more readable
#define FNK_L LT(_FNK, KC_ESC)
#define NAV_L LT(_NAV, KC_DEL)
// #define NUM_L TT(_NUM)
// #define NUMPD_L TG(_NUM_PAD)
// #define TAP_ALT KC_F18
#define SYM_L LT(_SYM, KC_F18)

// Which key do you use to enter a layer
#define _ENTRY_ _______

// My usage
// ctrl 0.3  0.0 = 0.3
// alt  0.4  0.2 = 0.6
// shft 0.8  3.0 = 3.8
// gui  7.2  0.0 = 7.2

#define _LCTL LCTL_T(KC_A)
#define _LALT LALT_T(KC_R)
#define _LSFT LSFT_T(KC_S)
#define _LGUI LGUI_T(KC_T)

#define _RGUI RGUI_T(KC_N)
#define _RSFT RSFT_T(KC_E)
#define _RALT RALT_T(KC_I)
#define _RCTL RCTL_T(KC_O)

#define DF_COLE DF(_COLEMAKDH)
#define DF_QWER DF(_QWERTY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

  [_COLEMAKDH] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       XXXXXXX ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,            KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_BSPC ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,_LCTL   ,_LALT   ,_LSFT   ,_LGUI   ,KC_G    ,            KC_M    ,_RGUI   ,_RSFT   ,_RALT   ,_RCTL   ,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       XXXXXXX ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,            KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLASH,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      FNK_L   ,NAV_L   ,KC_SPACE,   NUM_L   ,SYM_L   ,KC_RALT
                                   //`--------------------------'  `--------------------------'
  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,            KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       KC_LGUI ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,            KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_QUOT ,KC_DEL  ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,            KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLASH,XXXXXXX ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      FNK_L   ,NAV_L   ,KC_SPACE,   NUM_L   ,SYM_L   ,KC_RALT
                                   //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,K_TERMI ,APP_PRV ,APP_NXT ,KC_PSCR ,XXXXXXX ,            KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,_______ ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_LCTL ,KC_LALT ,KC_LSFT ,KC_LGUI ,KC_ESC  ,            KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RIGHT,XXXXXXX ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,K_UNDO  ,K_CUT   ,K_COPY  ,K_PASTE ,K_REDO  ,            XXXXXXX ,KC_TAB  ,K_INDEL ,K_INDER ,KC_INS  ,_______ ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,_ENTRY_ ,_______ ,   XXXXXXX ,KC_CAPS ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),
  [_NUM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,KC_PERC ,KC_7    ,KC_8    ,KC_9    ,KC_PPLS ,            NUMPD_L ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_PAST ,KC_4    ,KC_5    ,KC_6    ,KC_MINS ,            XXXXXXX ,KC_RGUI ,KC_RSFT ,KC_RALT ,KC_RCTL ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_PSLS ,KC_1    ,KC_2    ,KC_3    ,KC_EQL  ,            K_REDO  ,K_PASTE ,K_COPY  ,K_CUT   ,K_UNDO  ,_______ ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      KC_DOT   ,KC_0   ,_______ ,   _ENTRY_ ,XXXXXXX ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),
  [_NUM_PAD] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,KC_PERC ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PPLS ,            NUMPD_L ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_PAST ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PMNS ,            XXXXXXX ,KC_RGUI ,KC_RSFT ,KC_RALT ,KC_RCTL ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_PSLS ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,            K_REDO  ,K_PASTE ,K_COPY  ,K_CUT   ,K_UNDO  ,_______ ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      KC_PDOT ,KC_P0   ,_______ ,   _ENTRY_ ,XXXXXXX ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),

  [_FNK] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,XXXXXXX ,            GU_TOGG ,RGB_TOG ,KC_BRID ,KC_BRIU ,DT_UP   ,_______ ,
    //|--------+--------+--------+--------+--------|--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,XXXXXXX ,            CG_NORM ,KC_MUTE ,KC_VOLD ,KC_VOLU ,DT_DOWN ,_______ ,
    //|--------+--------+--------+--------+--------|--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,            CG_SWAP ,KC_MPLY ,KC_MPRV ,KC_MNXT ,DT_PRNT ,EE_CLR  ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      _ENTRY_ ,XXXXXXX ,_______ ,   DF_QWER ,DF_COLE ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.           ,-----------------------------------------------------.
       _______ ,KC_QUES ,KC_EXLM ,K_ARROW ,KC_COLN ,KC_PPLS ,            XXXXXXX ,KC_LCBR ,KC_RCBR ,KC_AMPR ,_______ ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_AT   ,KC_DLR  ,KC_UNDS ,KC_SCLN ,KC_MINS ,            KC_GRV  ,KC_LPRN ,KC_RPRN ,KC_DQUO ,KC_PIPE ,_______ ,
    //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
       _______ ,KC_TILD ,KC_HASH ,KC_CIRC ,KC_PSLS ,KC_PAST ,            XXXXXXX ,KC_LBRC ,KC_RBRC ,KC_QUOT ,KC_BSLS ,_______ ,
    //|--------+--------+--------+--------+--------+--------+---|  |----+--------+--------+--------+--------+--------+--------|
                                      XXXXXXX ,KC_CAPS ,_______ ,   XXXXXXX ,_ENTRY_ ,XXXXXXX
                                   //`--------------------------'  `--------------------------'
  ),

    // clang-format on
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case _LGUI:
        case _RGUI:
            return TAPPING_TERM - 10;
        case _LSFT:
        case _RSFT:
            return TAPPING_TERM - 20;
        case _LALT:
        case _RALT:
            return TAPPING_TERM + 0;
        case _LCTL:
        case _RCTL:
            return TAPPING_TERM + 20;
        default:
            return TAPPING_TERM;
    }
}

bool tap_ctrl_and_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code(ctrlKey);
        tap_code_delay(keycode, 20);
        unregister_code(ctrlKey);
    }
    return false;
}

bool switch_num_layers(void) {
    numActive = !numActive;
    numLayer  = numActive ? _NUM_PAD : _NUM;

    if (numActive) {
        layer_on(_NUM_PAD);
        layer_off(_NUM);
    } else {
        layer_off(_NUM_PAD);
        layer_on(_NUM);
    }

    return false;
}

void num_layers_off(void) {
    layer_off(_NUM);
    layer_off(_NUM_PAD);
}

void num_layer_on(void) {
    layer_on(numLayer);
    numTapCount = 0;
}

bool tap_num_layers(keyrecord_t *record) {
    // dprint("tap_num_layers");
    // record->tap.count
    // record->tap.interrupted

    if (!numLocked) {
        if (record->event.pressed && numTapCount < 1) {
            numTapCount++;
        }
    }

    dprintf("tap_num_layers - TAPPING_TERM: %d, now: %d, last: %d, TAPcount: %d\n", TAPPING_TERM, record->event.time, numTimestamp, record->tap.count);
    // Did double tap
    if (!numLocked && record->event.pressed && record->tap.count > 1 && record->event.time < numTimestamp + TAPPING_TERM) {
        num_layer_on();
        dprint("Did double tap!\n");
        numLocked = true;
        return false;
    }

    if (numLocked) {
        dprint("is locked\n");
        if (record->event.pressed) {
            dprint("unlocking\n");
            numLocked = false;
            num_layers_off();
        } else {
        }
        return true;
    }

    if (record->event.pressed) {
        numTimestamp = record->event.time;
        num_layer_on();
    } else {
        num_layers_off();
    }
    return true;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        // writePin(BLUE_LED_PIN, led_state.caps_lock);

        isCapsLockOn = led_state.caps_lock;
    }
    return res;
}

// Combo stuff

const uint16_t PROGMEM combo_enter[]           = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_tab[]             = {KC_X, KC_C, COMBO_END};
combo_t                key_combos[COMBO_COUNT] = {
    COMBO(combo_enter, KC_ENT), COMBO(combo_tab, KC_TAB),
    // COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};

// OLED stuff

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

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
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("NAVigation"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("numb3r5"), false);
            break;
        case _NUM_PAD:
            oled_write_ln_P(PSTR("num PAD"), false);
            break;
        case _FNK:
            oled_write_ln_P(PSTR("! FN !"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("$ymbols"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?"), false);
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);
}

void oled_render_keylog(void) {
    // oled_write(keylog_str, false);
}

void oled_render_caps_status(void) {
    oled_write_P(PSTR("\n- "), false);
    oled_write_P(isOnMac ? PSTR(" Mac ") : PSTR(" Win "), false);

    if (isCapsLockOn) {
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
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
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
    uint8_t current_layer = get_highest_layer(layer_state);

#ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif // OLED_ENABLE

    switch (keycode) {
        case CG_NORM:
            if (record->event.pressed) {
                isOnMac = true;
                ctrlKey = KC_LGUI;
            }
            return true;
        case CG_SWAP:
            if (record->event.pressed) {
                isOnMac = false;
                ctrlKey = KC_LCTL;
            }
            return true;
        case KC_PSCR:
            if (record->event.pressed) {
                if (isOnMac) {
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    tap_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            } else {
                if (isOnMac) {
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
        case APP_NXT:
        case APP_PRV:
            // Only accept while on layer NAV
            if (current_layer == _NAV || isSwappingApps) {
                if (record->event.pressed) {
                    isSwappingApps = true;

                    register_code(isOnMac ? KC_LGUI : KC_LALT);
                    if (keycode == APP_PRV) {
                        register_code(KC_LSFT);
                    }
                    tap_code(KC_TAB);
                    if (keycode == APP_PRV) {
                        unregister_code(KC_LSFT);
                    }
                } else {
                    unregister_code(KC_TAB);
                }
                return true;
            }
            return false;
        case NAV_L:
            if (!record->event.pressed && isSwappingApps) {
                isSwappingApps = false;
                unregister_code(isOnMac ? KC_LGUI : KC_LALT);
                unregister_code(KC_TAB);
            }
            return true;
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
        case SYM_L:
            dprintf("TAP_ALT: %d, now: %d\n", record->event.pressed, record->event.time);
            if (record->tap.count > 0) {
                dprintf("tap.count = %d\n", record->tap.count);
                if (record->event.pressed) {
                    dprint("set oneshot!\n");
                    set_oneshot_mods(MOD_BIT(KC_ALGR));
                } else {
                }
                return false;
            }
            break;
        case NUM_L:
            return tap_num_layers(record);
        case NUMPD_L:
            if (record->event.pressed) {
                switch_num_layers();
            }
            return true;
        default:
            return true; // Process all other keycodes normally
    }

    return true;
}
