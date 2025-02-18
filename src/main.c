/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:58 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 18:49:18 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	join_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i]->tid, NULL);
		i++;
	}
	printf("\t\tAll Philosopher Threads have rejoined the Main Thread.\n");
}

static bool	create_death_monitor(t_data *data)
{
	if (pthread_create(&data->death_monitor_tid, NULL,
			death_monitor_routine, data) != 0)
	{
		data->is_dead = true;
		pthread_mutex_unlock(&data->start_mx);
		pthread_mutex_unlock(&data->dead_mx);
		join_philosophers(data);
		return (true);
	}
	return (false);
}

static bool	create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philo[i]->tid, NULL, \
				philo_routine, data->philo[i]) != 0)
		{
			data->is_dead = true;
			data->philo_num = i;
			pthread_mutex_unlock(&data->start_mx);
			pthread_mutex_unlock(&data->dead_mx);
			join_philosophers(data);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	run_philosophers(t_data *data)
{
	pthread_mutex_lock(&data->start_mx);
	pthread_mutex_lock(&data->dead_mx);
	if (create_philo(data) != 0)
		return (false);
	if (create_death_monitor(data) != 0)
		return (false);
	pthread_mutex_unlock(&data->dead_mx);
	data->has_started = true;
	data->start = get_time(data);
	pthread_mutex_unlock(&data->start_mx);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (valid_args(ac, av))
		return (EXIT_FAILURE);
	if (init_data(&data, ac, av))
		return (EXIT_FAILURE);
	if (!run_philosophers(&data))
		return (free_data(&data, 0, 0), EXIT_FAILURE);
	join_philosophers(&data);
	pthread_join(data.death_monitor_tid, NULL);
	printf("\t\tThe Death Monitor Thread has rejoined the Main Thread.\n");
	free_data(&data, 0, 0);
	return (EXIT_SUCCESS);
}
