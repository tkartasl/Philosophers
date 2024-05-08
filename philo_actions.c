/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/08 15:44:39 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday failed\n", 20);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	time_to_loop(size_t time_to)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_to)
		usleep(100);
}

void	print_action(t_philo_data *data, int msg_nbr)
{
	long long	time;
	char		*str;

	str = 0;
	if (data->info->death_count != 0)
		return ;
	pthread_mutex_lock(&data->info->write);
	time = print_time(data->start);
	if (msg_nbr == 1)
		str = "has taken a fork\n";
	else if (msg_nbr == 2)
	{
		str = "is eating\n";
		data->prev_meal = time;
	}
	else if (msg_nbr == 3)
		str = "is sleeping\n";
	else if (msg_nbr == 4)
		str = "is thinking\n";
	if (data->info->death_count == 0)
		printf("%lld %d %s", time, data->nbr, str);
	pthread_mutex_unlock(&data->info->write);
}

long long	print_time(long long start)
{
	long long		elapsed;

	elapsed = get_current_time() - start;
	return (elapsed);
}

void	eating(t_philo_data *data)
{
	pthread_mutex_lock(data->left_fork);
	print_action(data, 1);
	if (data->info->philo_count == 1)
	{
		while (data->info->death_count == 0)
			usleep(100);
		return ;
	}
	pthread_mutex_lock(data->right_fork);
	print_action(data, 1);
	print_action(data, 2);
	time_to_loop(data->info->time_eat);
	data->meals++;
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}
