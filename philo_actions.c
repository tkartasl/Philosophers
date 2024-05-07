/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/07 15:29:20 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday failed\n", 20);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t time_to)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_to)
		usleep(500);
	return (0);
}

/*long long	elapsed_time(long long start, t_philo_data *data)
{
	long long	elapsed;

	current = get_current_time();
	elapsed = ((current.tv_sec-start.tv_sec)*1000000LL
		+ current.tv_usec-start.tv_usec) / 1000;
	//pthread_mutex_unlock(&data->action);
eturn (elapsed);
}*/

void	print_action(t_philo_data *data, int msg_nbr)
{
	long long	time;

	pthread_mutex_lock(&data->info->write);
	time = print_time(data->start); 
	if (msg_nbr == 1 && data->info->death_count == 0)
		printf("%lld %d has taken a fork\n", time, data->nbr);
	if (msg_nbr == 2 && data->info->death_count == 0)
		printf("%lld %d is eating\n", time, data->nbr);
	if (msg_nbr == 3 && data->info->death_count == 0)
		printf("%lld %d is sleeping\n", time, data->nbr);
	if (msg_nbr == 4 && data->info->death_count == 0)
		printf("%lld %d is thinking\n", time, data->nbr);
	pthread_mutex_unlock(&data->info->write);
}

/*void	time_to_loop(t_philo_data *data, int time_to)
{
	long long	elapsed;
	struct timeval	start;
	struct timeval	current;

//	pthread_mutex_lock(&data->action);
	elapsed = 0;
//	pthread_mutex_unlock(&data->action);
	gettimeofday(&start, 0);
	while (elapsed < time_to)
	{
		gettimeofday(&current, 0);
		elapsed = ((current.tv_sec-start.tv_sec)*1000000LL
			+ current.tv_usec-start.tv_usec) / 1000;
	}
}*/

long long	print_time(long long start)
{
	long long		elapsed;

	elapsed = get_current_time() - start;
	return (elapsed);
}

/*void	sleeping(t_philo_data *data)
{
	print_action(data, 3, time);
	time_to_loop(data->info->time_sleep);
}*/

/*void	pick_forks(t_philo_data *data)
{
	if (data->nbr % 2 == 0 && data->info->philo_count % 2 == 0)
	{
		pthread_mutex_lock(data->right_fork);
		print_action(data, 1);
		pthread_mutex_lock(data->left_fork);
		print_action(data, 1);
	}
	else
	{
		pthread_mutex_lock(data->left_fork);
		print_action(data, 1);
		pthread_mutex_lock(data->right_fork);
		print_action(data, 1);
	}
	if (data->info->philo_count == 1)
	{
		while (data->info->death_count == 0);
		return ;
	}
	print_action(data, 2);
	eating(data);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

void	eating(t_philo_data *data)
{
	gettimeofday(&data->prev_meal, 0);
	time_to_loop(data->info->time_eat);
	data->meals++;
	
}*/

void	eating(t_philo_data *data)
{
	pthread_mutex_lock(data->left_fork);
	print_action(data, 1);
	if (data->info->philo_count == 1)
	{
		while (data->info->death_count == 0);
		return ;
	}
	pthread_mutex_lock(data->right_fork);
	print_action(data, 1);
	print_action(data, 2);
	data->prev_meal = get_current_time();
	//time_to_loop(data, data->info->time_eat);
	ft_usleep(data->info->time_eat);
	data->meals++;
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

/*void	thinking(t_philo_data *data)
{
	long long	time;

	time = print_time(data); 
	print_action(data, 4, time);
}*/
