/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:26:28 by julauren          #+#    #+#             */
/*   Updated: 2026/03/05 06:28:37 by julauren         ###   ########.fr       */
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

typedef struct s_philo
{
	long int		t0_sec;
	long int		t0_usec;
	long int		ungry;
	int				meal;

	t_data			*data;
}	t_philo;

int	init_input(t_data *data, int ac, char **av);

#endif
