/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:01:14 by user42            #+#    #+#             */
/*   Updated: 2021/09/08 23:09:40 by user42           ###   ########.fr       */
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
	long int	start;
	int			nb_philo;
	long int			death_timer;
	long int			eat_timer;
	long int			sleep_timer;
	int			nb_eat;
}				t_rules;

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	long int		last_eat;
	t_rules		rules;
}				t_philo;

int		ft_atoi(const char *str);
int		ft_atoli(const char *str);

void	exit_error(int error);

int		check_args(int ac, char **av, t_rules *rules);

#endif
