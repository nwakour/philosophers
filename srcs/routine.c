/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:41:42 by nwakour           #+#    #+#             */
/*   Updated: 2021/09/11 17:57:28 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->busy))
		return (1);
	philo->ate = current_time();
	if (pthread_mutex_unlock(&philo->busy))
		return (1);
	philo->eating = 1;
	if (print_mutex(philo, EAT, time_passed(philo->start)))
		return (1);
	usleep((philo->info->time_to_eat * 1000) - 10000);
	sleepu(philo->ate + philo->info->time_to_eat);
	if (pthread_mutex_lock(&philo->busy))
		return (1);
	philo->eating = 0;
	if (pthread_mutex_unlock(&philo->busy))
		return (1);
	return (0);
}

int	fork_routine(t_philo *philo)
{
	int	left;
	int	right;

	if (philo->id % 2 == 0)
		right = (philo->id + 1) % (philo->info->nb_of_philos);
	else
		right = philo->id;
	if (philo->id % 2 == 0)
		left = philo->id;
	else
		left = (philo->id + 1) % (philo->info->nb_of_philos);
	if (pthread_mutex_lock(&philo->info->forks[left])
		|| print_mutex(philo, FORK, time_passed(philo->start)))
		return (1);
	if (pthread_mutex_lock(&philo->info->forks[right])
		|| print_mutex(philo, FORK, time_passed(philo->start)))
		return (1);
	if (sleep_routine(philo)
		|| pthread_mutex_unlock(&philo->info->forks[left])
		|| pthread_mutex_unlock(&philo->info->forks[right]))
		return (1);
	return (0);
}

void	*routine(void *param)
{
	unsigned long long	to_sleep;
	t_philo				*philo;

	philo = (t_philo *)param;
	if (philo == NULL || philo->info->nb_of_times_to_eat == 0)
		return (NULL);
	sleepu(philo->start + (5 * philo->info->nb_of_philos));
	philo->ate += (5 * philo->info->nb_of_philos);
	philo->start = philo->ate;
	while (1)
	{
		if (fork_routine(philo))
			return (NULL);
		if (philo->number_of_times_to_eat > 0
			&& !(--philo->number_of_times_to_eat))
			philo->info->finished++;
		if (print_mutex(philo, SLEEP, time_passed(philo->start)))
			return (NULL);
		to_sleep = current_time();
		usleep((philo->info->time_to_sleep * 1000) - 10000);
		sleepu(to_sleep + philo->info->time_to_sleep);
		if (print_mutex(philo, THINK, time_passed(philo->start)))
			return (NULL);
	}
	return (NULL);
}
