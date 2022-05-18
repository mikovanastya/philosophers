/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:37:16 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:27:14 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_fed(t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&env->eat_check);
	while (i < env->philos_count)
	{
		if (env->philos[i].nb_eat < env->eat_count)
		{
			pthread_mutex_unlock(&env->eat_check);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&env->eat_check);
	return (1);
}

int	eat(t_env *env)
{
	pthread_mutex_unlock(&env->time_check);
	if (env->eat_count != -1 && check_all_fed(env))
	{
		pthread_mutex_lock(&env->death_check);
		env->end_death = 1;
		pthread_mutex_unlock(&env->death_check);
		return (1);
	}
	return (0);
}

int	check_death(t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&env->time_check);
	while (i < env->philos_count)
	{
		if (get_time() - env->philos[i].last_time_eat > env->time_death)
		{
			print(env, env->philos[i].id, "died\n");
			pthread_mutex_lock(&env->death_check);
			env->end_death = 1;
			pthread_mutex_unlock(&env->death_check);
			pthread_mutex_unlock(&env->time_check);
			return (1);
		}
		i++;
	}
	eat(env);
	return (0);
}
