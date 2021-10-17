/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:37:00 by user42            #+#    #+#             */
/*   Updated: 2021/10/17 20:44:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_eat(t_checker *checker)
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
		return (1);
	}
	return (0);
}

int	check_end(t_checker *checker)
{
	int	i;
	int	verif_eat;

	i = 0;
	verif_eat = 0;
	while (i < checker->philo[0].rules->nb_philo)
	{
		if (checker->philo[0].rules->nb_eat != -1)
			verif_eat = check_eat(checker);
		if (verif_eat == 1)
			return (1);
		pthread_mutex_lock(checker->philo[i].rules->eat);
		if (ms_from_start(checker->philo[i].rules->start)
			> checker->philo[i].last_eat + checker->philo[i].rules->death_timer)
		{
			write_death(&checker->philo[i]);
			return (1);
		}
		pthread_mutex_unlock(checker->philo[i].rules->eat);
		i++;
	}
	return (0);
}
