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
	pthread_mutex_t		fork_mutex;
	int					last_user;
}			t_fork;

typedef struct s_list_phylo
{
	int					index;
	struct timeval		lst_eating_time;

	t_fork				*left_fork;
	t_fork				*right_fork;
	int					turns;
	pthread_t			thread;

	int					must_die;
	struct s_param		**param;
}			t_phlst;

typedef struct s_param
{
	int					n;
	size_t				time_to_eat;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_think;
	int					turns_to_eat;
	struct timeval		prog_start;
	t_phlst				**plist;

	int					prog_must_die;
	pthread_mutex_t		param_mutex;
	pthread_mutex_t		mutex_printf;
}			t_param;


void	join_all_threads(t_param *data, int n);

//usleep.c
void	my_usleep(int	period);

//exit.c
void	destroy_all_mutex(t_param *data, t_fork **forks);
int		exit_phylo(t_param *data, int flag);

//monitoring.c
int		is_dead(t_param *data, t_phlst *philo);
int		monitore_endlessly(t_param *data);
int		monitore_while_turns(t_param *data);

//algorithm.c
void	*print_action(int n, int action);
int		phylosophers_act(t_param *data, t_fork **forks);

//parsing.c
t_param	*parsing(int argc, char **argv);

//list_operations.c
t_phlst	*init_plist_and_forks(t_phlst **plist, int n, t_fork **forks, t_param *data);



//dbg.c
void	print_data_list(t_param *data, t_phlst **forks);

#endif
