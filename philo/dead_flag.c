/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:23:25 by ksainte           #+#    #+#             */
/*   Updated: 2024/08/16 13:54:59 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_program_error(int error, t_program *program)
{
	char	*str;

	if (error == 0)
		str = "0 1 is dead\n";
	if (error == 1)
		str = "Failed Allocation!\n";
	if (error == 2)
	{
		str = "Initialization of a mutex failed!\n";
	}
	if (error == 3)
	{
		str = "Thread creation failed!\n";
		ft_destroy_mutex(6, program, program->philo_count);
	}
	write(1, str, ft_strlen(str));
	return (0);
}

int	ft_philos_are_full(t_program *program)
{
	pthread_mutex_lock(&program->is_dead_mutex);
	program->is_dead = 1;
	pthread_mutex_unlock(&program->is_dead_mutex);
	ft_usleep(25);
	return (0);
}

int	ft_a_philo_is_dead(t_program *program, int i)
{
	pthread_mutex_lock(&program->is_dead_mutex);
	program->is_dead = 1;
	pthread_mutex_unlock(&program->is_dead_mutex);
	pthread_mutex_lock(&program->timestamp_mutex);
	program->timestamp = get_current_time() - program->start_time;
	pthread_mutex_unlock(&program->timestamp_mutex);
	pthread_mutex_lock(&program->print_mutex);
	printf("%ld %d died\n", program->timestamp, program->philo_array[i].own_id);
	pthread_mutex_unlock(&program->print_mutex);
	ft_usleep(25);
	return (0);
}

int	ft_dead_flag(t_program *program)
{
	int		i;
	int		eating_count;
	size_t	last_meal;

	eating_count = -1;
	while (1)
	{
		i = 0;
		while (i < program->philo_count)
		{
			pthread_mutex_lock(&program->count_mutex);
			eating_count = program->eating_count;
			pthread_mutex_unlock(&program->count_mutex);
			if (eating_count == program->philo_count)
				return (ft_philos_are_full(program));
			pthread_mutex_lock(&program->last_meal_mutex);
			last_meal = program->philo_array[i].time_since_last_meal;
			pthread_mutex_unlock(&program->last_meal_mutex);
			if (get_current_time()
				- last_meal > program->philo_array[i].time_to_die)
				return (ft_a_philo_is_dead(program, i));
			i++;
		}
	}
	return (1);
}
