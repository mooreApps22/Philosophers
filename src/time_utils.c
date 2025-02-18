/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:23:46 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 17:30:05 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	ft_usleep(t_data *data, int dur)
{
	long long	scheduled_time;

	scheduled_time = get_time(data) + dur;
	while (get_time(data) < scheduled_time)
	{
		usleep(10);
	}
}

long long	get_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec) * 1000 + (time.tv_usec / 1000) - data->start);
}
