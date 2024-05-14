/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:05:51 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/14 12:58:26 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_args
{
	int				philo_count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_to_eat;
	int				alive;
	pthread_mutex_t	write;
}				t_args;

typedef struct s_philos
{
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	eat;
	int				meals;
	int				nbr;
	int				philo_count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_to_eat;
	long			prev_meal;
	long			start;
	t_args			*info;
}				t_philo_data;

typedef struct s_monitor
{
	pthread_t		monitor;
	t_philo_data	**data;
}				t_monitor;

int				check_arguments(int argc, char *argv[], t_args *data);
void			eating(t_philo_data *data);
void			ft_free_pointer_array(t_philo_data **arr);
long			print_time(long start);
t_philo_data	**init_philo_array(t_args *data);
void			print_action(t_philo_data *data, int msg_nbr);
void			time_to_loop(long time_to, t_philo_data *data);
long			get_current_time(void);
int				check_if_alive(t_philo_data *data);
int				init_timers(t_philo_data **philos, pthread_mutex_t *forks);
void			free_and_exit(t_philo_data **philos, pthread_mutex_t *forks);
pthread_mutex_t	*create_forks(t_args *data, t_philo_data **philos);
void			*monitoring(void *arg);
int				check_meal_count(t_philo_data *data);
int				check_exit_status(t_philo_data *data);
void			one_philo_eat(t_philo_data *data);

#endif