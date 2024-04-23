#include "../phylosopher.h"



void	init_forks(t_fork **forks, int n)
{
	int	i;

	i = 0;
	while(i < n)
	{
		forks[i] = (t_fork *)malloc(sizeof(t_fork));
		forks[i]->fork = i + 1;
		forks[i]->last_user = 0;
		i++;
	}
}

t_phlst	*init_plist_and_forks(t_phlst **plist, int n, t_fork **forks)
{
	int	i;

	i = 0;
	init_forks(forks, n);
	while(i < n)
	{
		plist[i] = (t_phlst *)malloc(sizeof(t_phlst));
		plist[i] -> index = i + 1;
		plist[i]->must_die = 0;
		if (i != n - 1)
		{
			plist[i] -> left_fork = forks[i];
			plist[i] -> right_fork = forks[i + 1];
		}
		else
		{
			plist[i] -> left_fork = forks[i];
			plist[i] -> right_fork = forks[0];
		}
		i++;
	}
	plist[i] = NULL;
	return (*plist);
}
