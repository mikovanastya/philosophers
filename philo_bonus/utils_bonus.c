/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:12:35 by rtwitch           #+#    #+#             */
/*   Updated: 2022/04/08 20:17:08 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	go_sleep(long long int start_time)
{
	long long int	time;

	time = get_time() + start_time;
	while (time > get_time())
		usleep(600);
}

long long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned int	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	if (result > 2147483648 && sign == -1)
		return (0);
	if (result > 2147483647 && sign == 1)
		return (-1);
	return (result * sign);
}

int	is_digit(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] < 48 || str[i][j] > 57) && !(str[i][j] == 45))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	free_all(t_env	*env)
{
	int	i;
	int	status;

	i = 0;
	while (i < env->philos_count)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < env->philos_count)
			{
				kill(env->philo[i].pid, SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
	destroy_sems(env);
	if (env->philo)
		free(env->philo);
}
