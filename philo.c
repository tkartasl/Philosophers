/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/23 15:46:18 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(char *argv[])
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i] != 0)
	{
		while (argv[i][j] != 0)
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)	
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	assign_args(t_args *data, char *argv[])
{
	data->philo_count = ft_atoi(argv[1]);
	if (data->philo_count < 0)
		return (1);
	data->time_die = ft_atoi(argv[2]);
	if (data->time_die < 0)
		return (1);
	data->time_eat = ft_atoi(argv[3]);
	if (data->time_eat < 0)
		return (1);
	data->time_sleep = ft_atoi(argv[4]);
	if (data->time_sleep < 0)
		return (1);
	if (argv[5] != 0)	
	{	
		data->times_to_eat = ft_atoi(argv[5]);
		if (data->times_to_eat < 0)
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			data;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong amount of arguments\n");
		return (1);
	}
	memset(&data.start, 0, sizeof(struct timeval));
	memset(&data.current, 0, sizeof(struct timeval));
	memset(&data, 0, sizeof(t_args));
	gettimeofday(&data.start, 0);
	if (check_arguments(argv) != 0)
	{
		printf("check arguments\n");
		return (1);
	}
	if (assign_args(&data, argv) != 0)
	{
		printf("MAX / MIN INT WARNING\n");
		return (1);
	}
	init_philos();
	return (0);
}
