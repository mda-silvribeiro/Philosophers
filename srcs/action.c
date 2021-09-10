/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:02:51 by mda-silv          #+#    #+#             */
/*   Updated: 2021/09/09 14:02:53 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_fork(t_philo *p)
{
	size_t	f;

	f = (p->philo_id + 1) % p->data->num_of_philos;
	pthread_mutex_lock(&(p->data->forks[p->philo_id]));
	printf(MAG"[%ld] Philosopher's %lu has taken a fork\n", get_time()
		- p->data->init_time, p->philo_id + 1);
	if (p->data->num_of_philos == 1)
	{
		sleep_time(p->data->time_to_eat);
		pthread_mutex_unlock(&(p->data->forks[p->philo_id]));
		pthread_exit(0);
	}
	pthread_mutex_lock(&(p->data->forks[f]));
	printf(MAG"[%ld] Philosopher's %lu has taken a fork\n", get_time()
		- p->data->init_time, p->philo_id + 1);
	pthread_mutex_unlock(&(p->data->forks[p->philo_id]));
}

static void	other_fork(t_philo *p)
{
	pthread_mutex_unlock(&(p->data->forks[p->philo_id]));
	pthread_mutex_unlock(&(p->data->forks[(p->philo_id + 1)
			% p->data->num_of_philos]));
	p->ate = 0;
	printf(GRE"[%ld] Philosopher's %lu is sleeping\n", get_time()
		- p->data->init_time, p->philo_id + 1);
	sleep_time(p->data->time_to_sleep);
}

static void	philo_eat(t_philo *p)
{
	printf(YEL"[%ld] Philosopher's %lu is eating\n", get_time()
		- p->data->init_time, p->philo_id + 1);
	p->ate = 1;
	p->last_eat = get_time();
	(p->eat_count)++;
	pthread_mutex_unlock(&(p->data->locked));
	if (p->data->philo_eat > 0 && p->eat_count >= p->data->philo_eat)
	{
		pthread_mutex_unlock(&(p->data->forks[p->philo_id]));
		pthread_mutex_unlock(&(p->data->forks[(p->philo_id + 1)
				% p->data->num_of_philos]));
		p->data->must_eat++;
		p->must_eat = 1;
		if (p->data->must_eat >= p->data->num_of_philos)
		{
			p->data->some_died = 1;
			printf(OTA"Philosophers satisfied!!!\n");
		}
		pthread_mutex_unlock(&(p->data->locked));
		pthread_exit(0);
	}
	pthread_mutex_unlock(&(p->data->locked));
	sleep_time(p->data->time_to_eat);
}

void	*routine_philo(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	if (philo->philo_id % 2)
		sleep_time(philo->data->time_to_eat);
	while (1)
	{
		philo_fork(philo);
		philo_eat(philo);
		other_fork(philo);
		printf(BLU"[%ld] Philosopher's %lu is thinking\n", get_time()
			- philo->data->init_time, philo->philo_id + 1);
		if (philo->data->some_died)
			pthread_exit(0);
	}
	pthread_exit(0);
}
