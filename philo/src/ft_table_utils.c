/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:56:07 by julauren          #+#    #+#             */
/*   Updated: 2026/02/20 15:57:59 by julauren         ###   ########.fr       */
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
