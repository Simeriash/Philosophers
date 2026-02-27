/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:41:04 by julauren          #+#    #+#             */
/*   Updated: 2026/02/27 11:50:06 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_init_mutex(t_node *table)
{
	t_node	*node;

	pthread_mutex_init(&table->data->philo, NULL);
	node = table->next;
	while (node != table)
	{
		pthread_mutex_init(&node->fork, NULL);
		node = node->next;
	}
}

static void	ft_destroy_mutex(t_node *table)
{
	t_node	*node;

	pthread_mutex_destroy(&table->data->philo);
	node = table->next;
	while (node != table)
	{
		pthread_mutex_destroy(&node->fork);
		node = node->next;
	}
}

static void	ft_thread(t_node *table)
{
	int				thread;
	t_node			*node;
	struct timeval	t0;

	gettimeofday(&t0, 0);
	ft_init_mutex(table);
	node = table->next;
	while (node != table)
	{
		node->t0_sec = t0.tv_sec;
		node->t0_usec = t0.tv_usec;
		thread = pthread_create(&node->thread, NULL, &ft_thread_routine, node);
		node = node->next;
		if (thread != 0)
			break ;
	}
	node = table->next;
	while (node != table)
	{
		pthread_join(node->thread, NULL);
		node = node->next;
	}
	ft_destroy_mutex(table);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_node	*table;

	if (ac < 5 || ac > 6)
		return (0);
	if (ft_init_input(&data, ac, av))
		return (0);
	table = ft_everyone_to_the_table(&data);
	if (!table)
		return (0);
	ft_thread(table);
	ft_free_table(table);
}
