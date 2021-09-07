/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:57:29 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 19:00:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_args(int ac, char **av, t_parse *parse)
{
	if (ft_atoi(av[1]) > 0)
		parse->nb_philo = ft_atoi(av[1]);
	else
		return (-2);
	if (ft_atoi(av[2]) >= 0)
		parse->death_timer = ft_atoi(av[2]);
	else
		return (-3);
	if (ft_atoi(av[3]) >= 0)
		parse->eat_timer = ft_atoi(av[3]);
	else
		return (-4);
	if (ft_atoi(av[4]) >= 0)
		parse->sleep_timer = ft_atoi(av[4]);
	else
		return (-5);
	parse->nb_eat = -1;
	if (ac == 6)
	{
		if (ft_atoi(av[5]) >= 0)
			parse->nb_eat = ft_atoi(av[5]);
		else
			return (-6);
	}
	return (0);
}
