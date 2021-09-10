/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:03:05 by mda-silv          #+#    #+#             */
/*   Updated: 2021/09/09 14:03:07 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
(pthread_mutex_init(&(data->locked), NULL **mandatory to init the mutex
*/
#include "philo.h"

static char	init_mutex(t_data *data)
{
	size_t	count;

	if (pthread_mutex_init(&(data->locked), NULL))
		return (0);
	if (pthread_mutex_init(&(data->die), NULL))
		return (0);
	data->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* data->num_of_philos);
	if (!data->forks)
		return (0);
	count = 0;
	while (count < data->num_of_philos)
	{
		if (pthread_mutex_init(&(data->forks[count]), NULL))
			return (0);
		count++;
	}
	return (1);
}

static char	init_philo(t_data *p)
{
	size_t	count;

	p->philo = (t_philo *) malloc(sizeof(t_philo) * p->num_of_philos);
	if (!p->philo)
		return (0);
	count = 0;
	while (count < p->num_of_philos)
	{
		p->philo[count].philo_id = count;
		p->philo[count].data = p;
		p->philo[count].ate = 0;
		p->philo[count].eat_count = 0;
		p->philo[count].last_eat = get_time();
		p->philo[count].must_eat = 0;
		count++;
	}
	return (1);
}

static char	set_arg(size_t *get, char const **av, int count)
{
	int	len;

	len = ft_my_atoi(av[count]);
	if (len <= 0)
		return (0);
	(*get) = (size_t)len;
	return (1);
}

static char	init_args(t_data *data, char const **av, int ac)
{
	if (!set_arg(&(data->num_of_philos), av, 1))
		return (0);
	if (!set_arg(&(data->time_to_die), av, 2))
		return (0);
	if (!set_arg(&(data->time_to_eat), av, 3))
		return (0);
	if (!set_arg(&(data->time_to_sleep), av, 4))
		return (0);
	if (ac == 6)
	{
		if (!set_arg(&(data->philo_eat), av, 5))
			return (0);
	}
	else
		data->philo_eat = 0;
	data->init_time = get_time();
	data->some_died = 0;
	data->must_eat = 0;
	return (1);
}

char	init_all(t_data *data, char const **av, int ac)
{
	data->philo = NULL;
	if (!init_args(data, av, ac))
		return (0);
	if (!init_philo(data))
		return (0);
	if (!init_mutex(data))
		return (0);
	return (1);
}
