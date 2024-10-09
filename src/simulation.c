/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:42:22 by razaccar          #+#    #+#             */
/*   Updated: 2024/10/08 20:52:21 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void	simulation_free(t_simulation *self)
{
	int	i;

	free(self->philos);
	i = -1;
	while (++i < self->n_philos)
		pthread_mutex_destroy(&self->forks[i]);
	free(self->forks);
}

void	simulation_monitor(t_simulation *self)
{
	while (is_running(self))
	{
		if (is_someone_starving(self))
		{
			self->is_running = false;
			break ;
		}
		if (self->n_meals_to_eat >= 0)
		{
			if (is_everyone_full(self))
			{
				self->is_running = false;
				break ;
			}
		}
	}
}

void	*simulation_routine(void *data)
{
	t_philo	*self;

	self = (t_philo *)data;
	while (1)
	{
		philo_take_forks(self);
		philo_eat(self);
		philo_sleep_and_think(self);
	}
	return (NULL);
}

void	simulation_run(t_simulation *self)
{
	t_philo	*philo;
	int		i;

	i = -1;
	self->start_timestamp = get_timestamp(0);
	self->is_running = true;
	while (++i < self->n_philos)
	{
		philo = self->philos + i;
		pthread_create(&philo->thread, NULL, simulation_routine, (void *)philo);
	}
	simulation_monitor(self);
	i = -1;
	while (++i < self->n_philos)
		pthread_detach(self->philos[i].thread);
}

