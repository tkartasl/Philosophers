/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:05:51 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/22 14:10:42 by tkartasl         ###   ########.fr       */
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
	int			philo_count;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			times_to_eat;
	long long	elapsed;
}				t_args;

typedef struct s_philos
{
	pthread_t		philo;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
}

int	ft_atoi(const char *str);

#endif