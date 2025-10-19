

#include "yayterm.h"

int handle_key(SDL_Keycode key, SDL_Keymod mod) 
{
    int shift = (mod & KMOD_SHIFT) != 0;

    if (key >= SDLK_a && key <= SDLK_z) {
        if (shift) return 'A' + (key - SDLK_a);
        else return 'a' + (key - SDLK_a);
    }

    if (key >= SDLK_0 && key <= SDLK_9) {
        if (shift) {
            switch (key) {
                case SDLK_1: return '!'; case SDLK_2: return '@';
                case SDLK_3: return '#'; case SDLK_4: return '$';
                case SDLK_5: return '%'; case SDLK_6: return '^';
                case SDLK_7: return '&'; case SDLK_8: return '*';
                case SDLK_9: return '('; case SDLK_0: return ')';
            }
        } else return '0' + (key - SDLK_0);
    }

    if (key == SDLK_SPACE) return ' ';
    if (key == SDLK_RETURN) return '\n';
    if (key == SDLK_BACKSPACE) return 0x08;
    if (key == SDLK_TAB) return '\t';

    if (key == SDLK_MINUS)  return shift ? '_' : '-';
    if (key == SDLK_EQUALS) return shift ? '+' : '=';
    if (key == SDLK_LEFTBRACKET)  return shift ? '{' : '[';
    if (key == SDLK_RIGHTBRACKET) return shift ? '}' : ']';
    if (key == SDLK_BACKSLASH)    return shift ? '|' : '\\';
    if (key == SDLK_SEMICOLON)    return shift ? ':' : ';';
    if (key == SDLK_QUOTE)        return shift ? '"' : '\'';
    if (key == SDLK_COMMA)        return shift ? '<' : ',';
    if (key == SDLK_PERIOD)       return shift ? '>' : '.';
    if (key == SDLK_SLASH)        return shift ? '?' : '/';
    if (key == SDLK_BACKQUOTE)        return shift ? '~' : '`';

    return 0;
}

