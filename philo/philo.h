/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:52:28 by julauren          #+#    #+#             */
/*   Updated: 2026/02/19 15:57:07 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>

typedef struct	s_data
{
	int	nb_philo;
	int	time_2_die;
	int	time_2_eat;
	int	time_2_sleep;
	int	nb_times;
}	t_data;

int	ft_isdigit(int c);

#endif
