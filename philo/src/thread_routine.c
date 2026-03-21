/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:37:06 by julauren          #+#    #+#             */
/*   Updated: 2026/03/21 10:47:49 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long int	time_elapsed(struct timeval t0)
{
	struct timeval	t1;
	long int		t;

	gettimeofday(&t1, 0);
	t = (t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000;
	return (t);
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

static int	next_routine(t_philo *philo, long int *t, int *i)
{
	while (*i)
	{
		*i = fork_grip(philo->fork_1, philo->fork_2);
		*t = time_elapsed(philo->t0);
		if (control(philo, *t))
			return (1);
	}
	*i = 1;
	message(&philo->data->printf, *t, philo->number, 0);
	message(&philo->data->printf, *t, philo->number, 0);
	philo->hungry = *t;
	message(&philo->data->printf, *t, philo->number, 1);
	if (control_loop(philo, philo->data->time_2_eat, t))
		return (1);
	drop_the_forks(philo->fork_1, philo->fork_2);
	(philo->meal)++;
	message(&philo->data->printf, *t, philo->number, 2);
	if (control_loop(philo, philo->data->time_2_sleep, t))
		return (1);
	message(&philo->data->printf, *t, philo->number, 3);
	usleep(500);
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
	if (philo->number % 2 == 0)
		usleep(1000);
	i = 1;
	while (1)
	{
		if (next_routine(philo, &t, &i))
			return (NULL);
	}
	return (NULL);
}
