/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:06:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/06 15:32:44 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi_philo(const char *str, int *num)
{
	int		i;

	i = 0;
	*num = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (1);
		*num = (*num) * 10 + str[i] - 48;
		if (*num > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_no_time_2_lose(t_data *data)
{
	if (data->nb_philo == 0 || data->time_2_die == 0
		|| (data->time_2_die < (data->time_2_eat + data->time_2_sleep))
		|| data->time_2_die < data->time_2_eat
		|| data->time_2_die < data->time_2_sleep
		|| data->nb_times == 0)
	{
		free(data);
		return (1);
	}
	return (0);
}

int	parse(int ac, char **av, t_data **data)
{
	*data = malloc(sizeof(**data));
	if (!(*data))
		return (1);
	if (ft_atoi_philo(av[1], &(*data)->nb_philo)
		|| ft_atoi_philo(av[2], &(*data)->time_2_die)
		|| ft_atoi_philo(av[3], &(*data)->time_2_eat)
		|| ft_atoi_philo(av[4], &(*data)->time_2_sleep))
	{
		free(*data);
		return (1);
	}
	if (ac == 6 && ft_atoi_philo(av[5], &(*data)->nb_times))
	{
		free(*data);
		return (1);
	}
	else
		(*data)->nb_times = -1;
	if (ft_no_time_2_lose(*data))
		return (1);
	(*data)->end = 1;
	(*data)->nb_meal = 0;
	pthread_mutex_init(&(*data)->data, NULL);
	pthread_mutex_init(&(*data)->printf, NULL);
	return (0);
}
