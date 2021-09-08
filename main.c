/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:50:32 by user42            #+#    #+#             */
/*   Updated: 2021/09/09 01:29:51 by user42           ###   ########.fr       */
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
	//Les nombre pair partent plus tard pour laisser leur fourchette aux autres
	if (philo->num % 2 != 1)
		my_usleep(25);
	//fork - eat
	if (philo->last_eat + philo->rules.eat_timer > philo->last_eat + philo->rules.death_timer)
	{
		//diying
		my_usleep(philo->rules.death_timer);
		fprintf(stderr, "%ld %d has \033[1;31mdied\033[00m\n", ms_from_start(philo->rules.start), philo->num);
		return (philo);
	}
	pthread_mutex_lock(&philo->lfork);
	fprintf(stderr, "%ld %d has taken his \033[1;34mleft fork\033[00m\n", ms_from_start(philo->rules.start), philo->num);
	if (!philo->rfork)
	{
		//diying
		my_usleep(philo->rules.death_timer);
		fprintf(stderr, "%ld %d has \033[1;31mdied\033[00m\n", ms_from_start(philo->rules.start), philo->num);
		return (philo);
	}
	pthread_mutex_lock(philo->rfork);
	fprintf(stderr, "%ld %d has taken his \033[1;32mright fork\033[00m\n", ms_from_start(philo->rules.start), philo->num);
	fprintf(stderr, "%ld %d is eating\n", ms_from_start(philo->rules.start), philo->num);
	my_usleep(philo->rules.eat_timer);
	philo->last_eat = ms_from_start(philo->rules.start);
	pthread_mutex_unlock(&philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	//sleep
	fprintf(stderr, "%ld %d is sleeping\n", ms_from_start(philo->rules.start), philo->num);
	my_usleep(philo->rules.sleep_timer);
	//thinking
	fprintf(stderr, "%ld %d is thinking\n", ms_from_start(philo->rules.start), philo->num);
	return (philo);
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
		philo[i].last_eat = 0;
		pthread_mutex_init(&philo[i].lfork, NULL);
		if (i != rules->nb_philo - 1 && rules->nb_philo != 1)
			philo[i].rfork = &philo[i + 1].lfork;
		else if (rules->nb_philo != 1)
			philo[i].rfork = &philo[0].lfork;
		ret = pthread_create(&philo[i].thread, NULL, philo_func, &philo[i]);
		if (ret != 0)
		{
			free(philo);
			exit_error(-7);
		}
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
