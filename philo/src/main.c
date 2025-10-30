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
	data->die_ms = 1000 * ft_atoi_u(av[2]);
	data->eat_ms = 1000 * ft_atoi_u(av[3]);
	data->sleep_ms = 1000 * ft_atoi_u(av[4]);
	if (av[5])
		data->eat_count = ft_atoi_u(av[5]);
	else
		data->eat_count = 0;
	printf("die: %u eat: %u sleep: %u, eat_count: %u\n", data->die_ms, data->eat_ms, data->sleep_ms, data->eat_count);
	return (0);
}

/**
 *
 */
void	start_thinking(t_philo_data *data)
{
	unsigned int	i;
	struct timeval	time;

	i = 0;
	if (gettimeofday(&time, NULL) > 0)
		error_and_exit("Error: gettimeofday failed.");
	data->start_time = time;
	// while (i < data->philo_count)
	// {
	// 	pthread_create(data->philo_threads[i], NULL, init_philosopher, (void *)data);
	// 	i++;
	// }
}

void	init_philosophers(t_philo_data *data, t_philosophers *philos)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_count)
	{
		philos[i].is_alive = true;
		philos[i].fork_count = 0;
		philos[i].left_fork = malloc(sizeof(t_fork));
		if (!philos[i].left_fork)
			printf("Error: malloc left_fork\n"); // to fix for allocating all
		if (i == 0 && data->philo_count > 1)
		{
			philos[data->philo_count].right_fork = philos[i].left_fork;
			philos[data->philo_count].right_fork->fork = true;
		}
		else
		{
			philos[i - 1].right_fork = philos[i].left_fork;
			philos[i - 1].right_fork->fork = true;
		}
		if (i == 0 && data->philo_count > 1) // to remove
			printf("philo %u: left: %p, last: %p\n", i, (void *)philos[i].left_fork, (void *)philos[data->philo_count].right_fork);
		else
			printf("philo %u: right %u: %p, left: %p\n", i, i - 1, (void *)philos[i - 1].right_fork, (void *)philos[i].left_fork);
		i++;
	}
}

void	init_data(t_philo_data *data, pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		error_and_exit("Error: pthread_mutex_init failed.");
	data->mutex = mutex;
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
	pthread_mutex_t	mutex;
	t_philo_data	data;

	if (ac == 5 || ac == 6)
		parse_args(av, &data);
	else
		print_usage();
	init_data(&data, &mutex);
	start_thinking(&data);
	return (0);
}

