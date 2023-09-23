/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:28:54 by araji-af          #+#    #+#             */
/*   Updated: 2023/06/01 16:19:30 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	check_input(int ac, char **av)
{
	pars_args(ac, av);
	check_empty(ac, av);
	check_spaces(av);
}

static void	clean_up(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->meal_sem);
	sem_close(data->print_sem);
	sem_unlink("forks");
	sem_unlink("meal_sem");
	sem_unlink("print_sem");
}

static void	free_processes(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->n_philos)
		kill(philo[i].pid, SIGKILL);
}

static void	free_all(t_philo *philo, t_data *data)
{
	clean_up(data);
	free(data);
	data = NULL;
	free(philo);
	philo = NULL;
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	*data;

	data = NULL;
	philo = NULL;
	check_input(ac, av);
	data = initialize_data(ac, av);
	if (!data)
		return (0);
	philo = initialize_philos(data);
	if (!philo)
		return (0);
	semaphores_initializing(philo);
	process_creator(philo);
	waitpid(-1, NULL, 0);
	free_processes(philo);
	free_all(philo, data);
	return (0);
}
