/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:10:28 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 01:39:31 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

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
	if (argc == 6)
		saves->meals_nb = ft_atoi(argv[5]);
	else
		saves->meals_nb = 0;
	saves->philo.eat_count = 0;
	return (saves);
}

void	sem_start(t_struct *saves)
{
	char	*name;
	char	*toprint;

	name = "/forks";
	toprint = "/print";
	sem_unlink(name);
	sem_unlink(toprint);
	saves->sem = sem_open(name, O_CREAT, 0666, saves->philo_num);
	saves->print = sem_open(toprint, O_CREAT, 0666, 1);
}
