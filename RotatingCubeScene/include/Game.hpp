#ifndef GAME_H
#define GAME_H

#include <glut.h>
#include <IL/ilut.h>
#include <string>

/// <summary>
/// TODO: Namespace doc
/// </summary>
namespace OpenGLScene
{
	/// <summary>
	/// TODO
	/// </summary>
	class Game
	{
		public:
			Game(const unsigned int WIDTH, const unsigned int HEIGHT, const std::string TITLE, const bool SHOW_DEBUG_PANE = true);

		private:
			GLint m_windowID;
			unsigned int m_width;
			unsigned int m_height;
			std::string m_title;
			bool m_showDebugPane;
	};
}

#endif
