/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:57:29 by user42            #+#    #+#             */
/*   Updated: 2021/09/17 01:38:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	is_only_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av, t_rules *rules)
{
	if (is_only_num(av[1]) == 1
		&& ft_atoi(av[1]) > 0 && ft_atoi(av[1]) <= 2147483647)
		rules->nb_philo = ft_atoi(av[1]);
	else
		return (-2);
	if (is_only_num(av[2]) == 1
		&& ft_atoli(av[2]) >= 0 && ft_atoli(av[2]) <= 9223372036854775807)
		rules->death_timer = ft_atoli(av[2]);
	else
		return (-3);
	if (is_only_num(av[3]) == 1
		&& ft_atoli(av[3]) >= 0 && ft_atoli(av[3]) <= 9223372036854775807)
		rules->eat_timer = ft_atoli(av[3]);
	else
		return (-4);
	if (is_only_num(av[4]) == 1
		&& ft_atoli(av[4]) >= 0 && ft_atoli(av[4]) <= 9223372036854775807)
		rules->sleep_timer = ft_atoli(av[4]);
	else
		return (-5);
	rules->nb_eat = -1;
	if (ac == 6)
	{
		if (is_only_num(av[5]) == 1
			&& ft_atoi(av[5]) >= 0 && ft_atoi(av[5]) <= 2147483647)
			rules->nb_eat = ft_atoi(av[5]);
		else
			return (-6);
	}
	return (0);
}
