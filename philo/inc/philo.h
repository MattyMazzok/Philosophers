/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:38:49 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/10 00:50:57 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define DEAD "died"

struct	s_struct;

typedef struct s_philo {
	struct s_struct	*saves;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				prev_status;
	struct timeval	start_sleep;
	struct timeval	start_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_philo;

typedef struct s_struct
{
	pthread_t			*tid;
	int					philo_num;
	int					meals_nb;
	int					dead;
	int					finished;
	int					checker_is_run;
	t_philo				*philos;
	unsigned long		death_time;
	unsigned long		eat_time;
	unsigned long		sleep_time;
	struct timeval		start_time;
	pthread_mutex_t		*forks;
}	t_struct;

//	utils
int				ft_atoi(char *s);
unsigned long	ft_timestamp(struct timeval sec);
t_struct		*init_all(int argc, char **argv);

//	allocc
t_struct		*alloc_saves(char **argv, char argc);
void			alloc_philos(t_philo	*philos, t_struct *saves);

//	thread
void			routine(t_philo *philo);
int				supervisor(t_philo *philo, int i);
void			*exec_thread(void *saves);

#endif
