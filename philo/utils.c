/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:41:44 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/31 10:59:11 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_curr_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start_time;

	start_time = get_curr_time();
	while ((get_curr_time() - start_time) < time)
		usleep(50);
	return (0);
}

int	print_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lu ", get_curr_time() - philo->data->t_start);
	printf(" %d", philo->philo_id);
	printf(" %s\n", str);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

void	clear_mutexes(t_philo *philo)
{
	int		i;
	t_data	*data;

	data = philo->data;
	i = -1;
	while (++i < philo->data->n_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(philo->left_fork);
	pthread_mutex_destroy(philo->right_fork);
	free(data->forks);
	data->forks = NULL;
	free(data);
	data = NULL;
	free(philo);
	philo = NULL;
}
