
#pragma once

#define CB(name, action, ...) C_##name,
enum user_combos {
#include "combos.def"
};
#undef CB

#define CB(name, action, ...) const uint16_t PROGMEM name##_combo[] = {__VA_ARGS__, COMBO_END};
#include "combos.def"
#undef CB

combo_t key_combos[] = {
#define CB(name, action, ...) COMBO(name##_combo, action),
#include "combos.def"
#undef CB
};
