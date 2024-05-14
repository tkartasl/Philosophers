/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/14 13:33:57 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_pointer_array(t_philo_data **arr)
{
	int	n;

	n = 0;
	while (arr[n] != 0)
	{
		pthread_mutex_destroy(arr[n]->left_fork);
		pthread_mutex_destroy(&arr[n]->lock);
		pthread_mutex_destroy(&arr[n]->eat);
		free(arr[n]);
		n++;
	}
	free(arr);
	arr = 0;
}

void	free_and_exit(t_philo_data **philos, pthread_mutex_t *forks)
{
	pthread_mutex_destroy(&philos[0]->info->write);
	free(forks);
	ft_free_pointer_array(philos);
}

static void	*sim(void *arg)
{
	t_philo_data	*data;

	data = (t_philo_data *)arg;
	if (data->nbr % 2 == 0)
		time_to_loop(data->time_eat / 2, data);
	while (check_exit_status(data) == 0)
	{
		eating(data);
		if (data->times_to_eat > 0)
			if (check_meal_count(data) == 1)
				break ;
		print_action(data, 3);
		time_to_loop(data->time_sleep, data);
		print_action(data, 4);
	}
	return (0);
}

static int	create_threads(t_philo_data **philos, t_args *data, t_monitor *mt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mt->data = philos;
	while (j < data->philo_count)
	{
		while (i < data->philo_count)
		{
			if (pthread_create(&philos[i]->philo, NULL, &sim, philos[i]) != 0)
				return (1);
			i++;
			if (i == data->philo_count)
				if (pthread_create(&mt->monitor, NULL, &monitoring, mt) != 0)
					return (1);
		}
		if (pthread_join(philos[j]->philo, NULL) != 0)
			return (1);
		j++;
	}
	if (pthread_join(mt->monitor, NULL) != 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			data;
	t_philo_data	**philos;
	t_monitor		mt;
	pthread_mutex_t	*forks;

	memset(&data, 0, sizeof(t_args));
	if (check_arguments(argc, argv, &data) != 0)
		return (1);
	philos = init_philo_array(&data);
	if (philos == 0)
		return (1);
	forks = create_forks(&data, philos);
	if (forks == 0)
		return (1);
	if (init_timers(philos, forks) != 0)
		return (1);
	if (create_threads(philos, &data, &mt) == 1)
	{
		free_and_exit(philos, forks);
		return (1);
	}
	free_and_exit(philos, forks);
	return (0);
}
