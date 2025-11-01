#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

struct s_philo_data;
typedef struct s_philo_data t_philo_data;

typedef struct	s_fork
{
	bool			fork;
	pthread_mutex_t	mutex;
}			t_fork;

/**
 * @brief Data for a philosopher
 *
 * @param id philosopher id
 * @param is_alive boolean of the philosopher being alive (default: true)
 * @param fork_count current fork on hand (default: 0)
 * @param left_fork pointer to shared left fork
 * @param right_fork pointer to shared right fork
 * @param data pointer to general data
 */
typedef struct	s_philosophers
{
	unsigned int	id;
	bool			is_alive;
	bool			has_eaten;
	short			fork_count;
	pthread_mutex_t	philo_mutex; // test
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_philo_data	*data;
}					t_philosophers;

/**
 * @brief Data for the philosopher project
 *
 * @param die_ms miliseconds to die if hungry (microseconds)
 * @param eat_ms miliseconds it takes to eat in microseconds
 * @param sleep_ms miliseconds it takes to sleep in microseconds
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
	struct timeval	start_timeval;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_t		*philo_threads;
	t_philosophers	*philosophers;
}					t_philo_data;

void	*init_philosopher(void *arg);

long	get_ms(struct timeval time);

#endif
