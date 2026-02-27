/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_everyone_to_the_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:42:14 by julauren          #+#    #+#             */
/*   Updated: 2026/02/27 16:05:20 by julauren         ###   ########.fr       */
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

static t_node	*ft_create_table(t_data *data)
{
	t_node	*table;

	table = malloc(sizeof(*table));
	if (!table)
		return (NULL);
	table->val = 0;
	table->data = data;
	table->thread = 0;
	memset(&table->fork, 0, sizeof(pthread_mutex_t));
	memset(&table->data->philo, 0, sizeof(pthread_mutex_t));
	table->prev = table;
	table->next = table;
	return (table);
}

static int	ft_add_after(t_node *node, t_data *data, int val)
{
	t_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (1);
	new_node->val = val;
	new_node->data = data;
	new_node->thread = 0;
	new_node->ungry = 0;
	new_node->eat = 0;
	memset(&new_node->fork, 0, sizeof(pthread_mutex_t));
	new_node->prev = node;
	new_node->next = node->next;
	node->next->prev = new_node;
	node->next = new_node;
	return (0);
}

t_node	*ft_everyone_to_the_table(t_data *data)
{
	t_node	*table;
	t_node	*node;
	int		i;

	table = ft_create_table(data);
	if (!table)
		return (NULL);
	i = 1;
	node = table->next;
	while (i <= data->nb_philo)
	{
		if (ft_add_after(node, data, i))
		{
			ft_free_table(table);
			return (NULL);
		}
		i++;
		node = node->next;
	}
	return (table);
}
