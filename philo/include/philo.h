/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:54:41 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/04/24 12:30:41 by lmarcucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DEAD "died"

typedef struct s_fork
{
	pthread_mutex_t	mut;
	int				av;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				meal;
	long			last_m;
	pthread_t		thread;
	t_fork			*left;
	t_fork			*right;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				phi_nb;
	int				time_d;
	int				time_e;
	int				time_s;
	int				meal_nb;
	int				stop;
	long			start_time;
	t_philo			*phi;
	t_fork			*fork;
	pthread_mutex_t	start;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	pthread_mutex_t	meal;
}					t_data;

// init
int				init_data(t_data *data, const char **argv);
int				launch_threads(t_data *data);
void			*philo_loop(void *arg);

// monitoring
void			monitoring(t_data *data);
int				set_finished(t_data *data, int dead);

// action
int				print_action(char *msg, t_philo *phi);
int				philo_eat(t_philo *phi);
int				philo_sleep(t_philo *phi);
int				take_fork(t_philo *phi);
int				let_fork(t_philo *phi);

// security
int				check_args(int argc, const char **argv);
void			free_all(t_data *data);
void			destroy_mut(t_data *data, int all);

// utils
int				my_sleep(int time, t_data *data);
int				is_finished(t_data *data);
long int		get_time_sim(t_data *data);
long int		get_time(void);
long long int	ft_atoll(const char *str);

#endif