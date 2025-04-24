/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:11:19 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/24 12:32:58 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork_loop(t_philo *phi, t_fork *to_take)
{
	if (!to_take)
		return (0);
	while (!is_finished(phi->data))
	{
		if (pthread_mutex_lock(&to_take->mut) == -1)
		{
			perror("pthread_mutex_lock");
			return (set_finished(phi->data, 0), 0);
		}
		if (to_take->av == 0)
		{
			to_take->av = 1;
			pthread_mutex_unlock(&to_take->mut);
			print_action(FORK, phi);
			return (1);
		}
		pthread_mutex_unlock(&to_take->mut);
		usleep(100);
	}
	return (0);
}

static int	take_fork_mod(t_philo *phi)
{
	if (!take_fork_loop(phi, phi->right) || !take_fork_loop(phi, phi->left))
		return (0);
	return (1);
}

int	take_fork(t_philo *phi)
{
	if (phi->id % 2)
	{
		if (!take_fork_loop(phi, phi->left) || !take_fork_loop(phi, phi->right))
			return (0);
	}
	else
		return (take_fork_mod(phi));
	return (1);
}

static int	let_fork_mod(t_philo *phi)
{
	if (pthread_mutex_lock(&phi->right->mut) == -1)
		return (perror("pthread_mutex_lock"), 0);
	phi->right->av = 0;
	pthread_mutex_unlock(&phi->right->mut);
	if (pthread_mutex_lock(&phi->left->mut) == -1)
		return (perror("pthread_mutex_lock"), 0);
	phi->left->av = 0;
	pthread_mutex_unlock(&phi->left->mut);
	return (1);
}

int	let_fork(t_philo *phi)
{
	if (phi->id % 2)
	{
		if (pthread_mutex_lock(&phi->left->mut) == -1)
			return (perror("pthread_mutex_lock"), 0);
		phi->left->av = 0;
		pthread_mutex_unlock(&phi->left->mut);
		if (pthread_mutex_lock(&phi->right->mut) == -1)
			return (perror("pthread_mutex_lock"), 0);
		phi->right->av = 0;
		pthread_mutex_unlock(&phi->right->mut);
		return (1);
	}
	else
		return (let_fork_mod(phi));
}
