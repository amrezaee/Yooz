#include <Platform/yzMessageBox.hpp>

namespace yz
{
static const SDL_MessageBoxColorScheme color_scheme = {
        {/* .colors (.r, .g, .b) */
         /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
         {255, 0, 0},
         /* [SDL_MESSAGEBOX_COLOR_TEXT] */
         {0, 255, 0},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
         {255, 255, 0},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
         {0, 0, 255},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
         {255, 0, 255}}};

void MessageBoxFatal(const char* const msg)
{
	static const SDL_MessageBoxButtonData buttons[] = {
	        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK"},
	};

	const SDL_MessageBoxData messageboxdata = {
	        SDL_MESSAGEBOX_ERROR,   /* .flags */
	        NULL,                   /* .window */
	        "Yooz Engine",          /* .title */
	        msg,                    /* .message */
	        SDL_arraysize(buttons), /* .numbuttons */
	        buttons,                /* .buttons */
	        &color_scheme /* .colorScheme */};
	int buttonid;
	if(SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		SDL_Log("Error displaying message box.");
}
}  // namespace yz
