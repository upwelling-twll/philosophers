#include "phylosopher.h"

int	main(int argc, char *argv[])
{
	t_param	*data;
	t_fork	*forks[200];
	int		i;

	data = parsing(argc, argv);
	if (data == NULL)
		return (exit_phylo(data, 2));
	gettimeofday(&(data->prog_start), NULL);
	phylosophers_act(data, forks);
	exit_phylo(data, 1);
	printf("the end ~para-pa-para pa!\n");
	return (0);
}
