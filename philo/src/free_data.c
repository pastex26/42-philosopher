/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:24:34 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/22 10:38:30 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mut(t_data *data, int all)
{
	int	i;

	i = 0;
	while (i < data->phi_nb)
	{
		pthread_mutex_destroy(&data->fork[i].mut);
		i++;
	}
	if (all)
	{
		pthread_mutex_destroy(&data->start);
		pthread_mutex_destroy(&data->dead);
	}
}

void	free_all(t_data *data)
{
	destroy_mut(data, 1);
	free(data->phi);
	free(data->fork);
}
