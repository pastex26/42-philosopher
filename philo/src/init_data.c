/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:22:48 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/24 11:21:33 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	attribute_forks(t_philo *phi, t_data *data)
{
	phi->left = &data->fork[phi->id - 1];
	if (data->phi_nb == 1)
	{
		phi->right = NULL;
		return ;
	}
	if (phi->id == data->phi_nb)
	{
		phi->right = &data->fork[0];
	}
	else
	{
		phi->right = &data->fork[phi->id];
	}
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phi_nb)
	{
		data->phi[i].id = i + 1;
		data->phi[i].meal = 0;
		data->phi[i].data = data;
		attribute_forks(&data->phi[i], data);
		i++;
	}
}

static int	init_secondary_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->start, NULL) == -1)
		return (perror("pthread_mutex_init"), 0);
	if (pthread_mutex_init(&data->dead, NULL) == -1)
	{
		perror("pthread_mutex_init");
		pthread_mutex_destroy(&data->start);
		return (0);
	}
	if (pthread_mutex_init(&data->write, NULL) == -1)
	{
		perror("pthread_mutex_init");
		pthread_mutex_destroy(&data->dead);
		pthread_mutex_destroy(&data->start);
		return (0);
	}
	if (pthread_mutex_init(&data->meal, NULL) == -1)
	{
		perror("pthread_mutex_init");
		pthread_mutex_destroy(&data->start);
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->dead);
		return (0);
	}
	return (1);
}

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0 ;
	while (i < data->phi_nb)
	{
		if (pthread_mutex_init(&data->fork[i].mut, NULL) == -1)
		{
			perror("pthread_mutex_init");
			while (i--)
				pthread_mutex_destroy(&data->fork[i].mut);
			return (0);
		}
		data->fork[i].av = 0;
		i++;
	}
	if (!init_secondary_mutex(data))
		return (destroy_mut(data, 0), 0);
	return (1);
}

int	init_data(t_data *data, const char **argv)
{
	data->phi_nb = (int)ft_atoll(argv[1]);
	data->time_d = (int)ft_atoll(argv[2]);
	data->time_e = (int)ft_atoll(argv[3]);
	data->time_s = (int)ft_atoll(argv[4]);
	data->meal_nb = -1;
	if (argv[5])
		data->meal_nb = (int)ft_atoll(argv[5]);
	data->phi = malloc(data->phi_nb * sizeof(t_philo));
	if (!data->phi)
		return (perror("malloc"), 0);
	data->fork = malloc(data->phi_nb * sizeof(t_fork));
	if (!data->fork)
	{
		perror("malloc");
		return (free(data->phi), 0);
	}
	if (!init_mutex(data))
	{
		free(data->phi);
		free(data->fork);
		return (0);
	}
	init_philo(data);
	return (1);
}
