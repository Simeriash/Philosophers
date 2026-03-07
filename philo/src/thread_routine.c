/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:06 by julauren          #+#    #+#             */
/*   Updated: 2026/03/07 14:36:09 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	message(pthread_mutex_t *mutex, long int t, int num, int code)
{
	pthread_mutex_lock(mutex);
	if (code == 0)
		printf("%ld | %i has taken a fork\n", t, num);
	else if (code == 1)
		printf("%ld | %i is eating\n", t, num);
	else if (code == 2)
		printf("%ld | %i is sleeping\n", t, num);
	else if (code == 3)
		printf("%ld | %i is thinking\n", t, num);
	else if (code == 4)
		printf("%ld | %i died\n", t, num);
	pthread_mutex_unlock(mutex);
}

void	*thread_routine(void *arg)
{
	t_philo		*philo;
	long int	t;
	int			i;

	philo = (t_philo *)arg;
	i = 1;
	while (1)
	{
		while (i)
			i = fork_grip(philo);
		t = time_elapsed(philo->t0);
		if (control_loop(philo, t))
			return (NULL);
		message(&philo->data->printf, t, philo->number, 0);
		message(&philo->data->printf, t, philo->number, 0);
	}
	return (NULL);
}
