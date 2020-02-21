#include "asm.h"

void 		common_error(int num)
{
	ft_fprintf(2, "%s", errors[num]);
	exit (1);
}

void 		lexical_error(unsigned row, unsigned col)
{
	ft_fprintf(2, "%d:%d: lexical error", row + 1, col + 1);
	exit(2);
}

void 		token_error(t_lex *lx)
{
	ft_fprintf(2, "%d:%d: "
			   "unexpected %s \"%s\"", lx->row + 1, lx->col + 1,
			   tokens[lx->type], lx->lex);
	exit(3);
}

void 		argument_error(t_lex *lx, char *op)
{
	ft_fprintf(2, "%d:%d: "
			   "invalid argument %s \"%s\" for operator \"%s\"",
			   lx->row + 1, lx->col + 1, tokens[lx->type], lx->lex, op);
	exit(4);
}

void 		undeclared_label_error(t_lab *lab)
{
	t_lab 	*lab_next;

	while (lab)
	{
		lab_next = lab->next;
		ft_fprintf(2, "undeclared label \"%s\" at %d:%d\n",
				   lab->name, lab->row + 1, lab->col + 1);
		ft_strdel(&lab->name);
		free(lab);
		lab = lab_next;
	}
	exit(5);
}