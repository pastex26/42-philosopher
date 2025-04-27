/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:38:38 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/27 18:21:48 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *phi;

	phi = (t_philo *)arg;
	if (!lock_mutex(&phi->data->start))
		return (NULL);
	phi->last_m = phi->data->start_time;
	pthread_mutex_unlock(&phi->data->start);
	if (phi->id % 2)
		usleep(100);
	while (1)
	{
		if (!philo_eat(phi))
		{
			//unlock forks;
			return (NULL);
		}
		// sleep 
		// think
	}
	return (NULL);
}
