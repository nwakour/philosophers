/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:42:45 by nwakour           #+#    #+#             */
/*   Updated: 2021/09/11 13:49:25 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*creat_philo(pthread_mutex_t *forks, t_info *info)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * info->nb_of_philos);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < info->nb_of_philos)
	{
		philo[i].info = info;
		philo[i].id = i;
		philo[i].info->forks = forks;
		philo[i].number_of_times_to_eat = info->nb_of_times_to_eat;
		philo[i].eating = 0;
		pthread_mutex_init(&philo[i].busy, NULL);
	}
	return (philo);
}

pthread_mutex_t	*init_forks(int nb_of_froks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_of_froks);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < nb_of_froks)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}
