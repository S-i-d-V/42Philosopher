/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugotheveny <ugotheveny@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:21:34 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/08 16:22:13 by ugotheveny       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	exit_properly(t_checker *checker)
{
	int i;

	i = 0;
	while (i < checker->philo->rules->nb_philo)
	{
		pthread_mutex_destroy(&checker->philo[i].lfork);
		i++;
	}
	pthread_mutex_destroy(&checker->write);
	pthread_mutex_destroy(&checker->die);
	pthread_mutex_destroy(&checker->eat);
	exit(0);
}
