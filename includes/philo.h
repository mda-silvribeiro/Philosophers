/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:02:17 by mda-silv          #+#    #+#             */
/*   Updated: 2021/09/09 14:02:30 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\x1B[31m"
# define GRE "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define OTA "\x1B[36m"

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
	size_t			philo_id;
	size_t			last_eat;
	size_t			eat_count;
	char			must_eat;
	char			ate;
	pthread_t		thread;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	size_t				num_of_philos;
	size_t				philo_eat;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				init_time;
	size_t				must_eat;
	char				some_died;
	pthread_t			death;
	pthread_mutex_t		*forks;
	pthread_mutex_t		die;
	pthread_mutex_t		locked;
	t_philo				*philo;
}				t_data;

char			init_all(t_data *data, char const **av, int ac);
void			clean_free(t_data *data);
unsigned int	get_time(void);
void			sleep_time(unsigned int delay);
void			*routine_philo(void *p);
void			*ft_die(void *philo);
long			ft_my_atoi(const char *str);

#endif
