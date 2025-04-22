/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:11:19 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/22 15:17:04 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork_mod(t_philo *phi)
{
	if (pthread_mutex_lock(&phi->right->mut) == -1)
		return (perror("pthread_mutex_lock"), 0);
	if (phi->right->av != phi->id)
	{
		phi->right->av = phi->id;
		if (!print_action(FORK, phi))
			return (pthread_mutex_unlock(&phi->right->mut), 0);
	}
	pthread_mutex_unlock(&phi->right->mut);
	if (pthread_mutex_lock(&phi->left->mut) == -1)
		return (perror("pthread_mutex_lock"), 0);
	if (phi->left->av != phi->id)
	{
		phi->left->av = phi->id;
		if (!print_action(FORK, phi))
			return (pthread_mutex_unlock(&phi->left->mut), 0);
	}
	pthread_mutex_unlock(&phi->left->mut);
	return (1);
}

int	take_fork(t_philo *phi)
{
	if (phi->id % 2)
	{
		if (pthread_mutex_lock(&phi->left->mut) == -1)
			return (perror("pthread_mutex_lock"), 0);
		if (phi->left->av != phi->id)
		{
			phi->left->av = phi->id;
			if (!print_action(FORK, phi))
				return (pthread_mutex_unlock(&phi->left->mut), 0);
		}
		pthread_mutex_unlock(&phi->left->mut);
		if (pthread_mutex_lock(&phi->right->mut) == -1)
			return (perror("pthread_mutex_lock"), 0);
		if (phi->right->av != phi->id)
		{
			phi->right->av = phi->id;
			if (!print_action(FORK, phi))
				return (pthread_mutex_unlock(&phi->right->mut), 0);
		}
		pthread_mutex_unlock(&phi->right->mut);
		return (1);
	}
	else
		return (take_fork_mod(phi));
}

static int	let_fork_mod(t_philo *phi)
{
	if (pthread_mutex_lock(&phi->right->mut) == -1)
		return (perror("pthread_mutex_lock"), 0);
	if (!phi->right->av)
		phi->right->av = 0;
	pthread_mutex_unlock(&phi->left->mut);
	if (pthread_mutex_lock(&phi->left->mut) == -1)
		return (perror("pthread_mutex_lock"), 0);
	if (!phi->left->av)
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
		if (!phi->left->av)
			phi->left->av = 0;
		pthread_mutex_unlock(&phi->left->mut);
		if (pthread_mutex_lock(&phi->right->mut) == -1)
			return (perror("pthread_mutex_lock"), 0);
		if (!phi->right->av)
			phi->right->av = 0;
		pthread_mutex_unlock(&phi->right->mut);
		return (1);
	}
	else
		return (let_fork_mod(phi));
}
