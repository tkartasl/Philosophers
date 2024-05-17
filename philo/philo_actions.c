/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/17 11:26:38 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo_data *data, int msg_nbr)
{
	long	time;
	char	*str;
	int		end;

	str = 0;
	pthread_mutex_lock(&data->info->write);
	time = get_current_time() - data->start;
	if (msg_nbr == 1)
		str = "has taken a fork\n";
	else if (msg_nbr == 2)
		str = "is eating\n";
	else if (msg_nbr == 3)
		str = "is sleeping\n";
	else if (msg_nbr == 4)
		str = "is thinking\n";
	end = data->info->alive;
	if (end == 0)
		printf("%ld %d %s", time, data->nbr, str);
	pthread_mutex_unlock(&data->info->write);
}

void	one_philo_eat(t_philo_data *data)
{
	pthread_mutex_lock(data->left_fork);
	print_action(data, 1);
	time_to_loop(data->time_die, data);
	usleep(500);
	pthread_mutex_unlock(data->left_fork);
}

int	pick_forks(t_philo_data *data)
{
	if (data->philo_count == 1)
	{
		one_philo_eat(data);
		return (1);
	}
	pthread_mutex_lock(data->left_fork);
	if (check_exit_status(data) == 1)
	{
		pthread_mutex_unlock(data->left_fork);
		return (1);
	}
	print_action(data, 1);
	pthread_mutex_lock(data->right_fork);
	if (check_exit_status(data) == 1)
	{
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		return (1);
	}
	print_action(data, 1);
	return (0);
}

void	eating(t_philo_data *data)
{
	long	time;

	print_action(data, 2);
	pthread_mutex_lock(&data->lock);
	time = get_current_time() - data->start;
	data->prev_meal = time;
	pthread_mutex_unlock(&data->lock);
	time_to_loop(data->time_eat, data);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_lock(&data->eat);
	data->meals++;
	pthread_mutex_unlock(&data->eat);
}
