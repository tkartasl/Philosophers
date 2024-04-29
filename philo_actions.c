/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/29 15:39:10 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	elapsed_time(struct timeval start, t_philo_data *data)
{
	long long		elapsed;
	struct timeval	current;

	pthread_mutex_lock(&data->info->get_time);
	gettimeofday(&current, 0);
	pthread_mutex_unlock(&data->info->get_time);
	elapsed = ((current.tv_sec-start.tv_sec)*1000000LL
			+ current.tv_usec-start.tv_usec) / 1000;
	return (elapsed);
}

static int	print_action(t_philo_data *data, int nbr, char *msg, int *died)
{
	//if (*died != 0)
	//	return (1);
	//pthread_mutex_lock(&data->info->write);
	if (elapsed_time(data->prev_meal, data) >= data->info->time_die)
	{
		pthread_mutex_lock(&data->info->write);
		printf("%lld\n", elapsed_time(data->prev_meal, data));
		*died = 1;
		printf("%lld %d died\n", elapsed_time(data->start, data), nbr);
		pthread_mutex_unlock(&data->info->write);
		return (1);
	}
	pthread_mutex_lock(&data->info->write);
	printf("%lld %d %s\n", elapsed_time(data->start, data), nbr, msg);
	pthread_mutex_unlock(&data->info->write);
	return (0);
}

int	sleeping(t_philo_data *data, int *died)
{
	/*long long	elapsed;
	
	elapsed = elapsed_time(data->prev_meal, data);
	if (elapsed + data->info->time_sleep >= data->info->time_die)
	{
		usleep((data->info->time_die - elapsed) * 1000);
		print_action(data, data->nbr, "died", died);
			return (1);
	}*/	
	if (print_action(data, data->nbr, "is sleeping", died) != 0)
		return (1);
	usleep(data->info->time_sleep * 1000);
	return (0);
}

int	eating(t_philo_data *data, int *died)
{
	if (data->nbr % 2 == 0)
	{
		pthread_mutex_lock(data->left_fork);
		if (print_action(data, data->nbr, "has taken a fork", died) != 0)
			return (1);
		pthread_mutex_lock(data->right_fork);
		if (print_action(data, data->nbr, "has taken a fork", died) != 0)
			return (1);
	}
	else
	{
		pthread_mutex_lock(data->right_fork);
		if (print_action(data, data->nbr, "has taken a fork", died) != 0)
			return (1);
		pthread_mutex_lock(data->left_fork);
		if (print_action(data, data->nbr, "has taken a fork", died) != 0)
			return (1);
	}
	gettimeofday(&data->prev_meal, 0);
	//pthread_mutex_lock(&data->info->write);
	printf("%lld %d is eating\n", elapsed_time(data->start, data), data->nbr);
	//pthread_mutex_unlock(&data->info->write);
	usleep(data->info->time_eat * 1000);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	data->meals++;
	return (0);
}

int	thinking(t_philo_data *data, int *died)
{
	if (print_action(data, data->nbr, "is thinking", died) != 0)
		return (1);
	return (0);
}
