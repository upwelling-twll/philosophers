#include "../phylosopher.h"

int	exit_phylo(t_param *data, int flag)
{
	if (data != NULL)
		free(data);
	if (flag == 2)
		write(1, "Invalid parameters\n", 20);
	if (flag == 1)
		write(1, "Program exit\n", 14);
	return (1);
}
