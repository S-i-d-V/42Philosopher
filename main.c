/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 19:07:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_parse	parse;

	if (ac < 5 || ac > 6)
		exit_error(-1);
	else if (check_args(ac, av, &parse) < 0)
		exit_error(check_args(ac, av, &parse));
	printf("nb_philo = %d.\n", parse.nb_philo);
	printf("death_timer = %d ms.\n", parse.death_timer);
	printf("eat_timer = %d ms.\n", parse.eat_timer);
	printf("sleep_timer = %d ms.\n", parse.sleep_timer);
	printf("nb_eat = %d.\n", parse.nb_eat);
	return (0);
}
