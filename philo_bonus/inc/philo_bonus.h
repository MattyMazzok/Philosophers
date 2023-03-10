/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:38:49 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 01:40:54 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <semaphore.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define DEAD "died"

struct	s_struct;

typedef struct s_philo {
	int					id;
	int					status;
	int					eat_count;
	struct timeval		start_sleep;
	struct timeval		start_eat;
}				t_philo;

typedef struct s_struct
{
	int					philo_num;
	int					meals_nb;
	unsigned long		death_time;
	unsigned long		eat_time;
	unsigned long		sleep_time;
	struct timeval		start_time;
	t_philo				philo;
	sem_t				*sem;
	sem_t				*print;
	pid_t				parent;
}	t_struct;

//	utils
int				ft_atoi(char *s);
unsigned long	ft_timestamp(struct timeval sec);
t_struct		*init_all(int argc, char **argv);
void			check_death(t_struct *saves);

//	allocc
t_struct		*alloc_saves(char **argv, char argc);
void			sem_start(t_struct *saves);

//	thread
void			exec_child(t_struct *saves);
void			do_sleep(t_struct *saves);
void			do_think_and_fork(t_struct *saves);
void			do_fork_and_eat(t_struct *saves);
void			check_finish_or_sleep(t_struct *saves);

#endif
