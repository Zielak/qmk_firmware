#include QMK_KEYBOARD_H
#include "print.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAKDH 0
#define _QWERTY 1
#define _GAME1 2
#define _GAME2 3
#define _SYMB 4
#define _NAV 5
#define _ADJUST 6
#define _REST 7

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
};

// App swapping and Print screen are different on Mac...
static bool isOnMac = true;
static bool isSwappingApps = false;
static uint16_t ctrlKey = KC_LCTL;


// Shortcuts to make keymap more readable
#define SYM_L   TT(_SYMB)
#define NAV_L   TT(_NAV)
#define ADJ_L   LT(_ADJUST, KC_ESC) // MO(_ADJUST)
#define RST_L   MO(_REST)
#define GM2_L   MO(_GAME2)

// Which key do you use to enter a layer
# define _ENTRY_ _______
// Inaccessible or hard to reach key in this combo
# define XINACCX XXXXXXX

#define DEF_COL DF(_COLEMAKDH)
#define DEF_QWE DF(_QWERTY)
#define DEF_GAM DF(_GAME1)

// ctrl 0.3  0.0 = 0.3
// alt  0.4  0.2 = 0.6
// shft 0.8  3.0 = 3.8
// gui  7.2  0.0 = 7.2

#define _LGUI LGUI_T(KC_Z) // KC_Z
#define _LALT RALT_T(KC_X) // KC_X  // because I type PL letters on windows
#define _LSFT LSFT_T(KC_C) // KC_C
#define _LCTL LCTL_T(KC_D) // KC_D

#define _RCTL RCTL_T(KC_H) // KC_H
#define _RSFT RSFT_T(KC_COMM) // KC_COMM
#define _RALT RALT_T(KC_DOT) // KC_DOT
#define _RGUI RGUI_T(KC_SLASH) // KC_SLASH

// Home row for nav layer
#define NA_LGUI LGUI_T(KC_P7)
#define NA_LALT RALT_T(KC_P8) // because I type PL letters on windows
#define NA_LSFT LSFT_T(KC_P9)
#define NA_LCTL LCTL_T(KC_PSLS)

#define OSM_CTL OSM(MOD_RCTL)
#define OSM_ALT OSM(MOD_RALT)
#define OSM_SFT OSM(MOD_RSFT)
#define OSM_GUI OSM(MOD_RGUI)

#define ENT_SFT MT(MOD_LSFT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAKDH] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,XXXXXXX ,                          XXXXXXX ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSPC ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LCTL ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G    ,XXXXXXX ,                          XXXXXXX ,KC_M    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LSFT ,_LGUI   ,_LALT   ,_LSFT   ,_LCTL   ,KC_V    ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_K    ,_RCTL   ,_RSFT   ,_RALT   ,_RGUI   ,ADJ_L   ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LALT ,     NAV_L   ,    KC_SPC  ,XXXXXXX ,        XXXXXXX ,ENT_SFT ,    SYM_L   ,     KC_GRAVE ,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

    [_QWERTY] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,XXXXXXX ,                          XXXXXXX ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,XXXXXXX ,                          XXXXXXX ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLASH,ADJ_L   ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LALT ,     NAV_L   ,    KC_SPC  ,XXXXXXX ,        XXXXXXX ,ENT_SFT ,    SYM_L   ,     KC_GRAVE ,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

    [_GAME1] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,XXXXXXX ,                          XXXXXXX ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,XXXXXXX ,                          XXXXXXX ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLASH,ADJ_L   ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LALT ,     GM2_L   ,    KC_SPC  ,XXXXXXX ,        XXXXXXX ,ENT_SFT ,    SYM_L   ,     KC_GRAVE,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

    [_GAME2] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_ESC  ,XXXXXXX ,                          XXXXXXX ,KC_HOME ,KC_END  ,KC_UP   ,KC_WH_U ,KC_DEL  ,KC_BSPC ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_4    ,KC_5    ,KC_6    ,KC_MINS ,KC_ENT  ,XXXXXXX ,                          XXXXXXX ,KC_PGUP ,KC_LEFT ,KC_DOWN ,KC_RIGHT,APP_PRV ,APP_NXT ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_7    ,KC_8    ,KC_9    ,KC_EQL  ,KC_BSPC ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_PGDN ,KC_WH_D ,K_INDEL ,K_INDER ,K_PRSCR ,ADJ_L   ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_0    ,     _ENTRY_ ,    _______ ,XXXXXXX ,        XXXXXXX ,_______ ,    RST_L   ,     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

    [_NAV] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PPLS ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_HOME ,KC_END  ,KC_UP   ,KC_WH_U ,KC_DEL  ,KC_BSPC ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_DOT  ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PMNS ,KC_ENT  ,XXXXXXX ,                          XXXXXXX ,KC_PGUP ,KC_LEFT ,KC_DOWN ,KC_RIGHT,APP_PRV ,APP_NXT ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_COLN ,NA_LGUI ,NA_LALT ,NA_LSFT ,NA_LCTL ,KC_PAST ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_PGDN ,KC_WH_D ,K_INDEL ,K_INDER ,K_PRSCR ,ADJ_L   ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_P0   ,     _ENTRY_ ,    _______ ,XXXXXXX ,        XXXXXXX ,_______ ,    RST_L   ,     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

    [_SYMB] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_QUES ,KC_EXLM ,K_ARROW ,KC_PPLS ,KC_PERC ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_TILD ,KC_UNDS ,XXXXXXX ,KC_COLN ,_______ ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_AT   ,KC_DLR  ,KC_AMPR ,KC_PMNS ,KC_PEQL ,XXXXXXX ,                          XXXXXXX ,KC_LPRN ,KC_RPRN ,KC_LBRC ,KC_RBRC ,KC_PIPE ,KC_DQUO ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,XXXXXXX ,KC_HASH ,KC_CIRC ,KC_PSLS ,KC_PAST ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_LCBR ,KC_RCBR ,KC_LABK ,KC_RABK ,KC_BSLS ,_______ ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,     RST_L   ,    _______ ,XXXXXXX ,        XXXXXXX ,_______ ,    _ENTRY_ ,     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

    [_ADJUST] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,CG_SWAP ,CG_NORM ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_VOLD ,KC_VOLU ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,DEF_COL ,DEF_QWE ,DEF_GAM ,DB_TOGG ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_MPRV ,KC_MNXT ,XXXXXXX ,_ENTRY_ ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,KC_MPLY ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

    [_REST] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______ ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,XXXXXXX ,OSM_CTL ,OSM_SFT ,OSM_ALT ,OSM_GUI ,ADJ_L   ,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _ENTRY_ ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    _ENTRY_ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
        case _COLEMAKDH:
        case _GAME1:
            set_led_off;
            break;
        case _SYMB:
            set_led_green;
            break;
        case _NAV:
            set_led_blue;
            break;
        case _ADJUST:
        case _REST:
            set_led_red;
            break;
        case _GAME2:
            set_led_white;
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

bool tap_ctrl_and_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code(ctrlKey);
        tap_code(keycode);
        unregister_code(ctrlKey);
    }
    return false;
}

// K_INDEL
// K_INDER
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
        case APP_NXT:
        case APP_PRV:
            // Only accept while help RALT
            if (get_mods() & MOD_BIT(KC_RALT) || isSwappingApps) {
                dprint("+KC_RALT");
                if (record->event.pressed) {
                    dprint("press\n");
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
                dprint("completely release\n");
                isSwappingApps = false;
                unregister_code(isOnMac ? KC_LGUI : KC_LALT);
                unregister_code(KC_TAB);
            }
        default:
            return true; // Process all other keycodes normally
    }
    return true;
}
