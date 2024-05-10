/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:48:25 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/10 17:22:11 by tkartasl         ###   ########.fr       */
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

long long	print_time(long long start)
{
	long long		elapsed;

	elapsed = get_current_time() - start;
	return (elapsed);
}

int	check_if_alive(t_philo_data *data)
{
	long long	elapsed;

	//pthread_mutex_lock(data->lock);
	elapsed = print_time(data->info->start);
	if (elapsed - data->prev_meal < (long long)data->info->time_die)
		return (0);
	//pthread_mutex_unlock(data->lock);
	printf("%lld start\n", print_time(data->info->start));
	printf("%lld prev meal\n", data->prev_meal);
	printf("%lld without meal\n", print_time(data->info->start) - data->prev_meal);
	printf("%d ttd\n", data->info->time_die);
	return (1);
}
