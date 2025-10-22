#include "yayterm.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_CAP
# define BUFFER_CAP 4096
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

typedef struct buffer_s
{
	char			buffer[BUFFER_CAP];
	size_t			size;
	size_t			cursor;
}				buffer_t;

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


int insert_key(buffer_t *buffer, int key)
{
  if (buffer->size >= BUFFER_CAP - 1)
	  return 1;
  memmove(buffer->buffer + buffer->cursor + 1, buffer->buffer + buffer->cursor, buffer->size - buffer->cursor);
  buffer->buffer[buffer->cursor] = key;
  return 0;
}

char *sub_str(const char *str, int pos, int end_pos)
{
  	char *rtn;
  	int	size;

  	size = end_pos - pos + 1;
	rtn = calloc(size, sizeof(char));
  	memmove(rtn, str + pos, end_pos);
  	rtn[size - 1] = 0;
	return rtn;
}

int draw_lines(wm_t wm, buffer_t buffer)
{
  SDL_Color color = {255, 255, 255, 255};
  char *stop;
  char *str = strdup(buffer.buffer);
  char *tmp = str;
  char *temp = NULL;
  int	i = 0;

  while (str && *str)
  {

	stop = strchr(str, '\n');
	if (!stop)
	{
	  draw_text(wm, str, 0, i*15, color);
	  break;
	}
   	temp = sub_str(str, 0, (size_t)(stop - str));
	draw_text(wm, temp, 0, i*15, color);
  	free(temp);
	str = stop + 1;
	i++;
  }
  free(tmp);
  return 0;
}

void key_handler(int key, buffer_t *buffer)
{
  switch(key){
  case '\b':
	{
	  if (buffer->size && buffer->cursor)
	  {
		buffer->buffer[buffer->cursor - 1] = 0;
		buffer->cursor--;
		buffer->size--;
	  }
	  break;
	}
  default:
	{
	  if (!key)
		break;
	  printf("key = %d\n", key);
	  insert_key(buffer, key);
	  buffer->size++;
	  buffer->cursor++;
	}
  }
}


int main() {

	wm_t		wm;
	buffer_t	buffer;
	int			loop;
	int			key;

	memset(&buffer, 0, sizeof(buffer_t));
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
				key_handler(key, &buffer);
			}
		}
		SDL_RenderClear(wm.ren);
		//		draw_text(wm, buffer.buffer, 0, 0, color);
		draw_lines(wm, buffer);
		SDL_SetRenderDrawColor(wm.ren, 0, 0, 0, 255);
        SDL_RenderPresent(wm.ren);
    }

    SDL_DestroyRenderer(wm.ren);
    SDL_DestroyWindow(wm.win);
    SDL_Quit();
    return 0;
}

