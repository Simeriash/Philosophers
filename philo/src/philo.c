/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:04:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/08 11:30:45 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutex(t_data *data, t_fork *fork_list)
{
	int	i;

	if (data)
	{
		pthread_mutex_destroy(&data->data);
		pthread_mutex_destroy(&data->printf);
	}
	i = 0;
	if (fork_list)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&fork_list[i].mutex);
			i++;
		}
	}
}

static void	create_thread(t_data *data, t_philo *philo, t_fork *fork)
{
	int				n;
	int				i;
	struct timeval	t0;

	n = data->nb_philo;
	i = -1;
	while (++i < n)
		fork_choice(philo, fork, i);
	i = -1;
	gettimeofday(&t0, 0);
	while (++i < n)
	{
		philo[i].t0 = t0;
		if (pthread_create(&philo[i].thread, NULL, &thread_routine,
				&philo[i]))
			break ;
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_fork	*fork;
	t_philo	*philo;
	int		i;

	if (ac < 5 || ac > 6 || parse(ac, av, &data)
		|| init_struc(data, &fork, &philo))
		return (1);
	create_thread(data, philo, fork);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	destroy_mutex(data, fork);
	free(fork);
	free(data);
	free(philo);
	return (0);
}
