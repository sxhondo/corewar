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

void 		undeclared_label_error(char *name, size_t row, size_t col)
{
	ft_fprintf(2, "undeclared label \"%s\" at %d:%d\n",
				   name, row + 1, col + 1);
	exit(5);
}