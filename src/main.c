#include "yayterm.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

#ifndef FRAME_BUFFER_SIZE
# define FRAME_BUFFER_SIZE 4096
#endif

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSerif.ttf"

typedef struct	wm_s
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		event;
	TTF_Font		*font;
	int				w;
	int				h;
}					wm_t;

typedef struct tm_s
{
	char	buffer[BUFFER_SIZE];
	char	*pindex;
	char	*cursor;
}				tm_t;

SDL_Rect draw_text(wm_t wm, const char* text, int x, int y, SDL_Color color) 
{
	SDL_Rect		dest;
	SDL_Surface		*surface;
	SDL_Texture		*texture;

    if (!text || !wm.font) return (SDL_Rect){0, 0,0,0};

    surface = TTF_RenderText_Blended(wm.font, text, color);
    if (!surface) return dest;
    texture = SDL_CreateTextureFromSurface(wm.ren, surface);
	dest = (SDL_Rect){x, y, surface->w, surface->h};
	SDL_RenderCopy(wm.ren, texture, NULL, &dest);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	return dest;
}

wm_t init_window_manager(char const *str)
{
	wm_t	wm;
	
	memset(&wm, 0, sizeof(wm_t));
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        return wm;
    wm.win = SDL_CreateWindow(str,  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE
    );
    if (!wm.win) 
        return wm;
    wm.ren = SDL_CreateRenderer(wm.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!wm.ren) 
	{
        SDL_DestroyWindow(wm.win);
        return wm;
    }
	TTF_Init();
	wm.font = TTF_OpenFont(FONT_PATH, 20);
	if (!wm.font)
		return wm;
	return wm;
}

int wc(char *str, int delim)
{
	int	rtn;

	rtn = 0;
	while (str && *str)
	{
		while (*str == delim)
			str++;
		rtn += *str != 0;
		str = strchr(str, delim);
	}
	return (rtn);
}

char **split(char *str, int delim, int *count)
{
	char **rtn;
	int		wc_c;
	int		i;

	wc_c = wc(str, delim);
	*count = wc_c;
	rtn = (char **)malloc(wc_c * sizeof(char *));
	if (!rtn)
		return NULL;
	i = 0;
	while (i < wc_c)
	{
		
	}
}

void draw_lines(wm_t wm, tm_t tm)
{
	char **lines;
	int	 count;
	

	lines = split(tm.buffer, &count);


}

void handle_buffer(tm_t *tm, int key)
{
	if (key == '\b')
	{
		tm->cursor--;
		*tm->cursor = ' ';
	}
	else
	{
		*tm->cursor = key;
		tm->cursor++;
		tm->pindex++;
	}
}

int main() {

	wm_t	wm;
	tm_t	tm;
	int		loop;
	int		key;

	memset(&tm, 0, sizeof(wm_t));
	tm.cursor = tm.buffer;
	tm.pindex = tm.buffer;
	wm = init_window_manager("yayterm");
	if (!wm.win || !wm.ren || !wm.font)
		{perror("wm"); exit(1);}
	loop = 1;
	SDL_StartTextInput();
	while (loop)
	{
        while (SDL_PollEvent(&wm.event))
		{
            if (wm.event.type == SDL_QUIT) 
                loop = 0;
			else if (wm.event.type == SDL_WINDOWEVENT && wm.event.window.event == SDL_WINDOWEVENT_RESIZED) 
			{
                wm.w = wm.event.window.data1;
                wm.h = wm.event.window.data2;
                SDL_RenderPresent(wm.ren);
            }
			else if (wm.event.type == SDL_KEYDOWN)
			{
				key = handle_key(wm.event.key.keysym.sym, wm.event.key.keysym.mod);
				handle_buffer(&tm, key);
			}
		}
		SDL_RenderClear(wm.ren);
		draw_lines(wm, tm);
		SDL_SetRenderDrawColor(wm.ren, 0, 0, 0, 255);
        SDL_RenderPresent(wm.ren);
    }

    SDL_DestroyRenderer(wm.ren);
    SDL_DestroyWindow(wm.win);
    SDL_Quit();
    return 0;
}




