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

#define _BASE 1    // 0b00000001
#define _LOWER 2   // 0b00000010
#define _RAISE 4   // 0b00000100
#define _ADJUST 8  // 0b00001000

enum custom_keycodes {
  KC_LRAISE = SAFE_RANGE,
  KC_LLOWER,
  KC_DESK_LEFT,
  KC_DESK_RIGHT
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
      KC_LSHIFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_DESK_LEFT, KC_DESK_RIGHT,
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

#include "animations.h"
#include "decompress.c"

static void oled_render_logo_0(void) {
    oled_write_compressed_P(bongo_0_block_x_map, bongo_0_block_x_list);
}

static void oled_render_logo_1(void) {
    oled_write_compressed_P(bongo_1_block_x_map, bongo_1_block_x_list);
}

static void oled_render_logo_2(void) {
    oled_write_compressed_P(bongo_2_block_x_map, bongo_2_block_x_list);
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

uint8_t animation_type_index = 0;
typedef void (*func_type)(void);
uint32_t animation_timer = 0;
uint16_t animation_delay[1][5] = {
  {1500, 200, 300, 200, 300},
};
static func_type animation_funcs[1][5] = {
  {&oled_render_logo_0, &oled_render_logo_1, &oled_render_logo_2, &oled_render_logo_1, &oled_render_logo_2},
};
uint8_t animation_index = 0;

bool master_oled_alive = true;

void oled_render_animation(void) {
	if (timer_elapsed32(animation_timer) > animation_delay[animation_type_index][animation_index]) {
		animation_index = (animation_index + 1) % 5;
		animation_timer = timer_read32();
	}
	animation_funcs[animation_type_index][animation_index]();
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
    case KC_DESK_LEFT:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI)SS_TAP(X_LEFT)SS_UP(X_LCTL)SS_UP(X_LGUI));
      }
      break;
    case KC_DESK_RIGHT:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI)SS_TAP(X_RIGHT)SS_UP(X_LCTL)SS_UP(X_LGUI));
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

void keyboard_post_init_user(void) {
  layer_state_set(_BASE);
}
