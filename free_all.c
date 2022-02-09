/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:37:23 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:47:37 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	free_all(t_philo *philo)
{
	free(philo->s_rules->forks_taken);
	free(philo);
}

void	join_threads(t_philo *philo, pthread_t	philosophers[200])
{
	int	i;

	i = 0;
	while (i < philo->s_rules->num_philo)
	{
		pthread_join (philosophers[i], NULL);
		i++;
	}
}
