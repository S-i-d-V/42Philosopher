/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugotheveny <ugotheveny@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:57:29 by user42            #+#    #+#             */
/*   Updated: 2021/10/08 17:08:56 by ugotheveny       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	get_nb_eat(int ac, char **av, t_rules *rules)
{
	rules->nb_eat = -1;
	if (ac == 6)
	{
		if (is_only_num(av[5]) == 1
			&& ft_atoi(av[5]) >= 0 && ft_atoi(av[5]) <= 2147483647)
			rules->nb_eat = ft_atoi(av[5]);
		else
			return (-6);
	}
	rules->start = get_actual_time();
	return (0);
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
	return (get_nb_eat(ac, av, rules));
}
