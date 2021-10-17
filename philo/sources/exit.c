/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:21:34 by ugotheveny        #+#    #+#             */
/*   Updated: 2021/10/17 16:23:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	exit_properly(t_checker *checker)
{
	int	i;

	i = 0;
	while (i < checker->philo->rules->nb_philo)
	{
		pthread_mutex_destroy(&checker->philo[i].lfork);
		i++;
	}
	pthread_mutex_destroy(&checker->write);
	pthread_mutex_destroy(&checker->die);
	pthread_mutex_destroy(&checker->eat);
	pthread_mutex_destroy(&checker->finish);
	free(checker->philo);
	return (1);
}
