project('yayterm', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

sdl2_dep = dependency('sdl2', required : true)
sdl2_ttf_dep = dependency('SDL2_ttf', required : true)


executable('yayterm',
           'src/main.c',
            'src/key_handler.c',
           install : true, 
          
           dependencies: [
              sdl2_dep,
              sdl2_ttf_dep
             ]
           )
