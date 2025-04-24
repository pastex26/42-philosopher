/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:38:38 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/24 11:21:54 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_start(t_philo *phi)
{
	if (pthread_mutex_lock(&phi->data->start) == -1)
		return (perror("pthread_mutex_lock"), 0);
	if (pthread_mutex_lock(&phi->data->meal) == -1)
	{
		perror("pthread_mutex_lock");
		return (pthread_mutex_unlock(&phi->data->start), 0);
	}
	phi->last_m = get_time();
	pthread_mutex_unlock(&phi->data->meal);
	pthread_mutex_unlock(&phi->data->start);
	if (!(phi->id % 2))
		usleep(200);
	return (1);
}

void	*philo_loop(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	if (!wait_start(phi))
		return (NULL);
	while (1)
	{
		if (!take_fork(phi))
			return (NULL);
		if (!philo_eat(phi))
			return (NULL);
		if (!philo_sleep(phi))
			return (NULL);
		if (!print_action(THINK, phi))
			return (NULL);
	}
	return (NULL);
}
