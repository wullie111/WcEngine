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

#include "renderEngine/renderEngine.h"

// basic game window information
static SDL_Window* gameWindow = NULL;
static SDL_GLContext * Context = NULL;

// options for the main game window 
// may apply to editor UI latter
static int gameWindowFlags = 0;
static int gameWindowMultSaples = 0;
static int gameWindowMultisamplesBuffs = 0;
static int GameWindowAntialiasing = 0;

// creating a SDL2 window
static void wRenderStart() {

	// the window its self
	Window = SDL_CreateWindow("WcEngine", SDL_WINDOWPOS_UNDIFNED, SDL_WINDOWPOS_UNDEFINED, 800, 600, gameWindowFlags);
	
	if (gameWindow == NULL){
		error("could not create a SDL window: %s", SDL_GetError());
	}
	
	// setting window atributs
	// stuff the the icon name and basic rendering settings 
	
		

}
