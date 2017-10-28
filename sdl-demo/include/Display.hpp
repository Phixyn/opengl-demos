#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "SDL.h"

namespace SDLDemos
{
	class Display
	{
		public:
			Display(int width, int height, const std::string& title);
			// TODO constructor that accepts xpos and ypos for window
			~Display();

			void update();
			void clear();
		private:
			/// <summary>
			/// Pointer to an SDL_Window instance for the game.
			/// </summary>
			SDL_Window* m_window;
			/// <summary>
			/// A SDL context for OpengGL
			/// </summary>
			SDL_GLContext m_glContext;

	};
}

#endif
