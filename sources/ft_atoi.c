/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:02:13 by user42            #+#    #+#             */
/*   Updated: 2021/09/17 01:40:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long int	ft_atoli(const char *str)
{
	int			i;
	long int	nb;
	int			nbsigne;

	i = 0;
	nb = 0;
	nbsigne = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			nbsigne++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (nbsigne == 1)
		nb = nb * -1;
	return (nb);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	nbsigne;

	i = 0;
	nb = 0;
	nbsigne = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			nbsigne++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (nbsigne == 1)
		nb = nb * -1;
	return (nb);
}
