/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:07:57 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/27 18:26:41 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	lock_mutex(pthread_mutex_t *mut)
{
	if (pthread_mutex_lock(mut) == -1)
		return (perror("pthread_mutex_lock"), 0);
	return (1);
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
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (check_dead(data))
			return (0);
		usleep(100);
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
