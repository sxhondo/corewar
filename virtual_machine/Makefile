# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgyles <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 14:20:48 by rgyles            #+#    #+#              #
#    Updated: 2020/02/24 14:13:26 by bdudley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

PROJECT_PATH = $(shell pwd)

SDL_DIR = sdl/SDL2-2.0.10

SDL_TTF_DIR = sdl/SDL_ttf

SDL_MIXER_DIR = sdl/SDL2_mixer-2.0.4

FREETYPE_DIR = sdl/freetype-2.4.9

LIBMAD_DIR = sdl/libmad-0.15.1b

SDL_TARGET = lib/libSDL2.dylib

SDL_TTF_TARGET = lib/libSDL2_ttf.dylib

SDL_MIXER_TARGET = lib/libSDL2_mixer.dylib

FREETYPE_TARGET = lib/libfreetype.dylib

LIBMAD_TARGET = lib/libmad.dylib

LIBFT_DIR = ../libft/

LIBFT = ../libft/libft.a

SDL_LIB = lib

SDL_INCLUDE = include

INCLUDE = -I ../libft/incs -I include -I $(SDL_INCLUDE)/SDL2

LIB = -L $(SDL_LIB) -l SDL2 -l SDL2_ttf -l SDL2_mixer

FLAGS = -Wall -Wextra -Werror

SRC_DIR = src

OBJ_DIR = obj

SRC = main.c \
	  read.c \
	  help.c \
	  reverse.c \
	  get_and_set.c \
	  print_arena.c \
	  processes.c \
	  gladiatorial_fight.c \
	  lld_lldi_lfork_aff.c \
	  live_ld_st_add.c \
	  zjmp_ldi_sti_fork.c \
	  sub_and_or_xor.c \
	  write_read_card.c \
	  free_resources.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

SDL_SRC = init_sdl.c \
		  error_message.c \
		  initialize_visual_arena.c \
		  set_replica.c \
		  draw_byte.c \
		  draw_shapes.c \
		  draw_annotations.c \
		  draw_game_controls.c \
		  int_to_char.c \
		  render_text.c \
		  update_byte.c \
		  show_data.c \
		  show.c \
		  explosion.c \
		  announce_winner.c \
		  event_handler.c

SDL_OBJ = $(addprefix $(OBJ_DIR)/, $(SDL_SRC:.c=.o))

CHECK_MARK= \033[0;32m\xE2\x9C\x94\033[0m
SHIFT = "    "

CLEAR = \033[2K
UP= \033[1A

RED = \033[0;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
CYAN = \033[1;36m
GREEN_UNDERLINE = \033[4;32m
NC = \033[0m

all: $(NAME)

$(NAME): $(SDL_LIB) $(OBJ) $(SDL_OBJ)
	@echo "\n" $(SHIFT) "$(CHECK_MARK)$(BLUE) Linking Corewar...$(NC)"
	@gcc $(FLAGS) $(LIBFT) $(LIB) -o $(NAME) $(OBJ) $(SDL_OBJ)
	@echo $(SHIFT) " $(CHECK_MARK)$(GREEN) Corewar is ready!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/corewar.h | $(OBJ_DIR)
	gcc $(FLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR)/main.o: include/visual.h include/sdl_struct.h

$(SDL_OBJ): include/visual.h include/sdl_struct.h

$(OBJ_DIR)/init_sdl.o: include/sound.h

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo $(SHIFT) "$(CHECK_MARK)$(GREEN) Object directory is created! (./obj)$(NC)\n"

$(SDL_LIB): $(SDL_TARGET) $(SDL_TTF_TARGET) $(SDL_MIXER_TARGET)
	@echo $(SHIFT) "$(CHECK_MARK)$(GREEN) SDL libraries are installed at $(SDL_LIB) (./lib)!$(NC)"
	@echo $(SHIFT) "$(CHECK_MARK)$(GREEN) SDL headers are set at $(SDL_INCLUDE) (./include)!$(NC)"
	@echo $(SHIFT) "$(CHECK_MARK)$(RED) Deleting build directories...$(NC)"
	@rm -rf $(SDL_DIR) $(SDL_TTF_DIR) $(FREETYPE_DIR) $(SDL_MIXER_DIR) $(LIBMAD_DIR)


$(SDL_TARGET):
	@echo $(SHIFT) "$(CLEAR)$(BLUE)Extracting SDL...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)-$(RED)>                   $(GREEN)#$(NC)\r\c"
	@tar -xf $(SDL_DIR).zip -C sdl
	@CC=$(PROJECT_PATH)/$(SDL_DIR)/build-scripts/gcc-fat.sh
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Configuring SDL build...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)--$(RED)>                  $(GREEN)#$(NC)\r\c"
	@cd $(SDL_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(SDL_DIR) \
									--disable-static \
									--disable-joystick \
									--disable-haptic \
									--disable-sensor \
									--disable-power \
									--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
									--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
									> /dev/null
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Building SDL...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)---$(RED)>                 $(GREEN)#$(NC)\r\c"
	@make -j4 -C $(SDL_DIR) > /dev/null 2>&1
	@make -j4 -C $(SDL_DIR) install > /dev/null 2>&1
	@echo $(SHIFT) "$(UP)$(CLEAR)$(CHECK_MARK)$(YELLOW) SDL is ready!$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)----$(RED)>                $(GREEN)#$(NC)\r\c"

$(SDL_TTF_TARGET): $(FREETYPE_TARGET) 
	@echo $(SHIFT) "$(CLEAR)$(BLUE)Extracting SDL_ttf...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)---------$(RED)>           $(GREEN)#$(NC)\r\c"
	@tar -xf $(SDL_TTF_DIR).zip -C sdl
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Configuring SDL_ttf build...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)----------$(RED)>          $(GREEN)#$(NC)\r\c"
	@cd $(SDL_TTF_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(SDL_TTF_DIR) \
										--disable-static \
										--with-sdl-prefix=$(PROJECT_PATH)/$(SDL_DIR) \
										--with-freetype-prefix=$(PROJECT_PATH)/$(FREETYPE_DIR) \
										--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
										--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
										> /dev/null
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Building SDL_ttf...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)-----------$(RED)>         $(GREEN)#$(NC)\r\c"
	@make -j4 -C $(SDL_TTF_DIR) > /dev/null 2>&1
	@make -j4 -C $(SDL_TTF_DIR) install > /dev/null 2>&1
	@echo $(SHIFT) "$(UP)$(CLEAR)$(CHECK_MARK)$(YELLOW) SDL_ttf is ready!$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)------------$(RED)>        $(GREEN)#$(NC)\r\c"

$(FREETYPE_TARGET):
	@echo $(SHIFT) "$(CLEAR)$(BLUE)Extracting freetype...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)-----$(RED)>               $(GREEN)#$(NC)\r\c"
	@tar -xf $(FREETYPE_DIR).tar.bz2 -C sdl
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Configuring freetype build...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)------$(RED)>              $(GREEN)#$(NC)\r\c"
	@cd $(FREETYPE_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(FREETYPE_DIR) \
										--disable-static \
										--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
										--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
										> /dev/null
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Building freetype...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)-------$(RED)>             $(GREEN)#$(NC)\r\c"
	@make -j4 -C $(FREETYPE_DIR) > /dev/null 2>&1
	@make -j4 -C $(FREETYPE_DIR) install > /dev/null 2>&1
	@echo $(SHIFT) "$(UP)$(CLEAR)$(CHECK_MARK)$(YELLOW) freetype is ready!$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)--------$(RED)>            $(GREEN)#$(NC)\r\c"

$(SDL_MIXER_TARGET): export CPPFLAGS = -I$(PROJECT_PATH)/$(SDL_INCLUDE)

$(SDL_MIXER_TARGET): $(LIBMAD_TARGET)
	@echo $(SHIFT) "$(CLEAR)$(BLUE)Extracting SDL2_mixer...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)-----------------$(RED)>   $(GREEN)#$(NC)\r\c"
	@tar -xf $(SDL_MIXER_DIR).zip -C sdl
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Configuring SDL2_mixer build...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)------------------$(RED)>  $(GREEN)#$(NC)\r\c"
	@cd $(SDL_MIXER_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(SDL_MIXER_DIR) \
										--disable-static \
										--with-sdl-prefix=$(PROJECT_PATH)/$(SDL_DIR) \
										--enable-music-mp3-mad-gpl=yes \
										--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
										--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
										> /dev/null 2>&1
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Building SDL2_mixer...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)-------------------$(RED)> $(GREEN)#$(NC)\r\c"
	@make -j4 -C $(SDL_MIXER_DIR) > /dev/null 2>&1
	@make -j4 -C $(SDL_MIXER_DIR) install > /dev/null 2>&1
	@echo $(SHIFT) "$(UP)$(CLEAR)$(CHECK_MARK)$(YELLOW) SDL2_mixer is ready!$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)--------------------$(RED)>$(GREEN)#$(NC)\r\c"

$(LIBMAD_TARGET):
	@echo $(SHIFT) "$(CLEAR)$(BLUE)Extracting libmad...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)-------------$(RED)>       $(GREEN)#$(NC)\r\c"
	@tar -xf $(LIBMAD_DIR).zip -C sdl
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Configuring libmad build...$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)--------------$(RED)>      $(GREEN)#$(NC)\r\c"
	@cd $(LIBMAD_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(LIBMAD_DIR) \
									--disable-static \
									--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
									--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
									> /dev/null 2>&1
	@sed -i '' "129s/.*/CFLAGS=-Wall/" $(LIBMAD_DIR)/Makefile
	@echo $(SHIFT) "$(UP)$(CLEAR)$(BLUE)Building libmad...$(NC)"
	@make -j4 -C $(LIBMAD_DIR) > /dev/null 2>&1
	@make -j4 -C $(LIBMAD_DIR) install > /dev/null 2>&1
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)---------------$(RED)>     $(GREEN)#$(NC)\r\c"
	@echo $(SHIFT) "$(UP)$(CLEAR)$(CHECK_MARK)$(YELLOW) libmad is ready!$(NC)"
	@echo $(SHIFT) "$(GREEN)Progress: #$(CYAN)----------------$(RED)>    $(GREEN)#$(NC)\r\c"

clean:
	@echo $(SHIFT) "$(RED)Deleting object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(SHIFT) "$(RED)Deleting program...$(NC)"
	@rm -rf $(NAME)

lclean:
	@echo $(SHIFT) "$(RED)Deleting SDL, SDL_TTF, freetype libraries and header files...$(NC)"
	@rm -rf $(SDL_LIB) $(SDL_INCLUDE)/SDL2 $(SDL_INCLUDE)/ft2build.h $(SDL_INCLUDE)/freetype2 $(SDL_INCLUDE)/mad.h
	@rm -rf sdl/freetype_build sdl/sdl_build sdl/sdl_ttf_build

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(NAME)
