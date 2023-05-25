/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:28:54 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/24 23:39:33 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	check_input(int ac, char **av)
{
	pars_args(ac, av);
	check_empty(ac, av);
	check_spaces(av);
}

void	ft_leaks(void)
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	*data;

	// atexit(ft_leaks);
	data = NULL;
	philo = NULL;
	check_input(ac, av);
	data = initialize_data(ac, av);
	if (!data)
		return (0);
	philo = initialize_philos(data);
	if (!philo)
		return (0);
	data->forks = initialize_forks(data, philo);
	if (threads_creator(philo))
		return (1);
	clear_mutexes(philo);
	return (0);
}
