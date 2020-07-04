# sdl2 cmake project-config input for ./configure scripts

set(prefix "/Users/sxhondo/corewar/virtual_machine/sdl/SDL2-2.0.10") 
set(exec_prefix "${prefix}")
set(libdir "/Users/sxhondo/corewar/virtual_machine/lib")
set(SDL2_PREFIX "/Users/sxhondo/corewar/virtual_machine/sdl/SDL2-2.0.10")
set(SDL2_EXEC_PREFIX "/Users/sxhondo/corewar/virtual_machine/sdl/SDL2-2.0.10")
set(SDL2_LIBDIR "/Users/sxhondo/corewar/virtual_machine/lib")
set(SDL2_INCLUDE_DIRS "/Users/sxhondo/corewar/virtual_machine/include/SDL2")
set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}  -lSDL2")
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
