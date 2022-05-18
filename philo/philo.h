/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:58:41 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:52:21 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philos{
	int				id;
	int				left_fork;
	int				right_fork;
	int				nb_eat;
	long long int	last_time_eat;
	struct s_env	*env;
	pthread_t		thread;
}	t_philos;

typedef struct s_env
{
	int				philos_count;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				end_death;
	long long int	start_time;
	int				eat_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat_check;
	pthread_mutex_t	death_check;
	pthread_mutex_t	time_check;
	t_philos		*philos;
}	t_env;

int				init_arg(t_env *env, char **argv);
int				ft_atoi(const char *str);
int				ft_create(t_env *env);
int				is_digit(char **str);
int				init_philos(t_env *env);
int				check_death(t_env *env);
int				eat(t_env *env);
int				proverka(t_env *env);
long long int	get_time(void);

void			go_sleep(long long int time);
void			print(t_env *env, int id, char *active);
void			free_all(t_env	*env);
void			check_eat(t_env *env);
void			act_eat(t_philos *philo);
void			lock_forks(t_philos *philo);
void			one_philo(t_philos *philo, t_env *env);

#endif
