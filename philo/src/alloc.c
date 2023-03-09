/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:10:28 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 00:50:48 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_struct	*alloc_saves(char **argv, char argc)
{
	t_struct	*saves;

	saves = malloc(sizeof(t_struct));
	if (!saves)
		return (NULL);
	saves->philo_num = ft_atoi(argv[1]);
	saves->death_time = ft_atoi(argv[2]);
	saves->eat_time = ft_atoi(argv[3]);
	saves->sleep_time = ft_atoi(argv[4]);
	saves->finished = 0;
	if (argc == 6)
		saves->meals_nb = ft_atoi(argv[5]);
	else
		saves->meals_nb = 0;
	saves->checker_is_run = 0;
	saves->forks = malloc(saves->philo_num * sizeof(pthread_mutex_t));
	gettimeofday(&saves->start_time, NULL);
	return (saves);
}

void	alloc_philos(t_philo	*philos, t_struct *saves)
{
	int	i;

	i = -1;
	while (++i < saves->philo_num)
	{
		philos[i].saves = saves;
		philos[i].id = i;
		pthread_mutex_init(saves->forks + i, NULL);
		philos[i].status = 5;
		philos[i].prev_status = 0;
		philos[i].eat_count = 0;
		gettimeofday(&philos[i].start_sleep, NULL);
	}
	i = -1;
	while (++i < saves->philo_num)
	{
		philos[i].l_fork = saves->forks + i;
		if (i == saves->philo_num - 1)
			philos[i].r_fork = saves->forks;
		else
			philos[i].r_fork = (saves->forks + i + 1);
	}
	i = -1;
	while (++i < saves->philo_num)
		pthread_create(&philos[i].t1, NULL, &exec_thread, philos + i);
}
