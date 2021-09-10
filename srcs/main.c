/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:03:12 by mda-silv          #+#    #+#             */
/*   Updated: 2021/09/09 14:08:16 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//./philo arg1 arg2 arg3 arg4 arg5
//arg1 = number_of_philosophers
//arg2 = time_to_die
//arg3 = time_to_eat
//arg4 = time_to_sleep
//arg5 = number_of_times_each_philosopher_must_eat
//pthread_create(&(global->death), NULL, &ft_die, (void *)(global))
//to create a thread with pthread
//Each fork has its own mutex which allows to lock it when a philosopher 
//takes it.
//We also use a mutex shared by all the philosophers which allows to print 
//text without mixing as in the example above.

#include "philo.h"

static char	philo(t_data *global)
{
	size_t	count;

	if (pthread_create(&(global->death), NULL, &ft_die, (void *)(global)))
		return (0);
	pthread_detach(global->death);
	count = -1;
	while (++count < global->num_of_philos)
	{
		if (pthread_create(&(global->philo[count].thread),
				NULL, &routine_philo, (void *)(&(global->philo[count]))))
			return (0);
	}
	count = -1;
	while (++count < global->num_of_philos)
		if (pthread_join(global->philo[count].thread, NULL))
			return (0);
	return (1);
}

int	main(int ac, char const **av)
{
	t_data	global;

	if (ac < 5 || ac > 6)
		return (printf(RED"Error, wrong arguments!\n"));
	if (!init_all(&global, av, ac))
	{
		clean_free(&global);
		return (printf(RED"We can't start, init error or negative number!\n"));
	}
	if (!philo(&global))
	{
		clean_free(&global);
		return (printf(RED"Error, threads error!\n"));
	}
	pthread_mutex_lock(&(global.die));
	pthread_mutex_unlock(&(global.die));
	sleep_time(5);
	clean_free(&global);
	return (0);
}
