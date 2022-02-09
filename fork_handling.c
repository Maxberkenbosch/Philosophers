/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 16:20:19 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:47:07 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void	fork_managment(t_philo *philo)
{
	if (philo->s_rules->num_philo == 1)
	{
		timestamp(philo, "died");
		change_dead_locked(philo, 0);
	}
	philo->left_fork = philo->philo_id - 1;
	philo->right_fork = philo->philo_id;
	if (philo->philo_id == philo->s_rules->num_philo)
		philo->left_fork = 0;
}

void	forks_available(t_philo *philo)
{
	usleep(1000);
	pthread_mutex_lock(&philo->s_rules->waiter);
	if (philo->s_rules->forks_taken[philo->left_fork] == 0 && \
		philo->s_rules->forks_taken[philo->right_fork] == 0)
		philo->ask_waiter_again = 0;
	else
		philo->ask_waiter_again = 1;
	pthread_mutex_unlock(&philo->s_rules->waiter);
}

void	change_forks_taken(t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->s_rules->waiter);
	if (code == 1)
		philo->s_rules->forks_taken[philo->left_fork] = 1;
	else if (code == 2)
		philo->s_rules->forks_taken[philo->right_fork] = 1;
	else if (code == 3)
	{
		philo->s_rules->forks_taken[philo->left_fork] = 0;
		philo->s_rules->forks_taken[philo->right_fork] = 0;
	}
	pthread_mutex_unlock(&philo->s_rules->waiter);
}
