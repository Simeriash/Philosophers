/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:04:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/07 11:43:56 by julauren         ###   ########.fr       */
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

static void	create_thread(t_data *data, t_fork *fork_list, t_philo *philo_list)
{
	int				n;
	int				i;
	struct timeval	t0;

	(void)fork_list;
	n = data->nb_philo;
	i = -1;
	gettimeofday(&t0, 0);
	while (++i < n)
	{
		philo_list[i].t0 = t0;
		if (pthread_create(&philo_list[i].thread, NULL, &thread_routine,
				&philo_list[i]))
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_fork	*fork_list;
	t_philo	*philo_list;
	int		i;

	if (ac < 5 || ac > 6 || parse(ac, av, &data)
		|| init_struc(data, &fork_list, &philo_list))
		return (1);
	create_thread(data, fork_list, philo_list);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo_list[i].thread, NULL);
		i++;
	}
	destroy_mutex(data, fork_list);
	free(fork_list);
	free(data);
	free(philo_list);
	return (0);
}
