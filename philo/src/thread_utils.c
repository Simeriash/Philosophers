/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:36:37 by julauren          #+#    #+#             */
/*   Updated: 2026/03/08 14:55:07 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	fork_grip(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_1->mutex);
	usleep(50);
	if (philo->fork_1->free == 0)
	{
		philo->fork_1->free = 1;
		pthread_mutex_unlock(&philo->fork_1->mutex);
		pthread_mutex_lock(&philo->fork_2->mutex);
		usleep(50);
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
			usleep(50);
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
	usleep(50);
	philo->fork_1->free = 0;
	pthread_mutex_unlock(&philo->fork_1->mutex);
	pthread_mutex_lock(&philo->fork_2->mutex);
	usleep(50);
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
	usleep(50);
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
	return (i);
}
