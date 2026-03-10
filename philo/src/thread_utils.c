/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:36:37 by julauren          #+#    #+#             */
/*   Updated: 2026/03/10 15:50:25 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	next_fork(t_fork *fork_1, t_fork *fork_2)
{
	pthread_mutex_unlock(&fork_2->mutex);
	pthread_mutex_lock(&fork_1->mutex);
	usleep(20);
	fork_1->free = 0;
	pthread_mutex_unlock(&fork_1->mutex);
}

int	fork_grip(t_fork *fork_1, t_fork *fork_2)
{
	pthread_mutex_lock(&fork_1->mutex);
	usleep(20);
	if (fork_1->free == 0)
	{
		fork_1->free = 1;
		pthread_mutex_unlock(&fork_1->mutex);
		pthread_mutex_lock(&fork_2->mutex);
		usleep(20);
		if (fork_2->free == 0)
		{
			fork_2->free = 1;
			pthread_mutex_unlock(&fork_2->mutex);
			return (0);
		}
		else
			next_fork(fork_1, fork_2);
	}
	else
		pthread_mutex_unlock(&fork_1->mutex);
	return (1);
}

static void	next_control(t_philo *philo, int *i)
{
	if (philo->meal == philo->data->nb_times)
	{
		(philo->data->nb_meal)++;
		(philo->meal)++;
	}
	if (philo->data->nb_meal == philo->data->nb_philo)
	{
		philo->data->end = 0;
		(*i)++;
	}
}

int	control(t_philo *philo, long int t)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->data);
	usleep(20);
	if (philo->data->end == 0)
		i++;
	else
	{
		if (t - philo->hungry > philo->data->time_2_die)
		{
			philo->data->end = 0;
			message(&philo->data->printf, t, philo->number, 4);
			i++;
		}
		else
			next_control(philo, &i);
	}
	pthread_mutex_unlock(&philo->data->data);
	if (i)
		drop_the_forks(philo->fork_1, philo->fork_2);
	return (i);
}

int	control_loop(t_philo *philo, int timer, long int *t)
{
	long int	t1;

	t1 = *t;
	while ((t1 - *t) < timer)
	{
		if (control(philo, t1))
			return (1);
		usleep(500);
		t1 = time_elapsed(philo->t0);
	}
	*t = t1;
	return (0);
}
