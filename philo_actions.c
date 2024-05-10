/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/10 17:22:04 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo_data *data, int msg_nbr)
{
	long long	time;
	char		*str;

	str = 0;
	if (data->info->death_count != 0)
		return ;
	pthread_mutex_lock(&data->info->write);
	time = print_time(data->info->start);
	if (msg_nbr == 1)
		str = "has taken a fork\n";
	else if (msg_nbr == 2)
		str = "is eating\n";
	else if (msg_nbr == 3)
		str = "is sleeping\n";
	else if (msg_nbr == 4)
		str = "is thinking\n";
	if (data->info->death_count == 0)
		printf("%lld %d %s", time, data->nbr, str);
	pthread_mutex_unlock(&data->info->write);
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
	//pthread_mutex_lock(data->lock);
	data->prev_meal = print_time(data->info->start);
	//pthread_mutex_unlock(data->lock);
	time_to_loop(data->info->time_eat);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	data->meals++;
}
