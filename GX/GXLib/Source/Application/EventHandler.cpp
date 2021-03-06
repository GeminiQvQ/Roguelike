// Local Includes
#include <GXLib/Application/EventHandler.h>

namespace GX
{
	//-----------------------------------------------------------------------------------------------------
	// Window
	//-----------------------------------------------------------------------------------------------------

	void EventHandler::on_window_create(Window& /*window*/)
	{
	}

	void EventHandler::on_window_destroy(Window& /*window*/)
	{
	}

	void EventHandler::on_window_resize(Window& /*window*/, int /*width*/, int /*height*/)
	{
	}

	//-----------------------------------------------------------------------------------------------------
	// Input
	//-----------------------------------------------------------------------------------------------------

	void EventHandler::on_key_down(Window* /*window*/, Key /*key*/, const std::vector<Modifier>& /*modifiers*/)
	{
	}

	void EventHandler::on_key_up(Window* /*window*/, Key /*key*/, const std::vector<Modifier>& /*modifiers*/)
	{
	}

	void EventHandler::on_mouse_button_down(Window* /*window*/, MouseButton /*button*/, int /*x*/, int /*y*/, const std::vector<Modifier>& /*modifiers*/)
	{
	}

	void EventHandler::on_mouse_button_up(Window* /*window*/, MouseButton /*button*/, int /*x*/, int /*y*/, const std::vector<Modifier>& /*modifiers*/)
	{
	}

	void EventHandler::on_mouse_move(Window* /*window*/, int /*x*/, int /*y*/)
	{
	}
}