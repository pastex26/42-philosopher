/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:07:57 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/22 12:43:46 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	is_finished(t_data *data)
{
	if (pthread_mutex_lock(&data->dead) == -1)
		return (perror("pthread_mutex_lock"), 1);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

long int	get_time_sim(t_data *data)
{
	return (get_time() - data->start_time);
}

int	my_sleep(int time, t_data *data)
{
	long int	actual_time;

	actual_time = get_time();
	while (get_time() < actual_time + time)
	{
		if (is_finished(data))
			return (0);
		usleep(200);
	}
	return (1);
}

long long int	ft_atoll(const char *str)
{
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
