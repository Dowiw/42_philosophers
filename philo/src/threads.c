/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:13:15 by kmonjard          #+#    #+#             */
/*   Updated: 2026/04/09 18:13:16 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Extension of monitor_simulation.
 * Main logic for locking mutexes and checking dead_flag.
 * Modifies full_philos if current one is full.
 */
static int	monitor_each(t_philo_data *data, int *full_philos, int i)
{
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	if (get_time_in_ms() - data->philos[i].last_meal >= data->die_time)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", get_time_in_ms() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		return (1);
	}
	if (data->must_eat_count != -1
		&& data->philos[i].meals_eaten >= data->must_eat_count)
		(*full_philos)++;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (0);
}

/**
 * @brief Monitoring loop that checks for deaths or full bellies.
 * Runs main thread while philosophers eat/sleep/think.
 */
static void	monitor_simulation(t_philo_data *data)
{
	int	i;
	int	full_philos;

	while (1)
	{
		i = 0;
		full_philos = 0;
		while (i < data->philo_count)
		{
			if (monitor_each(data, &full_philos, i) != 0)
				return ;
			i++;
		}
		if (data->must_eat_count != -1 && full_philos == data->philo_count)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return ;
		}
		usleep(1000);
	}
}

/**
 * @brief Launches all threads and starts the main loop.
 */
void	start_simulation(t_philo_data *data)
{
	int	i;

	data->start_time = get_time_in_ms();
	if (data->start_time == -1)
		return ;
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				&philosopher_routine, &data->philos[i]) != 0)
		{
			write(STDERR_FILENO, "Error: pthread_create failed\n", 30);
			return ;
		}
		i++;
	}
	monitor_simulation(data);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
