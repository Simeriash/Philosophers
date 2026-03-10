/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:04:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/10 15:34:49 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	message(pthread_mutex_t *mutex, long int t, int num, int code)
{
	pthread_mutex_lock(mutex);
	if (code == 0)
		printf("%ld | %i has taken a fork\n", t, num);
	else if (code == 1)
		printf("%ld | %i is eating\n", t, num);
	else if (code == 2)
		printf("%ld | %i is sleeping\n", t, num);
	else if (code == 3)
		printf("%ld | %i is thinking\n", t, num);
	else if (code == 4)
		printf("%ld | %i died\n", t, num);
	pthread_mutex_unlock(mutex);
}

void	drop_the_forks(t_fork *fork_1, t_fork *fork_2)
{
	pthread_mutex_lock(&fork_1->mutex);
	usleep(20);
	fork_1->free = 0;
	pthread_mutex_unlock(&fork_1->mutex);
	pthread_mutex_lock(&fork_2->mutex);
	usleep(20);
	fork_2->free = 0;
	pthread_mutex_unlock(&fork_2->mutex);
}

void	destroy_mutex(t_data *data, t_fork *fork)
{
	int	i;

	if (data)
	{
		pthread_mutex_destroy(&data->data);
		pthread_mutex_destroy(&data->printf);
	}
	if (fork)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&fork[i].mutex);
			i++;
		}
	}
}

static int	create_thread(t_data *data, t_philo *philo, t_fork *fork)
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
		if (pthread_create(&philo[i].thread, NULL, &thread_routine, &philo[i]))
		{
			pthread_mutex_lock(&philo->data->data);
			philo->data->end = 0;
			pthread_mutex_unlock(&philo->data->data);
			break ;
		}
	}
	return (i);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_fork	*fork;
	t_philo	*philo;
	int		i;
	int		n;

	if (ac < 5 || ac > 6 || parse(ac, av, &data)
		|| init_struc(data, &fork, &philo))
		return (1);
	n = create_thread(data, philo, fork);
	i = 0;
	while (i < n)
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
