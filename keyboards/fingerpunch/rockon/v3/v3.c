/* Copyright 2021 Sadek Baroudi <sadekbaroudi@gmail.com>
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

#include "v3.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    { 66, 4, 6, 64, 65, 5, 3, 2 },
    { 59, 11, 9, 61, 60, 10, 12, 13 },
    { 52, 18, 20, 50, 51, 19, 17, 16 },
    { 45, 25, 23, 47, 46, 24, 26, 27 },
    { 39, 31, 33, 37, 38, 32, 30, 29 },
    { 43, 48, 35, 57, 54, 68, 22, 1 },
    { 55, 7, 36, 63, 49, 21, 34, 14 },
    { 42, 8, NO_LED, 62, NO_LED, NO_LED, 28, 15 },
    { 56, 53, 40, 41, 69, 44, 58, 67 }
}, {
    {7,1},       {21,1},       {36,2},       {51,1},       {65,5},       {79,10},       {93,14},
    {90,21},     {76,20},      {62,16},      {48,12},      {33,12},      {19,12},       {4,10},
    {2,20},      {16,22},      {31,23},      {46,23},      {60,27},      {74,31},       {88,35},
    {87,50},     {71,42},      {57,38},      {43,33},      {28,34},      {14,33},       {0,31},
    {25,46},     {40,48},      {56,51},      {70,56},      {84,63},
    {99,64},     {112,64},     {125,64},
    {138,63},    {152,56},     {166,51},     {182,48},     {197,46},     {223,31},      {209,33},
    {200,34},    {179,33},     {165,38},     {151,42},     {135,50},     {134,35},      {148,31},
    {162,27},    {176,23},     {191,23},     {206,22},     {220,20},     {218,9},       {203,12},
    {189,12},    {174,12},     {160,16},     {146,20},     {132,24},     {129,14},      {143,10},
    {157,5},     {171,1},      {186,2},      {201,1},      {215,0}
}, {
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1,
    1, 1, 1,
    1, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1
} };
#endif
