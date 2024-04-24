/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:33 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/24 09:55:23 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_args data, t_philo_data philo)
{
	struct timeval	start;
	struct timeval	current;
	long long		elapsed;
	
	memset(&start, 0, sizeof(struct timeval));
	memset(&current, 0, sizeof(struct timeval));
	elapsed = 0;
	gettimeofday(&start, 0);
	while(1)
	{
	
		gettimeofday(&current, 0);
		elapsed = ((start.tv_sec-current.tv_sec)*1000000LL
			+ start.tv_usec-current.tv_usec) / 1000;
		if (elapsed >= data.time_sleep)
			break ;	
	}
}

void	eating(void	*arg)
{
	struct timeval	start;
	struct timeval	current;
	long long		elapsed;

	memset(&start, 0, sizeof(struct timeval));
	memset(&current, 0, sizeof(struct timeval));
	elapsed = 0;
	gettimeofday(&start, 0);
	while(1)
	{

		gettimeofday(&current, 0);
		elapsed = ((start.tv_sec-current.tv_sec)*1000000LL
			+ start.tv_usec-current.tv_usec) / 1000;
		if (elapsed >= data.time_eat)
			break ;
	}
}

void	thinking(t_args data)
{

}
