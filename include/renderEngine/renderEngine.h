/* Copyright 2024 WULLIE STUDIO

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

//the heart of the rendering engine

#ifndef renderengine_h
#define renderengine_h

#include "engine.h"

// window management

void wRenderWindowSetTitle(const char* title);	// tile for said window
void wRenderWindowSetPOS(int x, int y);	// optinal position
void wRenderWindowSetSize(int width, int hight); // size for said window

// cursor managemant 
void wRenderSetCursorHidden(bool hidden);
bool wRenderGetCursorHidden();
#endif
