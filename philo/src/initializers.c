#include "philosophers.h"

/**
 * @brief Sets each philosopher and assigns forks.
 */
static int	init_philosophers(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].meal_mutex);
			write(STDERR_FILENO, "Error: meal_mutex init failed\n", 30);
			free(data->philos);
			data->philos = NULL;
			return (1);
		}
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		i++;
	}
	return (0);
}

/**
 * @brief Initialize all forks, destroy previous if failed
 */
static int	init_forks(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			write(STDERR_FILENO, "Error: mutex init\n", 24);
			free(data->forks);
			data->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Allocates memory and initializes all mutexes.
 */
int	init_data(t_philo_data *data)
{
	data->dead_flag = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (write(STDERR_FILENO, "Error: print_mutex init fail\n", 30), 1);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (write(STDERR_FILENO, "Error: dead_mutex init fail\n", 29), 1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->philos = malloc(sizeof(t_philosopher) * data->philo_count);
	if (!data->forks || !data->philos)
	{
		delete_data(data);
		return (write(STDERR_FILENO, "Error: malloc failed\n", 22), 1);
	}
	if (init_forks(data) != 0)
		return (delete_data(data), 1);
	if (init_philosophers(data) != 0)
		return (delete_data(data), 1);
	return (0);
}
