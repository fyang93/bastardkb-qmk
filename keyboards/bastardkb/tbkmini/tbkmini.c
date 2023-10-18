/**
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tbkmini.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // left
    {18, 17, 12, 11, 6, 5},
    {19, 16, 13, 10, 7, 4},
    {20, 15, 14, 9, 8, 3},
    {NO_LED, NO_LED, NO_LED, 2, 1, 0},
    // {  0,  5,  6, 11, 12, 15 },
    // {  1,  4,  7, 10, 13, 16 },
    // {  2,  3,  8,  9, 14, 17 },
    // { NO_LED, 18, NO_LED, 19, 20, NO_LED },
    // right
    {39, 38, 33, 32, 27, 26},
    {40, 37, 34, 31, 28, 25},
    {41, 36, 35, 30, 29, 24},
    {NO_LED, NO_LED, NO_LED, 23, 22, 21}
    // { 21, 26, 27, 32, 33, 36 },
    // { 22, 25, 28, 31, 34, 37 },
    // { 23, 24, 29, 30, 35, 38 },
    // { NO_LED, 39, NO_LED, 40, 41, NO_LED }
}, {
    // left
    {102, 64}, {81, 64}, {61, 64}, // left thumb cluster
    {102, 42}, {102, 21}, {102, 0}, {81, 0}, {81, 21}, {81, 42},
    {61, 42}, {61, 21}, {61, 0}, {41, 0}, {41, 21}, {41, 42},
    {20, 42}, {20, 21}, {20, 0}, {0, 0}, {0, 21}, {0, 42},
    // {   0,   0 }, {   0,  21 }, {   0,  42 }, // col 1
    // {  20,  42 }, {  20,  21 }, {  20,   0 }, // col 2
    // {  41,   0 }, {  41,  21 }, {  41,  42 },
    // {  61,  42 }, {  61,  21 }, {  61,   0 },
    // {  81,   0 }, {  81,  21 }, {  81,  42 },
    // { 102,   0 }, { 102,  21 }, { 102,  42 },
    // {  61,  64 }, {  81,  64 }, { 102,  64 }, // left thumb cluster
    // right
    {122, 64}, {143, 64}, {163, 64}, // right thumb cluster
    {122, 42}, {122, 21}, {122, 0}, {143, 0}, {143, 21}, {143, 42},
    {163, 42}, {163, 21}, {163, 0}, {183, 0}, {183, 21}, {183, 42},
    {204, 42}, {204, 21}, {204, 0}, {224, 0}, {224, 21}, {224, 42}
    // { 224,   0 }, { 224,  21 }, { 224,  42 }, // col 12
    // { 204,  42 }, { 204,  21 }, { 204,   0 }, // col 11
    // { 183,   0 }, { 183,  21 }, { 183,  42 },
    // { 163,  42 }, { 163,  21 }, { 163,   0 },
    // { 142,   0 }, { 142,  21 }, { 142,  42 },
    // { 122,   0 }, { 122,  21 }, { 122,  42 },
    // { 163,  64 }, { 142,  64 }, { 122,  64 }  // right thumb cluster
}, {
    // left
    2, 2, 2, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2,
    // right
    2, 2, 2, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2
} };

uint8_t default_rgb_mode = RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE;
uint8_t idle_rgb_mode = RGB_MATRIX_BREATHING;
uint16_t last_keypress_timer = 0; // 记录最后一次按键的时间

void matrix_scan_user(void) {
  if (timer_elapsed(last_keypress_timer) > 5000 && rgb_matrix_get_mode() != idle_rgb_mode) {
    default_rgb_mode = rgb_matrix_get_mode();
    rgb_matrix_mode(idle_rgb_mode);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    last_keypress_timer = timer_read();
    if (!rgb_matrix_is_enabled()) {
      rgb_matrix_enable_noeeprom();
    }
    if (rgb_matrix_get_mode() == idle_rgb_mode) {
      rgb_matrix_mode(default_rgb_mode);
    }
  }
  return true;
}
#endif
// clang-format on
