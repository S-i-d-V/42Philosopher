/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:50:35 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/08 20:36:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	write_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->rules->write);
	printf("%ld %d %s\n", ms_from_start(philo->rules->start), philo->num, msg);
	pthread_mutex_unlock(philo->rules->write);
}

void	philo_eat(t_philo *philo)
{
	philo_lock_first_fork(philo);
	write_action(philo, "\033[1;34mhas taken a fork\033[00m");
	philo_lock_second_fork(philo);
	write_action(philo, "\033[1;34mhas taken a fork\033[00m");
	pthread_mutex_lock(philo->rules->eat);
	philo->last_eat = ms_from_start(philo->rules->start);
	pthread_mutex_unlock(philo->rules->eat);
	write_action(philo, "\033[1;32mis eating\033[00m");
	pthread_mutex_lock(philo->rules->finish);
	if (philo->rules->nb_eat != -1)
	{
		philo->finished++;
		if (philo->finished == philo->rules->nb_eat)
			philo->is_satiated = 1;
	}
	pthread_mutex_unlock(philo->rules->finish);
	my_usleep(philo->rules->eat_timer);
	philo_unlock_forks(philo);
}

void	philo_sleep_think(t_philo *philo)
{
	write_action(philo, "\033[1;33mis sleeping\033[00m");
	my_usleep(philo->rules->sleep_timer);
	write_action(philo, "\033[1;39mis thinking\033[00m");
}

void	write_death(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->write);
	printf("%ld %d \033[1;31mhas died\033[00m\n",
		ms_from_start(philo->rules->start), philo->num);
	my_usleep(25);
}

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->die);
	philo->is_dead = 1;
	pthread_mutex_unlock(philo->rules->die);
	write_death(philo);
	my_usleep(25);
}
