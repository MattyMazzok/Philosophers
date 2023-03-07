/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:04:21 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/07 12:07:21 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	alloc(t_struct *saves)
{
	saves->tid = malloc(sizeof(pthread_t) * saves->philo_num);
	if (!saves->tid)
		return (error("Failed to allocate the ID's thread! Error!", saves));
	saves->forks = malloc(sizeof(pthread_mutex_t) * saves->philo_num);
	if (!saves->forks)
		return (error("Failed to allocate the forks's thread! Error!", saves));
	saves->philos = malloc(sizeof(t_philo) * saves->philo_num);
	if (!saves->philos)
		return (error("Failed to allocate the philos's thread! Error!", saves));
	return (0);
}

int	input_checker(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				return (error("Invalid input! Error!", NULL));
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

long	ft_atoi(const char *str)
{
	int	i;
	int	is_neg;
	long	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == 9 || str[i] == 10 || str[i] == 11
		|| str[i] == 12 || str[i] == 13 || str[i] == 20)
		i++;
	if (str[i] == '-')
		is_neg = -1;
	else
		is_neg = 1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * is_neg);
}
