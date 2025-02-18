/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think_routines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:24:28 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 15:46:12 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	think_routine(t_data *data, t_philo *philo)
{
	print_state(data, philo->id, get_time(data), "is thinking");
	usleep(5);
}

static int	sleep_dur(int ms, t_data *data)
{
	int	start;

	start = get_time(data);
	while ((get_time(data) - start) < ms)
		usleep(10);
	return (0);
}

void	sleep_routine(t_data *data, t_philo *philo)
{
	if (check_death(data))
		return ;
	print_state(data, philo->id, get_time(data), "is sleeping");
	sleep_dur(data->sleep_dur, data);
}
