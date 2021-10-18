/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:26:33 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 18:43:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	init_simulation(t_checker *checker)
{
	pthread_mutex_init(&checker->write, NULL);
	pthread_mutex_init(&checker->die, NULL);
	pthread_mutex_init(&checker->eat, NULL);
	pthread_mutex_init(&checker->finish, NULL);
	pthread_mutex_init(&checker->end, NULL);
	checker->rules.write = &checker->write;
	checker->rules.die = &checker->die;
	checker->rules.eat = &checker->eat;
	checker->rules.finish = &checker->finish;
	checker->rules.end = &checker->end;
	init_philos(checker);
}

t_rules	teach_rules(t_rules *rules)
{
	t_rules	ret;

	ret.nb_philo = rules->nb_philo;
	ret.death_timer = rules->death_timer;
	ret.eat_timer = rules->eat_timer;
	ret.sleep_timer = rules->sleep_timer;
	ret.nb_eat = rules->nb_eat;
	ret.end_var = rules->end_var;
	return (ret);
}

void	init_philos(t_checker *checker)
{
	int			i;

	i = 0;
	while (i < checker->rules.nb_philo)
	{
		checker->philo[i].num = i + 1;
		checker->philo[i].rules = &checker->rules;
		checker->philo[i].last_eat = 0;
		checker->philo[i].is_satiated = 0;
		checker->philo[i].finished = 0;
		if (checker->rules.nb_eat == -1)
			checker->philo[i].finished = -1;
		pthread_mutex_init(&checker->philo[i].lfork, NULL);
		i++;
	}
	i = 0;
	while (i < checker->rules.nb_philo && checker->rules.nb_philo != 1)
	{
		if (i != checker->rules.nb_philo - 1)
			checker->philo[i].rfork = &checker->philo[i + 1].lfork;
		else
			checker->philo[i].rfork = &checker->philo[0].lfork;
		i++;
	}
}
