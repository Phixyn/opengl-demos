#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "SDL.h"

/// <summary>
/// A namespace for the SDL Demo.
/// </summary>
namespace SDLDemo
{
	/// <summary>
	/// Class that provides initialization and operations for SDL windows
	/// with support for OpenGL graphics.
	/// </summary>
	class Display
	{
		public:
			/// <summary>
			/// Initializes SDL and OpenGL. Creates an SDL window ready to
			/// handle OpenGL graphics.
			/// </summary>
			///
			/// <param name="WIDTH"> The width of the SDL window. </param>
			/// <param name="HEIGHT"> The height of the SDL window. </param>
			/// <param name="TITLE"> A title for the SDL window. </param>
			Display(const unsigned int WIDTH, const unsigned int HEIGHT, const std::string& TITLE);
			// TODO constructor that accepts xpos and ypos for window
			/// <summary>
			/// Cleans up SDL and OpenGL and frees up memory if necessary.
			/// Destroys the SDL window and quits SDL.
			/// </summary>
			~Display();

			/// <summary>
			/// Updates the SDL window.
			/// </summary>
			void update();
			/// <summary>
			/// Clears the SDL window.
			/// </summary>
			void clear();
		private:
			/// <summary>
			/// Pointer to an SDL_Window instance for the game.
			/// </summary>
			SDL_Window* m_window;
			/// <summary>
			/// An SDL context for OpengGL.
			/// </summary>
			SDL_GLContext m_glContext;
	};
}

#endif
