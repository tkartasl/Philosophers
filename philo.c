/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/29 14:55:56 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_exit(t_philo_data **philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (philos[i] != 0)
	{
		pthread_detach(philos[i]->philo);
		i++;
	}
	pthread_mutex_destroy(&philos[0]->info->write);
	ft_free_pointer_array(philos);
	free(forks);
}

static t_philo_data	*init_philo_struct(void)
{
	t_philo_data	*new;

	new = malloc(sizeof(t_philo_data));
	if (new == 0)
		return (0);
	return (new);
}

pthread_mutex_t init_mutex(void)
{
	pthread_mutex_t	new;

	pthread_mutex_init(&new, NULL);
	return (new);
}

pthread_mutex_t *assign_forks(t_args *data, t_philo_data **philos)
{
	pthread_mutex_t	*forks;
	int			i;

	i = 0;
	forks = malloc((data->philo_count) * sizeof(pthread_mutex_t));
	while (i < data->philo_count)
	{
		forks[i] = init_mutex();		
		i++;
	}
	i = 0;
	while(philos[i] != 0)
	{
		philos[i]->left_fork = &forks[i];
		if (i != 0)
			philos[i]->right_fork = &forks[i - 1];
		i++;
	}
	philos[0]->right_fork = &forks[data->philo_count - 1];
	return (forks);
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
		philos[i]->nbr = i + 1;
		philos[i]->info = data;
		i++;
	}
	philos[i] = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->get_time, NULL);
	return (philos);
}

void	*simulation(void *arg)
{
	t_philo_data	*data;
	int				died;			

	died = 0;
	data = (t_philo_data *)arg;
	pthread_mutex_lock(&data->info->get_time);
	gettimeofday(&data->start, 0);
	gettimeofday(&data->prev_meal, 0);
	pthread_mutex_unlock(&data->info->get_time);
	while (1)
	{
		if (eating(data, &died) != 0)
			break ;
		if (data->meals == data->info->times_to_eat)
			break ;
		if (sleeping(data, &died) != 0)
			break ;
		if (thinking(data, &died) != 0)
			break ;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			data;
	t_philo_data	**philos;
	pthread_mutex_t	*forks;
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
	forks = assign_forks(&data, philos);
	if (forks == 0)
	{
		ft_free_pointer_array(philos);
		return (1);
	}
	while (j < data.philo_count)
	{
		while (i < data.philo_count)
		{
			if (pthread_create(&philos[i]->philo, NULL, &simulation, philos[i]) != 0)
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
		j++;
	}
	free_and_exit(philos, forks);
	return (0);
}
