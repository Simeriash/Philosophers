/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:06 by julauren          #+#    #+#             */
/*   Updated: 2026/03/07 11:44:03 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long int	time_elapsed(struct timeval t0)
{
	struct timeval	t1;
	long int		t;

	gettimeofday(&t1, 0);
	t = (t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000;
	return (t);
}

void	*thread_routine(void *arg)
{
	t_philo		*philo;
	long int	t;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->printf);
	t = time_elapsed(philo->t0);
	printf("%li\tphilo : %i\tthread : %ld\n", t, philo->number, philo->thread);
	pthread_mutex_unlock(&philo->data->printf);
	return (NULL);
}
