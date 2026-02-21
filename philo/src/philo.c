/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:41:04 by julauren          #+#    #+#             */
/*   Updated: 2026/02/21 17:17:35 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*ft_thread_routine(void *arg)
{
	t_node	*node;

	node = (t_node *)arg;
	printf("Thread [%ld] - philo n⁰ %i\n", node->thread, node->val);
	return (NULL);
}

static void	ft_thread(t_node *table, t_data *data)
{
	int		i;
	t_node	*node;

	node = table->next;
	i = 1;
	while (i <= data->nb_philo)
	{
		pthread_create(&node->thread, NULL, &ft_thread_routine, node);
		node = node->next;
		i++;
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
	printf("OK\n");						/*		A EFFACER 	/!\		*/
	table = ft_everyone_to_the_table(data.nb_philo);
	if (!table)
		return (0);
	ft_thread(table, &data);
	// thread join pour chaque thread
	ft_free_table(table);
}
