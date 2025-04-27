/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:57:06 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/27 18:40:19 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_nb)
	{
		if (pthread_create(&data->phi[i].thread, NULL, philo_routine, &data->phi[i]) == -1)
		{
			perror("pthread_create");
			return (0);
		}
		i++;
	}
	return (1);
}

int	monitoring_dead(t_data *data, t_philo *phi)
{
	long int	time;

	time = get_time();
	if (!lock_mutex(&data->meal))
		return (1);
	if (phi->last_m - data->start_time >= time - data->time_d)
	{
		if (!lock_mutex(&data->dead))
			return (pthread_mutex_unlock(&data->meal), 1);
		data->stop = 1;
		pthread_mutex_unlock(&data->dead);
		if (!lock_mutex(&data->write))
			return (pthread_mutex_unlock(&data->meal), 1);
		printf("%ld %d %s\n", get_time_sim(data), phi->id, DEAD);
		pthread_mutex_unlock(&data->write);
	}
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_unlock(&data->meal);
	return (0);
}

int	check_full_eat(t_data *data, t_philo *phi, int *total_meal)
{
	if (!lock_mutex(&data->meal))
		return (0);
	if (data->meal_nb != -1 && phi->meal >= data->meal_nb)
		*total_meal += 1;
	if (*total_meal == data->meal_nb)
	{
		lock_mutex(&data->dead);
		data->stop = 1;
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->meal);
		return (0);
	}
	pthread_mutex_unlock(&data->meal);
	return (1);
}

int	check_state(t_data *data)
{
	int	i;
	int	meals;

	i = 0;
	meals = 0;
	while (i < data->phi_nb)
	{
		if (monitoring_dead(data, &data->phi[i]))
			return (1);
		if (!check_full_eat(data, &data->phi[i], &meals))
			return (1);
		i++;
	}
	return (0);
}

void	monitoring(t_data *data)
{
	int	i;

	if (!lock_mutex(&data->start))
		return ;
	if (!launch_threads(data))
		return ;
	data->start_time = get_time();
	pthread_mutex_unlock(&data->start);
	usleep(3000);
	while (1)
	{
		if (check_state(data))
			break ;
		usleep(500);
	}
	i = 0;
	while (i < data->phi_nb)
	{
		pthread_join(data->phi[i].thread, NULL);
		i++;
	}
}
