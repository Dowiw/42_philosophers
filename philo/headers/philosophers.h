/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:07:27 by kmonjard          #+#    #+#             */
/*   Updated: 2026/04/09 18:07:29 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

struct	s_philo_data;

/**
 * @brief Individual Philosopher Data
 */
typedef struct s_philosopher
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	long				last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
	struct s_philo_data	*data;
}	t_philosopher;

/**
 * @brief Global Program Data
 */
typedef struct s_philo_data
{
	int				philo_count;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				must_eat_count;
	int				dead_flag;
	long			start_time;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philosopher	*philos;
}	t_philo_data;

// --- Function Prototypes ---

// main.c / parsing.c

unsigned int	ft_atoi_u(char *str);
int				parse_args(int ac, char **av, t_philo_data *data);

// initializers.c

int				init_data(t_philo_data *data);

// philosopher.c / simulation

void			*philosopher_routine(void *arg);
void			start_simulation(t_philo_data *data);

// utils.c

long			get_time_in_ms(void);
void			ft_usleep(long milliseconds, t_philo_data *data);
void			print_status(t_philosopher *philo, char *status);
void			delete_data(t_philo_data *data);

#endif
