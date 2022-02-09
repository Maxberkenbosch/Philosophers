/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mberkenb <mberkenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 13:30:43 by mberkenb      #+#    #+#                 */
/*   Updated: 2022/02/02 13:52:36 by mberkenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc > 6 || argc < 5)
	{
		printf("Error : you entered the wrong amount of arguments.\n");
		return (1);
	}
	if (store_args(argv, &rules) == 1)
		return (1);
	if (store_extra_rules(&rules) == 1)
		return (1);
	make_threads(&rules);
	return (0);
}
