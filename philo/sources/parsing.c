/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:57:29 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 18:41:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

t_rules	get_args(int ac, char **av)
{
	t_rules	rules;

	if (is_only_num(av[1]) == 1
		&& ft_atoi(av[1]) > 0 && ft_atoi(av[1]) <= 2147483647)
		rules.nb_philo = ft_atoi(av[1]);
	else
		rules.nb_philo = -1;
	if (is_only_num(av[2]) == 1
		&& ft_atoli(av[2]) >= 0 && ft_atoli(av[2]) <= 9223372036854775807)
		rules.death_timer = ft_atoli(av[2]);
	else
		rules.death_timer = -1;
	if (is_only_num(av[3]) == 1
		&& ft_atoli(av[3]) >= 0 && ft_atoli(av[3]) <= 9223372036854775807)
		rules.eat_timer = ft_atoli(av[3]);
	else
		rules.eat_timer = -1;
	if (is_only_num(av[4]) == 1
		&& ft_atoli(av[4]) >= 0 && ft_atoli(av[4]) <= 9223372036854775807)
		rules.sleep_timer = ft_atoli(av[4]);
	else
		rules.sleep_timer = -1;
	rules.nb_eat = get_nb_eat(ac, av);
	rules.start = get_actual_time();
	rules.end_var = 0;
	return (rules);
}

int	get_nb_eat(int ac, char **av)
{
	if (ac == 6)
	{
		if (is_only_num(av[5]) == 1
			&& ft_atoi(av[5]) > 0 && ft_atoi(av[5]) <= 2147483647)
			return (ft_atoi(av[5]));
		else
			return (-1);
	}
	return (-1);
}

int	check_args(int ac, t_rules rules)
{
	if (rules.nb_philo == -1)
		return (-2);
	if (rules.death_timer == -1)
		return (-3);
	if (rules.eat_timer == -1)
		return (-4);
	if (rules.sleep_timer == -1)
		return (-5);
	if (ac == 6)
	{
		if (rules.nb_eat == -1)
			return (-6);
	}
	return (0);
}
