/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:26:33 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 17:09:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

t_rules	teach_rules(t_checker checker, t_rules *rules)
{
	t_rules ret;

	ret.start = rules->start;
	ret.nb_philo = rules->nb_philo;
	ret.death_timer = rules->death_timer;
	ret.eat_timer = rules->eat_timer;
	ret.sleep_timer = rules->sleep_timer;
	ret.nb_eat = rules->nb_eat;
	ret.write = &checker.write;
	return (ret);
}

t_checker	init_philos(t_rules *rules)
{
	t_checker 	checker;
	int 		i;
	int 		ret;
	
	checker.philo = malloc(sizeof(t_philo) * (rules->nb_philo));
	i = 0;
	ret = 0;
	while (i < rules->nb_philo)
	{
		checker.philo[i].num = i + 1;
		checker.philo[i].rules = teach_rules(checker, rules);
		checker.philo[i].last_eat = 0;
		checker.philo[i].is_dead = 0;
		if (checker.philo[i].rules.nb_eat == -1)
			checker.philo[i].finished = -1;
		else
			checker.philo[i].finished = 0;
		pthread_mutex_init(&checker.philo[i].lfork, NULL);
		if (i != rules->nb_philo - 1 && rules->nb_philo != 1)
			checker.philo[i].rfork = &checker.philo[i + 1].lfork;
		else if (rules->nb_philo != 1)
			checker.philo[i].rfork = &checker.philo[0].lfork;
		i++;
	}
	return (checker);
}