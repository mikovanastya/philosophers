/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:44:05 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 15:03:27 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print(t_env *env, int id, char *active)
{
	sem_wait(env->print);
	sem_wait(env->death_check);
	if (!env->end_death)
		printf("%lld %d %s", (get_time() - env->start_time), (id + 1), active);
	sem_post(env->death_check);
	sem_post(env->print);
}
