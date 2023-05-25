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
# define PHILO_H

# include<stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	unsigned long	t_start;
	int				n_philos;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	int				n_eat;
	int				stop_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
}t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread_id;
	unsigned int	philo_id;
	unsigned int	dying_time;
	int				eat_times;
	unsigned long	last_meal;
	int				eating_flag;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

}t_philo;

int				alocation(t_data *data, t_philo *philos);
t_philo			*initialize_philos(t_data *data);
pthread_mutex_t	*initialize_forks(t_data	*data, t_philo *philo);
t_data			*initialize_data(int ac, char **av);
int				initialization_caller(t_philo *philo, t_data *data,
					int ac, char **av);
void			ft_perror(void);
void			pars_args(int ac, char **av);
void			check_empty(int ac, char **av);
void			check_spaces(char **av);
bool			check_finished_meals(t_philo *philo);
void			check_death(t_philo *philo);
bool			eating_behaviour(t_philo *philo);
void			*routine(void *philo_ptr);
int				threads_creator(t_philo *philo);
unsigned long	get_curr_time(void);
int				ft_usleep(unsigned long time);
int				print_msg(t_philo *philo, char *str);
void			iniatalise_eat(t_philo *philo);
int				ft_atoi(const char *str);
void			clear_mutexes(t_philo *philo);
void			helper(int ac, char **av, t_data *data);

#endif
