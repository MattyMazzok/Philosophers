/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:30:38 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 01:41:03 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	do_sleep(t_struct *saves)
{
	check_death(saves);
	if (ft_timestamp(saves->philo.start_sleep) >= saves->sleep_time)
	{
		saves->philo.status = 1;
		do_think_and_fork(saves);
	}
}

void	do_think_and_fork(t_struct *saves)
{
	sem_wait(saves->print);
	printf("%lu %d %s\n", ft_timestamp(saves->start_time),
		saves->philo.id, THINK);
	sem_post(saves->print);
	check_death(saves);
	sem_wait(saves->sem);
	sem_wait(saves->print);
	printf("%lu %d %s\n", ft_timestamp(saves->start_time),
		saves->philo.id, FORK);
	sem_post(saves->print);
	check_death(saves);
	saves->philo.status = 2;
	do_fork_and_eat(saves);
}

void	do_fork_and_eat(t_struct *saves)
{
	if (saves->philo_num == 1)
	{
		sem_wait(saves->print);
		printf("%lu %d %s\n", ft_timestamp(saves->start_time),
			saves->philo.id, DEAD);
		if (saves->philo.status == 3)
			sem_post(saves->sem);
		sem_post(saves->sem);
		exit(0);
	}
	check_death(saves);
	sem_wait(saves->sem);
	sem_wait(saves->print);
	printf("%lu %d %s\n", ft_timestamp(saves->start_time),
		saves->philo.id, FORK);
	printf("%lu %d %s\n", ft_timestamp(saves->start_time),
		saves->philo.id, EAT);
	sem_post(saves->print);
	check_death(saves);
	gettimeofday(&saves->philo.start_eat, NULL);
	saves->philo.status = 3;
	check_finish_or_sleep(saves);
}

void	check_finish_or_sleep(t_struct *saves)
{
	check_death(saves);
	if (ft_timestamp(saves->philo.start_eat) >= saves->eat_time)
	{
		saves->philo.eat_count++;
		if (saves->philo.eat_count == saves->meals_nb)
		{
			sem_post(saves->sem);
			sem_post(saves->sem);
			sem_unlink("/forks");
			sem_unlink("/print");
			sem_close(saves->sem);
			sem_close(saves->print);
			exit(1);
		}
		sem_post(saves->sem);
		sem_post(saves->sem);
		sem_wait(saves->print);
		printf("%lu %d %s\n", ft_timestamp(saves->start_time),
			saves->philo.id, SLEEP);
		sem_post(saves->print);
		gettimeofday(&saves->philo.start_sleep, NULL);
		saves->philo.status = 0;
		do_sleep(saves);
	}
}

void	exec_child(t_struct *saves)
{
	saves->philo.eat_count = 0;
	saves->philo.status = 1;
	gettimeofday(&saves->philo.start_sleep, NULL);
	gettimeofday(&saves->start_time, NULL);
	while (1)
	{
		if (saves->philo.status == 0)
			do_sleep(saves);
		else if (saves->philo.status == 1)
			do_think_and_fork(saves);
		else if (saves->philo.status == 3)
			check_finish_or_sleep(saves);
	}
}
