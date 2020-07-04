# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgyles <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/19 20:39:13 by rgyles            #+#    #+#              #
#    Updated: 2020/02/24 14:25:41 by bdudley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VIR_NAME = corewar

ASM_NAME = asm

VIR_DIR = virtual_machine

ASM_DIR = assembler

LIBFT_DIR = libft/

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

all: lib vm asm

vm:
	@echo $(SHIFT) "\n$(GREEN)*** $(GREEN_UNDERLINE)Corewar build summary$(NC)$(GREEN) ***$(NC)\n"
	@make -C $(VIR_DIR)
	@ln -fs $(VIR_DIR)/$(VIR_NAME) $(VIR_NAME)

asm:
	@echo $(SHIFT) "\n$(GREEN)*** $(GREEN_UNDERLINE)Corewar build summary$(NC)$(GREEN) ***$(NC)\n"
	@make -C $(ASM_DIR)
	@ln -fs $(ASM_DIR)/$(ASM_NAME) $(ASM_NAME)

lib:
	@echo $(SHIFT) "$(CLEAR)$(BLUE)Checking libft...$(NC)"
	@make -C $(LIBFT_DIR)
	@echo $(SHIFT) "$(UP)$(CLEAR)$(CHECK_MARK)$(YELLOW) Libft is ready!$(NC)"

clean:
	@echo $(SHIFT) "$(RED)Cleaning libft...$(NC)"
	@make -C $(LIBFT_DIR) clean
	@echo $(SHIFT) "$(RED)Cleaning corewar...$(NC)"
	@make -C $(VIR_DIR) clean
	@echo $(SHIFT) "$(RED)Cleaning assembler...$(NC)"
	@make -C $(ASM_DIR) clean

fclean:
	@echo $(SHIFT) "$(RED)Deleting libft...$(NC)"
	@make -C $(LIBFT_DIR) fclean
	@echo $(SHIFT) "$(RED)Deleting corewar...$(NC)"
	@make -C $(VIR_DIR) fclean
	@echo $(SHIFT) "$(RED)Deleting asm...$(NC)"
	@make -C $(ASM_DIR) fclean
	@rm -f $(VIR_NAME)
	@rm -f $(ASM_NAME)

lclean:
	@make -C $(VIR_DIR) lclean


re: fclean all
