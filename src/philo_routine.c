/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:19:34 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 17:36:37 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	choose_routine(t_philo *philo, t_data *data)
{
	if (philo->state == EAT)
		eat_routine(data, philo);
	else if (philo->state == SLEEP)
		sleep_routine(data, philo);
	else if (philo->state == THINK)
		think_routine(data, philo);
}

static void	action_routine(t_data *data, t_philo *philo)
{
	int	i;

	if (philo->id % 2 == 0)
	{
		i = philo->fork[0];
		philo->fork[0] = philo->fork[1];
		philo->fork[1] = i;
		i = 0;
	}
	else if (philo->id == data->philo_num)
		i = 1;
	else
		i = 2;
	while (true)
	{
		if (check_death(data))
			return ;
		choose_routine(philo, data);
		philo->state++;
		if (philo->state == RESET)
			philo->state = EAT;
	}
}

static void	lone_philo_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->fork_mx[philo->fork[0]]);
	print_state(data, philo->id, get_time(data), "has taken a fork");
	pthread_mutex_unlock(&data->fork_mx[philo->fork[0]]);
	while (1)
	{
		if (check_death(data))
			return ;
		ft_usleep(data, data->sleep_dur);
	}
	return ;
}

static bool	start_sync(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->start_mx);
	if (data->has_started == false)
	{
		pthread_mutex_unlock(&philo->data->start_mx);
		usleep(10);
		pthread_mutex_lock(&data->start_mx);
	}
	pthread_mutex_unlock(&philo->data->start_mx);
	return (false);
}

void	*philo_routine(void *argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)argv;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(10000);
	start_sync(data, philo);
	pthread_mutex_lock(&philo->meal_mx);
	philo->last_meal = get_time(data);
	pthread_mutex_unlock(&philo->meal_mx);
	if (data->philo_num == 1)
		lone_philo_routine(data, philo);
	else
		action_routine(data, philo);
	return (NULL);
}
