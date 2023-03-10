/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:41:35 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 01:39:45 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	exec_parent(t_struct *saves)
{
	int	count_m;
	int	status;

	count_m = 0;
	while (waitpid(0, &status, 0))
	{
		if (((status >> 8) & 0x0000000ff) == 0)
		{
			kill(0, SIGKILL);
			break ;
		}
		if (((status >> 8) & 0x0000000ff) == 1)
		{
			count_m++;
			if (count_m == saves->philo_num)
				break ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_struct	*saves;
	int			i;

	saves = init_all(argc, argv);
	if (!saves)
		return (0);
	sem_start(saves);
	i = -1;
	while (++i < saves->philo_num)
	{
		saves->parent = fork();
		if (saves->parent == 0)
		{
			saves->philo.id = i;
			break ;
		}
	}
	if (saves->parent == 0)
		exec_child(saves);
	exec_parent(saves);
	return (0);
}
