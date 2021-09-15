/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:28:46 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 01:38:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long int	get_actual_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit(0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void		my_usleep(long int time)
{
	long int start;

	start = get_actual_time();
	while ((get_actual_time() < time + start))
		usleep(1);
}

long int	ms_from_start(long int start)
{
	return (get_actual_time() - start);
}
