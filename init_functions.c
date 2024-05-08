/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:30:50 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/08 12:16:39 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	init_mutex(void)
{
	pthread_mutex_t	new;

	pthread_mutex_init(&new, NULL);
	return (new);
}

static t_philo_data	*init_philo_struct(void)
{
	t_philo_data	*new;

	new = malloc(sizeof(t_philo_data));
	if (new == 0)
		return (0);
	return (new);
}

t_philo_data	**init_philo_array(t_args *data)
{
	t_philo_data	**philos;
	int				i;

	i = 0;
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
		philos[i]->nbr = i + 1;
		philos[i]->info = data;
		i++;
	}
	philos[i] = 0;
	return (philos);
}

pthread_mutex_t	*assign_forks(t_args *data, t_philo_data **philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc((data->philo_count) * sizeof(pthread_mutex_t));
	if (forks == 0)
		return (0);
	while (i < data->philo_count)
	{
		forks[i] = init_mutex();
		i++;
	}
	i = 0;
	while (philos[i] != 0)
	{
		if (i == data->philo_count)
			break ;
		philos[i]->left_fork = &forks[i];
		if (i != 0)
			philos[i]->right_fork = &forks[i - 1];
		i++;
	}
	pthread_mutex_init(&philos[0]->info->write, NULL);
	philos[0]->right_fork = &forks[data->philo_count - 1];
	return (forks);
}
