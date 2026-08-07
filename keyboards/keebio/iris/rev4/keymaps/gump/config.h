// Keymap-level overrides for Iris rev4 (gump).

#pragma once

// Split underglow: 6 WS2812 LEDs per half, 12 total.
#define RGBLED_NUM 12
#define RGBLED_SPLIT { 6, 6 }

// Sync RGB mode/hue/sat/val from master to slave over TRRS.
#define RGBLIGHT_SPLIT

// Turn LEDs off when the host goes to sleep.
#define RGBLIGHT_SLEEP

// Nicer defaults: static light on first boot until you cycle with RGB_MOD.
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#define RGBLIGHT_DEFAULT_HUE  213   // blue-ish
#define RGBLIGHT_DEFAULT_SAT  255
#define RGBLIGHT_DEFAULT_VAL  128
