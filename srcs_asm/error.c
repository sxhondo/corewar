#include "asm.h"

void 		common_error(int num)
{
	ft_fprintf(2, errors[num]);
	exit (1);
}

void 		lexical_error(unsigned row, unsigned col)
{
	ft_fprintf(2, "%d:%d: lexical error", row + 1, col + 1);
	exit(2);
}
