/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:16:13 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/27 18:39:42 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_data *data)
{
	if (!lock_mutex(&data->dead))
		return (1);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}

int	print_action(t_philo *phi, char *action)
{
	if (check_dead(phi->data))
		return (0);
	if (!lock_mutex(&phi->data->write))
		return (0);
	printf("%ld %d %s\n", get_time_sim(phi->data), phi->id, action);
	pthread_mutex_unlock(&phi->data->write);
	return (1);
}

int	philo_eat(t_philo *phi)
{
	//lock_forks;
	if (!print_action(phi, EAT))
		return (0);
	if (!lock_mutex(&phi->data->meal))
		return (/* unlockfork,  */ 0);
	phi->last_m = get_time();
	phi->meal += 1;
	pthread_mutex_unlock(&phi->data->meal);
	if (!my_sleep(phi->data->time_e, phi->data))
		return (0);
	return (1);
}
