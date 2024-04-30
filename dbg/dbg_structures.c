#include "../phylosopher.h"

void	print_philo_struct(t_phlst *plist)
{
	printf("Philo index %i; ", plist->index);
	printf("last_eating_time %li; ", plist->lst_eating_time.tv_sec);
	printf("Left fork %i; ", plist->left_fork->fork);
	printf("Right fork %i; ", plist->right_fork->fork);
	printf("must die %i.\n", plist->must_die);
}

void	print_data_list(t_param *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		print_philo_struct(data->plist[i]);
		i++;
	}
}

