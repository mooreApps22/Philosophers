/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:23:46 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 17:32:14 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	print_state(t_data *data, int waiter_id, long long time, char *str)
{
	pthread_mutex_lock(&data->stamp_mx);
	pthread_mutex_lock(&data->dead_mx);
	if (data->is_dead == false || waiter_id == -1)
		printf("%lld %d %s\n", time, waiter_id, str);
	pthread_mutex_unlock(&data->dead_mx);
	pthread_mutex_unlock(&data->stamp_mx);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str [i] == '+')
		i++;
	else if (str [i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str [i] == '+')
		i++;
	else if (str [i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	msg(const char *message)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (message == NULL)
		return ;
	while (message[i] != '\0')
	{
		count = write(2, &message[i], 1);
		i++;
	}
	(void) count;
}
