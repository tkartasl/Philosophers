/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:05:51 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/07 15:27:36 by tkartasl         ###   ########.fr       */
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

typedef struct	s_args
{
	int				philo_count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_to_eat;
	int				sim_start;
	int				death_count;
	pthread_mutex_t	write;
}				t_args;

typedef struct s_philos
{
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				meals;
	int				nbr;
	long long		start;
	long long		prev_meal;
	t_args			*info;
}				t_philo_data;

typedef struct	s_monitor
{
	pthread_t		monitor;
	t_philo_data	**data;
}				t_monitor;

int				check_arguments(int argc, char* argv[], t_args *data);
void			sleeping(t_philo_data *data);
void			eating(t_philo_data *data);
void			thinking(t_philo_data *data);
void			ft_free_pointer_array(t_philo_data **arr);
long long		elapsed_time(struct timeval start, t_philo_data *data);
long long		print_time(long long start);
t_philo_data	**init_philo_array(t_args *data);
pthread_mutex_t *assign_forks(t_args *data, t_philo_data **philos);
void			print_action(t_philo_data *data, int msg_nbr);
void			time_to_loop(t_philo_data *data, int time_to);
int				ft_usleep(size_t milliseconds);
size_t			get_current_time(void);

#endif