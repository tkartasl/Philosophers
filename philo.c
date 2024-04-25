/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/25 16:05:34 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_exit(t_philo_data **philos)
{
	int	i;

	i = 0;
	while (philos[i] != 0)
	{
		pthread_detach(philos[i]->philo);
		i++;
	}
	pthread_mutex_destroy(&philos[i]->info->write);
	ft_free_pointer_array(philos);
}

static t_philo_data	*init_philo_struct(void)
{
	t_philo_data	*new;

	new = malloc(sizeof(t_philo_data));
	if (new == 0)
		return (0);
	return (new);
}

static t_philo_data	**init_philo_array(t_args *data, int i)
{
	t_philo_data	**philos;

	philos = malloc((data->philo_count + 1) * sizeof(t_philo_data *));
	if (philos == 0)
	{
		write(2, "Malloc failure\n", 15);
		return (0);
	}
	while (i < data->philo_count)
	{
		philos[i] = init_philo_struct();
		if (philos[i] == 0)
		{
			ft_free_pointer_array(philos);
			return (0);
		}
		pthread_mutex_init(&philos[i]->fork, NULL);
		philos[i]->nbr = i + 1;
		philos[i]->info = data;
		i++;
	}
	philos[i] = 0;
	pthread_mutex_init(&data->write, NULL);
	return (philos);
}

void	*simulation(void *arg)
{
	t_philo_data	*data;

	data = (t_philo_data *)arg;
	gettimeofday(&data->sim_start, 0);
	gettimeofday(&data->prev_meal, 0);
	while (1)
	{
		/*if (data->info->times_to_eat != 0
			&& data->meals == data->info->times_to_eat)
		{
			pthread_detach(data->philo);
		}*/
		if (data->info->philo_count > 1)
			if (eating(data) == 1)
				break ;
		sleeping(data);
		thinking(data);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			data;
	t_philo_data	**philos;
	int				i;
	int				j;

	j = 0;
	i = 0;
	philos = 0;
	memset(&data, 0, sizeof(t_args));
	if (check_arguments(argc, argv, &data) != 0)
		return (1);
	philos = init_philo_array(&data, i);
	if (philos == 0)
	{
		ft_free_pointer_array(philos);
		return (1);
	}
	while (j < data.philo_count)
	{
		while (i < data.philo_count)
		{
			if (pthread_create(&philos[i]->philo, NULL, &simulation, &data) != 0)
			{
				ft_free_pointer_array(philos);
				return (1);
			}
			i++;
		}
		if (pthread_join(philos[j]->philo, NULL) != 0)
		{
				ft_free_pointer_array(philos);
				return (1);
		}
	}
	free_and_exit(philos);
	return (0);
}
