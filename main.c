/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 21:40:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*init_philos(t_rules *rules)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo) * (rules->nb_philo + 1));
	return (philo);
}

int	main(int ac, char **av)
{
	t_rules	rules;
	t_philo *philo;

	if (ac < 5 || ac > 6)
		exit_error(-1);
	else if (check_args(ac, av, &rules) < 0)
		exit_error(check_args(ac, av, &rules));
	philo = init_philos(&rules);
	printf("nb_philo = %d.\n", rules.nb_philo);
	printf("death_timer = %d ms.\n", rules.death_timer);
	printf("eat_timer = %d ms.\n", rules.eat_timer);
	printf("sleep_timer = %d ms.\n", rules.sleep_timer);
	printf("nb_eat = %d.\n", rules.nb_eat);
	free(philo);
	return (0);
}
