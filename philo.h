/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:05:51 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/29 12:25:13 by tkartasl         ###   ########.fr       */
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
	pthread_mutex_t	write;
	pthread_mutex_t	get_time;
}				t_args;

typedef struct s_philos
{
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				meals;
	int				nbr;
	struct timeval	start;
	struct timeval	prev_meal;
	t_args			*info;
}				t_philo_data;

int		check_arguments(int argc, char* argv[], t_args *data);
int		sleeping(t_philo_data *data, int *died);
int		eating(t_philo_data *data, int *died);
int		thinking(t_philo_data *data, int *died);
void	ft_free_pointer_array(t_philo_data **arr);

#endif