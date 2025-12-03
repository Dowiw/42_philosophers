#include "philosophers.h"

/**
 *
 */
static int assign_forks(t_philo_data *data)
{
	unsigned int	i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!forks)
	{
		delete_data(data);
		write(2, "Error: forks malloc\n", 21);
		return (1);
	}
	i = 0;
	if (data->philo_count == 1)
	{
		data->philosophers[i].left_fork = &forks[i];
		data->philosophers[i].right_fork = NULL;
		return (0);
	}
	while (i < data->philo_count)
	{
		data->philosophers[i].left_fork = &forks[i];
		data->philosophers[i].right_fork = &forks[(i + 1) % data->philo_count];
		i++;
	}
	return (0);
}

/**
 *
 */
static int	init_philo(t_philo_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philosophers[i].dead_bool = &data->dead_bool;
		data->philosophers[i].id = i;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].meals_to_finish = data->eat_count;
		data->philosophers[i].die_ms = data->die_ms;
		data->philosophers[i].eat_ms = data->eat_ms;
		data->philosophers[i].sleep_ms = data->sleep_ms;
		data->philosophers[i].print_mutex = &data->print_mutex;
		data->philosophers[i].eat_mutex = &data->eat_mutex;
		data->philosophers[i].dead_mutex = &data->dead_mutex;
		i++;
	}
	return (assign_forks(data));
}

/**
 *
 */
static int	malloc_philo(t_philo_data *data)
{
	data->philo_threads = malloc(sizeof(pthread_t) * data->philo_count);
	if (!data->philo_threads)
	{
		delete_data(data);
		write(STDERR_FILENO, "Error: philo_threads malloc\n", 29);
		return (1);
	}
	data->philosophers = malloc(sizeof(t_philosopher) * data->philo_count);
	if (!data->philo_count)
	{
		delete_data(data);
		write(STDERR_FILENO, "Error: philosophers malloc\n", 28);
		return (1);
	}
	return (init_philo(data));
}

/**
 * 
 */
int	init_data(t_philo_data *data)
{
	data->dead_bool = 0;
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		write(STDERR_FILENO, "Error: dead_mutex init\n", 24);
		return (1);
	}
	if (pthread_mutex_init(&data->eat_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->dead_mutex);
		write(STDERR_FILENO, "Error: eat_mutex init\n", 23);
		return (1);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		delete_data(data);
		write(STDERR_FILENO, "Error: print_mutex init\n", 25);
		return (1);
	}
	return (malloc_philo(data));
}
