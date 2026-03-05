/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:04:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/05 16:57:02 by julauren         ###   ########.fr       */
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

static t_fork	*create_fork_list(t_data *data)
{
	int		i;
	t_fork	*fork_list;

	fork_list = malloc(sizeof(*fork_list) * data->nb_philo);
	if (!fork_list)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		fork_list[i].free = 0;
		pthread_mutex_init(&(fork_list)[i].mutex, NULL);
		i++;
	}
	return (fork_list);
}

static t_philo	*create_philo_list(t_data *data)
{
	int		i;
	t_philo	*philo_list;

	philo_list = malloc(sizeof(*philo_list) * data->nb_philo);
	if (!philo_list)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo_list[i].data = data;
		i++;
	}
	return (philo_list);
}

static void	create_thread(t_data *data, t_fork *fork, t_philo *philo_list)
{
	int		n;
	int		i;
	struct timeval	t0;

	(void)fork;
	n = data->nb_philo;
	i = -1;
	gettimeofday(&t0, 0);
	while (++i < n)
	{
		philo_list[i].t0 = t0;
		philo_list[i].ungry = 0;
		philo_list[i].meal = 0;
		philo_list[i].number = i + 1;
		// philo_list[i].data = data;
		if (pthread_create(&philo_list[i].thread, NULL, &thread_routine, &philo_list[i]))
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_fork	*fork_list;
	t_philo	*philo_list;
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	data = init_input(ac, av);
	if (!data)
		return (1);
	fork_list = create_fork_list(data);
	if (!fork_list)
		return (1);
	philo_list = create_philo_list(data);
	if (!philo_list)
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
