// Caps word settings
// #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
// #define CAPS_WORD_IDLE_TIMEOUT 3000  // 3 seconds.

#define TAPPING_TOGGLE 2
// #define RETRO_TAPPING # can't quickly hold and click mouse button, as mouse isn'r recognized by QMK

#define TAPPING_TERM 175

#define COMBO_COUNT 2
#define COMBO_STRICT_TIMER
// #define COMBO_ONLY_FROM_LAYER 0

/*
    This is the c configuration file for the keymap

    Copyright 2012 Jun Wako <wakojun@gmail.com>
    Copyright 2015 Jack Humbert

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

#pragma once

// #define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// #define TAPPING_FORCE_HOLD
// #define TAPPING_TERM 100

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif

// #define OLED_FONT_H "keyboards/crkbd/keymaps/zielak/glcdfont.c"

// #define OLED_FONT_WIDTH 8
// #define OLED_FONT_HEIGHT 10
