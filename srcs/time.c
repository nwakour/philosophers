/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:40:46 by nwakour           #+#    #+#             */
/*   Updated: 2021/09/11 13:46:51 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	time_passed(unsigned long long start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (((end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000))
		- start);
}

unsigned long long	current_time(void)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (((end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000)));
}

void	sleepu(unsigned long long end)
{
	while (current_time() < end)
		usleep(10);
}
