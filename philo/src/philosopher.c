/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:55:23 by kmonjard          #+#    #+#             */
/*   Updated: 2025/08/20 21:56:32 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Safely checks if the simulation should stop.
 */
int	check_dead(t_philo_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->dead_mutex);
	stop = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	return (stop);
}

static void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->philo_count == 1)
	{
		ft_usleep(philo->data->die_time, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	print_status(philo, "is eating");
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->eat_time, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);

	while (!check_dead(philo->data))
	{
		philo_eat(philo);
		if (philo->data->must_eat_count != -1 &&
			philo->meals_eaten >= philo->data->must_eat_count)
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->sleep_time, philo->data);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
