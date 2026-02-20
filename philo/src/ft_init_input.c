/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:33:53 by julauren          #+#    #+#             */
/*   Updated: 2026/02/20 10:36:25 by julauren         ###   ########.fr       */
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

int	ft_init_input(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi_philo(av[1]);
	if (data->nb_philo == -1)
		return (1);
	data->time_2_die = ft_atoi_philo(av[2]);
	if (data->time_2_die == -1)
		return (1);
	data->time_2_eat = ft_atoi_philo(av[3]);
	if (data->time_2_eat == -1)
		return (1);
	data->time_2_sleep = ft_atoi_philo(av[4]);
	if (data->time_2_sleep == -1)
		return (1);
	if (ac == 6)
	{
		data->nb_times = ft_atoi_philo(av[5]);
		if (data->nb_times == -1)
			return (1);
	}
	else
		data->nb_times = 0;
	return (0);
}
