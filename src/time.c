/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:41:41 by razaccar          #+#    #+#             */
/*   Updated: 2024/10/14 14:17:06 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static long	get_diff(struct timeval *start)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - start->tv_sec) * 1000000;
	diff += now.tv_usec - start->tv_usec;
	return (diff);
}

void	ft_usleep(long useconds)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (get_diff(&start) < useconds)
		usleep(150);
}

long	get_timestamp(long start_timestamp)
{
	long long		ms_timestamp;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms_timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (!start_timestamp)
		return (ms_timestamp);
	return (ms_timestamp - start_timestamp);
}
