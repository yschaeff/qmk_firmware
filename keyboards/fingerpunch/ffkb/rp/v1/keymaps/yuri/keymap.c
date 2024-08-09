#include QMK_KEYBOARD_H

// Some interesting keys
// QK_AUDIO_CLICKY_TOGGLE

#define KC_PRNT         KC_PRINT_SCREEN

enum custom_keycodes {
    VIM_W = SAFE_RANGE,
    VIM_WQ,

};

#define W_0(kc)        (    (    (    (kc))))
#define W_1(kc)        (    (    (LCTL(kc))))
#define W_2(kc)        (    (LALT(    (kc))))
#define W_3(kc)        (LSFT(    (    (kc))))
#define W_4(kc)    LGUI(    (    (    (kc))))
#define W_5(kc)    LGUI(    (    (LCTL(kc))))
#define W_6(kc)    LGUI(    (LALT(    (kc))))
#define W_7(kc)    LGUI(LSFT(    (    (kc))))


bool
process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case VIM_W:
            if (record->event.pressed) {
                SEND_STRING(":w");
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
};


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE = AUTO_MOUSE_DEFAULT_LAYER,

    _WINGS0,
    _WINGS2,
};

//  MO(layer): base + (layer)       until release
//  TO(layer): base + layer         forever
// OSL(layer): layers + (layer)     until key press
//  TG(layer): layers -+ layer      forever

#define LOWER           MO(_LOWER)
#define RAISE           MO(_RAISE)
#define TQWERTY         TO(_QWERTY)

#define TWINGS0         TO(_WINGS0)
#define OWINGS2         OSL(_WINGS2)
#define NORMAL          TG(_WINGS0)

#define W_MOD_X     OSM(MOD_LCTL)
#define W_MOD_Y     OSM(MOD_LSFT)
#define W_MOD_Z     OSM(MOD_LALT)


#define W_PROG          LCTL(KC_8)

#define W_DEL           KC_DEL
#define W_GROW          KC_PLUS
#define W_SHRNK         KC_MINS
#define W_LOOP          KC_L
#define W_RING          KC_G
#define W_UNDO          LCTL(LALT(KC_Z))
#define W_REDO          LCTL(LSFT(KC_Z))
#define W_RECAL         XXXXXXX
#define W_STORE         XXXXXXX

#define W_NUM           XXXXXXX
#define W_AX_X          TO(_WINGSX)
#define W_AX_Y          TO(_WINGSY)
#define W_AX_Z          TO(_WINGSZ)

#define W_VERT          KC_V
#define W_EDGE          KC_E
#define W_FACE          KC_F
#define W_OBJ           KC_B
#define W_CANCL         KC_SPC

#define W_CAM           LCTL(KC_BTN3)
#define W_FRAME         LSFT(KC_A)
#define W_VW_X          KC_X
#define W_VW_Xi         LSFT(KC_X)
#define W_VW_Y          KC_Y
#define W_VW_Yi         LSFT(KC_Y)
#define W_VW_Z          KC_Z
#define W_VW_Zi         LSFT(KC_Z)

#define W_MOVE          KC_1
#define W_ROTAT         KC_2
#define W_SCALE         KC_3
#define W_FLTTN         KC_4
#define W_EXTRD         KC_5

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
  W_PROG , W_DEL  , W_GROW  , W_LOOP , W_UNDO , W_RECAL,       _______, _______, _______, _______, _______, _______,
  KC_BTN1, W_NUM  , W_MOD_Z , W_MOD_Y, W_MOD_X, W_CAM  ,       _______, _______, _______, _______, _______, _______,
  KC_BTN2, W_FLTTN, W_SCALE , W_ROTAT, W_MOVE , W_EXTRD,       _______, _______, _______, _______, _______, _______,
           _______,           _______, W_CANCL, KC_LGUI,       NORMAL , _______, _______,          _______
),

[_WINGS2] =  LAYOUT_ffkb(
  _______, KC_DEL , KC_LEFT, KC_RGHT, KC_DOT , KC_BSPC,       _______, _______, _______, _______, _______, _______,
  _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,       _______, _______, _______, _______, _______, _______,
  _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,       _______, _______, _______, _______, _______, _______,
           _______,          _______, TWINGS0, KC_ENT ,       NORMAL , _______, _______,          _______
),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
