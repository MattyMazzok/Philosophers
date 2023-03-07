/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:09:15 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/07 12:07:19 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	start_forks(t_struct *saves)
{
	int	i;

	i = -1;
	while (++i < saves->philo_num)
		pthread_mutex_init(&saves->forks[i], NULL);
	i = 0;
	saves->philos[0].l_fork = &saves->forks[0];
	saves->philos[0].r_fork = &saves->forks[saves->philo_num - 1];
	i = 1;
	while (i < saves->philo_num)
	{
		saves->philos[i].l_fork = &saves->forks[i];
		saves->philos[i].r_fork = &saves->forks[i - 1];
		i++;
	}
	return (0);
}

void	start_philos(t_struct *saves)
{
	int	i;

	i = 0;
	while (i < saves->philo_num)
	{
		saves->philos[i].saves = saves;
		saves->philos[i].id = i + 1;
		saves->philos[i].time_to_die = saves->death_time;
		saves->philos[i].eat_cont = 0;
		saves->philos[i].eating = 0;
		saves->philos[i].status = 0;
		pthread_mutex_init(&saves->philos[i].lock, NULL);
		i++;
	}
}

int	start_saves(t_struct *saves, char **argv, int argc)
{
	if ((int) ft_atoi(argv[1]) <= 0 || (int) ft_atoi(argv[1]) > 200 || (int) ft_atoi(argv[2]) < 0
		|| (int) ft_atoi(argv[3]) < 0 || (int) ft_atoi(argv[4]) < 0)
		return (error("Invalid input! Error!", NULL));
	saves->philo_num = (int) ft_atoi(argv[1]);
	saves->death_time = (uint64_t) ft_atoi(argv[2]);
	saves->eat_time = (uint64_t) ft_atoi(argv[3]);
	saves->sleep_time = (uint64_t) ft_atoi(argv[4]);
	if (argc == 6)
		saves->meals_nb = (int) ft_atoi(argv[5]);
	else
		saves->meals_nb = -1;
	saves->dead = 0;
	saves->finished = 0;
	pthread_mutex_init(&saves->write, NULL);
	pthread_mutex_init(&saves->lock, NULL);
	return (0);
}

int	start(t_struct *saves, char **argv, int argc)
{
	if (start_saves(saves, argv, argc))
		return (1);
	if (alloc(saves))
		return (1);
	if (start_forks(saves))
		return (1);
	start_philos(saves);
	return (0);
}
