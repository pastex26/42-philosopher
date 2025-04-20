/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:00:44 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/20 11:46:49 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_num(const char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '-')
		return (write(2, "negative value not allowed\n", 28), 0);
	while (arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (write(2, "numeric arguments required\n", 27), 0);
		i++;
	}
	return (1);
}

int	check_args(int argc, const char **argv)
{
	size_t	i;

	if (argc < 5)
		return (write(2, "not enough arguments\n", 22), 0);
	if (argc > 6)
		return (write(2, "too many arguments\n", 20), 0);
	i = 1;
	while (argv[i])
	{
		if (!check_num(argv[i]))
			return (0);
		if (ft_atoll(argv[i]) > __INT_MAX__)
			return (write(2, "value greater than INT MAX\n", 28), 0);
		i++;
	}
	if (ft_atoll(argv[0]) > 200)
		return (write(2, "philo number should be less than 200\n", 38), 0);
	return (1);
}
