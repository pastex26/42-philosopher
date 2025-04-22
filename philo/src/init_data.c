/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:22:48 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/22 13:03:20 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	attribute_forks(t_philo *phi, t_data *data)
{
	phi->left = &data->fork[phi->id - 1];
	printf("phi[%d].left=fork[%d]\n", phi->id, phi->id - 1);
	if (data->phi_nb == 1)
	{
		phi->right = NULL;
		printf("phi[%d].right=NULL\n", phi->id);
		return ;
	}
	if (phi->id == data->phi_nb)
	{
		phi->right = &data->fork[0];
		printf("phi[%d].right=fork[%d]\n", phi->id, 0);
	}
	else
	{
		phi->right = &data->fork[phi->id];
		printf("phi[%d].right=fork[%d]\n", phi->id, phi->id);
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
	if (pthread_mutex_init(&data->start, NULL) == -1)
		return (perror("pthread_mutex_init"), destroy_mut(data, 0), 0);
	if (pthread_mutex_init(&data->dead, NULL) == -1)
	{
		perror("pthread_mutex_init");
		return (pthread_mutex_destroy(&data->start), destroy_mut(data, 0), 0);
	}
	return (1);
}

int	init_data(t_data *data, const char **argv)
{
	data->phi_nb = (int)ft_atoll(argv[1]);
	data->time_d =  (int)ft_atoll(argv[2]);
	data->time_e =  (int)ft_atoll(argv[3]);
	data->meal_nb = -1;
	if (argv[4])
		data->meal_nb =  (int)ft_atoll(argv[4]);
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
