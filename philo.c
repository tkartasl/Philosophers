/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/24 12:46:45 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo_data	*init_philo_struct(void)
{
	t_philo_data	*new;

	new = malloc(sizeof(t_philo_data));
	if (new == 0)
		return (0);
	return (new);
}

static int	init_philo_array(t_philo_data **philos, t_args *data)
{
	int				i;
	
	i = 0;	
	philos = malloc((data->philo_count + 1) * sizeof(t_philo_data *));
	if (philos == 0)
	{
		write(2, "Malloc failure\n", 15);
		return (-1);
	}
	data->philos = (*philos);	
	while (i < data->philo_count)
	{
		philos[i] = init_philo_struct();
		if (philos[i] == 0)
			return (-1);
		pthread_mutex_init(&philos[i]->fork, NULL);
		i++;
	}
	philos[i] = 0;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			data;
	t_philo_data	**philos;

	philos = 0;
	memset(&data.start, 0, sizeof(struct timeval));
	memset(&data.current, 0, sizeof(struct timeval));
	memset(&data, 0, sizeof(t_args));
	if (check_arguments(argc, argv, &data) != 0)
		return (1);
	if (init_philo_array(philos, &data) < 0)
		return (1);
	while (1)
	{
		
		
	}
	return (0);
}
