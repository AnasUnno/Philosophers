/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:41:44 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/21 01:46:51 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_curr_time()
{
	struct	timeval time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 100) + (time.tv_usec / 1000));
	return (time_ms);
}

int ft_usleep(useconds_t time) {
    unsigned long start_time;

    start_time = get_curr_time();
    while ((get_curr_time() - start_time) < time)
        usleep(time / 10);
    return 0;
}