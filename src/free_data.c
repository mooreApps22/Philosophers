/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:44 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 17:25:59 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	clear_mutex(t_data *data, int stage, int iteration)
{
	int	i;

	if (stage > 1 || stage == 0)
		pthread_mutex_destroy(&data->stamp_mx);
	if (stage > 2 || stage == 0)
		pthread_mutex_destroy(&data->dead_mx);
	if (stage > 3 || stage == 0)
		pthread_mutex_destroy(&data->start_mx);
	if (stage > 4 || stage == 0)
	{
		i = 0;
		while (i < iteration)
		{
			if (stage == 5 && i + 1 == iteration)
				break ;
			pthread_mutex_destroy(&data->fork_mx[i]);
			if (stage == 6 && i + 1 == iteration)
				break ;
			pthread_mutex_destroy(&data->philo[i]->meal_mx);
			i++;
		}
	}
}

void	free_data(t_data *data, int stage, int iteration)
{
	int	i;

	if (data == NULL)
		return ;
	if (stage != 1)
	{
		if (stage == 0)
			clear_mutex(data, stage, data->philo_num);
		else
			clear_mutex(data, stage, iteration);
	}
	if (data->philo != NULL)
	{
		i = 0;
		while (i < data->philo_num && data->philo[i] != NULL)
		{
			free(data->philo[i]);
			data->philo[i] = NULL;
			i++;
		}
		free(data->philo);
	}
	if (data->fork_mx != NULL)
		free(data->fork_mx);
}
