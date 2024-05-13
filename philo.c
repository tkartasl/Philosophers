/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/10 19:57:27 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_exit(t_philo_data **philos, pthread_mutex_t *forks)
{
	pthread_mutex_destroy(&philos[0]->info->write);
	free(forks);
	ft_free_pointer_array(philos);
}

static void	*monitoring(void *arg)
{
	t_monitor	*m;
	int			i;

	i = 0;
	m = (t_monitor *)arg;
	while (m->data[0]->info->sim_start == 0)
		continue ;
	while (1)
	{
		if (i == m->data[0]->info->philo_count)
			i = 0;
		if (check_if_alive(m->data[i]) == 1)
		{
			pthread_mutex_lock(&m->data[0]->info->write);
			m->data[i]->info->death_count = 1;
			pthread_mutex_unlock(&m->data[0]->info->write);
			printf("%lld %d died\n", print_time(m->data[i]->info->start),
				m->data[i]->nbr);
			break ;
		}
		if (m->data[i]->info->times_to_eat > 0)
		{
			pthread_mutex_lock(&m->data[i]->info->eat);
			if (m->data[i]->meals == m->data[i]->info->times_to_eat)
			{	
				pthread_mutex_unlock(&m->data[i]->info->eat);
				break ;
			}
		}
		i++;
	}
	return (0);
}

static void	*sim(void *arg)
{
	t_philo_data	*data;

	data = (t_philo_data *)arg;
	while (data->info->sim_start == 0)
		continue ;
	if (data->nbr % 2 == 0)
	{
		usleep(data->info->time_eat / 2 * 1000);
		if (data->nbr / 2 % 2 != 0)
			usleep(500);
	}
	while (data->info->death_count == 0)
	{
		eating(data);
		if (data->info->times_to_eat > 0)
		{
			pthread_mutex_lock(&data->info->eat);
			if (data->meals == data->info->times_to_eat)
			{	
				pthread_mutex_unlock(&data->info->eat);
				break ;
			}
		}
		print_action(data, 3);
		time_to_loop(data->info->time_sleep);
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
	//if (init_mutexes(philos, forks) != 0)
	//	return (1);
	if (init_philo_timers(philos, forks) != 0)
		return (1);
	if (create_threads(philos, &data, &mt) == 1)
	{
		free_and_exit(philos, forks);
		return (1);
	}
	free_and_exit(philos, forks);
	return (0);
}
