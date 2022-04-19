/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:59:03 by nwakour           #+#    #+#             */
/*   Updated: 2021/09/11 17:36:05 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define DIE 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define FORK 5

typedef struct s_info
{
	long				nb_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nb_of_times_to_eat;
	long				finished;
	unsigned long long	deca;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		*forks;
}t_info;

typedef struct s_philo
{
	pthread_t			value;
	int					id;
	int					eating;
	int					number_of_times_to_eat;
	pthread_mutex_t		busy;
	unsigned long long	ate;
	unsigned long long	start;
	t_info				*info;
}	t_philo;

						/* PHILO */
int					error_handle(char *error, int ret);
int					print_mutex(t_philo *philo, int to_write,
						unsigned long long time_ms);
int					main_thread(t_info *info, t_philo *philos);
int					creat_threads(t_info *info, pthread_mutex_t *forks);
						/*PARSING*/
int					ft_atoi_err(const char *str, int *len);
int					check_data(long *args, int argc);
int					get_data(long *args, int argc, char **argv);
						/*ROUTINE*/
int					sleep_routine(t_philo *philo);
int					fork_routine(t_philo *philo);
void				*routine(void *param);
						/*TIME*/
void				sleepu(unsigned long long end);
unsigned long long	time_passed(unsigned long long start);
unsigned long long	current_time(void);
						/*INIT*/
t_philo				*creat_philo(pthread_mutex_t *forks, t_info *info);
pthread_mutex_t		*init_forks(int nb_of_froks);

#endif
