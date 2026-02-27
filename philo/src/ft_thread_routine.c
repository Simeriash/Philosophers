/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:32:17 by julauren          #+#    #+#             */
/*   Updated: 2026/02/27 11:58:36 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_message(long int t, int val, int msg_code)
{
	if (msg_code == 0)
		printf("%ld | %i has taken a fork\n", t, val);
	else if (msg_code == 1)
		printf("%ld | %i is eating\n", t, val);
	else if (msg_code == 2)
		printf("%ld | %i is sleeping\n", t, val);
	else if (msg_code == 3)
		printf("%ld | %i is thinking\n", t, val);
	else if (msg_code == 4)
		printf("%ld | %i is died\n", t, val);
}

void	*ft_thread_routine(void *arg)
{
	t_node			*node;
	struct timeval	t1;
	long int		t;

	node = (t_node *)arg;
	pthread_mutex_lock(&node->fork);
	if (node->val != 1)
		pthread_mutex_lock(&node->prev->fork);
	else
		pthread_mutex_lock(&node->prev->prev->fork);
	gettimeofday(&t1, 0);
	t = (t1.tv_sec - node->t0_sec) * 1000 + (t1.tv_usec - node->t0_usec) / 1000;
	ft_message(t, node->val, 0);
	ft_message(t, node->val, 1);
	usleep(node->data->time_2_eat * 1000);
	if (node->val != 1)
		pthread_mutex_unlock(&node->prev->fork);
	else
		pthread_mutex_unlock(&node->prev->prev->fork);
	pthread_mutex_unlock(&node->fork);
	gettimeofday(&t1, 0);
	t = (t1.tv_sec - node->t0_sec) * 1000 + (t1.tv_usec - node->t0_usec) / 1000;
	ft_message(t, node->val, 2);
	return (NULL);
}
