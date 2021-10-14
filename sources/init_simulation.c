/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugotheveny <ugotheveny@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:26:33 by user42            #+#    #+#             */
/*   Updated: 2021/10/14 11:55:12 by ugotheveny       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	init_simulation(t_checker *checker, t_rules *rules)
{
	pthread_mutex_init(&checker->write, NULL);
	pthread_mutex_init(&checker->die, NULL);
	pthread_mutex_init(&checker->eat, NULL);
	pthread_mutex_init(&checker->finish, NULL);
	rules->write = &checker->write;
	rules->die = &checker->die;
	rules->eat = &checker->eat;
	rules->finish = &checker->finish;
	init_philos(checker, rules);
}

t_rules	teach_rules(t_rules *rules)
{
	t_rules	ret;

	ret.nb_philo = rules->nb_philo;
	ret.death_timer = rules->death_timer;
	ret.eat_timer = rules->eat_timer;
	ret.sleep_timer = rules->sleep_timer;
	ret.nb_eat = rules->nb_eat;
	return (ret);
}

void	init_philos(t_checker *checker, t_rules *rules)
{
	int			i;

	i = 0;
	while (i < rules->nb_philo)
	{
		checker->philo[i].num = i + 1;
		checker->philo[i].rules = rules;
		checker->philo[i].last_eat = 0;
		checker->philo[i].is_satiated = 0;
		checker->philo[i].finished = 0;
		if (rules->nb_eat == -1)
			checker->philo[i].finished = -1;
		pthread_mutex_init(&checker->philo[i].lfork, NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo && rules->nb_philo != 1)
	{
		if (i != rules->nb_philo - 1)
			checker->philo[i].rfork = &checker->philo[i + 1].lfork;
		else
			checker->philo[i].rfork = &checker->philo[0].lfork;
		i++;
	}
}
