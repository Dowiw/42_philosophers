/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:13:51 by kmonjard          #+#    #+#             */
/*   Updated: 2026/04/09 18:13:52 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

/**
 * @brief Checks if a string contains digits.
 * @return 1 if all numeric, 0 otherwise.
 */
static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Convert string to long.
 * @return Long form of the string.
 */
static long	ft_atol(char *str)
{
	long	num;

	num = 0;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

/**
 * @brief Parse the given arguments into data inside the struct.
 */
int	parse_args(int ac, char **av, t_philo_data *data)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (!is_numeric(av[i]))
		{
			return (write(STDERR_FILENO, "Error: Argument is not"
					"a valid positive integer.\n", 49), 1);
		}
		i++;
	}
	data->philo_count = (int)ft_atol(av[1]);
	data->die_time = ft_atol(av[2]);
	data->eat_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	if (ac == 6)
		data->must_eat_count = (int)ft_atol(av[5]);
	else
		data->must_eat_count = -1;
	return (0);
}
