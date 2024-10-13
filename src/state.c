/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:04:50 by razaccar          #+#    #+#             */
/*   Updated: 2024/10/12 15:16:58 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

static bool	is_full(t_philo	*philo)
{
	bool	state;
	int		meals_eated;

	state = false;
	pthread_mutex_lock(&philo->simulation->monitoring);
	meals_eated = philo->meals_eated;
	pthread_mutex_unlock(&philo->simulation->monitoring);
	if (meals_eated >= philo->simulation->n_meals_to_eat)
		state = true;
	return (state);
}

bool	is_everyone_full(t_simulation *simulation)
{
	int	i;
	
	i = -1;
	while (++i < simulation->n_philos)
	{
		if (is_full(&simulation->philos[i]) == false)
			return (false);
	}
	return (true);
}

static bool	is_starving(t_philo	*philo)
{
	bool	state;
	long	timestamp;
	long	time_without_eating;

	state = false;
	timestamp = get_timestamp(philo->simulation->start_timestamp);
	pthread_mutex_lock(&philo->simulation->monitoring);
	time_without_eating = timestamp - philo->last_meal_timestamp;
	pthread_mutex_unlock(&philo->simulation->monitoring);
	if (time_without_eating >= philo->simulation->time_to_die)
		state = true;
	return (state);
}

bool	is_someone_starving(t_simulation *simulation)
{
	long	timestamp;
	int		i;

	i = -1;
	while (++i < simulation->n_philos)
	{
		if (is_starving(&simulation->philos[i]) == true)
		{
			philo_print(&simulation->philos[i], DEAD);
			return (true);
		}
	}
	return (false);
}

bool	is_running(t_simulation *simulation)
{
	bool	state;

	pthread_mutex_lock(&simulation->monitoring);
	state = simulation->is_running;
	pthread_mutex_unlock(&simulation->monitoring);
	return (state);
}
