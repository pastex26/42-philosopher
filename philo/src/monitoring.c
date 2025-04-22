/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:57:06 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/22 15:11:51 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_finished(t_data *data)
{
	if (pthread_mutex_lock(&data->dead))
	{
		perror("pthread_mutex_lock");
		data->stop = 1;
		return (0);
	}
	data->stop = 1;
	pthread_mutex_unlock(&data->dead);
	return (1);
}

int	check_finished(t_data *data)
{
	int	i;
	int	meal;

	meal = 0;
	i = 0;
	while (i < data->phi_nb)
	{
		if (data->meal_nb != -1
			&& data->phi[i].meal >= data->meal_nb)
			meal++;
		i++;
	}
	if (meal == data->phi_nb)
		return (1);
	return (0);
}

int	launch_threads(t_data *data)
{
	int	i;

	if (pthread_mutex_lock(&data->start) == -1)
		return (0);
	i = 0;
	while (i < data->phi_nb)
	{
		pthread_create(&data->phi[i].thread, NULL, philo_loop, &data->phi[i]);
		i++;
	}
	return (1);
}

void	monitoring(t_data *data)
{
	int	i;
	pthread_mutex_unlock(&data->start);
	usleep(100);
	while (1)
	{
		if (check_finished(data))
			return ;
		usleep(100);
	}
	i = 0;
	while (i < data->phi_nb)
	{
		pthread_join(data->phi[i].thread, NULL);
		i++;
	}
}
