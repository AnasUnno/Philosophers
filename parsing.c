/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 00:54:17 by marvin            #+#    #+#             */
/*   Updated: 2023/05/18 00:54:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_perror()
{
	printf("Parametres are wrong\n");
	printf("Parametres should be given in this order :\n");
	printf("[1]-number of philosophers\n");
	printf("[2]-time_to_die (in milliseconds)\n");
	printf("[3]-time_to_eat (in milliseconds)\n");
	printf("[4]-time_to_sleep (in milliseconds)\n");
	printf("[5]-number_of_times_each_philosopher_must_eat (optional argument)\n");
	exit(1);
}

void pars_args(int ac, char **av)
{
	int i;
	int j;

	if (ac != 5 && ac != 6)
		ft_perror();
	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+')
				j++;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				ft_perror();
			j++;
		}
		i++;
	}
}

void	check_empty(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!*av[i] || !av[i])
			ft_perror();
		i++;
	}
}

void	check_spaces(char **av)
{
	int	i;
	int	j;
	int	check;

	i = 1;
	check = 0 ;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
				check = 0;
			else
			{
				check = 1;
				break ;
			}
			j++;
		}
		if (check == 0)
			ft_perror();
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int			sign;
	long		res;
	int			i;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		||str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}