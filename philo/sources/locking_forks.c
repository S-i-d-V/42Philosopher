/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:56:15 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/18 18:24:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	philo_lock_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork);
}

void	philo_lock_second_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
}

void	philo_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}
