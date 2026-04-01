/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:05:17 by kmonjard          #+#    #+#             */
/*   Updated: 2026/03/31 15:21:57 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		num *= (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}


/**
 * - Converts milisecond values to correct microsecond values
 */
int	parse_args(int ac, char **av, t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!is_numeric(av[i]))
		{
			return (write(STDERR_FILENO, "Error: Argument '%s' is not"
			"a valid positive integer.\n", av[i]), 1);
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

/**
 * @brief Main
 */
int	main(int ac, char **av)
{
	t_philo_data	data;

	if (ac != 5 && ac != 6)
	{
		write(STDERR_FILENO, "Usage: ./philo <no. of philosophers> "
			"<time to die> <time to eat> <time to sleep> "
			"<times philo must eat>\n", 105);
		return (1);
	}
	if (parse_args(ac, av, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (1);
	start_simulation(&data);
	delete_data(&data);
	return (0);
}
