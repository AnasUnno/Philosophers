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

t_philo *initialize_philos(t_data *data)
{
	t_philo	*philos;
	int i;

	
	philos = malloc(sizeof(t_philo) * data->n_philos);
	i = 0;
	while (i < data->n_philos)
	{
		philos[i].data = data;
		philos[i].philo_id = i + 1;
		philos[i].dying_time = data->t_die;
		philos[i].eat_times = 0;
		philos[i].last_meal = 0;
		i++;
	}
	return (philos);
}

pthread_mutex_t	*initialize_forks(t_data	*data, t_philo *philo)
{
	int	i;

	i = 0;
	
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
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
	return (data->forks);
}

t_data *initialize_data(int ac, char **av)
{
	t_data	*data;
	
	if (ft_atoi(av[1]) < 1)
		ft_perror();
	data = malloc(sizeof(t_data));
	data->n_philos = ft_atoi(av[1]);
	data->t_die = (unsigned int)ft_atoi(av[2]);
	data->t_eat = (unsigned int)ft_atoi(av[3]);
	data->t_sleep = (unsigned int)ft_atoi(av[4]);
	if (ac == 6)
		data->n_eat = ft_atoi(av[5]);
	else
		data->n_eat = -1;
	data->all_finished = 0;
	data->stop_flag = 0;
	data->t_start = get_curr_time();
	return (data);
}
