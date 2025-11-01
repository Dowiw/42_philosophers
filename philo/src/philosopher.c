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
 * - Checks all philosophers if alive
 */
int	all_alive(t_philo_data	*data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->philosophers->philo_mutex);
		if (!data->philosophers[i].is_alive)
		{
			pthread_mutex_unlock(&data->philosophers->philo_mutex);
			return (false);
		}
		pthread_mutex_unlock(&data->philosophers->philo_mutex);
		i++;
	}
	return (true);
}

/**
 * - Optimize things once spotted
 */
void	philo_eat(t_philosophers *philo)
{
	struct timeval	time_passed;
	struct timeval	time;

	gettimeofday(&time, NULL);
	while ((philo->is_alive && all_alive(philo->data)) || (!(philo->has_eaten) && philo->is_alive))
	{
		gettimeofday(&time_passed, NULL);
		if (get_ms(time_passed) - get_ms(time) > (long)philo->data->die_ms)
		{
			printf("[%lu] Philosopher %u is dead\n", get_ms(time), philo->id);
			pthread_mutex_lock(&philo->philo_mutex);
			philo->is_alive = false;
			pthread_mutex_unlock(&philo->philo_mutex);
		}
		if (philo->fork_count != 2 && all_alive(philo->data))
		{
			pthread_mutex_lock(&philo->left_fork->mutex);
			if (philo->left_fork->fork == true)
			{
				gettimeofday(&time_passed, NULL); // add return check
				printf("[%lu] Philosopher %u has taken a fork\n", get_ms(time_passed), philo->id);
				philo->left_fork->fork = false;
				philo->fork_count++;
			}
			pthread_mutex_unlock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex);
			if (philo->right_fork->fork == true)
			{
				gettimeofday(&time_passed, NULL); // add return check
				printf("[%lu] Philosopher %u has taken a fork\n", get_ms(time_passed), philo->id);
				philo->right_fork->fork = false;
				philo->fork_count++;
			}
			pthread_mutex_unlock(&philo->right_fork->mutex);
		}
		if (philo->fork_count == 2 && all_alive(philo->data))
		{
			gettimeofday(&time_passed, NULL); // add return check
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("[%lu] Philosopher %u is eating\n", get_ms(time_passed), philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex); // locking print
			usleep(philo->data->eat_ms);
			philo->has_eaten = true;
			pthread_mutex_lock(&philo->left_fork->mutex); // lock left fork for return
			philo->left_fork->fork = true;
			pthread_mutex_unlock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex); // lock right fork for return
			philo->right_fork->fork = true;
			pthread_mutex_unlock(&philo->right_fork->mutex);
			printf("[%lu] Philosopher %u is done eating.\n", get_ms(time_passed), philo->id);
			philo->fork_count = 0;
		}
	}
	if (philo->fork_count > 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->fork = true;
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->fork = true;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		philo->fork_count = 0;
		printf("[%lu] Philosopher %u is done eating.\n", get_ms(time_passed), philo->id);
	}
}

/**
 *
 */
void	philo_sleep(t_philosophers *philo)
{
	struct timeval time;

	while (philo->has_eaten && philo->is_alive && all_alive(philo->data))
	{
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("[%lu] Philosopher %u is sleeping\n", get_ms(time), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		usleep(philo->data->sleep_ms);
		philo->has_eaten = false;
	}
}

/**
 * - For now use some inefficient way to retrieve data
 * to figure out required struct
 */
void	*init_philosopher(void *arg)
{
	unsigned int	i;
	t_philosophers	*philo;

	i = 0;
	philo = (t_philosophers *)arg;
	while (i < philo->data->eat_count && philo->is_alive && all_alive(philo->data))
	{
		philo_eat(philo);
		philo_sleep(philo);
		i++;
	}
	return (NULL);
}
