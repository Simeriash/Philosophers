/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:04:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/05 17:47:58 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	destroy_mutex(t_fork *fork_list, t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->data);
	pthread_mutex_destroy(&data->printf);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&fork_list[i].mutex);
		i++;
	}
}

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

static void	create_thread(t_data *data, t_fork *fork, t_philo *philo_list)
{
	int				n;
	int				i;
	struct timeval	t0;

	(void)fork;
	n = data->nb_philo;
	i = -1;
	gettimeofday(&t0, 0);
	while (++i < n)
	{
		philo_list[i].t0 = t0;
		if (pthread_create(&philo_list[i].thread, NULL, &thread_routine, &philo_list[i]))
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_fork	*fork_list;
	t_philo	*philo_list;
	int		i;

	if (ac < 5 || ac > 6)
		return (1);
	if (init_input(ac, av, &data))
		return (1);
	if (create_fork_list(data, &fork_list))
		return (1);
	if (create_philo_list(data, &philo_list))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(philo_list[i]).data = data;
		i++;
	}
	create_thread(data, fork_list, philo_list);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo_list[i].thread, NULL);
		i++;
	}
	destroy_mutex(fork_list, data);
	free(fork_list);
	free(philo_list);
	free(data);
	return (0);
}
