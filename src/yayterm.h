#ifndef __YAYTERM_H_
# define __YAYTERM_H_

#include <assert.h>


#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h> 
#include <fcntl.h>      
#include <errno.h>      
#include <signal.h>     
#include <termios.h>    
#include <pty.h>        
#include <sys/types.h>  
#include <sys/wait.h>   
#include <sys/ioctl.h>  
#include <sys/select.h> 
#include <sys/time.h>   

#include <SDL2/SDL.h>   
#include <SDL2/SDL_ttf.h>

int handle_key(SDL_Keycode key, SDL_Keymod mod);

#endif // __YAYTERM_H_
