/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:32:17 by julauren          #+#    #+#             */
/*   Updated: 2026/02/27 16:12:08 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long int	ft_time(t_node *node)
{
	long int		t;
	struct timeval	t1;

	gettimeofday(&t1, 0);
	t = (t1.tv_sec - node->t0_sec) * 1000 + (t1.tv_usec - node->t0_usec) / 1000;
	return (t);
}

static int	ft_so_long_goodbye(t_node *node, long int t, int *routine)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&node->data->philo);
	if (node->data->nb_philo == 0)
		i++;
	else if (t - node->ungry > node->data->time_2_die)
	{
		ft_message(t, node->val, 4);
		node->data->nb_philo = 0;
		i++;
	}
	pthread_mutex_unlock(&node->data->philo);
	if (i)
		*routine = 0;
	return (i);
}

static void	ft_unlock_mutex(t_node *node)
{
	if (node->val != 1)
		pthread_mutex_unlock(&node->prev->fork);
	else
		pthread_mutex_unlock(&node->prev->prev->fork);
	pthread_mutex_unlock(&node->fork);
}

static int	ft_thread_next(t_node *node, long int t, int *routine)
{
	node->ungry = t;
	ft_message(t, node->val, 0);
	ft_message(t, node->val, 1);
	usleep(node->data->time_2_eat * 1000);
	ft_unlock_mutex(node);
	(node->eat)++;
	if (node->eat == node->data->nb_times)
		return (1);
	t = ft_time(node);
	if (ft_so_long_goodbye(node, t, routine))
		return (1);
	ft_message(t, node->val, 2);
	usleep(node->data->time_2_sleep * 1000);
	t = ft_time(node);
	if (ft_so_long_goodbye(node, t, routine))
		return (1);
	ft_message(t, node->val, 3);
	return (0);
}

void	*ft_thread_routine(void *arg)
{
	t_node		*node;
	long int	t;
	int			routine;

	node = (t_node *)arg;
	routine = 1;
	while (routine)
	{
		pthread_mutex_lock(&node->fork);
		if (node->val != 1)
			pthread_mutex_lock(&node->prev->fork);
		else
			pthread_mutex_lock(&node->prev->prev->fork);
		t = ft_time(node);
		if (ft_so_long_goodbye(node, t, &routine))
		{
			ft_unlock_mutex(node);
			return (NULL);
		}
		if (ft_thread_next(node, t, &routine))
			return (NULL);
	}
	return (NULL);
}
