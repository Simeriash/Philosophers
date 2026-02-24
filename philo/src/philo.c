/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:41:04 by julauren          #+#    #+#             */
/*   Updated: 2026/02/24 12:56:31 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*ft_thread_routine(void *arg)
{
	t_node			*node;
	struct timeval	t0;

	gettimeofday(&t0, 0);
	node = (t_node *)arg;
	printf("Thread [%.15ld] - philo n⁰ %.3i\t%.15ld\t%.15ld\n",
		node->thread, node->val, t0.tv_sec - node->t0_sec,
		t0.tv_usec - node->t0_usec);
	return (NULL);
}

static void	ft_thread(t_node *table)
{
	int				thread;
	t_node			*node;
	struct timeval	t0;

	gettimeofday(&t0, 0);
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
