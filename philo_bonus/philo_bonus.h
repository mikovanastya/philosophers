/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:52:49 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 21:06:09 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_philo{
	int				id;
	int				left_fork;
	int				right_fork;
	int				nb_eat;
	long long int	last_time_eat;
	struct s_env	*env;
	pthread_t		thread;
	pid_t			pid;
}	t_philo;

typedef struct s_env
{
	int				philos_count;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				end_death;
	long long int	start_time;
	int				eat_count;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eat_check;
	sem_t			*death_check;
	sem_t			*time_check;
	t_philo			*philo;
}	t_env;

int				init_arg(t_env *env, char **argv);
int				ft_atoi(const char *str);
int				is_digit(char **str);
int				init_philos(t_env *env);
long long int	get_time(void);

void			go_sleep(long long int time);
void			print(t_env *env, int id, char *active);

void			free_all(t_env	*env);
void			check_eat(t_env *env);
int				init_sem(t_env *env);
int				ft_create(t_env *env);
void			*check_death(void *void_philos);
void			act_eat(t_philo *philo);
void			destroy_sems(t_env *env);
#endif