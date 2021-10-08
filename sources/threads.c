/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_day.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugotheveny <ugotheveny@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:57:48 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/08 17:07:07 by ugotheveny       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	check_end(t_checker *checker)
{
	int i;
	int finish;

	i = 0;
	finish = 0;
	while (i < checker->philo[0].rules->nb_philo)
	{
		pthread_mutex_lock(checker->philo[i].rules->die);
		if (checker->philo[i].is_dead == 1)
			exit(0);
		pthread_mutex_unlock(checker->philo[i].rules->die);
		pthread_mutex_lock(checker->philo[i].rules->finish);
		if (checker->philo[i].finished >= checker->philo[0].rules->nb_eat && checker->philo[0].rules->nb_philo != -1)
			finish++;
		pthread_mutex_unlock(checker->philo[i].rules->finish);
		i++;
	}
	if (finish == checker->philo[0].rules->nb_philo && checker->philo[0].rules->nb_eat != -1)
		exit(0);
}

void	*philo_day(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 != 1)
		my_usleep(50);
	while (1)
	{
		if (philo->rules->nb_philo != 1)
		{
			philo_eat(philo);
			philo_sleep_think(philo);
		}
		else
			philo_got_one_fork(philo);
	}
	return (NULL);
}

void	philo_got_one_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork);
	write_action(philo, "\033[1;34mhas taken a fork\033[00m");
	pthread_mutex_unlock(&philo->lfork);
	my_usleep(philo->rules->death_timer + 100);
}

void	*check_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(philo->rules->eat);
		if (ms_from_start(philo->rules->start) > philo->last_eat + philo->rules->death_timer)
			philo_die(philo);
		pthread_mutex_unlock(philo->rules->eat);
	}
	return (NULL);
}

void	start_thread(t_checker *checker)
{
	int	i;

	i = 0;
	while (i < checker->philo->rules->nb_philo)
	{
		pthread_create(&checker->philo[i].thread, NULL, philo_day, &checker->philo[i]);
		pthread_detach(checker->philo[i].thread);
		i++;
	}
	i = 0;
	while (i < checker->philo->rules->nb_philo)
	{
		pthread_create(&checker->philo[i].check, NULL, check_philo, &checker->philo[i]);
		pthread_detach(checker->philo[i].check);
		i++;
	}
	while (1)
		check_end(checker);
	exit_properly(checker);
}
