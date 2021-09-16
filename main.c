/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/17 01:21:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosopher.h"

void	wait_action(t_philo *philo, long int time)
{
	long int start;

	start = ms_from_start(philo->rules.start);
	while (ms_from_start(philo->rules.start) < time + start)
	{
		if (ms_from_start(philo->rules.start) > philo->last_eat + philo->rules.death_timer)
		{
			printf("%ld %d has \033[1;31mdied\033[00m\n", ms_from_start(philo->rules.start), philo->num);
			philo->is_dead = 1;
			exit(0);
		}
		usleep(1);
	}
}

void	*philo_func(void *data)
{
	t_philo	*philo;
	philo = (t_philo *)data;

	if (philo->num % 2 != 1)
		my_usleep(50);
	while (philo->finished < philo->rules.nb_eat || philo->rules.nb_eat == -1)
	{
		//FORK
		pthread_mutex_lock(&philo->lfork);
		pthread_mutex_lock(philo->rules.write);
		printf("\033[1;34m%ld %d has taken a fork\033[00m\n", ms_from_start(philo->rules.start), philo->num);
		pthread_mutex_unlock(philo->rules.write);
		if (philo->rules.nb_philo != 1)
		{
			//FORK
			pthread_mutex_lock(philo->rfork);
			pthread_mutex_lock(philo->rules.write);
			printf("\033[1;34m%ld %d has taken a fork\033[00m\n", ms_from_start(philo->rules.start), philo->num);
			pthread_mutex_unlock(philo->rules.write);
			//EAT
			if (philo->rules.nb_eat != -1)
				philo->finished++;
			pthread_mutex_lock(philo->rules.write);
			printf("\033[1;32m%ld %d is eating\033[00m (%d/%d) last_eat : %ld\n", ms_from_start(philo->rules.start), philo->num, philo->finished, philo->rules.nb_eat, philo->last_eat);
			pthread_mutex_unlock(philo->rules.write);
			philo->last_eat = ms_from_start(philo->rules.start);
			my_usleep(philo->rules.eat_timer);
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(&philo->lfork);
		}
		else
			my_usleep(philo->rules.death_timer + 100);
		//SLEEP
		pthread_mutex_lock(philo->rules.write);
		printf("\033[1;33m%ld %d is sleeping\033[00m\n", ms_from_start(philo->rules.start), philo->num);
		my_usleep(philo->rules.sleep_timer);
		pthread_mutex_unlock(philo->rules.write);
		//THINK
		pthread_mutex_lock(philo->rules.write);
		printf("\033[1;39m%ld %d is thinking\033[00m\n", ms_from_start(philo->rules.start), philo->num);
		pthread_mutex_unlock(philo->rules.write);
	}
	return (philo);
}

void	start_thread(t_checker *checker)
{
	int i;

	i = 0;
	while (i < checker->philo->rules.nb_philo)
	{
		pthread_create(&checker->philo[i].thread, NULL, philo_func, &checker->philo[i]);
		i++;
	}
	i = 0;
	while (i < checker->philo->rules.nb_philo)
	{
		pthread_join(checker->philo[i].thread, NULL);
		i++;
	}
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
