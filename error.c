/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:46:35 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 19:10:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	exit_error(int error)
{
	if (error == -1)
	{
		printf("[Erreur %d] Nombre d'arguments incorrect.\n", error);
		printf("(./philo nbphilo timetodie timetoeat timetosleep [nbeat]).\n");
	}
	if (error == -2)
		printf("[Erreur %d] Il doit y avoir au moins 1 philosophe.\n", error);
	if (error == -3)
		printf("[Erreur %d] Le temps avant deces doit etre >= a 0.\n", error);
	if (error == -4)
		printf("[Erreur %d] Le temps pour manger doit etre >= a 0.\n", error);
	if (error == -5)
		printf("[Erreur %d] Le temps pour dormir doit etre >= a 0.\n", error);
	if (error == -6)
		printf("[Erreur %d] Le nombre de repas doit etre >= a 0.\n", error);
	exit(0);
}
