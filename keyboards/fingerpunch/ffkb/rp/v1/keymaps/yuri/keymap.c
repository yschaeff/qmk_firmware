/**
 * BUILD INSTRUCTIONS
 *
 * cd /home/yuri/repo/keyboard/qmk_firmware
 * make -j 8 fingerpunch/ffkb/rp/v1:yuri CIRQUE_ENABLE=yes FP_TRACKBALL_ENABLE=no RGB_MATRIX_ENABLE=yes FP_EVQ=yes AUDIO_ENABLE=yes HAPTIC_ENABLE=no
 * cp fingerpunch_ffkb_rp_v1_yuri.uf2 /media/yuri/rp2040/
 */

// ctags -R quantum

// TODO Caps word
// https://docs.qmk.fm/features/caps_word

#include QMK_KEYBOARD_H
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "override.h"

// Some interesting keys
// QK_AUDIO_CLICKY_TOGGLE

#define KC_PRNT         KC_PRINT_SCREEN

enum custom_keycodes {
    //vim
    VIM_W = SAFE_RANGE, VIM_WQ,
    //home brew modifiers
    W_MOD_S, W_MOD_X, W_MOD_Y, W_MOD_Z,
};



//  MO(layer): base + (layer)       until release
//  TO(layer): base + layer         forever
// OSL(layer): layers + (layer)     until key press
//  TG(layer): layers -+ layer      forever

#define LOWER           MO(_LOWER)
#define RAISE           MO(_RAISE)
#define TQWERTY         TO(_QWERTY)

#define TWINGS0         TO(_WINGS0)
/*#define TWINGS1         TO(_WINGS1)*/
#define TWINGS2         TO(_WINGS2)

#define MWINGS0         MO(_WINGS0)
#define MWINGS1         MO(_WINGS1)
/*#define MWINGS2         MO(_WINGS2)*/

/*#define OWINGS2         OSL(_WINGS2)*/

#define W_PROG          LCTL(KC_8)
#define W_CANCL         LSFT_T(KC_SPC)
#define W_CAM           LCTL(KC_BTN3)

#define W_OBJ           KC_B
#define W_FACE          KC_F
#define W_VERTX         KC_V
#define W_EDGE          KC_E

#define W_F1            KC_LBRC
#define W_F2            KC_RBRC
#define W_F3            KC_SCLN
#define W_F4            KC_QUOT
#define W_F5            KC_BSLS
#define W_AX_F1         KC_COMM
#define W_AX_F2         KC_DOT
#define W_AX_F3         KC_SLSH
#define W_AX_F4         KC_GRV
#define W_AX_F5         KC_MINS
#define W_AX_F6         KC_EQL

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE = AUTO_MOUSE_DEFAULT_LAYER,

    _WINGS0,
    _WINGS1,
    _WINGS2,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |  TAB |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |BckSpc|
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |  ESC |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |  SFT |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  | SFT  |
 * `-----------------------------------------'             `-----------------------------------------'
 *          ,------.        ,--------------------.    ,--------------------.        ,------.
 *          | MUTE |        |   \  | Enter| LOWER|    | RAISE| Space| Del  |        | DELW |
 *          `------'        `--------------------'    `--------------------.        `------'
 */

// Default config uses home row mods. So hold each of the keys on the home row to use ctrl, gui, alt, or shift
[_QWERTY] = LAYOUT_ffkb(
  KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,             KC_BSPC,
  KC_ESC,  LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F), KC_G,         KC_H,    LGUI_T(KC_J), RALT_T(KC_K), RCTL_T(KC_L), RSFT_T(KC_SCLN),  KC_QUOT,
  KC_LSFT, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,          VIM_W,
           KC_MUTE,                    KC_BSLS,      KC_SPC,       LOWER,        RAISE,   KC_ENT,       KC_DEL,                     LCTL(KC_BSPC)
),

/* Raise
 *
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      | Tab  | Left | Up   | Down | Rght |             |      |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      | Home | PgUp | PgDn | End  |             |      |      |      |      |      |      |
 * `-----------------------------------------'             `-----------------------------------------'
 *          ,------.        ,--------------------.    ,--------------------.        ,------.
 *          | MUTE |        |   \  | Enter| LOWER|    | RAISE| Space| Del  |        | DELW |
 *          `------'        `--------------------'    `--------------------.        `------'
 */

[_RAISE] = LAYOUT_ffkb(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, KC_TAB,  KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
  _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,       _______, _______, _______, _______, _______, VIM_WQ,
           _______,          _______, _______, _______,      _______, _______, _______,          _______
),

/* Lower
 *
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |      |      |      |      |             |      |   _  |   +  |   {  |   }  |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |  Caps|      |      |      |      |             |      |      |      |   |  |   "  |      |
 * `-----------------------------------------'             `-----------------------------------------'
 *          ,------.        ,--------------------.    ,--------------------.        ,------.
 *          | MUTE |        |   \  | Enter| LOWER|    | RAISE| Space| Del  |        | DELW |
 *          `------'        `--------------------'    `--------------------.        `------'
 */
[_LOWER] = LAYOUT_ffkb(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
  _______, KC_CAPS, _______, _______, _______, _______,      _______, _______, _______, KC_PIPE, KC_DQT,  KC_PRNT,
           _______,          _______, _______, _______,      _______, _______, _______,          _______
),

/* Adjust (Lower + Raise)

 * ,-----------------------------------------.             ,-----------------------------------------.
 * |      | RGB_T| RGB_R| RGB_F|      |QWERTY|             |   F1 |  F2  |  F3  |  F4  |  F5  |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      | SPD_I| HUE_I| SAT_I| VAL_I|COLEMK|             |   F6 |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      | SPD_D| HUE_D| SAT_D| VAL_D|      |             |  F11 |  F12 |      |      | Reset|      |
 * `-----------------------------------------'             `-----------------------------------------'
 *          ,------.        ,--------------------.    ,--------------------.        ,------.
 *          | MUTE |        |   \  | Enter| LOWER|    | RAISE| Space| Del  |        | DELW |
 *          `------'        `--------------------'    `--------------------.        `------'
 */
[_ADJUST] =  LAYOUT_ffkb(
  _______, RGB_TOG, RGB_RMOD, RGB_MOD, _______, TQWERTY,      KC_F1,   KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,
  _______, RGB_SPI, RGB_HUI,  RGB_SAI, RGB_VAI, _______,      KC_F6,   KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
  _______, RGB_SPD, RGB_HUD,  RGB_SAD, RGB_VAD, TWINGS0,      KC_F10,  KC_F12 , _______, _______, QK_BOOT, _______,
           _______,           _______, _______, _______,      _______, _______, _______,          _______
),

[_MOUSE] =  LAYOUT_ffkb(
  _______, _______, KC_WH_U, _______, KC_WH_D, _______,       _______, _______, _______, _______, _______, _______,
  _______, KC_WH_L, KC_BTN3, KC_BTN2, KC_BTN1, KC_WH_R,       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
           _______,          _______, _______, _______,       _______, _______, _______,          _______
),


/*WINGS base layer*/
[_WINGS0] =  LAYOUT_ffkb(
  KC_TAB , W_F1   , W_F2   , W_F3   , W_F4   , W_F5   ,       _______, _______, _______, _______, _______, _______,
  KC_ESC , W_MOD_S, W_MOD_Z, W_MOD_Y, W_MOD_X, W_AX_F1,       _______, _______, _______, _______, _______, _______,
  _______, W_AX_F2, W_AX_F3, W_AX_F4, W_AX_F5, W_AX_F6,       _______, _______, _______, _______, _______, _______,
           _______,          _______, W_CANCL, MWINGS1,       TQWERTY, _______, _______,          _______
),

[_WINGS1] =  LAYOUT_ffkb(
  W_PROG , _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
  _______, W_OBJ  , W_VERTX, W_EDGE , W_FACE , W_CAM  ,       _______, _______, _______, _______, _______, _______,
  _______, KC_DEL , _______, _______, _______, KC_BSPC,       _______, _______, _______, _______, _______, _______,
           _______,          _______, _______, _______,       _______, _______, _______,          _______
),

[_WINGS2] =  LAYOUT_ffkb(
  KC_TAB , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,       _______, _______, _______, _______, _______, _______,
  _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,       _______, _______, _______, _______, _______, _______,
  _______, KC_DEL , KC_PLUS, KC_MINS, KC_DOT , KC_BSPC,       _______, _______, _______, _______, _______, _______,
           _______,                 , TWINGS0, KC_ENT ,       TQWERTY, _______, _______,          _______
)

};

layer_state_t
layer_state_set_user(layer_state_t state)
{
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

uint8_t homebrew_mods = 0;

/*PLAN: everything is a custom key.*/
/*For mods set a bitmap and return false*/
/*for others add modifiers bases on bitmap!*/

void
mod_toggle(const uint8_t n)
{
    const float notes[] = {440.0, 493.883, 523.251, 587.33};
    audio_play_click(0, notes[n], 200);

    homebrew_mods ^= 1<<n;
}

inline uint8_t
mod_get(const uint8_t n)
{
    // By shifting the mask this can be optimized to 1 instruction
    return homebrew_mods & (1<<n);
}
void
mod_clear(void)
{
    if (homebrew_mods) // only play sound when actually clearing it.
        audio_play_click(0, 391.995, 400);
    homebrew_mods = 0;
}
bool
mod_clear_cb(bool pressed, void *context)
{
    mod_clear();
    return true;
}

bool
rgb_matrix_indicators_user(void)
{

    if (layer_state_is(_WINGS0)) {
        if (homebrew_mods)
        {
            if (mod_get(0)) { rgb_matrix_set_color( 4,  0xFF, 0xFF, 0xFF); } // S
            if (mod_get(1)) { rgb_matrix_set_color(13,  0xFF, 0x00, 0x00); } // X
            if (mod_get(2)) { rgb_matrix_set_color(10,  0x00, 0xFF, 0x00); } // Y
            if (mod_get(3)) { rgb_matrix_set_color( 7,  0x00, 0x00, 0xFF); } // Z
        }

        rgb_matrix_set_color(2,  0xFF, 0x00, 0x00); //PROG

        /*rgb_matrix_set_color(18,  0x00, 0x00, 0x00);*/
        rgb_matrix_set_color(19,  0x00, 0xFF, 0x00); //cancel/deselect
        rgb_matrix_set_color(20,  0x00, 0x00, 0xFF); //cancel/deselect

        for (int i = 21; i<42; i++) {
            rgb_matrix_set_color(i,  0x00, 0x00, 0x00);
        }
        rgb_matrix_set_color(21,  0x00, 0xFF, 0xFF); //TQWERTY
    }
    return false; // I think return is ignored
}

bool
select_context_keys(uint16_t keycode)
{
    switch (keycode) {
        case W_F1: case W_F2: case W_F3: case W_F4: case W_F5:
            return true;
        default:
            return false;
    }
}
bool
axis_context_keys(uint16_t keycode)
{
    switch (keycode) {
        case W_AX_F1: case W_AX_F2: case W_AX_F3: case W_AX_F4: case W_AX_F5: case W_AX_F6:
            return true;
        default:
            return false;
    }
}

bool mods[] = {0, 0, 0, 0, 0, 0, 0};

OVERRIDE(override_select_f1, W_F1, _WINGS0, mod_clear_cb)
OVERRIDE(override_select_f2, W_F2, _WINGS0, mod_clear_cb)
OVERRIDE(override_select_f3, W_F3, _WINGS0, mod_clear_cb)
OVERRIDE(override_select_f4, W_F4, _WINGS0, mod_clear_cb)
OVERRIDE(override_select_f5, W_F5, _WINGS0, mod_clear_cb)
OVERRIDE(override_axis_f1, W_AX_F1, _WINGS0, mod_clear_cb)
OVERRIDE(override_axis_f2, W_AX_F2, _WINGS0, mod_clear_cb)
OVERRIDE(override_axis_f3, W_AX_F3, _WINGS0, mod_clear_cb)
OVERRIDE(override_axis_f4, W_AX_F4, _WINGS0, mod_clear_cb)
OVERRIDE(override_axis_f5, W_AX_F5, _WINGS0, mod_clear_cb)
OVERRIDE(override_axis_f6, W_AX_F6, _WINGS0, mod_clear_cb)

const key_override_t **key_overrides = (const key_override_t *[]){
    OVERRIDE_PTRS(override_select_f1),
    OVERRIDE_PTRS(override_select_f2),
    OVERRIDE_PTRS(override_select_f3),
    OVERRIDE_PTRS(override_select_f4),
    OVERRIDE_PTRS(override_select_f5),
    OVERRIDE_PTRS(override_axis_f1),
    OVERRIDE_PTRS(override_axis_f2),
    OVERRIDE_PTRS(override_axis_f3),
    OVERRIDE_PTRS(override_axis_f4),
    OVERRIDE_PTRS(override_axis_f5),
    OVERRIDE_PTRS(override_axis_f6),
    NULL
};

void
set_mod(int n) {
    for (int i = 0; i < 7; i++) {
        mods[i] = i==n;
    }
}

void
update_overrides(void)
{
    switch (homebrew_mods) {
        case 1: set_mod(0); break;
        case 2: set_mod(1); break;
        case 4: set_mod(2); break;
        case 8: set_mod(3); break;
        case 3: set_mod(4); break;
        case 5: set_mod(5); break;
        case 9: set_mod(6); break;
        default:
            mod_clear();
            set_mod(-1); // clears all
    }
}

bool
process_record_user(uint16_t keycode, keyrecord_t *record)
{

    if (layer_state_is(_WINGS0)) {
        if (record->event.pressed) {
            switch (keycode) {
                case W_MOD_S: mod_toggle(0); return false;
                case W_MOD_X: mod_toggle(1); return false;
                case W_MOD_Y: mod_toggle(2); return false;
                case W_MOD_Z: mod_toggle(3); return false;
                case W_CANCL: // Surprisingly the key up event never gets emitted. GOOD.
                    if (homebrew_mods) {
                        mod_clear();
                        return false;
                    }
                /*default: // any key should clear*/
                    /*mod_clear();*/
            }
        }
        update_overrides();
    }

    //ALL other layers

    switch (keycode) {
        case VIM_W:
            if (record->event.pressed) {
                SEND_STRING(":w");
                rgb_matrix_set_color(33, 0xFF, 0x00, 0x00);
            } else {
                SEND_STRING("\n");
                audio_play_click(0, 440.0, 200);
            }
            break;
        case VIM_WQ:
            if (record->event.pressed) {
                SEND_STRING(":wq");
            } else {
                SEND_STRING("\n");
                audio_play_click(0, 460.0, 200);
            }
            break;
    }
    return true;
}
