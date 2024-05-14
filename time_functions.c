/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:48:25 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/14 09:20:21 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday failed\n", 20);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	time_to_loop(long time_to)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_to)
		usleep(200);
}

long	print_time(long start)
{
	long		elapsed;

	elapsed = get_current_time() - start;
	return (elapsed);
}

int	check_if_alive(t_philo_data *data)
{
	long	elapsed;
	long	start;
	long	prev_meal;

	pthread_mutex_lock(&data->lock);
	start = data->start;
	prev_meal = data->prev_meal;
	pthread_mutex_unlock(&data->lock);
	if (start == prev_meal)
		elapsed = get_current_time() - prev_meal;
	else
		elapsed = get_current_time() - start - prev_meal;
	if (elapsed < data->info->time_die)
		return (0);
	return (1);
}
