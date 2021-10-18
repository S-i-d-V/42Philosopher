/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:01:14 by user42            #+#    #+#             */
/*   Updated: 2021/10/18 18:23:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	long int		start;
	int				nb_philo;
	long int		death_timer;
	long int		eat_timer;
	long int		sleep_timer;
	int				nb_eat;
	int				end_var;
	pthread_mutex_t	*write;
	pthread_mutex_t	*die;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*finish;
	pthread_mutex_t	*end;
}				t_rules;

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	long int		last_eat;
	int				is_satiated;
	int				finished;
	t_rules			*rules;
}				t_philo;

typedef struct s_checker
{
	t_philo			*philo;
	pthread_mutex_t	write;
	pthread_mutex_t	die;
	pthread_mutex_t	eat;
	pthread_mutex_t	finish;
	pthread_mutex_t	end;
	t_rules			rules;
}				t_checker;

int			ft_atoi(const char *str);
long int	ft_atoli(const char *str);
int			is_only_num(char *str);

long int	get_actual_time(void);
void		my_usleep(long int time);
long int	ms_from_start(long int start);

t_rules		get_args(int ac, char **av);
int			check_args(int ac, t_rules rules);
int			get_nb_eat(int ac, char **av);

void		philo_lock_first_fork(t_philo *philo);
void		philo_lock_second_fork(t_philo *philo);
void		philo_unlock_forks(t_philo *philo);

void		init_simulation(t_checker *checker);
t_rules		teach_rules(t_rules *rules);
void		init_philos(t_checker *checker);

int			write_action(t_philo *philo, char *msg);
int			philo_eat(t_philo *philo);
void		philo_sleep_think(t_philo *philo);
void		write_death(t_philo *philo);
void		philo_die(t_philo *philo);

int			check_end_var(t_philo *philo);
void		start_thread(t_checker *checker);
void		*philo_day(void *data);
void		philo_got_one_fork(t_philo *philo);

int			check_end(t_checker *checker);
int			check_eat(t_checker *checker);

int			exit_properly(t_checker *checker);

#endif
