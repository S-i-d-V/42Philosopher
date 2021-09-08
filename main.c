/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/08 20:03:00 by user42           ###   ########.fr       */
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
	//
	pthread_mutex_lock(&mutex);
	fprintf(stderr, "%ld %d is doing things.\n", get_actual_time() - philo->rules.start, philo->num);
	pthread_mutex_unlock(&mutex);
	my_usleep(210);
	//
	pthread_mutex_lock(&mutex);
	fprintf(stderr, "%ld %d is doing other things.\n", get_actual_time() - philo->rules.start, philo->num);
	pthread_mutex_unlock(&mutex);
	my_usleep(210);
	//
	pthread_mutex_lock(&mutex);
	fprintf(stderr, "%ld %d is still doing other things.\n", get_actual_time() - philo->rules.start, philo->num);
	pthread_mutex_unlock(&mutex);
	my_usleep(210);
	pthread_mutex_unlock(&mutex);
	//
	pthread_exit(NULL);
}

t_philo	*init_philos(t_rules *rules)
{
	t_philo *philo;
	int i;
	int ret;
	
	philo = malloc(sizeof(t_philo) * (rules->nb_philo));
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	ret = 0;
	while (i < rules->nb_philo)
	{
		philo[i].num = i + 1;
		philo[i].rules = teach_rules(rules);
		ret = pthread_create(&philo[i].thread, NULL, philo_func, &philo[i]);
		if (ret != 0)
			exit_error(-7);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (philo);
}

#include <limits.h>

int	main(int ac, char **av)
{
	t_rules		rules;
	t_philo		*philo;

	if (ac < 5 || ac > 6)
		exit(0);
	else if (check_args(ac, av, &rules) < 0)
		exit(0);
	rules.start = get_actual_time();
	philo = init_philos(&rules);
	free(philo);
	return (0);
}
