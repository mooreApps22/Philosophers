/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:20:05 by smoore            #+#    #+#             */
/*   Updated: 2025/02/16 18:54:18 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdatomic.h>

// ENUMS

enum e_state
{
	EAT,
	SLEEP,
	THINK,
	RESET
};

// STRUCTS

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pthread_t		tid;
	int				id;
	int				meal_ct;
	atomic_llong	last_meal;
	pthread_mutex_t	meal_mx;
	int				fork[2];
	enum e_state	state;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	atomic_llong	start;
	int				die_dur;
	int				eat_dur;
	int				think_dur;
	int				sleep_dur;
	int				max_meals;
	atomic_bool		has_started;
	atomic_bool		is_dead;
	pthread_mutex_t	stamp_mx;
	pthread_mutex_t	start_mx;
	pthread_mutex_t	dead_mx;
	pthread_mutex_t	*fork_mx;
	t_philo			**philo;
	pthread_t		death_monitor_tid;
}	t_data;

// MAIN

// VALID ARGS 
int			valid_args(int ac, char **av);

// INIT DATA
int			init_data(t_data *data, int ac, char **av);

// EAT ROUTINE
bool		check_death(t_data *data);
void		eat_routine(t_data *data, t_philo *philo);

// THINK/SLEEP ROUTINE
void		think_routine(t_data *data, t_philo *philo);
void		sleep_routine(t_data *data, t_philo *philo);

// DEATH MONITOR ROUTINE
void		*death_monitor_routine(void *argv);

//  PHILO ROUTINE  
void		*philo_routine(void *argv);

//  TIME UTILS  
void		ft_usleep(t_data *data, int dur);
long long	get_time(t_data *data);

// STR UTILS
void		msg(const char *message);
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
void		print_state(t_data *data, int philo_id, long long time, char *str);

//  FREE DATA  
void		free_data(t_data *data, int stage, int iteration);

#endif
