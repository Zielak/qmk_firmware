#include QMK_KEYBOARD_H
#include "print.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAKDH 0
#define _QWERTY 1
#define _SYMB 2
#define _NAV 3
#define _ADJUST 4

// enum custom_keycodes {
//   COLEMAKDH = SAFE_RANGE,
//   QWERTY,
//   SYMB,
//   NAV,
//   ADJUST,
// };

enum custom_keycodes {
  APP_NXT = SAFE_RANGE,
  APP_PRV,
};

// App swapping is only different on Mac...
static bool isOnMac = true;
static bool isSwappingApps = false;

// Shortcuts to make keymap more readable
#define SYM_L   MO(_SYMB)
#define NAV_L   MO(_NAV)
#define ADJ_L   MO(_ADJUST)

// Which key do you use to enter a layer
# define _ENTRY_ _______

#define LGUI_PL LGUI_T(KC_PPLS)

#define DEF_COL DF(_COLEMAKDH)
#define DEF_QWE DF(_QWERTY)

// ctrl 0.3  0.0 = 0.3
// alt  0.4  0.2 = 0.6
// shft 0.8  3.0 = 3.8
// gui  7.2  0.0 = 7.2

// Disable, until i figure out the tappity taps
#define _LGUI_A KC_A // LGUI_T(KC_A)
#define _LALT_R KC_R // RALT_T(KC_R) // because I type PL letters on windows
#define _LSFT_S KC_S // LSFT_T(KC_S)
#define _LCTL_T KC_T // LCTL_T(KC_T)

#define _RCTL_N KC_N // RCTL_T(KC_N)
#define _RSFT_E KC_E // RSFT_T(KC_E)
#define _RALT_I KC_I // RALT_T(KC_I)
#define _RGUI_O KC_O // RGUI_T(KC_O)

#define OSM_CTL OSM(MOD_RCTL)
#define OSM_ALT OSM(MOD_RALT)
#define OSM_SFT OSM(MOD_RSFT)
#define OSM_GUI OSM(MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAKDH] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,APP_NXT ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,KC_ESC  ,                          ADJ_L   ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,APP_PRV ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL ,_LGUI_A ,_LALT_R ,_LSFT_S ,_LCTL_T ,KC_G    ,KC_ENT  ,                          KC_ENT  ,KC_M    ,_RCTL_N ,_RSFT_E ,_RALT_I ,_RGUI_O ,KC_QUOT ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,KC_MINS ,KC_EQL  ,        KC_LBRC ,KC_RBRC ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        LGUI_PL ,KC_PMNS ,KC_PAST ,KC_PSLS ,     KC_LALT ,    KC_SPC  ,NAV_L   ,        SYM_L   ,KC_BSPC ,    KC_ALGR ,     KC_DEL  ,KC_INS  ,KC_HOME ,KC_END
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,APP_NXT ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_ESC  ,                          ADJ_L   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,APP_PRV ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_ENT  ,                          KC_ENT  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_MINS ,KC_EQL  ,        KC_LBRC ,KC_RBRC ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        LGUI_PL ,KC_PMNS ,KC_PAST ,KC_PSLS ,     KC_LALT ,    KC_SPC  ,NAV_L   ,        SYM_L   ,KC_BSPC ,    KC_ALGR ,     KC_DEL  ,KC_INS  ,KC_HOME ,KC_END
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,KC_BSLS ,KC_1    ,KC_2    ,KC_3    ,KC_SLSH ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_F12  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,KC_LBRC ,KC_4    ,KC_5    ,KC_6    ,KC_RBRC ,_______ ,                          _______ ,XXXXXXX ,OSM_CTL ,OSM_SFT ,OSM_ALT ,OSM_GUI ,KC_F13  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,KC_GRV  ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _ENTRY_ ,_______ ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_HOME ,KC_UP   ,KC_END  ,XXXXXXX ,KC_F12  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,OSM_GUI ,OSM_ALT ,OSM_SFT ,OSM_CTL ,XXXXXXX ,_______ ,                          _______ ,KC_BSPC ,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_DEL  ,KC_F13  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,XXXXXXX ,XXXXXXX ,CAPSWRD ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_PGUP ,XXXXXXX ,KC_PGDN ,XXXXXXX ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_ENTRY_ ,        _______ ,_______ ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            KC_VOLD ,KC_VOLU ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,CG_SWAP ,CG_NORM ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          _ENTRY_ ,KC_MPRV ,KC_MNXT ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          KC_MPLY ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,DEF_COL ,DEF_QWE ,XXXXXXX ,DB_TOGG ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            set_led_off;
            break;
        case _COLEMAKDH:
            set_led_off;
            break;
        case _SYMB:
            set_led_green;
            break;
        case _NAV:
            set_led_blue;
            break;
        case _ADJUST:
            set_led_red;
            break;
        default:
            break;
    }
    return state;
}

void caps_word_set_user(bool active) {
    if (active) {
        set_led_white;
    } else {
        set_led_off;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CG_NORM:
            if (record->event.pressed) {
                isOnMac = false;
            }
            return true;
        case CG_SWAP:
            if (record->event.pressed) {
                isOnMac = true;
            }
            return true;
        case APP_NXT:
        case APP_PRV:
            // Only accept while help RALT
            if (get_mods() & MOD_BIT(KC_RALT) || isSwappingApps) {
                dprint("+KC_RALT");
                if (record->event.pressed) {
                    dprint("press\n");
                    isSwappingApps = true;
                    unregister_code(KC_RALT);
                    unregister_code(KC_PGUP);
                    unregister_code(KC_PGUP);

                    register_code(isOnMac ? KC_LGUI : KC_LALT);
                    if(keycode == APP_PRV) {
                        register_code(KC_LSFT);
                    }
                    register_code(KC_TAB);
                    if(keycode == APP_PRV) {
                        unregister_code(KC_LSFT);
                    }
                } else {
                    unregister_code(KC_TAB);
                }
                return true;
            } else {
                if (keycode == APP_NXT) {
                    if (record->event.pressed) {
                        register_code(KC_PGUP);
                    } else {
                        unregister_code(KC_PGUP);
                    }
                    return true;
                }
                if (keycode == APP_PRV) {
                    if (record->event.pressed) {
                        register_code(KC_PGDN);
                    } else {
                        unregister_code(KC_PGDN);
                    }
                    return true;
                }
            }
        case KC_RALT:
            if(!record->event.pressed && isSwappingApps) {
                dprint("completely release\n");
                isSwappingApps = false;
                unregister_code(isOnMac ? KC_LGUI : KC_LALT);
                unregister_code(KC_TAB);
            }
        default:
            return true; // Process all other keycodes normally
    }
}
