/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/03 14:01:15 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	elapsed_time(struct timeval start, t_philo_data *data)
{
	long long		elapsed;
	struct timeval	current;
	
	gettimeofday(&current, 0);
	pthread_mutex_lock(&data->action);
	elapsed = ((current.tv_sec-start.tv_sec)*1000000LL
			+ current.tv_usec-start.tv_usec) / 1000;
	pthread_mutex_unlock(&data->action);
	return (elapsed);
}

long long	print_time(t_philo_data *data)
{
	long long		elapsed;
	struct timeval	current;
	
	gettimeofday(&current, 0);
	pthread_mutex_lock(&data->action);
	elapsed = ((current.tv_sec-data->start.tv_sec)*1000000LL
			+ current.tv_usec-data->start.tv_usec) / 1000;
	pthread_mutex_unlock(&data->action);
	return (elapsed);
}

/*static int	print_action(t_philo_data *data, int nbr, char *msg)
{
	if (elapsed_time(data->prev_meal, data) >= data->info->time_die)
	{
		printf("%lld\n", elapsed_time(data->prev_meal, data));
		pthread_mutex_lock(&data->action);
		data->info->death_count = 1;
		pthread_mutex_unlock(&data->action);
		printf("%lld %d died\n", print_time(data), nbr);
		return (1);
	}
	printf("%lld %d %s\n", elapsed_time(data), nbr, msg);
	return (0);
}*/

int	sleeping(t_philo_data *data)
{
	if (data->info->death_count == 1)
		return (1);
	printf("%lld %d is sleeping\n", print_time(data), data->nbr);
	usleep(data->info->time_sleep * 1000);
	return (0);
}

int	eating(t_philo_data *data)
{
	if (data->info->death_count == 1)
		return (1);
	pthread_mutex_lock(data->left_fork);
	printf("%lld %d has taken a fork\n", print_time(data), data->nbr);
	pthread_mutex_lock(data->right_fork);
	printf("%lld %d has taken a fork\n", print_time(data), data->nbr);
	gettimeofday(&data->prev_meal, 0);
	data->meals++;
	printf("%lld %d is eating\n", print_time(data), data->nbr);
	usleep(data->info->time_eat * 1000);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	return (0);
}

int	thinking(t_philo_data *data)
{
	if (data->info->death_count == 1)
		return (1);
	printf("%lld %d is thinking\n", print_time(data), data->nbr);
	return (0);
}
