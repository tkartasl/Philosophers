/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/03 14:46:25 by tkartasl         ###   ########.fr       */
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
		pthread_mutex_destroy(&philos[i]->action);
		i++;
	}
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
		if (i == data->philo_count)
			break ;
		philos[i]->left_fork = &forks[i];
		if (i != 0)
			philos[i]->right_fork = &forks[i - 1];
		pthread_mutex_init(&philos[i]->action, NULL);
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
	return (philos);
}

void	*monitoring(void *arg)
{
	t_monitor	*mt;
	int			i;
	long long	elapsed;
	
	i = 0;
	mt = (t_monitor *)arg;
	while (1)
	{
		if (i == mt->data[0]->info->philo_count)
			i = 0;
		//elapsed = elapsed_time(mt->data[i]->prev_meal);
		//printf("%lld\n", elapsed);
		if (elapsed_time(mt->data[i]->prev_meal, mt->data[i]) >= mt->data[i]->info->time_die)
		{
			mt->data[i]->info->death_count = 1;
			printf("%lld %d died\n", print_time(mt->data[i]), mt->data[i]->nbr);
			break ;
		}
		i++;
	}
	return (0);
}

/*void	monitoring(t_philo_data **philos)
{
	int			i;
	long long	elapsed;
	
	elapsed = 0;
	i = 0;
	while (1)
	{
		if (i == philos[0]->info->philo_count)
			i = 0;
		elapsed = elapsed_time(philos[i]->prev_meal);
		printf("%lld\n", elapsed);
		if (elapsed_time(philos[i]->prev_meal) >= philos[i]->info->time_die)
		{
			philos[i]->info->death_count = 1;
			printf("%lld %d died\n", print_time(philos[i]), philos[i]->nbr);
			break ;
		}
		i++;
	}
}*/

void	*simulation(void *arg)
{
	t_philo_data	*data;		

	data = (t_philo_data *)arg;
	while (data->info->sim_start == 0);
	gettimeofday(&data->start, 0);
	if (data->nbr % 2 == 0)
		usleep(300);
	gettimeofday(&data->prev_meal, 0);make 
	while (data->info->death_count == 0)
	{
		if (eating(data) != 0)
			break ;
		if (data->meals == data->info->times_to_eat)
			break ;
		if (sleeping(data) != 0)
			break ;
		if (thinking(data) != 0)
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
	t_monitor		mt;
	
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
	mt.data = philos;
	while (j < data.philo_count)
	{
		while (i < data.philo_count)
		{
				if (i == 0)
					pthread_create(&mt.monitor, NULL, &monitoring, &mt);
			if (pthread_create(&philos[i]->philo, NULL, &simulation, philos[i]) != 0)
			{
				ft_free_pointer_array(philos);
				return (1);
			}
			i++;
		}
		data.sim_start = 1;
		if (j == 0)
			if (pthread_join(mt.monitor, NULL) != 0)
				return (1);
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
