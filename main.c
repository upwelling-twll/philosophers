#include "phylosopher.h"

int	main(int argc, char *argv[])
{
	t_param	*data;

	data = parsing(argc, argv);
	if (data == NULL)
		return (exit_phylo(data, 2));
	phylosophers_act(data);
	exit_phylo(data, 1);
	return (0);
}
