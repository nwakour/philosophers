/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 16:02:01 by nwakour           #+#    #+#             */
/*   Updated: 2021/09/11 17:57:13 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handle(char *error, int ret)
{
	printf("%s\n", error);
	return (ret);
}

int	print_mutex(t_philo *philo, int to_write, unsigned long long time_ms)
{
	if (pthread_mutex_lock(&philo->info->write_mutex))
		return (1);
	if (to_write == DIE)
	{
		printf("%llu %d died\n", time_ms, philo->id + 1);
		return (1);
	}
	else if (to_write == EAT)
		printf("%llu %d is eating\n", time_ms, philo->id + 1);
	else if (to_write == SLEEP)
		printf("%llu %d is sleeping\n", time_ms, philo->id + 1);
	else if (to_write == FORK)
		printf("%llu %d has taken a fork\n", time_ms, philo->id + 1);
	else if (to_write == THINK)
		printf("%llu %d is thinking\n", time_ms, philo->id + 1);
	if (pthread_mutex_unlock(&philo->info->write_mutex))
		return (1);
	return (0);
}

int	main_thread(t_info *info, t_philo *philos)
{
	int	i;

	sleepu(philos->start + (5 * philos->info->nb_of_philos));
	while (info->nb_of_times_to_eat != 0
		&& info->finished != info->nb_of_philos)
	{
		i = -1;
		while (++i < info->nb_of_philos)
		{
			if (pthread_mutex_lock(&philos[i].busy))
				return (0);
			if (!philos[i].eating && time_passed(philos[i].ate)
				> (unsigned long long)(info->time_to_die + 5))
			{
				print_mutex(&philos[i], DIE, time_passed(philos[i].start));
				return (1);
			}
			if (pthread_mutex_unlock(&philos[i].busy))
				return (0);
		}
	}
	pthread_mutex_lock(&info->write_mutex);
	return (1);
}

int	creat_threads(t_info *info, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		i;

	if (!forks)
		return (0);
	i = -1;
	pthread_mutex_init(&info->write_mutex, NULL);
	philos = creat_philo(forks, info);
	info->deca = current_time();
	while (++i < info->nb_of_philos)
	{
		philos[i].start = info->deca;
		philos[i].ate = info->deca;
		if (pthread_create(&philos[i].value, NULL, &routine, &philos[i]))
			return (0);
	}
	return (main_thread(info, philos));
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (argc != 5 && argc != 6)
		return (error_handle("wrong number of args", 1));
	if (!get_data((long *)info, argc, argv))
		return (error_handle("wrong args", 1));
	if (!creat_threads(info, init_forks(info->nb_of_philos)))
		return (error_handle("Error", 1));
	return (0);
}
