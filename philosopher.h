/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagdano <nmagdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:40:27 by nmagdano          #+#    #+#             */
/*   Updated: 2024/07/09 15:43:57 by nmagdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

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

	int					is_eating;
	pthread_mutex_t		philo_mutex;
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
	t_fork				**forks;

	int					prog_must_die;
	pthread_mutex_t		param_mutex;
	pthread_mutex_t		mutex_printf;
}			t_param;


void			join_all_threads(t_param *data, int n);
//routine_philo.c
int				philo_routine(t_phlst *p, t_param *sd, pthread_mutex_t *sd_mutex);

//usleep.c
int				my_usleep(long long period, t_param *data);

//exit.c
void			join_all_threads(t_param *data, int n);
void			destroy_all_mutex(t_param *data, t_fork **forks);
int				exit_phylo(t_param *data, int flag);

//define_dead_philo.c
int				is_dead_signal(t_param *data, t_phlst *philo);
int				someone_is_dead(t_param *shared_data, pthread_mutex_t *sd_mutex);
int				is_dead(t_param *data, t_phlst *philo);

//manage_forks.c
pthread_mutex_t	*min_fork(t_phlst *one_philo);
pthread_mutex_t	*max_fork(t_phlst *one_philo);
int				max_frk_lst_usr(t_phlst *one_philo);
int				min_frk_lst_usr(t_phlst *one_philo);

//monitoring.c
int				everyone_ate_turns(int turns_to_eat, t_phlst **philos, int n);
int				monitore_endlessly(t_param *data);
int				monitore_while_turns(t_param *data);
int				monitore(t_param *data);

//sleeping_routin.c
int				sleeping_routine(t_phlst *philo, t_param *shared_data);

//eating_routin.c
// void	finish_eating_turn(t_phlst *philo);
int				eating_routine(t_phlst *philo, t_param *shared_data);
int				taking_forks(t_phlst *p, t_param *sd, pthread_mutex_t *sd_mutex);

//algorithm.c
void			*print_action(int n, int action, t_param *data);
int				create_threads(t_param *data);
void			*thread_start(void *one_philo);

//parsing.c
t_param			*parsing(int argc, char **argv);

//init_data.c
t_phlst			*init_plist_and_forks(t_phlst **plist, int n, t_fork **forks);
void			init_data(t_phlst **plist, t_param *data, t_fork **forks);

//validate_input.c
int				validate(char *arg);

//ft_atoi.c
int				ft_atoi(const char *str);

//dbg.c
void			print_data_list(t_param *data);
int				min_frk_id(t_phlst *one_philo);
int				max_frk_id(t_phlst *one_philo);
void			*action_dbg(int action);
#endif
