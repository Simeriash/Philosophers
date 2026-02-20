/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:52:28 by julauren          #+#    #+#             */
/*   Updated: 2026/02/20 18:21:01 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_data
{
	int	nb_philo;
	int	time_2_die;
	int	time_2_eat;
	int	time_2_sleep;
	int	nb_times;
}	t_data;

typedef struct s_node
{
	int	val;
	struct s_node	*previous;
	struct s_node	*next;
}	t_node;

int		ft_init_input(t_data *data, int ac, char **av);
t_node 	*ft_everyone_to_the_table(int nb);
void	ft_browse(t_node *table);
void	ft_reverse_browse(t_node *table);
void	ft_delete_node(t_node *node);
t_node	*ft_node_chr(t_node *table, int val);
void	ft_free_table(t_node *table);

#endif
