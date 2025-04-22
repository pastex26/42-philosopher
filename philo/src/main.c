/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:58:17 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/22 13:28:26 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char const *argv[])
{
	t_data	data;

	data = (t_data){0};
	if (!check_args(argc, argv))
		return (1);
	if (!init_data(&data, argv))
		return (1);
	if (!launch_threads(&data))
		return (free_all(&data), 1);
	monitoring(&data);
	free_all(&data);
	return (0);
}
