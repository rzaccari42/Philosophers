/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:19:05 by razaccar          #+#    #+#             */
/*   Updated: 2024/10/13 04:29:37 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <sys/_pthread/_pthread_mutex_t.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define RST		"\033[0m"
# define B_RED		"\033[1;31m"
# define B_GREEN	"\033[1;32m"
# define B_WHITE	"\033[1;37m"

#define TAKING_FORK "🍴 has taken a fork\n"
#define EATING "🍝 is eating\n"
#define SLEEPING "💤 is sleeping\n"
#define THINKING "🤔 is thinking\n"
#define DEAD "💀 died\n"

typedef struct s_simulation t_simulation;
typedef struct s_philo t_philo;

struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_timestamp;
	int				meals_eated;
	t_simulation	*simulation;
	pthread_t		thread;
};

struct s_simulation
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_meals_to_eat;
	long			start_timestamp;
	bool			is_running;
	pthread_mutex_t	printing;
	pthread_mutex_t	monitoring;
};


/* SIMULATION */
int		simulation_init(t_simulation *self, int argc, char **argv);
void	simulation_free(t_simulation *self);
void	simulation_run(t_simulation *self);
void	simulation_monitor(t_simulation *self);
void	*simulation_routine(void *data);

/* PHILO */
int		philos_init(t_simulation *simulation);
void	philo_take_forks(t_philo *self);
void	philo_eat(t_philo *self);
void	philo_sleep_and_think(t_philo *self);
void	philo_print(t_philo *philo, char *state);

/* MONITOR */
bool	is_running(t_simulation *simulation);
bool	is_someone_starving(t_simulation *simulation);
bool	is_everyone_full(t_simulation *simulation);

/* TIME */
long	get_timestamp(long start_timestamp);
void	ft_usleep(long usecond);

/* UTILS */
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isposnum(char *str);

#endif
