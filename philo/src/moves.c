/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:29:19 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/07 12:07:25 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILED\n", NULL));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	print(char *str, t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->saves->write);
	time = get_time() - philo->saves->start_time;
	if (ft_strcmp("died", str) == 0 && philo->saves->dead == 0)
	{
		printf("%lu %d %s\n", time, philo->id, str);
		philo->saves->dead = 1;
	}
	if (!philo->saves->dead)
		printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->saves->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print("has taken the right fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print("has taken the left fork", philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print("is sleeping", philo);
	usleep(philo->saves->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->saves->death_time;
	print("is eating", philo);
	philo->eat_cont++;
    usleep(philo->saves->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
