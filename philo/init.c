/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:35:44 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:59:10 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_env *env)
{
	int	i;

	i = 0;
	(env->forks) = malloc(sizeof(pthread_mutex_t) * env->philos_count);
	if (env->forks == 0)
		return (1);
	while (i < env->philos_count)
	{
		if (pthread_mutex_init(&(env->forks[i]), 0))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(env->print), 0))
		return (1);
	if (pthread_mutex_init(&(env->death_check), 0))
		return (1);
	if (pthread_mutex_init(&(env->eat_check), 0))
		return (1);
	if (pthread_mutex_init(&(env->time_check), 0))
		return (1);
	return (0);
}

int	init_philos(t_env *env)
{
	int	i;

	i = 0;
	(env->philos) = (t_philos *)malloc(sizeof(t_philos) * env->philos_count);
	if ((env->philos) == 0)
		return (1);
	while (i < env->philos_count)
	{
		env->philos[i].id = i;
		env->philos[i].env = env;
		env->philos[i].left_fork = i;
		env->philos[i].right_fork = (i + 1) % env->philos_count;
		env->philos[i].nb_eat = 0;
		env->philos[i].last_time_eat = get_time();
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
	if (init_mutex(env))
		return (1);
	return (0);
}
