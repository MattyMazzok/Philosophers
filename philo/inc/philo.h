/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:38:49 by mmazzocc          #+#    #+#             */
/*   Updated: 2023/03/07 12:05:23 by mmazzocc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

struct	s_struct;

typedef struct s_philo
{
	struct s_struct	*saves;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_struct
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_struct;

//	utils
long		ft_atoi(const char *str);
int			error(char *str, t_struct *saves);
int			ft_strcmp(char *s1, char *s2);
void		print(char *str, t_philo *philo);
void		ft_exit(t_struct *saves);
int			alloc(t_struct *saves);

//	time
uint64_t	get_time(void);

//	init
int			start(t_struct *saves, char **argv, int argc);
int			thread_init(t_struct *saves);

//	checker
int			input_checker(char **argv);

//	actions
void		eat(t_philo *philo);

//	threads
void		*routine(void *philo_pointer);
#endif
