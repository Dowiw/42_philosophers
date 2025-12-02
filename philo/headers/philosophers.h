#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

#  define UINT_MAX 4294967295

/**
 * @brief Data for a philosopher
 *
 * @param dead_bool boolean for all threads
 * @param id philosopher id
 * @param meals_to_finish meals to finish if set
 * @param meals_eaten meals completed
 * @param print_mutex mutex to print
 * @param eat_mutex mutex to eat
 * @param dead_mutex mutex to die
 * @param right_fork the right fork
 * @param left_fork the left fork
 */
typedef struct	s_philosophers
{
	int				*dead_bool;
	unsigned int	id;
	unsigned int	meals_to_finish;
	unsigned int	meals_eaten;
	__useconds_t	die_ms;
	__useconds_t	eat_ms;
	__useconds_t	sleep_ms;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philosophers;

/**
 * @brief Data for the philosopher project
 *
 * @param dead_bool bool if anyone diea
 * @param die_ms miliseconds to die if hungry (microseconds)
 * @param eat_ms miliseconds it takes to eat in microseconds
 * @param sleep_ms miliseconds it takes to sleep in microseconds
 * @param eat_count number of times a philosopher eats
 * @param philo_count number of philosophers
 * @param philo_threads allocated philosopher thread array
 */
typedef struct s_philo_data
{
	int				dead_bool;
	//
	unsigned int	philo_count;
	unsigned int	eat_count;
	__useconds_t	die_ms;
	__useconds_t	eat_ms;
	__useconds_t	sleep_ms;
	//
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_t		*philo_threads;
	t_philosophers	*philosophers;
}					t_philo_data;

// initializers.c
int	init_data(t_philo_data *data);

// parsing.c

void	parse_args(char **av, t_philo_data *data);

// utils.c

void	delete_data(t_philo_data *data);

#endif
