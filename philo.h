/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:05:51 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/03 14:02:49 by tkartasl         ###   ########.fr       */
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
}				t_args;

typedef struct s_philos
{
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	action;
	int				meals;
	int				nbr;
	struct timeval	start;
	struct timeval	prev_meal;
	t_args			*info;
}				t_philo_data;

typedef struct	s_monitor
{
	pthread_t		monitor;
	t_philo_data	**data;
}				t_monitor;

int			check_arguments(int argc, char* argv[], t_args *data);
int			sleeping(t_philo_data *data);
int			eating(t_philo_data *data);
int			thinking(t_philo_data *data);
void		ft_free_pointer_array(t_philo_data **arr);
long long	elapsed_time(struct timeval start, t_philo_data *data);
long long	print_time(t_philo_data *data);

#endif