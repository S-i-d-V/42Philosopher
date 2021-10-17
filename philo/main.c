/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/10/17 16:15:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosopher.h"

int	main(int ac, char **av)
{
	t_rules		rules;
	t_checker	checker;

	if (ac < 5 || ac > 6)
		return (0);
	else if (check_args(ac, av, &rules) < 0)
		return (0);
	checker.philo = malloc(sizeof(t_philo) * (rules.nb_philo));
	if (checker.philo == NULL)
		return (0);
	init_simulation(&checker, &rules);
	start_thread(&checker);
}
