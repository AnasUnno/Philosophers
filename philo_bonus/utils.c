/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:41:44 by araji-af          #+#    #+#             */
/*   Updated: 2023/06/01 14:29:56 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_msg(t_philo *philo, char *str)
{
	sem_wait(philo->data->print_sem);
	printf("%lu ", get_curr_time() - philo->data->t_start);
	printf(" %d", philo->philo_id);
	printf(" %s\n", str);
	if (ft_strcmp(str, "died"))
		sem_post(philo->data->print_sem);
}

int	thread_creator(t_philo *philo)
{
	philo->last_meal = get_curr_time();
	if (pthread_create(&philo->thread_id, NULL, &routine, philo) != 0)
		return (1);
	if (pthread_detach(philo->thread_id) != 0)
		return (2);
	check_death(philo);
	return (0);
}
