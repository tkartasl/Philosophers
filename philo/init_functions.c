/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:30:50 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/14 09:26:12 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_timers(t_philo_data **philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos[0]->info->philo_count)
	{
		philos[i]->start = get_current_time();
		philos[i]->nbr = i + 1;
		philos[i]->meals = 0;
		if (pthread_mutex_init(&philos[i]->lock, NULL) != 0)
		{
			free_and_exit(philos, forks);
			return (1);
		}
		if (pthread_mutex_init(&philos[i]->eat, NULL) != 0)
		{
			free_and_exit(philos, forks);
			return (1);
		}
		philos[i]->prev_meal = get_current_time();
		i++;
	}
	return (0);
}

static t_philo_data	*init_philo_struct(t_args *data)
{
	t_philo_data	*new;

	new = malloc(sizeof(t_philo_data));
	if (new == 0)
		return (0);
	new->philo_count = data->philo_count;
	new->time_die = data->time_die;
	new->time_eat = data->time_eat;
	new->time_sleep = data->time_sleep;
	new->times_to_eat = data->times_to_eat;
	return (new);
}

static void	assign_forks(t_args *d, t_philo_data **philos, pthread_mutex_t *f)
{
	int	i;

	i = 0;
	while (philos[i] != 0)
	{
		if (i == d->philo_count)
			break ;
		philos[i]->left_fork = &f[i];
		if (i != 0)
			philos[i]->right_fork = &f[i - 1];
		i++;
	}
	philos[0]->right_fork = &f[philos[0]->info->philo_count - 1];
}

pthread_mutex_t	*create_forks(t_args *data, t_philo_data **philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc((data->philo_count) * sizeof(pthread_mutex_t));
	if (forks == 0)
		return (0);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_free_pointer_array(philos);
			free(forks);
			return (0);
		}
		i++;
	}
	assign_forks(data, philos, forks);
	if (pthread_mutex_init(&philos[0]->info->write, NULL) != 0)
	{
		free(forks);
		ft_free_pointer_array(philos);
		return (0);
	}
	return (forks);
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
		philos[i] = init_philo_struct(data);
		if (philos[i] == 0)
		{
			ft_free_pointer_array(philos);
			return (0);
		}
		philos[i]->info = data;
		i++;
	}
	philos[i] = 0;
	return (philos);
}
