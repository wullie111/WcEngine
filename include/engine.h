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

#ifndef engine_h
#define engine_h

// standard libs

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <float.h>
#include <pthread.h>

// SDL2 libs 

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>

// misc libs


// inforamtion on vars 
#ifndef FILE_MAX_PATH
#define FILE_MAX_PATH 512

extern char error_buf[ERROR_BUFFER_SIZE];
extern char error_str[ERROR_BUFFER_SIZE];

// error handling 
#define error(MSG, ...) { \
  snprintf(error_str,(ERROR_BUFFER_SIZE-1), "[ERROR] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
  snprintf(error_buf,(ERROR_BUFFER_SIZE-1), MSG, ##__VA_ARGS__); strcat(error_str, error_buf);    \
  error_(error_str); }

#endif
#endif
