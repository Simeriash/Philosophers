/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:04:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/05 09:14:20 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_fork	*create_fork_list(t_data data)
{
	t_fork	*fork;
	int		i;

	fork = malloc(sizeof(*fork) * data.nb_philo);
	if (!fork)
		return (NULL);
	i = 0;
	while (i < data.nb_philo)
	{
		fork[i].free = 0;
		pthread_mutex_init(&fork[i].mutex, NULL);
		i++;
	}
	return (fork);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_fork			*fork;

	if (ac < 5 || ac > 6)
		return (1);
	if (init_input(&data, ac, av))
		return (1);
	fork = create_fork_list(data);
	if (!fork)
		return (1);
	free(fork);
	return (0);
}
