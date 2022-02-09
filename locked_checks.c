/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   locked_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 10:47:42 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:52:45 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

long	get_cur_time(t_philo *philo)
{
	struct timeval	current_time;
	long			cur_time;

	pthread_mutex_lock(&philo->s_rules->get_time_lock);
	gettimeofday(&current_time, NULL);
	cur_time = (current_time.tv_sec * 1000) + \
		(current_time.tv_usec / 1000);
	pthread_mutex_unlock(&philo->s_rules->get_time_lock);
	return (cur_time);
}

int	change_dead_locked(t_philo *philo, int code)
{
	pthread_mutex_lock(&philo->s_rules->change_dead_lock);
	if (code == 1)
	{
		if (philo->s_rules->dead_locked)
		{
			pthread_mutex_unlock(&philo->s_rules->change_dead_lock);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&philo->s_rules->change_dead_lock);
			return (0);
		}
	}
	if (!code)
		philo->s_rules->dead_locked = 1;
	pthread_mutex_unlock(&philo->s_rules->change_dead_lock);
	return (0);
}

// int	change_has_eaten(t_philo *philo, int i)
// {
// 	pthread_mutex_lock(&philo->s_rules->has_eaten_lock);
// 	if (philo[i].has_eaten == 0)
// 	{
// 		philo[i].has_eaten = 1;
// 		return (1);
// 	}
// 	if (philo[i].has_eaten == 1)
// 	{
// 		philo[i].has_eaten = 0;
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&philo->s_rules->has_eaten_lock);
// 	return (0);
// }