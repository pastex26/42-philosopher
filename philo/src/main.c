/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:58:17 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/27 18:38:15 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const *argv[])
{
	t_data	data;

	data = (t_data){0};
	if (!check_args(argc, argv))
		return (1);
	if (!init_data(&data, argv))
		return (1);
	printf("mealnb %d\n", data.meal_nb);
	monitoring(&data);
	free_all(&data);
	return (0);
}
