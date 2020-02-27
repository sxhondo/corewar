#include "vm.h"

void	init_struct(t_corewar *corewar)
{
	corewar->flgs.flgs = 0;
	corewar->champs = NULL;
}

t_champion	*create_node(const char *fname)
{
	t_champion	*new;

	if (!(new = malloc(sizeof(t_champion))))
		return (NULL);
	new->filename = (char *)fname;
	new->lst = new;
	new->next = NULL;
	return (new);
}

void		push_back_champ(t_champion *champs, const char *fname)
{
	if (!champs)
		champs = create_node(fname);
	else
		;
}
