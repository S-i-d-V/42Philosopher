/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:50:35 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/18 18:29:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	write_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->rules->write);
	if (check_end_var(philo) == 1)
	{
		pthread_mutex_unlock(philo->rules->write);
		return (1);
	}
	printf("%ld %d %s\n", ms_from_start(philo->rules->start), philo->num, msg);
	pthread_mutex_unlock(philo->rules->write);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	philo_lock_first_fork(philo);
	if (write_action(philo, "\033[1;34mhas taken a fork\033[00m") == 1)
	{
		pthread_mutex_unlock(&philo->lfork);
		return (1);
	}
	philo_lock_second_fork(philo);
	if (write_action(philo, "\033[1;34mhas taken a fork\033[00m") == 1)
	{
		pthread_mutex_unlock(philo->rfork);
		return (1);
	}
	pthread_mutex_lock(philo->rules->eat);
	philo->last_eat = ms_from_start(philo->rules->start);
	pthread_mutex_unlock(philo->rules->eat);
	write_action(philo, "\033[1;32mis eating\033[00m");
	pthread_mutex_lock(philo->rules->finish);
	if (philo->rules->nb_eat != -1)
		philo->finished++;
	pthread_mutex_unlock(philo->rules->finish);
	my_usleep(philo->rules->eat_timer);
	philo_unlock_forks(philo);
	return (0);
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
	pthread_mutex_unlock(philo->rules->write);
}
