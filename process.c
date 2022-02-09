/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 15:05:25 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:53:00 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void	actions(t_philo *philo)
{
	forks_available(philo);
	if (philo->ask_waiter_again)
		forks_available(philo);
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->s_rules->forks[philo->left_fork]);
	change_forks_taken(philo, 1);
	timestamp(philo, "picked up a fork");
	pthread_mutex_lock(&philo->s_rules->forks[philo->right_fork]);
	change_forks_taken(philo, 2);
	pthread_mutex_unlock(&philo->s_rules->waiter);
	timestamp(philo, "picked up a fork");
	philo_eat(philo);
	pthread_mutex_unlock(&philo->s_rules->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->s_rules->forks[philo->right_fork]);
	change_forks_taken(philo, 3);
	philo_sleep(philo);
}

void	*manage_threads(void *t_void)
{
	t_philo	*philo;

	philo = (t_philo *)t_void;
	usleep (100);
	fork_managment(philo);
	while (1 && !change_dead_locked(philo, 1))
	{
		usleep(10);
		actions(philo);
	}
	return (t_void);
}

int	make_threads(t_rules *rules)
{
	int			i;
	t_philo		*philo;
	pthread_t	philosophers[200];

	i = 0;
	philo = ft_calloc(rules->num_philo, sizeof(*philo));
	if (!philo)
	{
		printf("Error: a calloc error occured.\n");
		return (1);
	}
	while (i < rules->num_philo)
	{
		philo[i].s_rules = rules;
		philo[i].philo_id = i + 1;
		philo[i].has_eaten = 0;
		pthread_mutex_init(&rules->forks[i], NULL);
		pthread_create (&philosophers[i], NULL, \
			&manage_threads, (void *)&philo[i]);
		i++;
	}
	check_dead_new(philo);
	join_threads(philo, philosophers);
	free_all(philo);
	return (0);
}
