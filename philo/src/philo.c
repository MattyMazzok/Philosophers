/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:41:35 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 00:43:31 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clear_saves(t_struct	*saves)
{
	if (saves->tid)
		free(saves->tid);
	if (saves->forks)
		free(saves->forks);
	if (saves->philos)
		free(saves->philos);
	free(saves);
}

void	ft_close(t_struct *saves)
{
	int	i;

	i = -1;
	while (++i < saves->philo_num)
	{
		pthread_mutex_destroy(&saves->forks[i]);
		pthread_mutex_destroy(saves->philos[i].l_fork);
		pthread_mutex_destroy(saves->philos[i].r_fork);
	}
	clear_saves(saves);
}

void	*exec_thread(void *saves)
{
	t_philo	*philo;

	philo = (t_philo *)saves;
	while (!philo->saves->checker_is_run)
		continue ;
	if (philo->id % 2 == 0)
		usleep(1000);
	routine(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	*saves;
	int			i;

	saves = init_all(argc, argv);
	if (!saves)
		return (0);
	saves->checker_is_run = 1;
	while (1)
	{
		i = -1;
		while (++i < saves->philo_num)
		{
			if (!supervisor(saves->philos, i))
				return (0);
		}
	}
	ft_close(saves);
	return (0);
}
