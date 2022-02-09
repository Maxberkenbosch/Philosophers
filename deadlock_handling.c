/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deadlock_handling.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 17:29:15 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:45:16 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void	change_rules(t_philo *philo, int code, int i)
{
	long	cur_time;

	cur_time = get_cur_time(philo);
	if (code == 1)
	{
		philo[i].checker = philo->s_rules->cur_time;
		philo[i].has_eaten = 0;
	}
	if (code == 2)
	{
		pthread_mutex_lock(&philo->s_rules->print);
		change_dead_locked(philo, 0);
		printf("%ld %d died\n", cur_time, i + 1);
		pthread_mutex_unlock(&philo->s_rules->print);
	}
}

void	check_all_ate(t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philo->s_rules->num_philo)
	{
		usleep(100);
		pthread_mutex_lock(&philo->s_rules->ate_lock);
		if (philo[i].times_ate >= philo->s_rules->times_eat)
			count++;
		pthread_mutex_unlock(&philo->s_rules->ate_lock);
		i++;
	}
	if (count == philo->s_rules->num_philo)
		change_dead_locked(philo, 0);
}

void	check_deadlock(t_philo *philo)
{
	int		i;
	long	cur_time;

	i = 0;
	while (i < philo->s_rules->num_philo)
	{
		usleep(900);
		if (philo->s_rules->times_eat)
			check_all_ate(philo);
		pthread_mutex_lock(&philo->s_rules->has_eaten_lock);
		if (philo[i].has_eaten == 1)
		{
			change_rules(philo, 1, i);
		}
		pthread_mutex_unlock(&philo->s_rules->has_eaten_lock);
		cur_time = get_cur_time(philo);
		if (philo->s_rules->cur_time - philo[i].checker > \
			philo->s_rules->time_to_die)
		{
			change_rules(philo, 2, i);
			break ;
		}
		i++;
	}
}

int	check_has_eaten(t_philo *philo)
{
	int	i;

	while (!change_dead_locked(philo, 1))
	{
		i = 0;
		philo->s_rules->cur_time = get_cur_time(philo);
		check_deadlock(philo);
	}
	return (1);
}

void	check_dead_new(t_philo *philo)
{
	int	i;

	i = 0;
	usleep (10);
	while (i < philo->s_rules->num_philo)
	{
		philo[i].checker = get_cur_time(philo);
		i++;
	}
	check_has_eaten(philo);
}
