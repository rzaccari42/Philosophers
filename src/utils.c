/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:34:12 by razaccar          #+#    #+#             */
/*   Updated: 2024/10/07 16:38:38 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sys/_types/_timeval.h>
#include <sys/time.h>

long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str - 48;
		str++;
	}
	return (nbr);
}

int	ft_atoi(const char *str)
{
	int	nbr;

	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str - 48;
		str++;
	}
	return (nbr);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int ft_isposnum(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}
