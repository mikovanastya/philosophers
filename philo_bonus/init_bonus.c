/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:35:44 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:17:35 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_env *env)
{
	sem_unlink("print");
	sem_unlink("death");
	sem_unlink("eat");
	sem_unlink("time");
	sem_unlink("forks");
	env->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	env->death_check = sem_open("death", O_CREAT, S_IRWXU, 1);
	env->eat_check = sem_open("eat", O_CREAT, S_IRWXU, 1);
	env->time_check = sem_open("time", O_CREAT, S_IRWXU, 1);
	env->forks = sem_open("forks", O_CREAT, S_IRWXU, env->philos_count);
	return (0);
}

int	init_philos(t_env *env)
{
	int	i;

	i = 0;
	(env->philo) = (t_philo *)malloc(sizeof(t_philo) * env->philos_count);
	if ((env->philo) == 0)
		return (1);
	while (i < env->philos_count)
	{
		env->philo[i].id = i;
		env->philo[i].env = env;
		env->philo[i].left_fork = i;
		env->philo[i].right_fork = (i + 1) % env->philos_count;
		env->philo[i].nb_eat = 0;
		env->philo[i].last_time_eat = get_time();
		i++;
	}
	return (0);
}

int	init_arg(t_env *env, char **argv)
{
	if (is_digit(argv))
	{
		printf("error");
		return (1);
	}
	env->philos_count = ft_atoi(argv[1]);
	env->time_death = ft_atoi(argv[2]);
	env->time_eat = ft_atoi(argv[3]);
	env->time_sleep = ft_atoi(argv[4]);
	if (env->philos_count < 1 || env->time_death < 0
		|| env->time_eat < 1 || env->time_sleep < 1)
		return (1);
	if (argv[5])
	{
		env->eat_count = ft_atoi(argv[5]);
		if (env->eat_count < 1)
			return (1);
	}
	else
		env->eat_count = -1;
	env->end_death = 0;
	init_philos(env);
	if (init_sem(env))
		return (1);
	return (0);
}
