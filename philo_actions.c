/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/25 16:05:56 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	get_elapsed_time(struct timeval start)
{
	long long		elapsed;
	struct timeval	current;

	memset(&current, 0, sizeof(struct timeval));
	gettimeofday(&current, 0);
	elapsed = ((current.tv_sec-start.tv_sec)*1000000LL
			+ current.tv_usec-current.tv_usec) / 1000;
	return (elapsed);
}

static int	print_action(t_philo_data *data, int nbr, char *msg)
{
	pthread_mutex_lock(&data->info->write);
	if (get_elapsed_time(data->prev_meal) >= data->info->time_die)
	{
		printf("%lld %d died\n", get_elapsed_time(data->sim_start), nbr);
		return (1);
	}
	printf("%lld %d %s\n", get_elapsed_time(data->sim_start), nbr, msg);
	pthread_mutex_unlock(&data->info->write);
	return (0);
}

int	sleeping(t_philo_data *data)
{
	if (get_elapsed_time(data->prev_meal) >= data->info->time_die)
	{
		printf("%lld %d died\n", get_elapsed_time(data->prev_meal), data->nbr);
		return (1);
	}
	print_action(data, data->nbr, "is sleeping\n");
	usleep(data->info->time_sleep * 1000);
	return (0);
}

int	eating(t_philo_data *data)
{
	if (get_elapsed_time(data->prev_meal) >= data->info->time_die)
	{	 
		printf("%lld %d died\n", get_elapsed_time(data->prev_meal), data->nbr);
		return (1);
	}
	gettimeofday(&data->prev_meal, 0);
	pthread_mutex_lock(&data->fork);
	if (data->nbr == 1 && data->info->philo_count > 1)
		pthread_mutex_lock(&data[data->info->philo_count].fork);
	else
		pthread_mutex_lock(&data[data->nbr - 2].fork);
	if (print_action(data, data->nbr, "has taken a fork\n") != 0)
		return (1);
	if (print_action(data, data->nbr, "is eating\n") != 0)
		return (1);
	usleep(data->info->time_eat * 1000);
	pthread_mutex_unlock(&data->fork);
	if (data->nbr == 1)
		pthread_mutex_unlock(&data[data->info->philo_count].fork);
	else
		pthread_mutex_unlock(&data[data->nbr - 2].fork);
	data->meals++;
	return (0);
}

int	thinking(t_philo_data *data)
{
	if (get_elapsed_time(data->prev_meal) >= data->info->time_die)
	{	 
		printf("%lld %d died\n", get_elapsed_time(data->prev_meal), data->nbr);
		return (1);
	}
	print_action(data, data->nbr, "is thinking\n");
	return (0);
}
