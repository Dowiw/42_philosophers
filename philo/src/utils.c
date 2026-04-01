#include "philosophers.h"
#include <sys/time.h>

/**
 * @brief Prints the status in a thread-safe way.
 * Prevents further messages if one is dead.
 */
void	print_status(t_philosopher *philo, char *status)
{
	t_philo_data	*data;
	long			time;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead_flag)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->dead_mutex);
	time = get_time_in_ms() - data->start_time;
	printf("%ld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&data->print_mutex);
}

/**
 * @brief Precise sleep function.
 * Sleeps in small increments while checking current time.
 * Fixes oversleep due to OS scheduling.
 */
void	ft_usleep(long milliseconds, t_philo_data *data)
{
	long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < milliseconds)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead_flag)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		usleep(500);
	}
}

/**
 * @brief Gets the current time of day in milliseconds.
 * @return The time in ms as a long.
 */
long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (write(2, "Error: gettimeofday()\n", 23), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief Safely destroys all mutexes and frees all allocated memory.
 * Checks NULL for partial initialization failures.
 */
void	delete_data(t_philo_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	if (data->philos)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
			i++;
		}
		free(data->philos);
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
}
