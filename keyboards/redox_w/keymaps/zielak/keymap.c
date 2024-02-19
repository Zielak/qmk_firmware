#include QMK_KEYBOARD_H

#define _COLEMAKDH 0
#define _QWERTY 1
#define _NAV 2
#define _NUM 3
#define _FNK 4
#define _SYM 5

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
    APP_NXT,
    APP_PRV,
};

// App swapping and Print screen are different on Mac...
static uint16_t ctrlKey        = KC_LGUI;
static bool     isOnMac        = true;
static bool     isSwappingApps = false;
static bool     isCapsWordUp   = false;

// Shortcuts to make keymap more readable
#define NAV_L MO(_NAV)
#define NUM_L MO(_NUM)
#define FNK_L MO(_FNK)
#define SYM_L MO(_SYM)

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

  [_COLEMAKDH] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_8    ,KC_9    ,KC_0    ,KC_MINS ,KC_EQL  ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,KC_6    ,                          KC_7    ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_BSPC ,KC_DEL  ,
    // ├────────┼--------+--------+--------+--------+----────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LGUI ,_LCTL   ,_LALT   ,_LSFT   ,_LGUI   ,KC_G    ,KC_ESC  ,                          KC_ENT  ,KC_M    ,_RGUI   ,_RSFT   ,_RALT   ,_RCTL   ,KC_RGUI ,
    // ├────────┼--------+--------+--------+--------+----────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,KC_PGUP ,KC_PGDN ,        KC_HOME ,KC_END  ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LALT ,     FNK_L   ,    NAV_L   ,KC_SPACE,        NUM_L   ,SYM_L   ,    KC_ALGR ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,XXXXXXX ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_6    ,                          KC_7    ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LGUI ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_ESC  ,                          KC_ENT  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_RGUI ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_PGUP ,KC_PGDN ,        KC_HOME ,KC_END  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LALT ,     FNK_L   ,    NAV_L   ,KC_SPACE,        NUM_L   ,SYM_L   ,    KC_ALGR ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,K_TERMI ,APP_PRV ,APP_NXT ,K_PRSCR ,XXXXXXX ,KC_F6   ,                          KC_F7   ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_BSPC ,_______ ,
    // ├────────┼--------+--------+--------+--------+-------─┼────────┤                         ├────────┼--------+--------+--------+--------+-------─┼────────┤
        _______ ,KC_LCTL ,KC_LALT ,KC_LSFT ,KC_LGUI ,KC_ESC  ,_______ ,                          _______ ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_DEL  ,_______ ,
    // ├────────┼--------+--------+--------+--------+-------─┼────────┼────────┐       ┌────────┼────────┼--------+--------+--------+--------+-------─┼────────┤
        _______ ,K_UNDO  ,K_CUT   ,K_COPY  ,K_PASTE ,K_REDO  ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,K_INDEL ,K_INDER ,KC_INS  ,_______ ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    _ENTRY_ ,_______ ,        XXXXXXX ,CW_TOGG ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PPLS ,KC_PERC ,KC_F6   ,                          KC_F7   ,XXXXXXX ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PENT ,_______ ,
    // ├────────┼--------+--------+--------+--------+-------─┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PMNS ,KC_EQL  ,_______ ,                          _______ ,XXXXXXX ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,_______ ,
    // ├────────┼--------+--------+--------+--------+-------─┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PSLS ,KC_PAST ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PMNS ,_______ ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_P0   ,    KC_DOT  ,_______ ,        _ENTRY_ ,XXXXXXX ,    KC_P0   ,     KC_PDOT ,KC_PSLS ,KC_PAST ,XXXXXXX
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_FNK] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_F6   ,                          KC_F7   ,GU_TOGG ,RGB_TOG ,KC_BRID ,KC_BRIU ,DT_UP   ,_______ ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼--------+--------+--------+--------+-------─┼────────┤
        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          XXXXXXX ,CG_NORM ,KC_MUTE ,KC_VOLD ,KC_VOLU ,DT_DOWN ,_______ ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼--------+--------+--------+--------+-------─┼────────┤
        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,CG_SWAP ,KC_MPLY ,KC_MPRV ,KC_MNXT ,DT_PRNT ,_______ ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _ENTRY_ ,    XXXXXXX ,_______ ,        DF_QWER ,DF_COLE ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYM] = LAYOUT(
    // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______ ,KC_QUES ,KC_EXLM ,K_ARROW ,KC_LCBR ,KC_PIPE ,_______ ,                          _______ ,KC_AMPR ,KC_RCBR ,KC_DQUO ,KC_AMPR ,KC_BSPC ,_______ ,
    // ├────────┼--------+--------+--------+--------+-------─┼────────┤                         ├────────┼--------+--------+--------+--------+-------─┼────────┤
        _______ ,KC_AT   ,KC_DLR  ,KC_UNDS ,KC_LPRN ,KC_SCLN ,_______ ,                          _______ ,KC_COLN ,KC_RPRN ,KC_GRV  ,KC_QUOT ,KC_DEL  ,_______ ,
    // ├────────┼--------+--------+--------+--------+-------─┼────────┼────────┐       ┌────────┼────────┼--------+--------+--------+--------+-------─┼────────┤
        _______ ,KC_TILD ,KC_HASH ,KC_CIRC ,KC_LBRC ,KC_LT   ,_______ ,_______ ,        _______ ,_______ ,KC_GT   ,KC_RBRC ,KC_PSLS ,KC_PAST ,KC_BSLS ,_______ ,
    // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    CW_TOGG ,_______ ,        XXXXXXX ,_ENTRY_ ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
    // clang-format on

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            set_led_off;
            break;
        case _COLEMAKDH:
            set_led_off;
            break;
        case _SYM:
            set_led_green;
            break;
        case _NAV:
            set_led_blue;
            break;
        case _FNK:
            set_led_red;
            break;
        default:
            break;
    }
    return state;
}

void caps_word_set_user(bool active) {
    isCapsWordUp = active;
    if (active) {
        set_led_white;
    } else {
        set_led_off;
    }
}

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

// Combo stuff

const uint16_t PROGMEM combo_enter[]           = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_tab[]             = {KC_X, KC_C, COMBO_END};
combo_t                key_combos[COMBO_COUNT] = {
    COMBO(combo_enter, KC_ENT), COMBO(combo_tab, KC_TAB),
    // COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_layer = get_highest_layer(layer_state);

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
        case K_PRSCR:
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
                // return false;
            }
            return true;
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
