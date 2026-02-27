/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:52:28 by julauren          #+#    #+#             */
/*   Updated: 2026/02/27 11:04:04 by julauren         ###   ########.fr       */
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
	int			nb_philo;
	int			time_2_die;
	int			time_2_eat;
	int			time_2_sleep;
	int			nb_times;
}	t_data;

typedef struct s_node
{
	long int		t0_sec;
	long int		t0_usec;
	int				val;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_node	*prev;
	struct s_node	*next;
	t_data			*data;
}	t_node;

int		ft_init_input(t_data *data, int ac, char **av);
t_node	*ft_everyone_to_the_table(t_data *data);
t_node	*ft_node_chr(t_node *table, int val);
void	ft_free_table(t_node *table);

#endif
