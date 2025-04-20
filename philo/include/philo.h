/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:54:41 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/20 14:31:33 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mut;
	int				av;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			meal;
	pthread_t	thread;
	t_fork		*left;
	t_fork		*right;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	int	phi_nb;
	int	time_d;
	int	time_e;
	int	time_s;
	int	meal_nb;
	int	stop;
	t_philo	*phi;
	t_fork	*fork;
	pthread_mutex_t	start;
	pthread_mutex_t	dead;
}	t_data;

// security
int				check_args(int argc, const char **argv);
void			destroy_mut(t_data *data, int all);

// utils
long long int	ft_atoll(const char *str);

#endif