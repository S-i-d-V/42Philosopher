/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:57:29 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 18:56:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_args(int ac, char **av, t_rules *rules)
{
	if (ft_atoi(av[1]) > 0)
		rules->nb_philo = ft_atoi(av[1]);
	else
		return (-2);
	if (ft_atoi(av[2]) >= 0)
		rules->death_timer = ft_atoli(av[2]);
	else
		return (-3);
	if (ft_atoi(av[3]) >= 0)
		rules->eat_timer = ft_atoli(av[3]);
	else
		return (-4);
	if (ft_atoi(av[4]) >= 0)
		rules->sleep_timer = ft_atoli(av[4]);
	else
		return (-5);
	rules->nb_eat = -1;
	if (ac == 6)
	{
		if (ft_atoi(av[5]) >= 0)
			rules->nb_eat = ft_atoi(av[5]);
		else
			return (-6);
	}
	return (0);
}
