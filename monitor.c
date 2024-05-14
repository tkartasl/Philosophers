/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:08:45 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/14 09:21:02 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_count(t_philo_data *data)
{
	int	meals;
	int	times_to_eat;

	pthread_mutex_lock(&data->eat);
	meals = data->meals;
	times_to_eat = data->times_to_eat;
	pthread_mutex_unlock(&data->eat);
	if (meals == times_to_eat)
		return (1);
	return (0);
}

static void	change_exit_status(t_philo_data *data)
{
	pthread_mutex_lock(&data->info->write);
	data->info->alive = 1;
	pthread_mutex_unlock(&data->info->write);
}

int	check_exit_status(t_philo_data *data)
{
	int	status;

	pthread_mutex_lock(&data->info->write);
	status = data->info->alive;
	pthread_mutex_unlock(&data->info->write);
	return (status);
}

void	*monitoring(void *arg)
{
	t_monitor	*m;
	int			i;

	i = 0;
	m = (t_monitor *)arg;
	time_to_loop(m->data[i]->info->time_eat / 2);
	while (1)
	{
		if (i == m->data[0]->info->philo_count)
			i = 0;
		if (check_if_alive(m->data[i]) == 1)
		{
			change_exit_status(m->data[i]);
			printf("%ld %d died\n", print_time(m->data[i]->start),
				m->data[i]->nbr);
			break ;
		}
		if (m->data[i]->info->times_to_eat > 0)
			if (check_meal_count(m->data[i]) == 1)
				break ;
		usleep(25);
		i++;
	}
	return (0);
}
