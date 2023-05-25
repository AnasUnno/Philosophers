/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:19:50 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/25 20:05:23 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_finished_meals(t_philo *philo)
{
	int		i;
	t_data	*data;

	i = -1;
	data = philo[0].data;
	pthread_mutex_lock(&data->meal_mutex);
	while (++i < data->n_philos)
	{
		if (philo[i].eat_times < data->n_eat)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (false);
		}
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (true);
}

void	check_death(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->data->n_philos)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			if (get_curr_time() - philo[i].last_meal >= (unsigned long)
				philo[i].data->t_die)
			{
				print_msg(philo, "died");
				pthread_mutex_lock(&philo->data->print_mutex);
				philo->data->stop_flag = 1;
				return ;
			}
			pthread_mutex_unlock(&philo->data->meal_mutex);
			i++;
		}
		if (check_finished_meals(philo) && (philo->data->n_eat != -1))
			return ;
	}
}

bool	eating_behaviour(t_philo *philo)
{
	int	i;

	i = 1;
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "has taken a fork");
		ft_usleep(philo->data->t_die);
		return (false);
	}
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	ft_usleep(philo->data->t_eat);
	(!pthread_mutex_lock(&philo->data->meal_mutex)) && (philo->eat_times++);
	philo->last_meal = get_curr_time();
	(philo->eat_times == philo->data->n_eat) && (i = 0);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (i == 0)
		return (false);
	return (true);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)philo_ptr;
	if (philo->philo_id % 2)
	{
		while (++i < 500)
			usleep(1);
	}
	while (1)
	{
		if (!eating_behaviour(philo))
			return (NULL);
		print_msg(philo, "is sleeping");
		ft_usleep(philo->data->t_sleep);
		print_msg(philo, "is thinking");
	}
	return (NULL);
}

int	threads_creator(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->n_philos)
		philo[i].last_meal = get_curr_time();
	i = -1;
	while (++i < philo->data->n_philos)
	{
		if (pthread_create(&philo[i].thread_id, NULL, &routine, &philo[i]))
			return (1);
	}
	i = -1;
	while (++i < philo->data->n_philos)
	{
		if (pthread_detach(philo[i].thread_id))
			return (2);
	}
	check_death(philo);
	return (0);
}
