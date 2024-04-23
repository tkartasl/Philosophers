/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:17:27 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/22 14:17:19 by tkartasl         ###   ########.fr       */
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

int	assign_args(t_args *args, char *argv[])
{
	args->philo_count = ft_atoi(argv[1]);
	if (args->philo_count < 0)
		return (1);
	args->time_die = ft_atoi(argv[2]);
	if (args->time_die < 0)
		return (1);
	args->time_eat = ft_atoi(argv[3]);
	if (args->time_eat < 0)
		return (1);
	args->time_sleep = ft_atoi(argv[4]);
	if (args->time_sleep < 0)
		return (1);
	if (argv[5] != 0)	
	{	
		args->times_to_eat = ft_atoi(argv[5]);
		if (args->times_to_eat < 0)
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	struct timeval	start;
	struct timeval	current;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong amount of arguments\n");
		return (1);
	}
	memset(&start, 0, sizeof(struct timeval));
	memset(&current, 0, sizeof(struct timeval));
	memset(&args, 0, sizeof(t_args));
	if (check_arguments(argv) != 0)
	{
		printf("check arguments\n");
		return (1);
	}
	if (assign_args(&args, argv) != 0)
	{
		printf("MAX / MIN INT WARNING\n");
		return (1);
	}
	init_philos()
	return (0);
}
