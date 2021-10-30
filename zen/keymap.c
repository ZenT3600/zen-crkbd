/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H

#define _BASE 1
#define _LOWER 2
#define _RAISE 4
#define _ADJUST 8

enum my_layer_keycodes {
  KC_LRAISE = SAFE_RANGE,
  KC_LLOWER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3( // Base
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESCAPE,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSHIFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTRL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_GRAVE,  KC_TAB,
                                          KC_LGUI, KC_LLOWER,  KC_SPC,     KC_ENT, KC_LRAISE, KC_RALT

  ),

  [1] = LAYOUT_split_3x6_3( // Lower
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESCAPE,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSHIFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,  KC_SPC,     KC_ENT, KC_TRNS, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3( // Raise
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESCAPE, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSHIFT, KC_GRAVE, KC_LBRACKET, KC_RBRACKET, KC_SCOLON, KC_BSLS,        KC_GRAVE,  KC_EQL, KC_KP_MINUS, KC_PLUS, KC_QUES,  KC_DELETE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTRL, KC_PSCREEN, KC_HOME, KC_END, KC_PGDOWN, KC_PGUP,                KC_TILD, KC_UNDS, KC_KP_SLASH, KC_KP_ASTERISK, KC_RGUI, KC_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,  KC_SPC,     KC_ENT, KC_TRNS, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3( // Adjust
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                      KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RESET, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,  KC_SPC,     KC_ENT, KC_TRNS, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

//#include <numeric>
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define RGB_BRIGHTNESS 70

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case _BASE:
            oled_write_ln_P(PSTR("Default"), false);
			rgblight_sethsv(15, 255, RGB_BRIGHTNESS);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
			rgblight_sethsv_noeeprom(7, 255, RGB_BRIGHTNESS); //Orange
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Higher"), false);
			rgblight_sethsv_noeeprom(25, 255, RGB_BRIGHTNESS); // Yellow
            break; 
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
			rgblight_sethsv_noeeprom(0, 0, RGB_BRIGHTNESS);
            break;
        default:
            oled_write_ln_P(PSTR("Missing"), false);
            break;
    }
}

/*
void oled_render_wpm(void) {
    oled_write_P(PSTR("WPM: "), false);
    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
}
*/

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write_ln(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

static void oled_render_logo_0(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,192,192, 96,112, 24, 12, 28, 56,224,192,192,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  2,  6,254,254,198,198,198,198,236,252,  0,  0,  0,192,224,112, 48, 48, 48, 48,112,224,192,  0,  0, 48,240,240,112, 48, 48, 48,240,224,  0,  0,  0,192,224, 48, 48, 48, 48,112,240,240, 48, 48,  0,192,224,112, 48, 48, 48, 48,112,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224, 96, 48, 24, 12, 14,  6,  3,  1,129,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  3,  3,  3,  6,  6, 12, 12, 24, 24, 48, 48, 48, 48, 24, 24,248,248,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0, 16, 16, 31, 31, 16, 16, 16, 16, 24, 31, 15,  0,  0,  7, 15, 24, 48, 48, 48, 48, 24, 15,  7,  0,  0, 16, 31, 31, 16,  0,  0, 16, 31, 31, 16,  0,  0,  7, 15, 24,152,152,152,156,255,255,  0,  0,  0,  7, 15, 24, 48, 48, 48, 48, 24, 15,  7,  0,  0,  0,  0,  0,  0,  0,248,252,135,131,129,128,128,192,192,192, 96, 96, 96, 64,195,195,195,192,135,134,134,142, 12, 12,  0,  0,  0,  0,  0, 56, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56,127,231,128,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  3,  3,  3,  3,  6,  6, 30,126,103, 99, 96, 96, 96, 96, 96, 48, 48, 48, 48, 48, 48, 96, 96, 97,111,126,112,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void oled_render_logo_1(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8, 28, 28, 56, 56, 16,  3,  7,227,240,112, 51,115,113,112,240,224,192,128,192,192, 96, 48, 48, 24, 24, 24, 12, 14,  3,  1,  3,  7, 28, 24, 24, 48, 48, 48, 96, 96, 96,192,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  2,  6,254,254,198,198,198,198,236,252,  0,  0,  0,192,224,112, 48, 48, 48, 48,112,224,192,  0,  0, 48,240,240,112, 48, 48, 48,240,224,  0,  0,  0,192,224, 48, 48, 48, 48,112,240,240, 48, 48,  0,192,224,112, 48, 48, 48, 48,112,224,192,  0,  0,  0,  0,  0, 15,255,255,240,  0,  0,  0,  0,  0,  1,  3,  7,  7,  2,  0,  0,112,112,112,  0,224,192,192,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  3,  6,  6,  6,  6,  3,227,255, 31,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0, 16, 16, 31, 31, 16, 16, 16, 16, 24, 31, 15,  0,  0,  7, 15, 24, 48, 48, 48, 48, 24, 15,  7,  0,  0, 16, 31, 31, 16,  0,  0, 16, 31, 31, 16,  0,  0,  7, 15, 24,152,152,152,156,255,255,  0,  0,  0,  7, 15, 24, 48, 48, 48, 48, 24, 15,  7,  0,  0,  0,  0,  0,  0,  0,  1,  3,  2,  0,  0,  0,  0,  0,  0,  0, 12, 12, 12,  8, 24, 24, 24, 24, 48, 48, 48, 49, 97, 97, 96, 96,224,240,248, 31, 31, 28, 28, 60,120,240,224,128,  0,  0,  0,  0,  0,  7, 15, 60,240,192,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  7, 15,  4,  0,  0,  0,  0,  1,  7, 31, 30, 30,  6,  6,  6, 12, 12, 12, 13, 15, 14,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void oled_render_logo_2(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,128,128,128,  0,  0,  0,  0,  0,  0,128,128,192,192,192, 96,112, 24, 12, 28, 56,224,192,192,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  2,  6,254,254,198,198,198,198,236,252,  0,  0,  0,192,224,112, 48, 48, 48, 48,112,224,192,  0,  0, 48,240,240,112, 48, 48, 48,240,224,  0,  0,  0,192,224, 48, 48, 48, 48,112,240,240, 48, 48,  0,192,224,112, 48, 48, 48, 48,112,224,192,  0,  0,  0,  0,  0,120,255,255,131,  1,  3,  3,  3,  7, 15, 30, 60, 62, 22,  3,  1,129,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  3,  3,  3,  6,  6, 12, 12, 24, 24, 48, 48, 48, 48, 24, 24,248,248,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0, 16, 16, 31, 31, 16, 16, 16, 16, 24, 31, 15,  0,  0,  7, 15, 24, 48, 48, 48, 48, 24, 15,  7,  0,  0, 16, 31, 31, 16,  0,  0, 16, 31, 31, 16,  0,  0,  7, 15, 24,152,152,152,156,255,255,  0,  0,  0,  7, 15, 24, 48, 48, 48, 48, 24, 15,  7,  0,  0,  0,  0,  0,  0,  7, 15, 31, 16,  0,  0,  0,  0,  0,  0,  0, 96, 96, 96, 64,195,195,195,192,135,134,134,142, 12, 12,  0,  0,  0,128,192,248,248,224,224,224,192,128,  0,  0,  0,  0,  0,  0,  0, 56,127,231,128,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  3,  3,  3,  3,  7, 15, 63,120, 32,  0,  0,  1,  3, 15, 63,252,240,240, 48, 48, 48, 96, 96, 97,111,126,112,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void oled_render_locks(void) {
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        oled_write("CAPS ", false);
    }
    if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) {
        oled_write("NUM ", false);
    }
    if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) {
        oled_write("SCROLL ", false);
    }
	oled_write_ln("", false);
}

typedef void (*func_type)(void);
uint32_t animation_timer = 0;
uint16_t animation_delay[] = {1500, 200, 300, 200, 300};
static func_type animation_funcs[] = {&oled_render_logo_0, &oled_render_logo_1, &oled_render_logo_2, &oled_render_logo_1, &oled_render_logo_2};
uint8_t animation_index = 0;

bool master_oled_alive = true;

void oled_render_animation(void) {
	if (timer_elapsed32(animation_timer) > animation_delay[animation_index]) {
		animation_index = (animation_index + 1) % 5;
		animation_timer = timer_read32();
	}
	animation_funcs[animation_index]();
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
		if (is_oled_on() && master_oled_alive) {
			oled_render_layer_state();
			//oled_render_wpm();
			oled_render_keylog();
			oled_render_locks();
		} else {
			master_oled_alive = false;
			oled_render_animation();
		}
    } else {
		oled_render_animation();
    }
}

bool lower_on;
bool raise_on;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    if (!master_oled_alive) {
	  oled_clear();
    }
	master_oled_alive = true;
  }

  switch (keycode) {
    case KC_LLOWER:
      if (record->event.pressed) {
        lower_on = true;
      } else {
        lower_on = false;
      }
      break;
    case KC_LRAISE:
      if (record->event.pressed) {
        raise_on = true;
      } else {
        raise_on = false;
      }
      break;
    }

  if (lower_on && raise_on) {
    layer_state_set(_ADJUST);
  } else if (lower_on) {
    layer_state_set(_LOWER);
  } else if (raise_on) {
    layer_state_set(_RAISE);
  } else {
    layer_state_set(_BASE);
  }

  return true;
}
#endif // OLED_ENABLE
