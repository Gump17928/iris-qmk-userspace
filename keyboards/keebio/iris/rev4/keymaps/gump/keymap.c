// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Iris rev4 keymap ported from the Gump Sofle ZMK config.
// Sofle has 5 thumb keys per side; Iris has 3. Outer thumbs (GUI/ALT/CTRL) were
// dropped in favor of the three most-used: (CTRL/MOD, LOWER/RAISE, SPACE/ENT).
// No encoders on Iris, so the sofle MEDIA layer and sensor bindings are gone.
// No BLE / RGB on wired Iris rev4, so those keys are transparent.

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAMING,
};

// Classic QMK tri-layer: holding LOWER + RAISE together activates ADJUST.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define TG_GAME TG(_GAMING)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE - mirrors Sofle default_layer.
   *  Top-right corner (was TG_MEDIA on Sofle) -> KC_DEL, since no encoders.
   *  Row 3 middle keys (were C_MUTE / ext_power) -> KC_MUTE / KC_MPLY.
   *  Left thumbs (was GUI/ALT/CTRL/LOWER/SPACE) -> LCTRL / LOWER / SPACE.
   *  Right thumbs (was ENT/RAISE/CTRL/ALT/GUI) -> ENT / RAISE / RCTL.
   */
  [_BASE] = LAYOUT(
      KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                             KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL,
      KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                             KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
      KC_TAB,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                             KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
      KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_MUTE,        KC_MPLY,  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                                KC_LCTL, LOWER,  KC_SPC,                KC_ENT,   RAISE,  KC_RCTL
  ),

  /* LOWER - F-keys, numbers, symbols.  Mirrors Sofle lower_layer. */
  [_LOWER] = LAYOUT(
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
      _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
      _______,  KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,    _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                                  _______, _______, _______,             _______, _______, _______
  ),

  /* RAISE - nav / editing / GAMING toggle.  Mirrors Sofle raise_layer,
   * minus BT (wired) and RGB.  undo/cut/copy/paste become plain C(k). */
  [_RAISE] = LAYOUT(
      _______,  _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, TG_GAME,
      _______,  KC_INS,  KC_PSCR, KC_APP,  _______, _______,                      KC_PGUP, _______, KC_UP,   _______, KC_0,    _______,
      _______,  KC_LALT, KC_LCTL, KC_LSFT, _______, KC_CAPS,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_BSPC,
      _______,  C(KC_Z), C(KC_X), C(KC_C), C(KC_V), _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______,             _______, _______, _______
  ),

  /* ADJUST - auto-activated by LOWER + RAISE.  Sofle used this for BT/RGB;
   * on Iris we expose QK_BOOT in the corners so we can enter DFU from the
   * keyboard for future flashes.  Everything else transparent. */
  [_ADJUST] = LAYOUT(
      QK_BOOT,  _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, QK_BOOT,
      _______,  _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
      _______,  _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
      _______,  _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______,             _______, _______, _______
  ),

  /* GAMING - toggled via TG_GAME on RAISE.  Mirrors Sofle gaming_layer:
   * left column becomes ESC/TAB/LSHFT/LCTRL instead of GRV/ESC/TAB/LSHFT,
   * and left inner thumb becomes KC_CAPS instead of KC_LCTL. */
  [_GAMING] = LAYOUT(
      KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                             KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   TG_GAME,
      KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                             KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
      KC_LSFT,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                             KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
      KC_LCTL,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_MUTE,        KC_MPLY,  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                                KC_CAPS, LOWER,  KC_SPC,                KC_ENT,   RAISE,  KC_RCTL
  ),
};
