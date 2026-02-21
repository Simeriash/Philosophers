/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_everyone_to_the_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:42:14 by julauren          #+#    #+#             */
/*   Updated: 2026/02/21 15:39:22 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_node	*ft_create_table(void)
{
	t_node	*table;

	table = malloc(sizeof(*table));
	if (!table)
		return (NULL);
	table->val = 0;
	table->thread = 0;
	table->fork.fork = 0;
	memset(&table->fork.fork_mutex, 0, sizeof(pthread_mutex_t));
	table->previous = table;
	table->next = table;
	return (table);
}

/*int	ft_add_before(t_node *node, int val)
{
	t_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (1);
	new_node->val = val;
	new_node->previous = node->previous;
	new_node->next = node;
	node->previous->next = new_node;
	node->previous = new_node;
	return (0);
}*/

static int	ft_add_after(t_node *node, int val)
{
	t_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (1);
	new_node->val = val;
	new_node->thread = 0;
	new_node->fork.fork = 0;
	memset(&new_node->fork.fork_mutex, 0, sizeof(pthread_mutex_t));
	new_node->previous = node;
	new_node->next = node->next;
	node->next->previous = new_node;
	node->next = new_node;
	return (0);
}

t_node	*ft_everyone_to_the_table(int nb)
{
	t_node	*table;
	t_node	*node;
	int		i;

	table = ft_create_table();
	if (!table)
		return (NULL);
	i = 1;
	node = table->next;
	while (i <= nb)
	{
		if (ft_add_after(node, i))
		{
			ft_free_table(table);
			return (NULL);
		}
		i++;
		node = node->next;
	}
	return (table);
}
