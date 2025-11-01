/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:05:17 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/20 19:06:32 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Convert string to unsigned int. Exits like atoi(3).
 *
 * @param str string to convert into unsigned int
 * @return unsigned int form of the string
 */
unsigned int	ft_atoi_u(char *str)
{
	unsigned int	num;

	num = 0;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num);
}

/**
 * - Prints err string with newline
 * - Exits with failure
 */
void	error_and_exit(char *err)
{
	printf("%s\n", err);
	exit(EXIT_FAILURE);
}

/**
 *
 */
void	print_usage(void)
{
	printf("Usage: ./philo <no. of philosophers> <time to die> <time to eat> <time to sleep> <times philo must eat>\n");
	exit(EXIT_FAILURE);
}

/**
 * - Converts milisecond values to correct microsecond values
 */
int	parse_args(char **av, t_philo_data *data)
{
	printf("Philo count: %s\n", av[1]);
	data->philo_count = ft_atoi_u(av[1]);
	data->die_ms = ft_atoi_u(av[2]);
	data->eat_ms = ft_atoi_u(av[3]);
	data->sleep_ms = ft_atoi_u(av[4]);
	if (av[5])
		data->eat_count = ft_atoi_u(av[5]);
	else
		data->eat_count = UINT_MAX;
	printf("die: %u eat: %u sleep: %u, eat_count: %u\n", data->die_ms, data->eat_ms, data->sleep_ms, data->eat_count);
	return (0);
}

/**
 *
 */
void	start_thinking(t_philo_data *data, t_philosophers *philo)
{
	unsigned int	i;
	struct timeval	time;

	i = 0;
	if (gettimeofday(&time, NULL) > 0)
		error_and_exit("Error: gettimeofday failed.");
	data->start_timeval = time;
	data->start_time = get_ms(time);
	while (i < data->philo_count)
	{
		pthread_create(&data->philo_threads[i], NULL, init_philosopher, (void *)&philo[i]); // add return val check
		i++;
	}
}

void	init_philosophers(t_philo_data *data, t_philosophers *philos)
{
	t_fork			*forks;
	unsigned int	i;

	forks = malloc(sizeof(t_fork) * data->philo_count); // add error check
	i = 0;
	while (i < data->philo_count)
	{
		forks[i].fork = true;
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
			error_and_exit("Error: fork mutex init failed.");
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].is_alive = true;
		philos[i].has_eaten = false;
		philos[i].fork_count = 0;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->philo_count];
		philos[i].data = data;
		pthread_mutex_init(&philos[i].philo_mutex, NULL);
		i++;
	}
	printf("Initializing philosophers done.\n"); // to remove
}

void	init_data(t_philo_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		error_and_exit("Error: pthread_mutex_init failed.");
	data->philo_threads = malloc(sizeof(pthread_t) * data->philo_count);
	if (!data->philo_threads)
		error_and_exit("Error: philo_threads malloc failed.");
	data->philosophers = malloc(sizeof(t_philosophers) * data->philo_count);
	if (!data->philosophers) // add free philo_threads
		error_and_exit("Error: philosophers malloc failed.");
	init_philosophers(data, data->philosophers);
}

/**
 *
 */
int	main(int ac, char **av)
{
	t_philo_data	data;

	if (ac == 5 || ac == 6)
		parse_args(av, &data);
	else
		print_usage();
	init_data(&data);
	start_thinking(&data, data.philosophers);
	// join threads and destroy mutexes at the end.
	return (0);
}

