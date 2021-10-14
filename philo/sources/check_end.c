/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugotheveny <ugotheveny@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:37:00 by user42            #+#    #+#             */
/*   Updated: 2021/10/14 12:24:37 by ugotheveny       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	check_eat(t_checker *checker)
{
	int	i;
	int	finish;

	i = 0;
	finish = 0;
	while (i < checker->philo[0].rules->nb_philo
		&& checker->philo[0].rules->nb_eat != -1)
	{
		pthread_mutex_lock(checker->philo[i].rules->finish);
		if (checker->philo[i].finished >= checker->philo[i].rules->nb_eat)
			finish++;
		pthread_mutex_unlock(checker->philo[i].rules->finish);
		i++;
	}
	if (finish == checker->philo[0].rules->nb_philo
		&& checker->philo[0].rules->nb_eat != -1)
	{
		pthread_mutex_lock(&checker->write);
		exit_properly(checker);
	}
}

void	check_end(t_checker *checker)
{
	int	i;

	i = 0;
	while (i < checker->philo[0].rules->nb_philo)
	{
		if (checker->philo[0].rules->nb_eat != -1)
			check_eat(checker);
		pthread_mutex_lock(checker->philo[i].rules->eat);
		if (ms_from_start(checker->philo[i].rules->start) > checker->philo[i].last_eat + checker->philo[i].rules->death_timer)
		{
			write_death(&checker->philo[i]);
			exit_properly(checker);
		}
		pthread_mutex_unlock(checker->philo[i].rules->eat);
		i++;
	}
}
