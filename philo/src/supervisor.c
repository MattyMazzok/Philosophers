/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:31:59 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 00:42:13 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static	void	check_sleep(t_philo *philo, int i)
{
	printf("%lu %d %s\n", ft_timestamp(philo[i].saves->start_time),
		philo[i].id, SLEEP);
	philo[i].prev_status = 0;
}

static	void	check_think(t_philo *philo, int i)
{
	printf("%lu %d %s\n", ft_timestamp(philo[i].saves->start_time),
		philo[i].id, THINK);
	philo[i].prev_status = 5;
}

static	void	check_take_l_fork(t_philo *philo, int i)
{
	printf("%lu %d %s\n", ft_timestamp(philo[i].saves->start_time),
		philo[i].id, FORK);
	philo[i].prev_status = 1;
}

static	void	check_take_r_fork_eat(t_philo *philo, int i)
{
	printf("%lu %d %s\n", ft_timestamp(philo[i].saves->start_time),
		philo[i].id, FORK);
	printf("%lu %d %s\n", ft_timestamp(philo[i].saves->start_time),
		philo[i].id, EAT);
	philo[i].prev_status = 2;
}

int	supervisor(t_philo *philo, int i)
{
	if (philo->saves->meals_nb != 0
		&& philo->saves->finished == philo->saves->philo_num)
		return (0);
	if (ft_timestamp(philo[i].start_sleep) > philo[i].saves->death_time)
		philo[i].status = 4;
	if (philo[i].prev_status != philo[i].status)
	{
		if (philo[i].status == 0)
			check_sleep(philo, i);
		else if (philo[i].status == 5)
			check_think(philo, i);
		else if (philo[i].status == 1)
			check_take_l_fork(philo, i);
		else if (philo[i].status == 2)
			check_take_r_fork_eat(philo, i);
		else if (philo[i].status == 4)
		{
			printf("%lu %d %s\n", ft_timestamp(philo[i].saves->start_time),
				philo[i].id, DEAD);
			return (0);
		}
	}
	return (1);
}
