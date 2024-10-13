/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:19:31 by razaccar          #+#    #+#             */
/*   Updated: 2024/10/12 17:19:08 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>

int	philos_init(t_simulation *simulation)
{
	t_philo *philo;
	int		i;

	simulation->forks = malloc(simulation->n_philos * sizeof(pthread_mutex_t));
	if (!simulation->forks)
		return (1);
	i = -1;
	while (++i < simulation->n_philos)
		pthread_mutex_init(&simulation->forks[i], NULL);	
	simulation->philos = malloc(simulation->n_philos * sizeof(t_philo));	
	if (!simulation->philos)
		return (1);
	i = -1;
	while (++i < simulation->n_philos)
	{
		philo = simulation->philos + i;
		philo->id = i + 1;
		philo->left_fork = &simulation->forks[i];
		philo->right_fork = &simulation->forks[(i + 1) % simulation->n_philos];
		philo->meals_eated = 0;
		philo->last_meal_timestamp = 0;
		philo->simulation = simulation;
	}
	return (0);
}

int	simulation_init(t_simulation *simulation, int argc, char **argv)
{
	simulation->n_philos = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atol(argv[2]);
	simulation->time_to_eat = ft_atol(argv[3]);
	simulation->time_to_sleep = ft_atol(argv[4]);
	simulation->is_running = false;
	pthread_mutex_init(&simulation->monitoring, NULL);
	pthread_mutex_init(&simulation->printing, NULL);
	if (argc == 6)
	{
		simulation->n_meals_to_eat = ft_atol(argv[5]);
		if (simulation->n_meals_to_eat <= 0)
			return (1);
	}
	else
		simulation->n_meals_to_eat = -1;
	if (philos_init(simulation) != 0)
		return (2);
	return (0);
}
