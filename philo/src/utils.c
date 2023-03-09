/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:04:21 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 00:54:08 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	input_checker(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	value;
	int	sign;

	sign = 1;
	value = 0;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		value *= 10;
		value += *s - 48;
		s++;
	}
	return (value * sign);
}

t_struct	*init_all(int argc, char **argv)
{
	t_struct	*saves;

	if (argc < 5 || argc > 6 || !(ft_atoi(argv[1]) >= 1 && ft_atoi(argv[1]) <= 200)
		|| !input_checker(argc, argv))
	{
		printf("Wrong input format, try again! Error!\n");
		return (NULL);
	}
	saves = alloc_saves(argv, argc);
	if (saves->death_time < 1 || saves->sleep_time < 1 || saves->eat_time < 1)
	{
		printf("Wrong input format, try again! Error!\n");
		return (NULL);
	}
	saves->philos = malloc(saves->philo_num * sizeof(t_philo));
	saves->dead = 0;
	if (!saves->philos)
		return (NULL);
	alloc_philos(saves->philos, saves);
	return (saves);
}

unsigned long	ft_timestamp(struct timeval sec)
{
	struct timeval	now;
	unsigned long	res;

	gettimeofday(&now, NULL);
	res = (((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((sec.tv_sec * 1000) + (sec.tv_usec / 1000)));
	return (res);
}
