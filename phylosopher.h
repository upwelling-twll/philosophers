#ifndef PHYLO_H
#define PHYLO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_fork
{
	int					fork;
	pthread_mutex_t		*fork_mutex;
	int					last_user;
}			t_fork;

typedef struct s_list_phylo
{
	int					index;
	int					prog_start;
	int					n;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					turns_to_eat;
	struct timeval		lst_eating_time;

	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread;


	int					must_die;
//	t_param				*param;
	struct s_list_phylo	*next;
}			t_phlst;

typedef struct s_param
{
	int					n;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					turns_to_eat;
	t_phlst				**plist;

	pthread_mutex_t		*param_mutex;
	pthread_mutex_t		*mutex_printf;
}			t_param;

//exit.c
int		exit_phylo(t_param *data, int flag);

//algorithm.c
void	*print_action(int n, int action);
int		phylosophers_act(t_param *data, t_fork **forks);

//parsing.c
t_param	*parsing(int argc, char **argv);

//list_operations.c
t_phlst	*init_plist_and_forks(t_phlst **plist, int n, t_fork **forks);

//dbg.c
void	print_data_list(t_param *data, t_phlst **forks);

#endif
