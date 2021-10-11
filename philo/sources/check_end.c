/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:37:00 by user42            #+#    #+#             */
/*   Updated: 2021/10/08 20:37:41 by user42           ###   ########.fr       */
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
		if (checker->philo[i].is_satiated == 1)
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
		check_eat(checker);
		pthread_mutex_lock(checker->philo[i].rules->die);
		if (checker->philo[i].is_dead == 1)
			exit_properly(checker);
		pthread_mutex_unlock(checker->philo[i].rules->die);
		i++;
	}
}
