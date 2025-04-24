/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:16:13 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/24 11:24:59 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(char *msg, t_philo *phi)
{
	if (is_finished(phi->data))
		return (0);
	if (pthread_mutex_lock(&phi->data->write) == -1)
		return (perror("pthread_mutex_lock"), 0);
	printf("%ld %d %s\n", get_time_sim(phi->data), phi->id, msg);
	pthread_mutex_unlock(&phi->data->write);
	return (1);
}

int	philo_eat(t_philo *phi)
{
	if (!print_action(EAT, phi))
		return (0);
	if (pthread_mutex_lock(&phi->data->meal) == -1)
		return (perror("pthread_mutex_lock"), 0);
	phi->meal++;
	phi->last_m = get_time();
	pthread_mutex_unlock(&phi->data->meal);
	if (!my_sleep(phi->data->time_e, phi->data))
		return (let_fork(phi), 0);
	return (1);
}

int	philo_sleep(t_philo *phi)
{
	if (!print_action(SLEEP, phi))
		return (let_fork(phi), 0);
	let_fork(phi);
	if (!my_sleep(phi->data->time_s, phi->data))
		return (0);
	return (1);
}
