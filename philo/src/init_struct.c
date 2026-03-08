/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:57:19 by julauren          #+#    #+#             */
/*   Updated: 2026/03/08 10:00:56 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	create_fork_list(t_data *data, t_fork **fork)
{
	int		i;

	*fork = malloc(sizeof(**fork) * data->nb_philo);
	if (!(*fork))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*fork)[i].free = 0;
		pthread_mutex_init(&(*fork)[i].mutex, NULL);
		i++;
	}
	return (0);
}

void	fork_choice(t_philo *philo, t_fork *fork, int i)
{
	if ((philo)[i].number == 1)
	{
		(philo)[i].fork_1 = &fork[0];
		(philo)[i].fork_2 = &fork[(philo)[i].data->nb_philo - 1];
	}
	else
	{
		if ((philo)[i].number % 2 == 0)
		{
			(philo)[i].fork_1 = &fork[(philo)[i].number - 2];
			(philo)[i].fork_2 = &fork[(philo)[i].number - 1];
		}
		else
		{
			(philo)[i].fork_1 = &fork[(philo)[i].number - 1];
			(philo)[i].fork_2 = &fork[(philo)[i].number - 2];
		}
	}
}

static int	create_philo_list(t_data *data, t_philo **philo)
{
	int		i;

	*philo = malloc(sizeof(**philo) * data->nb_philo);
	if (!(*philo))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].ungry = 0;
		(*philo)[i].meal = 0;
		(*philo)[i].number = i + 1;
		i++;
	}
	return (0);
}

int	init_struc(t_data *data, t_fork **fork, t_philo **philo)
{
	if (create_fork_list(data, fork)
		|| create_philo_list(data, philo))
	{
		destroy_mutex(data, *fork);
		free(data);
		if ((*fork))
			free(*fork);
		return (1);
	}
	return (0);
}
