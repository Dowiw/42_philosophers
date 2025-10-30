#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct	s_fork
{
	bool	fork;
}			t_fork;

typedef struct	s_philosophers
{
	bool		is_alive;
	short		fork_count;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
}				t_philosophers;

/**
 * @brief Data for the philosopher project
 *
 * @param die_ms miliseconds to death in microseconds
 * @param eat_ms miliseconds to eat in microseconds
 * @param sleep_ms miliseconds to sleep in microseconds
 * @param eat_count number of times a philosopher eats
 * @param philo_count number of philosophers
 * @param philo_threads allocated philosopher thread array
 */
typedef struct s_philo_data
{
	__useconds_t	die_ms;
	__useconds_t	eat_ms;
	__useconds_t	sleep_ms;
	unsigned int	eat_count;
	unsigned int	philo_count;
	struct timeval	start_time;
	pthread_mutex_t	*mutex;
	pthread_t		*philo_threads;
	t_philosophers		*philosophers;
}					t_philo_data;

void	init_philosopher(void *arg);

#endif
