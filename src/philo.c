/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:08:01 by razaccar          #+#    #+#             */
/*   Updated: 2024/10/08 20:53:31 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void	philo_print(t_philo *self, char *state)
{
	long	timestamp;

	pthread_mutex_lock(&self->simulation->printing);
	timestamp = get_timestamp(self->simulation->start_timestamp);
	printf("%ld | %d %s", timestamp, self->id, state);
	pthread_mutex_unlock(&self->simulation->printing);	
}

void	philo_sleep_and_think(t_philo *self)
{
	philo_print(self, SLEEPING);
	ft_usleep(self->simulation->time_to_sleep * 1000);
	philo_print(self, THINKING);
}

void	philo_eat(t_philo *self)
{
	long	timestamp;
	timestamp = get_timestamp(self->simulation->start_timestamp);
	pthread_mutex_lock(&self->simulation->monitoring);
	self->meals_eated++;
	self->last_meal_timestamp = timestamp;
	pthread_mutex_unlock(&self->simulation->monitoring);
	philo_print(self, EATING);
	ft_usleep(1000 * self->simulation->time_to_eat);
	pthread_mutex_unlock(self->right_fork);
	pthread_mutex_unlock(self->left_fork);
}

void	philo_take_forks(t_philo *self)
{
	if (self->id & 1)
	{
		pthread_mutex_lock(self->right_fork);
		philo_print(self, TAKING_FORK);
		pthread_mutex_lock(self->left_fork);
		philo_print(self, TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(self->left_fork);
		philo_print(self, TAKING_FORK);
		pthread_mutex_lock(self->right_fork);
		philo_print(self, TAKING_FORK);
	
	}
}

