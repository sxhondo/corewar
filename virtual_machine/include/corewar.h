/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:10:22 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/08 13:32:17 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"
# include "op.h"
# include "sdl_struct.h"

# define DUMP "-dump"
# define N "-n"
# define COR ".cor"
# define LINE_SIZE 97
# define COUNT_OP 16

/*
** cc_live - cycle in which the live operation was last performed
** cc_op - number of cycles remaining before the operation is executed
** c_byte_op - how much to step over before the next operation
*/

typedef struct		s_processes
{

	int					cc_live;
	int					cc_op : 11;
	int					carry : 2;
	int					code_op;
	int					index : 14;
	int					reg[REG_NUMBER];
	struct s_processes	*next;
	struct s_processes	*prev;
}					t_processes;

typedef struct		s_info
{
	int				dump;
	t_header		players[MAX_PLAYERS];
	unsigned char	*arena;
	t_processes		*processes;
	int				count_process;
	int				last_live;
	int				count_cycles;
	int				cycle_to_die;
	int				count_live;
	int				count_check;
	int				i;
}					t_info;

typedef struct		s_op
{
	char					*name;
	unsigned int			count_args : 2;
	unsigned char			args_types[3];
	unsigned int			code : 6;
	unsigned int			cycle_for_exec : 11;
	char					*comment;
	unsigned int			change_carry : 1;
	unsigned int			args_types_code : 1;
	unsigned char			t_dir_size : 3;
	void					(*func)(t_info *, t_processes **, t_sdl *);
}					t_op;

void				save_carry(t_processes **prs, unsigned char *arena,
					unsigned char arg_reg);
void				read_card(void *dst, void *src,
							short int value, int length);
void				usage();
void				write_card(void *dst, void *src,
							short int value, int length);
void				present_champion(t_header *players);
unsigned int		get_magic(int fd);
int					get_arg(unsigned char code_arg, short int *shift,
						unsigned char *arena, t_processes **prs);
void				shift_next_op(unsigned char code_arg,
						short int num_fun, t_processes **prs, t_sdl *sdl);
int					get_t_dir(short int current_location,
							int shift, unsigned char *arena);
short int			get_t_ind(short int current_location,
						int shift, unsigned char *arena, int mod);
void				set_t_reg(int value, int shift,
						unsigned char *arena, t_processes **prs);
int					get_t_reg(int *value, int shift,
						unsigned char *arena, t_processes **prs);
unsigned short int	reverse_short_int(unsigned short int num);
void				read_arg(t_info *info, int argc, char *argv[]);
void				error(int err);
void				gladiatorial_fight(int *play, t_info *info, t_sdl *sdl);
char				get_nibble(unsigned char nibble);
void				print_arena(unsigned char *arena);
int					get_bytes_to_skip(int num, unsigned char code_arg);
int					reverse_int(int num);
void				initialize_visual_arena(t_sdl *sdl, t_info *info);
void				set_replica(t_processes *processes,
								t_info *info, t_sdl *sdl);
void				draw_annotations(t_info *info, t_sdl *sdl);
void				event_handler(t_info *info, t_sdl *sdl);

void				update_live(int player, int value, t_sdl *sdl);
void				update_byte(int location, t_sdl *sdl);
void				create_cursor(int location, int player, t_sdl *sdl);
void				update_bytes(int location, int length,
									int player, t_sdl *sdl);
void				set_byte(int location, int player, t_sdl *sdl);
void				move_cursor(int location, int shift,
									int player, t_sdl *sdl);

void				refresh_arena(t_info *info, t_sdl *sdl);
void				render_text(char *text, t_render *render_info,
												SDL_Surface *surface);
void				show_data(t_info *info, t_sdl *sdl);
void				announce_winner(int player, int *play,
									t_info *info, t_sdl *sdl);
void				free_resources(t_sdl *sdl);
short int			get_address(short int shift);

/*
** Создание и удаление кареток
*/

void				create_processes(t_info *info);
void				add_elem(t_processes **processes,
						int index, int number_player);
void				delete_elem(t_processes **processes, t_info *info);

/*
** Functions pointed to by the g_op_tab structure
*/

void				live_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				ld_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				st_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				add_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				sub_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				and_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				or_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				xor_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				zjmp_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				ldi_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				sti_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				fork_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				lld_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				lldi_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				lfork_op(t_info *info, t_processes **prs, t_sdl *sdl);
void				aff_op(t_info *info, t_processes **prs, t_sdl *sdl);

static t_op	g_op_tab[16] = {
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, &live_op},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1, 4, &ld_op},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 1, 4, &st_op},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1, 4, &add_op},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 1, 4, &sub_op},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 1, 4, &and_op},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 1, 4, &or_op},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 1, 4, &xor_op},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 0, 2, &zjmp_op},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 2, &ldi_op},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 2, &sti_op},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 0, 2, &fork_op},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1, 4, &lld_op},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2, &lldi_op},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 0, 2, &lfork_op},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 1, 4, &aff_op}
};

#endif
