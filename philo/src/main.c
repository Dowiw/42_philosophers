/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:05:17 by kmonjard          #+#    #+#             */
/*   Updated: 2026/03/31 15:21:57 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Main
 */
int	main(int ac, char **av)
{
	t_philo_data	data;

	if (ac != 5 && ac != 6)
	{
		write(STDERR_FILENO, "Usage: ./philo <no. of philosophers> "
			"<time to die> <time to eat> <time to sleep> "
			"<times philo must eat>\n", 105);
		return (1);
	}
	if (parse_args(ac, av, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (1);
	start_simulation(&data);
	delete_data(&data);
	return (0);
}
