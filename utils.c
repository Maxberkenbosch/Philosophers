/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 13:56:45 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 11:43:24 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (size == 0 || count == 0)
	{
		size = 1;
		count = 1;
	}
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	memset(ptr, '\0', count * size);
	return (ptr);
}

static int	whitespace(const char *s, int c)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	long	tot;
	int		mp;

	tot = 0;
	mp = 0;
	while (whitespace(" \n\t\v\r\f", *str))
		str++;
	if (*str == '-' || *str == '+')
	{
		mp = *str;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tot = tot * 10 + (*str - 48);
		str++;
	}
	if (mp == '-')
		return (tot * -1);
	return (tot);
}

void	timestamp(t_philo *philo, char	*str)
{
	long	cur_time;

	pthread_mutex_lock(&philo->s_rules->print);
	cur_time = get_cur_time(philo);
	if (!change_dead_locked(philo, 1))
		printf("%ld %d %s\n", cur_time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->s_rules->print);
}
