/* Copyright 2024 WULLIE MORRISON

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "engine.h"

#define MAX_AT_FUNCS 32
static error_func_t error_funcs[MAX_AT_FUNCS];

static int num_error_funcs = 0;

void at_error(void(*func)(const char*)) {
  if (num_error_funcs == MAX_AT_FUNCS) { 
    warning("Cannot register more than maximum of %i error functions", MAX_AT_FUNCS);
    return;
  }
  
  error_funcs[num_error_funcs] = (error_func_t)func;
  num_error_funcs++;
}
