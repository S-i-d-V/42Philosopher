/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/09 22:01:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t mutex;

long int	get_actual_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit(0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(long int time)
{
	long int start;

	start = get_actual_time();
	while ((get_actual_time() < time + start))
		usleep(10);
}

long int	ms_from_start(long int start)
{
	return (get_actual_time() - start);
}

t_rules	teach_rules(t_rules *rules)
{
	t_rules ret;

	ret.start = rules->start;
	ret.nb_philo = rules->nb_philo;
	ret.death_timer = rules->death_timer;
	ret.eat_timer = rules->eat_timer;
	ret.sleep_timer = rules->sleep_timer;
	ret.nb_eat = rules->nb_eat;
	return (ret);
}

void	*philo_func(void *data)
{
	t_philo	*philo;
	philo = (t_philo *)data;

	//fork - eat
	if (philo->num % 2 != 1)
		my_usleep(50);
	pthread_mutex_lock(&philo->lfork);
	fprintf(stderr, "%ld %d has taken his \033[1;34mleft fork\033[00m\n", ms_from_start(philo->rules.start), philo->num);
	pthread_mutex_lock(philo->rfork);
	//DEBUG
	if (philo->num != philo->rules.nb_philo)
		fprintf(stderr, "%ld %d has taken his \033[1;32mright fork\033[00m (%d's fork);\n", ms_from_start(philo->rules.start), philo->num, philo->num + 1);
	else
		fprintf(stderr, "%ld %d has taken his \033[1;32mright fork\033[00m (%d's fork);\n", ms_from_start(philo->rules.start), philo->num, 1);
	fprintf(stderr, "%ld %d is eating\n", ms_from_start(philo->rules.start), philo->num);
	my_usleep(philo->rules.eat_timer);
	philo->last_eat = ms_from_start(philo->rules.start);
	pthread_mutex_unlock(&philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (philo);
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
		checker.philo[i].rules = teach_rules(rules);
		checker.philo[i].last_eat = 0;
		checker.philo[i].is_dead = 0;
		pthread_mutex_init(&checker.philo[i].lfork, NULL);
		if (i != rules->nb_philo - 1 && rules->nb_philo != 1)
			checker.philo[i].rfork = &checker.philo[i + 1].lfork;
		else if (rules->nb_philo != 1)
			checker.philo[i].rfork = &checker.philo[0].lfork;
		i++;
	}
	return (checker);
}

void	start_thread(t_checker *checker)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (i < checker->philo->rules.nb_philo)
	{
		ret = pthread_create(&checker->philo[i].thread, NULL, philo_func, &checker->philo[i]);
		if (ret != 0)
		{
			free(checker->philo);
			exit_error(-7);
		}
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
	free(checker.philo);
	return (0);
}
