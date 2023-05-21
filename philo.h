/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:09:32 by marvin            #+#    #+#             */
/*   Updated: 2023/05/17 23:09:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>>


typedef struct s_data
{
	unsigned long	t_start;
	unsigned int	n_philos;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	int				n_eat;
	int				death_flag;
	int				stop_flag;
	int				all_finished;
	pthread_mutex_t	*forks;
}t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread_id;
	unsigned int	philo_id;
	unsigned int	dying_time;
	unsigned int	eat_times;
	unsigned long	last_meal;
	int				eating_flag;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

}t_philo;

#endif
