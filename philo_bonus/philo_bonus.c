/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:48:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:32:36 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	act_eat(t_philo *philo)
{
	t_env	*env;

	env = philo->env;
	sem_wait(env->forks);
	print(env, philo->id, "has taken a fork\n");
	sem_wait(env->forks);
	print(env, philo->id, "has taken a fork\n");
	sem_wait(env->eat_check);
	philo->nb_eat++;
	philo->last_time_eat = get_time();
	sem_post(env->eat_check);
	print(env, philo->id, "is eating\n");
	go_sleep(env->time_eat);
	sem_post(env->forks);
	sem_post(env->forks);
	if (env->eat_count != -1 && philo->nb_eat >= env->eat_count)
	{
		sem_post(env->eat_check);
		exit(0);
	}
}

void	*start(void *arg)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)arg;
	env = philo->env;
	pthread_create(&(philo->thread), 0, check_death, arg);
	if (philo->id % 2)
		usleep(10000);
	while (1)
	{
		sem_wait(env->death_check);
		sem_post(env->death_check);
		act_eat(philo);
		print(env, philo->id, "is sleeping\n");
		go_sleep(env->time_sleep);
		sem_wait(env->death_check);
		sem_post(env->death_check);
		print(env, philo->id, "is thinking\n");
	}
	pthread_join(philo->thread, 0);
	exit (1);
}

int	potok(t_env *env)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = env->philo;
	env->start_time = get_time();
	while (i < env->philos_count)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (1);
		if (philo[i].pid == 0)
			start(&(philo[i]));
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env		env;
	int			i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf ("error");
		return (1);
	}
	if (init_arg(&env, argv))
		return (1);
	if (potok(&env))
		return (1);
	free_all(&env);
	return (0);
}
