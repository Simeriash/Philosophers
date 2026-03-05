/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:04:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/05 10:51:00 by julauren         ###   ########.fr       */
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

static t_fork	*create_fork_list(t_data data)
{
	t_fork	*fork_list;
	int		i;

	fork_list = malloc(sizeof(*fork_list) * data.nb_philo);
	if (!fork_list)
		return (NULL);
	i = 0;
	while (i < data.nb_philo)
	{
		fork_list[i].free = 0;
		pthread_mutex_init(&fork_list[i].mutex, NULL);
		i++;
	}
	return (fork_list);
}

static void	create_thread(t_data *data, t_fork *fork)
{
	int		n;
	int		i;
	t_philo	philo;

	(void)fork;
	n = data->nb_philo;
	i = 0;
	philo.data = data;
	philo.ungry = 0;
	philo.meal = 0;
	gettimeofday(&philo.t0, 0);
	while (i < n)
	{
		philo.number = i + 1;
		if (pthread_create(&philo.thread, NULL, &thread_routine, &philo))
			return ;
		pthread_join(philo.thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data			data;
	t_fork			*fork_list;

	if (ac < 5 || ac > 6)
		return (1);
	if (init_input(&data, ac, av))
		return (1);
	fork_list = create_fork_list(data);
	if (!fork_list)
		return (1);
	create_thread(&data, fork_list);
	destroy_mutex(fork_list, &data);
	free(fork_list);
	return (0);
}
