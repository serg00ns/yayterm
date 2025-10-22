
#include "yayterm.h"

int handle_key(SDL_Keycode key, SDL_Keymod mod)
{
    int shift  = (mod & KMOD_SHIFT) != 0;
    int caps   = (mod & KMOD_CAPS)  != 0;
    int alt    = (mod & KMOD_ALT)   != 0;
    int ctrl   = (mod & KMOD_CTRL)  != 0;
    int altgr  = (mod & KMOD_MODE)  != 0; 

    if (key >= SDLK_a && key <= SDLK_z) {
        int base = key - SDLK_a;
        if (ctrl)
            return 0x01 + base; 

        int upper = (shift ^ caps);
        int ch = upper ? 'A' + base : 'a' + base;
        return alt ? (0x1B00 | ch) : ch;
    }

    if (key >= SDLK_0 && key <= SDLK_9) {
        int ch = 0;
        if (shift) {
            switch (key) {
                case SDLK_1: ch = '!'; break; case SDLK_2: ch = '@'; break;
                case SDLK_3: ch = '#'; break; case SDLK_4: ch = '$'; break;
                case SDLK_5: ch = '%'; break; case SDLK_6: ch = '^'; break;
                case SDLK_7: ch = '&'; break; case SDLK_8: ch = '*'; break;
                case SDLK_9: ch = '('; break; case SDLK_0: ch = ')'; break;
            }
        } else ch = '0' + (key - SDLK_0);
        return alt ? (0x1B00 | ch) : ch;
    }

    if (key == SDLK_SPACE)      return alt ? 0x1B20 : ' ';
    if (key == SDLK_RETURN)     return '\n';
    if (key == SDLK_BACKSPACE)  return 0x08;
    if (key == SDLK_TAB)        return '\t';
    if (key == SDLK_ESCAPE)     return 0x1B;

    #define MAP(sym, normal, shifted) \
        if (key == sym) { int ch = shift ? shifted : normal; return alt ? 0x1B00 | ch : ch; }

    MAP(SDLK_MINUS, '-', '_');
    MAP(SDLK_EQUALS, '=', '+');
    MAP(SDLK_LEFTBRACKET, '[', '{');
    MAP(SDLK_RIGHTBRACKET, ']', '}');
    MAP(SDLK_BACKSLASH, '\\', '|');
    MAP(SDLK_SEMICOLON, ';', ':');
    MAP(SDLK_QUOTE, '\'', '"');
    MAP(SDLK_COMMA, ',', '<');
    MAP(SDLK_PERIOD, '.', '>');
    MAP(SDLK_SLASH, '/', '?');
    MAP(SDLK_BACKQUOTE, '`', '~');

    #undef MAP

    return 0;
}


