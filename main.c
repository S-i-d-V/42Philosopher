/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/08 02:30:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_rules	teach_rules(t_rules *rules)
{
	t_rules ret;

	ret.nb_philo = rules->nb_philo;
	ret.death_timer = rules->death_timer;
	ret.eat_timer = rules->eat_timer;
	ret.sleep_timer = rules->sleep_timer;
	ret.nb_eat = rules->nb_eat;
	return (ret);
}

t_philo	*init_philos(t_rules *rules)
{
	t_philo *philo;
	int i;
	
	philo = malloc(sizeof(t_philo) * (rules->nb_philo));
	i = 0;
	while (i < rules->nb_philo)
	{
		philo[i].num = i;
		philo[i].rules = teach_rules(rules);
		printf("PHILO NUM %d\n", philo[i].num);
		printf("nb_philo = %d.\n", philo[i].rules.nb_philo);
		printf("death_timer = %d ms.\n", philo[i].rules.death_timer);
		printf("eat_timer = %d ms.\n", philo[i].rules.eat_timer);
		printf("sleep_timer = %d ms.\n", philo[i].rules.sleep_timer);
		printf("nb_eat = %d.\n\n", philo[i].rules.nb_eat);
		i++;
	}
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
	free(philo);
	return (0);
}
