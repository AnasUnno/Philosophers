/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:28:54 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/23 16:51:11 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	check_input(int ac, char **av)
{
	pars_args(ac, av);
	check_empty(ac, av);
	check_spaces(av);
}


int main(int ac, char **av)
{
	t_philo *philo;
	t_data	*data;

	data = NULL;
	philo = NULL;
	check_input(ac, av);
	data = initialize_data(ac, av);
	philo = malloc(sizeof(t_philo) * data->n_philos);
	philo = initialize_philos(data);
	data->forks = initialize_forks(data, philo);
	threads_creator(philo);
	return 0;
}