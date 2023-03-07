/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:37:33 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/07 12:07:24 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor(void *saves_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) saves_pointer;
	pthread_mutex_lock(&philo->saves->write);
	printf("saves val: %d", philo->saves->dead);
	pthread_mutex_unlock(&philo->saves->write);
	while (philo->saves->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->saves->finished >= philo->saves->philo_num)
			philo->saves->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->saves->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			print("died", philo);
		if (philo->eat_cont == philo->saves->meals_nb)
		{
			pthread_mutex_lock(&philo->saves->lock);
			philo->saves->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->saves->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->time_to_die = philo->saves->death_time + get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->saves->dead == 0)
	{
		eat(philo);
		print("is thinking", philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_struct *saves)
{
	int			i;
	pthread_t	thread0;

	i = -1;
	saves->start_time = get_time();
	if (saves->meals_nb > 0)
	{
		if (pthread_create(&thread0, NULL, &monitor, &saves->philos[0]))
			return (error("Failed to create the thred! Error!", saves));
	}
	while (++i < saves->philo_num)
	{
		if (pthread_create(&saves->tid[i], NULL, &routine, &saves->philos[i]))
			return (error("Failed to create the thred! Error!", saves));
		usleep(1);
	}
	i = -1;
	while (++i < saves->philo_num)
	{
		if (pthread_join(saves->tid[i], NULL))
			return (error("Failed to join the threads! Error!", saves));
	}
	return (0);
}
