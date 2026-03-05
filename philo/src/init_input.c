/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 06:06:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/05 16:50:46 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi_philo(const char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (-1);
		num = num * 10 + str[i] - 48;
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	return (num);
}

static int	ft_no_time_2_lose(t_data *data)
{
	if (data->nb_philo == 0 || data->time_2_die == 0
		|| (data->time_2_die < (data->time_2_eat + data->time_2_sleep))
		|| data->time_2_die < data->time_2_eat
		|| data->time_2_die < data->time_2_sleep
		|| data->nb_times == 0)
		return (1);
	pthread_mutex_init(&data->data, NULL);
	pthread_mutex_init(&data->printf, NULL);
	return (0);
}

t_data	*init_input(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	data->nb_philo = ft_atoi_philo(av[1]);
	if (data->nb_philo == -1)
		return (NULL);
	data->time_2_die = ft_atoi_philo(av[2]);
	if (data->time_2_die == -1)
		return (NULL);
	data->time_2_eat = ft_atoi_philo(av[3]);
	if (data->time_2_eat == -1)
		return (NULL);
	data->time_2_sleep = ft_atoi_philo(av[4]);
	if (data->time_2_sleep == -1)
		return (NULL);
	if (ac == 6)
	{
		data->nb_times = ft_atoi_philo(av[5]);
		if (data->nb_times == -1)
			return (NULL);
	}
	else
		data->nb_times = -1;
	if (ft_no_time_2_lose(data))
		return (NULL);
	data->end = 1;
	data->nb_meal = 0;
	return (data);
}
