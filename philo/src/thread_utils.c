/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:36:37 by julauren          #+#    #+#             */
/*   Updated: 2026/03/07 14:32:19 by julauren         ###   ########.fr       */
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

int	fork_grip(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_1->mutex);
	if (philo->fork_1->free == 0)
	{
		philo->fork_1->free = 1;
		pthread_mutex_unlock(&philo->fork_1->mutex);
		pthread_mutex_lock(&philo->fork_2->mutex);
		if (philo->fork_2->free == 0)
		{
			philo->fork_2->free = 1;
			pthread_mutex_unlock(&philo->fork_2->mutex);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&philo->fork_2->mutex);
			pthread_mutex_lock(&philo->fork_1->mutex);
			philo->fork_1->free = 0;
			pthread_mutex_unlock(&philo->fork_1->mutex);
		}
	}
	else
		pthread_mutex_unlock(&philo->fork_1->mutex);
	return (1);
}

void	drop_the_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_1->mutex);
	philo->fork_1->free = 0;
	pthread_mutex_unlock(&philo->fork_1->mutex);
	pthread_mutex_lock(&philo->fork_2->mutex);
	philo->fork_2->free = 0;
	pthread_mutex_unlock(&philo->fork_2->mutex);
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

int	control_loop(t_philo *philo, long int t)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->data);
	if (philo->data->end == 0)
		i++;
	else
	{
		if (t - philo->ungry > philo->data->time_2_die)
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
		drop_the_forks(philo);
	return (i);
}
