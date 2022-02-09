/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_and_sleep.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 16:53:48 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:46:45 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

void	sleep_timer(t_philo *philo)
{
	long	start_time;
	long	cur_time;

	start_time = get_cur_time(philo);
	while (!change_dead_locked(philo, 1))
	{
		cur_time = get_cur_time(philo);
		if (cur_time - start_time >= \
			philo->s_rules->time_to_sleep)
			return ;
		(usleep(1000));
	}
}

int	philo_sleep(t_philo *philo)
{
	timestamp(philo, "is sleeping");
	sleep_timer(philo);
	timestamp(philo, "is thinking");
	usleep((philo->s_rules->time_to_sleep / 2) * 10);
	return (0);
}

void	eat_timer(t_philo *philo)
{
	long	start_time;
	long	cur_time;

	start_time = get_cur_time(philo);
	while (!change_dead_locked(philo, 1))
	{
		cur_time = get_cur_time(philo);
		if (cur_time - start_time >= \
			philo->s_rules->time_to_eat)
			return ;
		(usleep(1000));
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_rules->has_eaten_lock);
	philo->has_eaten = 1;
	pthread_mutex_unlock(&philo->s_rules->has_eaten_lock);
	timestamp(philo, "is eating");
	pthread_mutex_lock(&philo->s_rules->ate_lock);
	philo->times_ate += 1;
	pthread_mutex_unlock(&philo->s_rules->ate_lock);
	eat_timer(philo);
}
