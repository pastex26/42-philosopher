/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:38:38 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/22 15:08:50 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_start(t_philo *phi)
{
	if (pthread_mutex_lock(&phi->data->start) == -1)
		return (perror("pthread_mutex_lock"), 0);
	phi->last_m = get_time();
	pthread_mutex_unlock(&phi->data->start);
	return (1);
}

int	has_forks(t_philo *phi)
{
	int	nb;

	nb = 0;
	if (pthread_mutex_lock(&phi->left->mut) == -1)
		return (set_finished(phi->data), -1);
	if (phi->left->av == phi->id)
		nb++;
	pthread_mutex_unlock(&phi->left->mut);
	if (pthread_mutex_lock(&phi->right->mut) == -1)
		return (set_finished(phi->data), -1);
	if (phi->right->av == phi->id)
		nb++;
	pthread_mutex_unlock(&phi->right->mut);
	return (nb);
}

void	*philo_loop(void *arg)
{
	t_philo *phi;

	phi = (t_philo *)arg;
	if (!wait_start(phi))
		return (NULL);
	while (1)
	{
		while (has_forks(phi) != 2 && !is_finished(phi->data))
		{
			if (!take_fork(phi))
				return (set_finished(phi->data), NULL);
		}
		if (!philo_eat(phi))
			return (NULL);
		if (!philo_sleep(phi))
			return (NULL);
		if (!print_action(THINK, phi))
			return (NULL);
	}
	return (NULL);
}
