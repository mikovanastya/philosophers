/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:44:05 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:51:58 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_env *env, int id, char *active)
{
	pthread_mutex_lock(&(env->print));
	pthread_mutex_lock(&(env->death_check));
	if (!env->end_death)
		printf("%lld %d %s", (get_time() - env->start_time), (id + 1), active);
	pthread_mutex_unlock(&(env->death_check));
	pthread_mutex_unlock(&(env->print));
}

void	one_philo(t_philos *philo, t_env *env)
{
	pthread_mutex_unlock(&env->forks[philo->left_fork]);
	go_sleep(env->time_death);
	print(env, philo->id, "died\n");
	pthread_mutex_lock(&env->death_check);
	env->end_death = 1;
	pthread_mutex_unlock(&env->death_check);
}

void	lock_forks(t_philos *philo)
{
	t_env	*env;

	env = philo->env;
	if (philo->id % 2)
	{
		pthread_mutex_lock(&env->forks[philo->left_fork]);
		print(env, philo->id, "has taken a left fork\n");
		pthread_mutex_lock(&env->forks[philo->right_fork]);
		print(env, philo->id, "has taken a right fork\n");
	}
	else
	{	
		pthread_mutex_lock(&env->forks[philo->right_fork]);
		print(env, philo->id, "has taken a right fork\n");
		if (env->philos_count == 1)
		{
			one_philo(philo, env);
			return ;
		}
		pthread_mutex_lock(&env->forks[philo->left_fork]);
		print(env, philo->id, "has taken a left fork\n");
	}
}

int	proverka(t_env *env)
{
	pthread_mutex_lock(&env->death_check);
	if (env->end_death)
	{
		pthread_mutex_unlock(&env->death_check);
		return (1);
	}
	pthread_mutex_unlock(&env->death_check);
	return (0);
}
