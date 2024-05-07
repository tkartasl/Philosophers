/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/07 15:26:56 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_and_exit(t_philo_data **philos, pthread_mutex_t *forks)
{
	pthread_mutex_destroy(&philos[0]->info->write);
	ft_free_pointer_array(philos);
	free(forks);
}

static void	*monitoring(void *arg)
{
	t_monitor	*m;
	int			i;
	long long	elapsed;

	elapsed = 0;
	i = 0;
	m = (t_monitor *)arg;
	while (m->data[0]->info->sim_start == 0);
	while (1)
	{
		if (i == m->data[0]->info->philo_count)
			i = 0;
		elapsed = print_time(m->data[i]->prev_meal);
		if (elapsed >= m->data[i]->info->time_die)
		{
			printf("%lld\n", elapsed);
			pthread_mutex_lock(&m->data[0]->info->write);
			m->data[i]->info->death_count = 1;
			pthread_mutex_unlock(&m->data[0]->info->write);
			printf("%lld %d died\n", print_time(m->data[0]->start), m->data[i]->nbr);
			break ;
		}
		if (m->data[i]->meals == m->data[i]->info->times_to_eat)
			break ;
		i++;
	}
	return (0);
}

static void	*sim(void *arg)
{
	t_philo_data	*data;

	data = (t_philo_data *)arg;
	while (data->info->sim_start == 0);
	data->start = get_current_time();
	data->prev_meal = get_current_time();
	if (data->nbr % 2 == 0)
		usleep(300);
	while (data->info->death_count == 0)
	{
		eating(data);
		if (data->meals == data->info->times_to_eat)
			break ;
		print_action(data, 3);
		//time_to_loop(data, data->info->time_sleep);
		ft_usleep(data->info->time_sleep);
		print_action(data, 4);
		//sleeping(data);
		//thinking(data);
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
		data->sim_start = 1;
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
	pthread_mutex_t	*forks;
	t_monitor		mt;

	memset(&data, 0, sizeof(t_args));
	memset(&mt, 0, sizeof(t_monitor));
	if (check_arguments(argc, argv, &data) != 0)
		return (1);
	philos = init_philo_array(&data);
	if (philos == 0)
		return (1);
	forks = assign_forks(&data, philos);
	if (forks == 0)
	{
		ft_free_pointer_array(philos);
		return (1);
	}
	if (create_threads(philos, &data, &mt) == 1)
	{
		free_and_exit(philos, forks);
		return (1);
	}
	free_and_exit(philos, forks);
	return (0);
}
