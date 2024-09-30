/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:23:44 by ksainte           #+#    #+#             */
/*   Updated: 2024/08/16 13:55:11 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	ft_print_arguments(t_program *program)
{
	printf("Philo threads Execution\n");
	printf("Time to die is is %zu\n", program->philo_array->time_to_die);
	printf("Time to eat is is %zu\n", program->philo_array->time_to_eat);
	printf("Time to sleep is is %zu\n", program->philo_array->time_to_sleep);
	printf("Number of times to eat is %d\n",
		program->philo_array->num_times_to_eat);
}

int	ft_isdigit(int c)
{
	if (c >= (int)48 && c <= (int)57)
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
