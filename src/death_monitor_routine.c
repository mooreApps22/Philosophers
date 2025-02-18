/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor_routine.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:19:43 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 16:49:27 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static int	check_all_eaten(t_data *data, t_philo *philo, int *all_eaten)
{
	if (philo->meal_ct >= data->max_meals)
	{
		(*all_eaten)++;
		if (*all_eaten == data->philo_num)
		{
			pthread_mutex_lock(&data->stamp_mx);
			pthread_mutex_lock(&data->dead_mx);
			data->is_dead = true;
			pthread_mutex_unlock(&data->dead_mx);
			pthread_mutex_unlock(&data->stamp_mx);
			pthread_mutex_unlock(&philo->meal_mx);
			return (0);
		}
	}
	return (1);
}

static int	investigate_death(t_data *data, t_philo *philo, int i)
{
	if (get_time(data) - philo->last_meal >= data->die_dur)
	{
		pthread_mutex_lock(&data->stamp_mx);
		pthread_mutex_lock(&data->dead_mx);
		data->is_dead = true;
		printf("%lld %d died\n", get_time(data), i + 1);
		pthread_mutex_unlock(&data->dead_mx);
		pthread_mutex_unlock(&data->stamp_mx);
		return (1);
	}
	return (0);
}

static void	death_monitor_work(t_data *data)
{
	int	i;
	int	all_eaten;

	while (1)
	{
		i = 0;
		all_eaten = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->philo[i]->meal_mx);
			if (investigate_death(data, data->philo[i], i) != 0)
			{
				pthread_mutex_unlock(&data->philo[i]->meal_mx);
				return ;
			}
			if (data->max_meals != -1)
			{
				if (check_all_eaten(data, data->philo[i], &all_eaten) == 0)
					return ;
			}
			pthread_mutex_unlock(&data->philo[i]->meal_mx);
			i++;
		}
	}
}

void	*death_monitor_routine(void *argv)
{
	t_data	*data;

	data = (t_data *)argv;
	pthread_mutex_lock(&data->start_mx);
	if (data->has_started == false)
	{
		pthread_mutex_unlock(&data->start_mx);
		return (NULL);
	}
	pthread_mutex_unlock(&data->start_mx);
	death_monitor_work(data);
	return (NULL);
}
