/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugotheveny <ugotheveny@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:56:15 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/08 16:56:43 by ugotheveny       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	philo_lock_first_fork(t_philo *philo)
{
	if (philo->num == philo->rules->nb_philo)
		pthread_mutex_lock(&philo->lfork);
	else
		pthread_mutex_lock(philo->rfork);
}

void	philo_lock_second_fork(t_philo *philo)
{
	if (philo->num == philo->rules->nb_philo)
		pthread_mutex_lock(philo->rfork);
	else
		pthread_mutex_lock(&philo->lfork);
}

void	philo_unlock_forks(t_philo *philo)
{
	if (philo->num == philo->rules->nb_philo)
		pthread_mutex_unlock(&philo->lfork);
	else
		pthread_mutex_unlock(philo->rfork);
	if (philo->num == philo->rules->nb_philo)
		pthread_mutex_unlock(philo->rfork);
	else
		pthread_mutex_unlock(&philo->lfork);
}
