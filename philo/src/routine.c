/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:30:38 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 00:52:05 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	do_sleep(t_philo *philo)
{
	if (ft_timestamp(philo->start_sleep) >= philo->saves->sleep_time)
	{
		philo->prev_status = 0;
		philo->status = 5;
		return ;
	}
}

void	do_take_l_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork) == 0)
		philo->status = 1;
}

void	do_take_r_fork(t_philo *philo)
{
	if (philo->saves->philo_num == 1)
		philo->status = 4;
	else if (pthread_mutex_lock(philo->r_fork) == 0)
	{
		philo->status = 2;
		gettimeofday(&philo->start_eat, NULL);
		return ;
	}
}

void	do_eat(t_philo *philo)
{
	if (ft_timestamp(philo->start_eat) >= philo->saves->eat_time)
	{
		philo->status = 0;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		if (philo->saves->meals_nb > 0)
		{
			philo->eat_count++;
			if (philo->eat_count == philo->saves->meals_nb)
			{
				philo->status = 10;
				philo->saves->finished++;
				return ;
			}
		}
		gettimeofday(&philo->start_sleep, NULL);
		return ;
	}
}

void	routine(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (philo->status == 0)
			do_sleep(philo);
		else if (philo->status == 5)
			do_take_l_fork(philo);
		else if (philo->status == 1)
			do_take_r_fork(philo);
		else if (philo->status == 2)
			do_eat(philo);
		else if (philo->status == 10)
			gettimeofday(&philo->start_sleep, NULL);
	}
}
