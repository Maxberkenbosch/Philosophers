/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 14:24:09 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:52:36 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	store_args(char *argv[], t_rules *rules)
{
	rules->num_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->times_eat = ft_atoi(argv[5]);
	else
		rules->times_eat = 0;
	if (rules->num_philo < 1 || rules->time_to_die <= 0 || \
		rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
	{
		printf("Error : you entered a wrong value.\n");
		return (1);
	}
	return (0);
}

int	store_extra_rules(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_init(&rules->waiter, NULL);
	pthread_mutex_init(&rules->print, NULL);
	pthread_mutex_init(&rules->get_time_lock, NULL);
	pthread_mutex_init(&rules->change_dead_lock, NULL);
	pthread_mutex_init(&rules->has_eaten_lock, NULL);
	pthread_mutex_init(&rules->ate_lock, NULL);
	rules->dead_locked = 0;
	rules->forks_taken = ft_calloc(rules->num_philo, sizeof(int *));
	if (!rules->forks_taken)
	{
		printf("Error: a calloc error occured.\n");
		return (1);
	}
	while (i < rules->num_philo)
	{
		rules->forks_taken[i] = 0;
		i++;
	}
	return (0);
}
