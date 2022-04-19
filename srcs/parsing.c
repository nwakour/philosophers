/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwakour <nwakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 15:58:27 by nwakour           #+#    #+#             */
/*   Updated: 2021/09/11 17:39:19 by nwakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi_err(const char *str, int *len)
{
	long long	i;
	long long	sum;
	int			sign;

	i = 0;
	sum = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		sum = (sum * 10) + str[i++] - '0';
	if (sum * sign > INT_MAX || sum * sign < INT_MIN || i > 12
		|| i == 0 || !ft_isdigit(str[i - 1]) || str[i] != '\0')
		return (*len = -1);
	*len = i;
	return (sign * sum);
}

int	check_data(long *args, int argc)
{
	if (args[0] > 200 || args[0] <= 0
		|| args[1] < 60 || args[2] < 60
		|| args[3] < 60)
		return (0);
	if (argc == 6 && args[4] < 0)
		return (0);
	return (1);
}

int	get_data(long *args, int argc, char **argv)
{
	int	i;
	int	ret;

	i = 0;
	while (++i < argc)
	{
		args[i - 1] = ft_atoi_err(argv[i], &ret);
		if (ret == -1)
			return (0);
	}
	if (argc == 5)
		args[4] = -1;
	args[5] = 0;
	if (!check_data(args, argc))
		return (0);
	return (1);
}
