#ifndef PHYLO_H
#define PHYLO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_param
{
	int	prog_start;
	int	n;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	turns_to_eat;

	t_mutex	*left;
	t_mutex	*right;
	t_phlst	*plist;
	int		must_die;
}			t_param;


typedef struct s_list_phylo
{
	int		index;
	int		something;
	t_phlst	*next;
	struct timeval	lst_eating_time;
}			t_phlst;


//exit.c
int		exit_phylo(t_param *data, int flag);

//algorithm.c
void	*print_action(int n, int action);
int		phylosophers_act(t_param *data);

//parsing.c
t_param	*parsing(int argc, char **argv);

//list_operations.c
t_phlst	*init_phylo_list(t_phlst *plist, int n);

#endif