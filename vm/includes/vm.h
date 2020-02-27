#ifndef VM_H
# define VM_H

# include "ft_ptintf.h"
# define N_FLG 1u
# define DUMP_FLG 2u
# define A_FLG 3u

typedef struct	s_campion
{
	char				*filename;
	struct s_champion	*lst;
	struct s_champion	*next;
}				t_champion;

typedef struct	s_flgs
{
	uint8_t	flgs;
	int		nxt_player_num;
	int		nbr_cycles_dump;
}				t_flgs;

typedef struct	s_corewar
{
	t_flgs		flgs;
	t_champion	*champs;
}				t_corewar;

void	init_struct(t_corewar *corewar);
t_champion	*create_node(const char *fname);
void	push_back_champ(t_champion *champs, const char *fname);

void	get_usage(void);
void	get_error(void);

void	parse_arguments(int ac, char **av, t_corewar *corewar);
void	check_arg(const char *arg, t_corewar *corewar);
void	write_flg_arg(const char *arg, t_flgs *flgs);

_Bool	is_flg(const char *arg, t_flgs *flgs);
_Bool is_champion(const char *arg, t_champion *champs);

#endif
