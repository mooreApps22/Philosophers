/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:19:39 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 17:34:08 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

int	valid_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (msg("./philo must have 4 or 5 arguments.\n"), 1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == '\0')
			return (msg("Must have arguments.\n"), 2);
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (msg("./philo args must be positive integers.\n"), 3);
			j++;
		}
		if (ft_atol(av[i]) >= INT_MAX || ft_atol(av[i]) <= 0)
			return (msg("Error - AV - These INT are mutated!!\n"), 4);
		i++;
	}
	return (0);
}
