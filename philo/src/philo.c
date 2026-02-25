/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:41:04 by julauren          #+#    #+#             */
/*   Updated: 2026/02/25 14:02:59 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

 void	ft_message(long int t, int val, int msg_code)
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

static void	*ft_thread_routine(void *arg)
{
	t_node			*node;
	struct timeval	t0;
	long int		t;

	gettimeofday(&t0, 0);
	node = (t_node *)arg;
	t = (t0.tv_sec - node->t0_sec) * 1000 + (t0.tv_usec - node->t0_usec);
	printf("Thread [%.15ld] - philo n⁰ %.3i\t%.15ld\n",
		node->thread, node->val, t);
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
		pthread_mutex_init(&node->fork.fork_mutex, NULL);
		thread = pthread_create(&node->thread, NULL, &ft_thread_routine, node);
		node = node->next;
		if (thread != 0)
			break ;
	}
	node = table->next;
	while (node != table)
	{
		pthread_mutex_destroy(&node->fork.fork_mutex);
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
