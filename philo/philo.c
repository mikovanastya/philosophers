/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:48:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:52:39 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	act_eat(t_philos *philo)
{
	t_env	*env;

	env = philo->env;
	pthread_mutex_lock(&env->time_check);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&env->time_check);
	pthread_mutex_lock(&env->eat_check);
	philo->nb_eat++;
	pthread_mutex_unlock(&env->eat_check);
	print(env, philo->id, "is eating\n");
	go_sleep(env->time_eat);
	pthread_mutex_unlock(&env->forks[philo->right_fork]);
	pthread_mutex_unlock(&env->forks[philo->left_fork]);
}

void	*start(void *arg)
{
	t_philos	*philo;
	t_env		*env;

	philo = (t_philos *)arg;
	env = philo->env;
	while (1)
	{
		if (proverka(env))
			break ;
		lock_forks(philo);
		act_eat(philo);
		if (proverka(env))
			break ;
		print(env, philo->id, "is sleeping\n");
		go_sleep(env->time_sleep);
		print(env, philo->id, "is thinking\n");
	}
	return (0);
}

int	ft_create(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philos_count)
	{
		if (pthread_create(&(env->philos[i].thread), 0, start, &env->philos[i]))
			return (1);
		i += 2;
	}
	usleep(200);
	i = 1;
	while (i < env->philos_count)
	{
		if (pthread_create(&(env->philos[i].thread), 0, start, &env->philos[i]))
			return (1);
		i += 2;
	}
	usleep(10000);
	i++;
	return (0);
}

int	potok(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	ft_create(env);
	while (1)
	{
		if (check_death(env))
			break ;
	}
	i = 0;
	while (i < env->philos_count)
	{	
		if (pthread_join(env->philos[i].thread, 0))
			return (1);
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
