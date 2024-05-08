/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:11:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/08 12:30:04 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_pointer_array(t_philo_data **arr)
{
	int	n;

	n = 0;
	while (arr[n] != 0)
	{
		pthread_mutex_destroy(arr[n]->left_fork);
		free(arr[n]);
		n++;
	}
	free(arr);
	arr = 0;
}

static int	ft_atoi(const char *str)
{
	int		res;
	int		neg;
	long	temp;

	temp = 0;
	res = 0;
	neg = 1;
	while (*str != 0 && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != 0 && *str >= '0' && *str <= '9')
	{
		temp = temp * 10 + (*str - 48);
		str++;
	}
	if (temp > 2147483647 || temp < -2147483648)
		return (-1);
	res = temp;
	return (res * neg);
}

static int	check_if_digit(char *argv[])
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

static int	assign_args(t_args *data, char *argv[])
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

int	check_arguments(int argc, char *argv[], t_args *data)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong amount of arguments\n", 26);
		return (1);
	}
	if (check_if_digit(argv) != 0)
	{
		write(2, "Arguments can only include numbers\n", 35);
		return (1);
	}
	if (assign_args(data, argv) != 0)
	{
		write(2, "Arguments has to be within 32bit integer range\n", 47);
		return (1);
	}
	if (data->philo_count == 0)
	{
		write(2, "The simulation requires atleast 1 Philosopher\n", 47);
		return (1);
	}
	return (0);
}
