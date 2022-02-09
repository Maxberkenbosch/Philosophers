/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 17:19:25 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/09 10:53:07 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef struct s_rules
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_eat;
	int				*forks_taken;
	int				dead_locked;
	long			cur_time;
	pthread_mutex_t	ate_lock;
	pthread_mutex_t	has_eaten_lock;
	pthread_mutex_t	change_dead_lock;
	pthread_mutex_t	get_time_lock;
	pthread_mutex_t	print;
	pthread_mutex_t	waiter;
	pthread_mutex_t	forks[200];
}	t_rules;

typedef struct s_philo
{
	int				times_ate;
	int				ask_waiter_again;
	int				has_eaten;
	long			checker;
	int				left_fork;
	int				right_fork;
	int				forks_up;
	int				philo_id;
	t_rules			*s_rules;
}	t_philo;

//process
int		make_threads(t_rules *rules);

//initialize
int		store_args(char *argv[], t_rules *rules);
int		store_extra_rules(t_rules *rules);

//utils
void	*ft_calloc(size_t count, size_t size);
long	ft_atoi(const char *str);
void	timestamp(t_philo *philo, char	*str);

//deadlock_handling
void	check_dead_new(t_philo *philo);

//eat_sleep
void	sleep_timer(t_philo *philo);
int		philo_sleep(t_philo *philo);
void	eat_timer(t_philo *philo);
void	philo_eat(t_philo *philo);

//fork_handling
void	fork_managment(t_philo *philo);
void	forks_available(t_philo *philo);
void	change_forks_taken(t_philo *philo, int code);

//free_all
void	free_all(t_philo *philo);
void	join_threads(t_philo *philo, pthread_t	philosophers[200]);

//Locked checks
long	get_cur_time(t_philo *philo);
int		change_dead_locked(t_philo *philo, int code);
int		change_has_eaten(t_philo *philo, int i);

#endif