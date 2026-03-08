/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:26:28 by julauren          #+#    #+#             */
/*   Updated: 2026/03/08 09:56:33 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_2_die;
	int				time_2_eat;
	int				time_2_sleep;
	int				nb_times;
	int				nb_meal;
	int				end;
	pthread_mutex_t	data;
	pthread_mutex_t	printf;
}	t_data;

typedef struct s_fork
{
	int				free;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				number;
	pthread_t		thread;
	struct timeval	t0;
	long int		ungry;
	int				meal;
	t_fork			*fork_1;
	t_fork			*fork_2;
	t_data			*data;
}	t_philo;

int			parse(int ac, char **av, t_data **data);
int			init_struc(t_data *data, t_fork **fork_list, t_philo **philo_list);
void		fork_choice(t_philo *philo, t_fork *fork_list, int i);
void		destroy_mutex(t_data *data, t_fork *fork_list);
void		*thread_routine(void *arg);
void		message(pthread_mutex_t *mutex, long int t, int num, int code);
long int	time_elapsed(struct timeval t0);
int			fork_grip(t_philo *philo);
void		drop_the_forks(t_philo *philo);
int			control_loop(t_philo *philo, long int t);

#endif
