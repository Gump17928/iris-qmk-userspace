// Keymap-level overrides for Iris rev4 (gump).
//
// NOTE: Upstream keebio/iris/rev4 already sets RGBLED_NUM = 12 (via info.json)
// and picks a default RGB mode.  We only add split-sync + sleep here.

#pragma once

// Tell RGB code that the WS2812 chain is physically split: 6 LEDs per half.
// Without this, the slave half's LEDs won't respond to the master.
#define RGBLED_SPLIT { 6, 6 }

// Sync RGB mode / hue / sat / val / speed from master to slave over TRRS.
#define RGBLIGHT_SPLIT

// Turn the underglow off when the host goes to sleep.
#define RGBLIGHT_SLEEP
