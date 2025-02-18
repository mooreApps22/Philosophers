/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:54 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 17:43:56 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->stamp_mx, NULL) != 0)
		return (free_data(data, 1, 0), 1);
	if (pthread_mutex_init(&data->dead_mx, NULL) != 0)
		return (free_data(data, 2, 0), 2);
	if (pthread_mutex_init(&data->start_mx, NULL) != 0)
		return (free_data(data, 3, 0), 2);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->fork_mx[i], NULL) != 0)
			return (free_data(data, 5, i), 3);
		if (pthread_mutex_init(&data->philo[i]->meal_mx, NULL) != 0)
			return (free_data(data, 6, i), 4);
		i++;
	}
	return (0);
}

static void	choose_state(t_philo *philo, int *alternate, t_data *data, int i)
{
	philo->state = (*alternate)++;
	if (i == data->philo_num - 1)
		philo->state = THINK;
	if (*alternate == THINK)
		*alternate = EAT;
}

static int	init_philo(t_data *data)
{
	int	i;
	int	alternate;

	alternate = EAT;
	data->philo = malloc(sizeof(t_philo *) * data->philo_num);
	if (data->philo == NULL)
		return (1);
	i = 0;
	while (i < data->philo_num)
	{
		data->philo[i] = malloc (sizeof(t_philo));
		if (data->philo[i] == NULL)
			return (2);
		data->philo[i]->id = i + 1;
		data->philo[i]->meal_ct = 0;
		data->philo[i]->last_meal = 0;
		data->philo[i]->fork[0] = i;
		data->philo[i]->fork[1] = i + 1;
		if (i == data->philo_num - 1)
			data->philo[i]->fork[1] = 0;
		choose_state(data->philo[i], &alternate, data, i);
		data->philo[i++]->data = data;
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	if (data == NULL || av == NULL || *av == NULL)
		return (1);
	data->philo_num = ft_atoi(av[1]);
	data->start = 0;
	data->die_dur = ft_atoi(av[2]);
	data->eat_dur = ft_atoi(av[3]);
	data->sleep_dur = ft_atoi(av[4]);
	data->think_dur = (data->die_dur - data->eat_dur - data->sleep_dur) / 2;
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	data->has_started = false;
	data->is_dead = false;
	data->philo = NULL;
	data->fork_mx = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (data->fork_mx == NULL)
		return (1);
	if (init_philo(data))
	{
		free_data(data, 1, 0);
		return (2);
	}
	if (init_mutex(data))
		return (3);
	return (0);
}
