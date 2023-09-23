/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:39 by araji-af          #+#    #+#             */
/*   Updated: 2023/05/31 12:12:39 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include<stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct s_data
{
	unsigned long	t_start;
	int				n_philos;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	int				n_eat;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*meal_sem;
}t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread_id;
	unsigned int	philo_id;
	int				pid;
	unsigned int	dying_time;
	int				eat_times;
	unsigned long	last_meal;
	int				eating_flag;

}t_philo;

int				alocation(t_data *data, t_philo *philos);
t_philo			*initialize_philos(t_data *data);
t_data			*initialize_data(int ac, char **av);
int				initialization_caller(t_philo *philo, t_data *data,
					int ac, char **av);
void			semaphores_initializing(t_philo *philo);
void			ft_perror(void);
void			pars_args(int ac, char **av);
void			check_empty(int ac, char **av);
void			check_spaces(char **av);
bool			check_finished_meals(t_philo *philo);
void			check_death(t_philo *philo);
bool			eating_behaviour(t_philo *philo);
void			*routine(void *philo_ptr);
unsigned long	get_curr_time(void);
int				ft_usleep(unsigned long time);
void			print_msg(t_philo *philo, char *str);
int				ft_atoi(const char *str);
void			clear_mutexes(t_philo *philo);
void			helper(int ac, char **av, t_data *data);
int				thread_creator(t_philo *philo);
void			process_creator(t_philo *philo);
int				ft_strcmp(char *s1, char *s2);
#endif
