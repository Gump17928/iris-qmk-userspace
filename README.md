# iris-qmk-userspace

QMK **external userspace** for a Keebio **Iris rev4** (wired, ATmega32u4).

This is the QMK equivalent of the ZMK `iris-zmk-config` folder — a small
personal repo containing only your keymap, that gets compiled against upstream
`qmk_firmware` by GitHub Actions.

## Layout

```
iris-qmk-userspace/
├─ .github/workflows/build.yml
├─ qmk.json                                      # build target(s)
└─ keyboards/keebio/iris/rev4/keymaps/gump/
   ├─ keymap.c                                   # QWERTY / LOWER / RAISE / ADJUST
   └─ rules.mk                                   # feature flags for this keymap
```

`qmk.json` tells GitHub Actions which `<keyboard, keymap>` pairs to build.

## First-time setup

1. Create an **empty** repo on GitHub, e.g. `iris-qmk-userspace`.
2. From this folder:

   ```powershell
   cd C:\GIT_REPOS\Keyboards\iris-qmk-userspace
   git init
   git add .
   git commit -m "Initial Iris QMK userspace"
   git branch -M main
   git remote add origin https://github.com/<you>/iris-qmk-userspace.git
   git push -u origin main
   ```

3. GitHub → **Actions** tab → the `Build QMK firmware` workflow runs.
4. When it goes green, download the `Firmware` artifact. It contains
   `keebio_iris_rev4_gump.hex`.

## Flashing

Since the Iris rev4 has an ATmega32u4 with the Atmel DFU bootloader:

### Option A — QMK Toolbox (easy, Windows/macOS)

1. Install [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).
2. In QMK Toolbox: **Open** → pick the `.hex` you downloaded.
3. Plug in your Iris **left** half via USB.
4. Put the board into DFU (bootloader) mode by pressing the physical
   **RESET** button on the underside (or bridge the `RST`+`GND` pins).
   Toolbox will show:
   `*** DFU device connected: Atmel Corp. ATmega32U4`
5. Click **Flash**. Wait for `Success`.
6. Unplug the left half, plug in the **right** half, DFU it, click **Flash**
   again. Same `.hex` for both halves — QMK auto-detects which side is which
   using `EE_HANDS` or default master/slave rules.

### Option B — Command line

Requires QMK CLI (`qmk setup` per the docs). Then:

```powershell
qmk flash iris-qmk-userspace\keebio_iris_rev4_gump.hex -bl dfu
```

## Editing the keymap

Edit [keyboards/keebio/iris/rev4/keymaps/gump/keymap.c](keyboards/keebio/iris/rev4/keymaps/gump/keymap.c),
commit, push. GitHub Actions rebuilds; you re-flash. Same loop as your Sofle
ZMK config, just a different toolchain under the hood.

## Local builds (optional)

If you'd rather compile locally:

1. Install [QMK MSYS](https://msys.qmk.fm/) (Windows) — see
   <https://docs.qmk.fm/newbs_getting_started>.
2. `qmk setup` (one-time, clones qmk_firmware into `~/qmk_firmware`).
3. Point QMK at this userspace:

   ```powershell
   qmk config user.overlay_dir=C:\GIT_REPOS\Keyboards\iris-qmk-userspace
   ```

4. Compile:

   ```powershell
   qmk userspace-compile
   ```

   The `.hex` lands in the userspace root.

## QMK → ZMK / QMK mental map

| Concept | QMK (this repo) |
|---|---|
| Layer switch (momentary) | `MO(_LOWER)` |
| Layer + key hold | `LT(_LOWER, KC_ENT)` |
| Mod-tap | `MT(MOD_LCTL, KC_A)` |
| Transparent key | `_______` (aka `KC_TRNS`) |
| Reset to bootloader | `QK_BOOT` |
| Tri-layer (LOWER+RAISE=ADJUST) | `TRI_LAYER_ENABLE = yes` in `rules.mk` + `MO(_ADJUST)` on both LOWER and RAISE (already wired up) |

Full keycode reference: <https://docs.qmk.fm/keycodes>.

## Notes

- If `qmk.json`'s `keebio/iris/rev4` target ever fails with "unknown keyboard",
  run `qmk list-keyboards | grep iris` locally (or check the GitHub Actions
  log) — the correct path for your board may be `keebio/iris/rev5` or similar,
  and if so, update both `qmk.json` and the `keymaps/gump/` folder path.
- `EE_HANDS` (per-side handedness stored in EEPROM) may need setting on first
  flash. See <https://docs.qmk.fm/features/split_keyboard#setting-handedness>
  if the halves swap or one goes dead.
