/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:37:16 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 21:06:05 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *void_philos)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *) void_philos;
	env = philo->env;
	while (1)
	{
		sem_wait(env->time_check);
		if (get_time() - philo->last_time_eat > env->time_death)
		{
			print(env, philo->id, "died\n");
			sem_wait(env->death_check);
			env->end_death = 1;
			sem_post(env->death_check);
			exit (1);
		}
		sem_post(env->time_check);
	}
	return (0);
}

void	destroy_sems(t_env *env)
{
	sem_close(env->print);
	sem_close(env->death_check);
	sem_close(env->eat_check);
	sem_close(env->time_check);
	sem_close(env->forks);
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/eat");
	sem_unlink("/time");
	sem_unlink("/forks");
}
