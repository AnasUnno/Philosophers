/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:21 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/31 12:12:21 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*initialize_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!philos)
	{
		free(data->forks);
		data->forks = NULL;
		data = NULL;
		free(data);
		return (NULL);
	}
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

t_data	*initialize_data(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ft_atoi(av[1]) && ft_atoi(av[2]) && ft_atoi(av[3]) && ft_atoi(av[4]))
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (NULL);
		if (ft_atoi(av[1]) > 200)
		{
			free(data);
			ft_perror();
		}
		data->n_philos = ft_atoi(av[1]);
		data->t_die = (unsigned int)ft_atoi(av[2]);
		data->t_eat = (unsigned int)ft_atoi(av[3]);
		data->t_sleep = (unsigned int)ft_atoi(av[4]);
	}
	else
		ft_perror();
	helper(ac, av, data);
	data->t_start = get_curr_time();
	return (data);
}

void	helper(int ac, char **av, t_data *data)
{
	if (ac == 6)
	{
		if (ft_atoi(av[5]))
			data->n_eat = ft_atoi(av[5]);
		else
		{
			free(data);
			data = NULL;
			ft_perror();
		}
	}
	else
		data->n_eat = -1;
}

void	semaphores_initializing(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("print_mutex");
	sem_unlink("meal_mutex");
	philo->data->forks = sem_open("forks", O_CREAT, S_IRUSR | S_IWUSR,
			philo->data->n_philos);
	philo->data->print_sem = sem_open("print_mutex",
			O_CREAT, S_IRUSR | S_IWUSR, 1);
	philo->data->meal_sem = sem_open("meal_mutex",
			O_CREAT, S_IRUSR | S_IWUSR, 1);
}
