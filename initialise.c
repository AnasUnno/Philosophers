/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 01:44:56 by marvin            #+#    #+#             */
/*   Updated: 2023/05/17 01:44:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int alocation(t_data *data, t_philo *philos)
{
	philos = malloc(sizeof(t_philo) * data->n_philos);
	if (philos)
		return (NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (NULL);
	return (1);
}

void initialize_philos(t_data *data, t_philo *philos)
{
	int i;

	i = 0;
	while (i < data->n_philos)
	{
		philos[i].data = data;
		philos[i].philo_id = i + 1;
		philos[i].dying_time = data->t_die;
		philos[i].eat_times = 0;
		i++;
	}
}

void	initialize_forks(t_data	*data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philos - 1)
	{
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[i + 1];
		i++;
	}
	philo[i].right_fork = &data->forks[i];
	philo[i].left_fork = &data->forks[0];
}

int initialize_data(t_data *data, int ac, char **av)
{
	data->n_philos = (unsigned int)ft_atoi(av[1]);
	data->t_die = (unsigned int)ft_atoi(av[2]);
	data->t_eat = (unsigned int)ft_atoi(av[3]);
	data->t_sleep = (unsigned int)ft_atoi(av[4]);
	if (ac == 6)
		data->n_eat = ft_atoi(av[5]);
	else
		data->n_eat = -2;
	data->all_finished = 0;
	data->stop_flag = 0;
	data->death_flag = 0; 
	if (data->n_philos < 1)
		return (0);
	return (1);
}

int initialization_caller(t_data *data, int ac, char **av)
{
	if (!initialise_data(data, ac, av))
		return (0);
	if (!allocation(data))
		return (0);
	return (1);
}