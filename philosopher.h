/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:01:14 by user42            #+#    #+#             */
/*   Updated: 2021/09/08 02:27:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_rules
{
	int	nb_philo;
	int	death_timer;
	int	eat_timer;
	int	sleep_timer;
	int	nb_eat;
}				t_rules;

typedef struct s_philo
{
	int	num;
	int	eating;
	int	sleeping;
	int	thinking;
	t_rules	rules;
}				t_philo;

int		ft_atoi(const char *str);

void	exit_error(int error);

int		check_args(int ac, char **av, t_rules *rules);

#endif
