/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:19:50 by araji-af          #+#    #+#             */
/*   Updated: 2023/06/01 15:13:50 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_finished_meals(t_philo *philo)
{
	t_data	*data;

	data = philo[0].data;
	sem_wait(data->meal_sem);
	if (philo->eat_times <= data->n_eat)
	{
		sem_post(data->meal_sem);
		return (false);
	}
	sem_post(data->meal_sem);
	return (true);
}

void	check_death(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->data->meal_sem);
		if (get_curr_time() - philo->last_meal >= (unsigned long)
			philo->data->t_die)
		{
			print_msg(philo, "died");
			return ;
		}
		sem_post(philo->data->meal_sem);
		usleep(500);
		if (check_finished_meals(philo) && (philo->data->n_eat != -1))
			return ;
	}
}

bool	eating_behaviour(t_philo *philo)
{
	if (philo->data->n_philos == 1)
	{
		sem_wait(philo->data->forks);
		print_msg(philo, "has taken a fork");
		ft_usleep(philo->data->t_die);
		return (false);
	}
	sem_wait(philo->data->forks);
	print_msg(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	ft_usleep(philo->data->t_eat);
	(!sem_wait(philo->data->meal_sem)) && philo->eat_times++;
	philo->last_meal = get_curr_time();
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	sem_post(philo->data->meal_sem);
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
		while (++i <= 500)
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

void	process_creator(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			thread_creator(&philo[i]);
			exit(0);
		}
		i++;
	}
}
