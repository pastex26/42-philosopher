/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:57:06 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/24 12:37:51 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_threads(t_data *data)
{
	int	i;

	if (pthread_mutex_lock(&data->start) == -1)
		return (perror("pthread_mutex_lock"), 0);
	i = 0;
	while (i < data->phi_nb)
	{
		pthread_create(&data->phi[i].thread, NULL, philo_loop, &data->phi[i]);
		data->phi[i].last_m = get_time();
		i++;
	}
	return (1);
}

int	set_finished(t_data *data, int dead)
{
	if (pthread_mutex_lock(&data->dead))
	{
		perror("pthread_mutex_lock");
		data->stop = 1;
		return (0);
	}
	data->stop = 1;
	pthread_mutex_unlock(&data->dead);
	if (dead)
	{
		if (pthread_mutex_lock(&data->write) != -1)
		{
			printf("%ld %d %s\n", get_time_sim(data), dead, DEAD);
			pthread_mutex_unlock(&data->write);
		}
		else
			perror("pthread_mutex_lock");
	}
	return (1);
}

static int	check_dead(t_philo *phi, long int actual_time)
{
	if (actual_time - phi->last_m >= phi->data->time_d)
		return (1);
	return (0);
}

static int	check_finished(t_data *data)
{
	int			i;
	int			meal_done;
	long int	actual_time;

	actual_time = get_time();
	meal_done = 0;
	i = 0;
	if (pthread_mutex_lock(&data->meal) == -1)
		return (perror("pthread_mutex_lock"), 0);
	while (i < data->phi_nb)
	{
		if (check_dead(&data->phi[i], actual_time))
			return (pthread_mutex_unlock(&data->meal), data->phi[i].id);
		if (data->meal_nb != -1 && data->phi[i].meal >= data->meal_nb)
			meal_done++;
		i++;
	}
	pthread_mutex_unlock(&data->meal);
	if (meal_done == data->phi_nb)
		return (0);
	return (-1);
}

void	monitoring(t_data *data)
{
	int	i;
	int	check;

	data->start_time = get_time();
	pthread_mutex_unlock(&data->start);
	while (1)
	{
		usleep(5000);
		check = check_finished(data);
		if (check != -1)
		{
			set_finished(data, check);
			break ;
		}
	}
	i = 0;
	while (i < data->phi_nb)
	{
		pthread_join(data->phi[i].thread, NULL);
		i++;
	}
}
