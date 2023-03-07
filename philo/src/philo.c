/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:41:35 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/07 12:07:28 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	case_one(t_struct *saves)
{
	saves->start_time = get_time();
	if (pthread_create(&saves->tid[0], NULL, &routine, &saves->philos[0]))
		return (error("Failed to create the thred! Error!", saves));
	pthread_detach(saves->tid[0]);
	while (saves->dead == 0)
		usleep(0);
	ft_exit(saves);
	return (0);
}

void	clear_saves(t_struct	*saves)
{
	if (saves->tid)
		free(saves->tid);
	if (saves->forks)
		free(saves->forks);
	if (saves->philos)
		free(saves->philos);
}

void	ft_exit(t_struct *saves)
{
	int	i;

	i = -1;
	while (++i < saves->philo_num)
	{
		pthread_mutex_destroy(&saves->forks[i]);
		pthread_mutex_destroy(&saves->philos[i].lock);
	}
	pthread_mutex_destroy(&saves->write);
	pthread_mutex_destroy(&saves->lock);
	clear_saves(saves);
}

int	error(char *str, t_struct *saves)
{
	printf("%s\n", str);
	if (saves)
		ft_exit(saves);
	return (1);
}

int	main(int argc, char **argv)
{
	t_struct	saves;

	if (argc < 5 || argc > 6)
		return (1);
	if (input_checker(argv))
		return (1);
	if (start(&saves, argv, argc))
		return (1);
	if (saves.philo_num == 1)
		return (case_one(&saves));
	if (thread_init(&saves))
		return (1);
	ft_exit(&saves);
	return (0);
}
