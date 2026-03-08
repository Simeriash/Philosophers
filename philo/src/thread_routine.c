/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:06 by julauren          #+#    #+#             */
/*   Updated: 2026/03/08 11:35:38 by julauren         ###   ########.fr       */
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

static int	next_routine(t_philo *philo, long int t)
{
	philo->ungry = t;
	message(&philo->data->printf, t, philo->number, 1);
	usleep(philo->data->time_2_eat * 1000);
	t = time_elapsed(philo->t0);
	if (control_loop(philo, t))
		return (1);
	drop_the_forks(philo);
	(philo->meal)++;
	message(&philo->data->printf, t, philo->number, 2);
	usleep(philo->data->time_2_sleep * 1000);
	t = time_elapsed(philo->t0);
	if (control_loop(philo, t))
		return (1);
	message(&philo->data->printf, t, philo->number, 3);
	return (0);
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
		{
			i = fork_grip(philo);
			t = time_elapsed(philo->t0);
			if (control_loop(philo, t))
				return (NULL);
		}
		i = 1;
		message(&philo->data->printf, t, philo->number, 0);
		message(&philo->data->printf, t, philo->number, 0);
		if (next_routine(philo, t))
			return (NULL);
	}
	return (NULL);
}
