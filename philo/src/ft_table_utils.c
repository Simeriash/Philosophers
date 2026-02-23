/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:56:07 by julauren          #+#    #+#             */
/*   Updated: 2026/02/23 09:28:01 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_browse(t_node *table)
{
	t_node	*node;

	node = table->next;
	while (node != table)
	{
		printf("%d\n", node->val);
		node = node->next;
	}
}

void	ft_reverse_browse(t_node *table)
{
	t_node	*node;

	node = table->previous;
	while (node != table)
	{
		printf("%d\n", node->val);
		node = node->previous;
	}
}

void	ft_delete_node(t_node *node)
{
	node->previous->next = node->next;
	node->next->previous = node->previous;
	free(node);
}

t_node	*ft_node_chr(t_node *table, int val)
{
	t_node	*node;

	node = table->next;
	while (node != table)
	{
		if (node->val == val)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	ft_free_table(t_node *table)
{
	t_node	*node;
	t_node	*tmp;

	node = table->next;
	while (node != table)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	free(table);
}
