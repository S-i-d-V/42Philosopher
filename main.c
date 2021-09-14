/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 18:58:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosopher.h"

void	wait_and_check(t_philo *philo, int time_to_wait)
{
	while (ms_from_start(philo->rules.start) < philo->last_eat + time_to_wait)
	{
		if (ms_from_start(philo->rules.start) > philo->last_eat + philo->rules.death_timer)
		{
			fprintf(stderr, "%ld %d has \033[1;31mdied\033[00m\n", ms_from_start(philo->rules.start), philo->num);
			philo->is_dead = 1;
			exit(0);
		}
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
		//death
		if (ms_from_start(philo->rules.start) > philo->last_eat + philo->rules.death_timer)
			wait_and_check(philo, 0);
		//FORK
		pthread_mutex_lock(&philo->lfork);
		fprintf(stderr, "%ld %d has taken his \033[1;34mleft fork\033[00m\n", ms_from_start(philo->rules.start), philo->num);
		if (philo->rules.nb_philo != 1)
		{
			pthread_mutex_lock(philo->rfork);
			if (philo->num != philo->rules.nb_philo)
				fprintf(stderr, "%ld %d has taken his \033[1;32mright fork\033[00m (%d's fork);\n", ms_from_start(philo->rules.start), philo->num, philo->num + 1);
			else
				fprintf(stderr, "%ld %d has taken his \033[1;32mright fork\033[00m (%d's fork);\n", ms_from_start(philo->rules.start), philo->num, 1);
			//EAT
			if (philo->rules.nb_eat != -1)
				philo->finished++;
			fprintf(stderr, "%ld %d is \033[1;33meating\033[00m (%d/%d) last_eat : %ld\n", ms_from_start(philo->rules.start), philo->num, philo->finished, philo->rules.nb_eat, philo->last_eat);
			//death
			wait_and_check(philo, philo->rules.eat_timer);
			philo->last_eat = ms_from_start(philo->rules.start);
			pthread_mutex_unlock(&philo->lfork);
			pthread_mutex_unlock(philo->rfork);
		}
		else
			wait_and_check(philo, philo->rules.death_timer + 1000);
		//SLEEP
		fprintf(stderr, "%ld %d is \033[1;37msleeping\033[00m\n", ms_from_start(philo->rules.start), philo->num);
		//death
		wait_and_check(philo, philo->rules.sleep_timer);
		//THINK
		fprintf(stderr, "%ld %d is \033[1;35mthinking\033[00m\n", ms_from_start(philo->rules.start), philo->num);
	}
	return (philo);
}

void	start_thread(t_checker *checker)
{
	int i;

	i = 0;
	pthread_create(&checker->thread, NULL, check_finish, &checker);
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
