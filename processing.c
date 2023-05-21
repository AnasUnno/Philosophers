/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:19:50 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/21 16:34:47 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_finished_meals(t_philo *philo)
{

	while (philo->data->stop_flag == 0)
	{
		if (philo->data->all_finished >= philo->data->n_philos)
			philo->data->stop_flag == 1;
	}
	return (NULL);
}

void	check_death(t_philo *philo)
{
	t_philo	*philo;

	if (get_curr_time() - philo->last_meal >= philo->data->t_die)
	{
		// a philo died.
		philo->data->death_flag = 1;
		philo->data->stop_flag = 1;
		return ; 
	}
	if (philo->eat_times == philo->data->n_eat)
	{
		philo->data->all_finished++;
		philo->eat_times++;
	}
	check_finished_meals(philo);
	if (philo->data->stop_flag == 1)
		return ; // means all philos have finished their meals
	return (NULL);
}

void	eating_behaviour(t_philo *philo)
{
	if (philo->data->n_philos > 1)
	{
		pthread_mutex_lock(&philo->right_fork); // philo took  his fork.
		pthread_mutex_lock(&philo->left_fork); // philo took his neighbours fork.
		// the philo start eating.
		philo->last_meal = get_curr_time();
		philo->eat_times++;
		ft_usleep(philo->data->t_eat);
		if (philo->data->death_flag == 1)
			return ;
		pthread_mutex_unlock(&philo->right_fork); // droped his fork.
		pthread_mutex_unlock(&philo->left_fork);  // droped his neighbour's fork.
	}
}
