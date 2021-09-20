/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/20 16:54:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosopher.h"

void	write_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->rules.write);
	printf("%ld %d %s\n", ms_from_start(philo->rules.start), philo->num, msg);
	pthread_mutex_unlock(philo->rules.write);
}

void	write_death(t_philo *philo)
{
	pthread_mutex_lock(philo->rules.write);
	printf("%ld %d \033[1;31mhas died\033[00m\n", ms_from_start(philo->rules.start), philo->num);
	my_usleep(50);
	pthread_mutex_unlock(philo->rules.write);
}

void	*check_func(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (ms_from_start(philo->rules.start) > philo->last_eat + philo->rules.death_timer)
		{
			philo->is_dead = 1;
			write_death(philo);
			exit(0);
		}
	}
	return (NULL);
}

void	*philo_func(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 != 1)
		my_usleep(50);
	while (1)
	{
		pthread_mutex_lock(&philo->lfork);
		write_action(philo, "\033[1;34mhas taken a fork\033[00m");
		//if (philo->rules.nb_philo != 1)
		//{
			pthread_mutex_lock(philo->rfork);
			write_action(philo, "\033[1;34mhas taken a fork\033[00m");
			if (philo->rules.nb_eat != -1)
				philo->finished++;
			write_action(philo, "\033[1;32mis eating\033[00m");
			philo->last_eat = ms_from_start(philo->rules.start);
			my_usleep(philo->rules.eat_timer);
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(&philo->lfork);
		//}
		//else
		//	my_usleep(philo->rules.death_timer + 100);
		write_action(philo, "\033[1;33mis sleeping\033[00m");
		my_usleep(philo->rules.sleep_timer);
		write_action(philo, "\033[1;39mis thinking\033[00m");
	}
	return (philo);
}

void	check_end(t_checker *checker)
{
	int i;
	int finish;

	i = 0;
	finish = 0;
	while (i < checker->philo[0].rules.nb_philo)
	{
		if (checker->philo[i].is_dead == 1)
			exit(0);
		if (checker->philo[i].finished >= checker->philo[0].rules.nb_eat && checker->philo[0].rules.nb_philo != -1)
			finish++;
		i++;
	}
	if (finish == checker->philo[0].rules.nb_philo && checker->philo[0].rules.nb_eat != -1)
		exit(0);
}

void	start_thread(t_checker *checker)
{
	int	i;

	i = 0;
	while (i < checker->philo->rules.nb_philo)
	{
		pthread_create(&checker->philo[i].thread, NULL, philo_func, &checker->philo[i]);
		i++;
	}
	i = 0;
	while (i < checker->philo->rules.nb_philo)
	{
		pthread_create(&checker->philo[i].check, NULL, check_func, &checker->philo[i]);
		i++;
	}
	while (1)
		check_end(checker);
}

int	main(int ac, char **av)
{
	t_rules		rules;
	t_checker	checker;

	if (ac < 5 || ac > 6)
		exit(0);
	else if (check_args(ac, av, &rules) < 0)
		exit(0);
	rules.start = get_actual_time();
	checker = init_philos(&rules);
	start_thread(&checker);
	return (0);
}
