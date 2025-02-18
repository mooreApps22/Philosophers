/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:24:28 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 17:25:36 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

bool	check_death(t_data *data)
{
	pthread_mutex_lock(&data->dead_mx);
	if (data->is_dead == true)
	{
		pthread_mutex_unlock(&data->dead_mx);
		return (true);
	}
	pthread_mutex_unlock(&data->dead_mx);
	return (false);
}

void	lock_forks(t_philo *philo, t_data *data)
{
	int	first;
	int	second;

	first = philo->fork[0];
	second = philo->fork[1];
	if (first < second)
	{
		pthread_mutex_lock(&data->fork_mx[first]);
		print_state(data, philo->id, get_time(data), "has taken a fork");
		pthread_mutex_lock(&data->fork_mx[second]);
		print_state(data, philo->id, get_time(data), "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->fork_mx[second]);
		print_state(data, philo->id, get_time(data), "has taken a fork");
		pthread_mutex_lock(&data->fork_mx[first]);
		print_state(data, philo->id, get_time(data), "has taken a fork");
	}
}

void	unlock_forks(t_philo *philo, t_data *data)
{
	int	first;
	int	second;

	first = philo->fork[0];
	second = philo->fork[1];
	if (first < second)
	{
		pthread_mutex_unlock(&data->fork_mx[second]);
		pthread_mutex_unlock(&data->fork_mx[first]);
	}
	else
	{
		pthread_mutex_unlock(&data->fork_mx[first]);
		pthread_mutex_unlock(&data->fork_mx[second]);
	}
}

void	eat_routine(t_data *data, t_philo *philo)
{
	if (check_death(data))
		return ;
	lock_forks(philo, data);
	print_state(data, philo->id, get_time(data), "is eating");
	pthread_mutex_lock(&philo->meal_mx);
	philo->last_meal = get_time(data);
	philo->meal_ct++;
	pthread_mutex_unlock(&philo->meal_mx);
	ft_usleep(data, data->eat_dur);
	unlock_forks(philo, data);
}
