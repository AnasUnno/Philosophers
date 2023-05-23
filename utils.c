/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:41:44 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/23 19:17:34 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_curr_time()
{
	struct	timeval time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_ms);
}

int ft_usleep(unsigned long time)
{
	unsigned long start_time;

	start_time = get_curr_time();
	while ((get_curr_time() - start_time) < time)
		usleep(50);
	return 0;
}

void    print_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lu ", get_curr_time() - philo->data->t_start);
	printf(" %d", philo->philo_id);
	printf(" %s\n", str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
