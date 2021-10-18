/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 18:17:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosopher.h"

int	main(int ac, char **av)
{
	t_checker	checker;

	if (ac < 5 || ac > 6)
		return (0);
	checker.rules = get_args(ac, av);
	if (check_args(ac, checker.rules) < 0)
		return (0);
	checker.philo = malloc(sizeof(t_philo) * (checker.rules.nb_philo));
	if (checker.philo == NULL)
		return (0);
	init_simulation(&checker);
	start_thread(&checker);
}
