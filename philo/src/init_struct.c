/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:57:19 by julauren          #+#    #+#             */
/*   Updated: 2026/03/06 17:17:55 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	create_fork_list(t_data *data, t_fork **fork_list)
{
	int		i;

	*fork_list = malloc(sizeof(**fork_list) * data->nb_philo);
	if (!(*fork_list))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*fork_list)[i].free = 0;
		pthread_mutex_init(&(*fork_list)[i].mutex, NULL);
		i++;
	}
	return (0);
}

static int	create_philo_list(t_data *data, t_philo **philo_list)
{
	int		i;

	*philo_list = malloc(sizeof(**philo_list) * data->nb_philo);
	if (!(*philo_list))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*philo_list)[i].data = data;
		(*philo_list)[i].ungry = 0;
		(*philo_list)[i].meal = 0;
		(*philo_list)[i].number = i + 1;
		i++;
	}
	return (0);
}

int	init_struc(t_data *data, t_fork **fork_list, t_philo **philo_list)
{
	if (create_fork_list(data, fork_list)
		|| create_philo_list(data, philo_list))
	{
		destroy_mutex(data, *fork_list);
		free(data);
		if ((*fork_list))
			free(*fork_list);
		return (1);
	}
	return (0);
}
