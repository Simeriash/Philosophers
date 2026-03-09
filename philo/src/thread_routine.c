/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:06 by julauren          #+#    #+#             */
/*   Updated: 2026/03/08 17:23:50 by julauren         ###   ########.fr       */
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

void	message(pthread_mutex_t *mutex, long int t, int num, int code)
{
	pthread_mutex_lock(mutex);
	usleep(50);
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

static void	one_philo(t_philo *philo)
{
	long int	t;

	t = time_elapsed(philo->t0);
	message(&philo->data->printf, t, philo->number, 0);
	usleep(philo->data->time_2_die * 1000);
	t = time_elapsed(philo->t0);
	message(&philo->data->printf, t, philo->number, 4);
}

static int	next_routine(t_philo *philo, long int t)
{
	message(&philo->data->printf, t, philo->number, 0);
	message(&philo->data->printf, t, philo->number, 0);
	philo->ungry = t;
	message(&philo->data->printf, t, philo->number, 1);
	usleep(philo->data->time_2_eat * 1000);
	t = time_elapsed(philo->t0);
	if (control_loop(philo, t))
		return (1);
	drop_the_forks(philo->fork_1, philo->fork_2);
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
	if (philo->data->nb_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	i = 1;
	while (1)
	{
		while (i)
		{
			i = fork_grip(philo->fork_1, philo->fork_2);
			t = time_elapsed(philo->t0);
			if (control_loop(philo, t))
				return (NULL);
		}
		i = 1;
		if (next_routine(philo, t))
			return (NULL);
	}
	return (NULL);
}
