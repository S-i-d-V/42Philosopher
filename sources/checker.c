/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:29:39 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 18:56:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int		is_finished(t_checker *checker)
{
	int i;

	i = 0;
	while (i < checker->philo[i].rules.nb_philo)
	{
		if (checker->philo[i].is_dead == 1)
			return (-1);
		i++;
	}
	return (0);
}

void	*check_finish(void *data)
{
	t_checker *checker;
	int i;

	i = 0;
	checker = *(t_checker **)data;
	while(is_finished(checker) == 0)
		my_usleep(10);
	while (i < checker->philo[i].rules.nb_philo)
	{
		pthread_detach(checker->philo[i].thread);
		i++;
	}
	free(checker->philo);
	return (checker);
}
