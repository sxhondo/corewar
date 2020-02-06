#include "asm.h"

void 		common_error(int num)
{
	ft_fprintf(2, errors[num]);
	exit (1);
}

void 		lexical_error(unsigned row, unsigned col)
{
	ft_fprintf(2, "lexical error: %d:%d", row, col);
	exit(2);
}
