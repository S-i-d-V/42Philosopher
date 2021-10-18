/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:57:48 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/18 18:29:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_end_var(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->end);
	if (philo->rules->end_var == 1)
	{
		pthread_mutex_unlock(philo->rules->end);
		return (1);
	}
	pthread_mutex_unlock(philo->rules->end);
	return (0);
}

void	*philo_day(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 != 1)
		my_usleep(60);
	if (philo->rules->nb_philo != 1)
	{
		while (1)
		{
			if (check_end_var(philo) == 1)
				return (NULL);
			if (philo_eat(philo) == 1)
				return (NULL);
			if (check_end_var(philo) == 1)
				return (NULL);
			philo_sleep_think(philo);
			if (check_end_var(philo) == 1)
				return (NULL);
		}
	}
	else
		philo_got_one_fork(philo);
	return (NULL);
}

void	philo_got_one_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork);
	write_action(philo, "\033[1;34mhas taken a fork\033[00m");
	pthread_mutex_unlock(&philo->lfork);
	my_usleep(philo->rules->death_timer + 100);
}

void	wait_end_simulation(t_checker *checker)
{
	int	ret;

	ret = 0;
	while (ret == 0)
	{
		ret = check_end(checker);
		if (ret == 1)
		{
			pthread_mutex_lock(&checker->end);
			checker->rules.end_var = 1;
			pthread_mutex_unlock(&checker->end);
			my_usleep(500);
			break ;
		}
		my_usleep(5);
	}
}

void	start_thread(t_checker *checker)
{
	int	i;

	i = 0;
	while (i < checker->philo->rules->nb_philo)
	{
		pthread_create(&checker->philo[i].thread,
			NULL, philo_day, &checker->philo[i]);
		pthread_detach(checker->philo[i].thread);
		i++;
	}
	wait_end_simulation(checker);
	exit_properly(checker);
}
