/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_destroy_mutexes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:23:18 by ksainte           #+#    #+#             */
/*   Updated: 2024/08/16 13:55:02 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_destroy_mutex(int index, t_program *program, int fork_index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&program->mutex_array[i]);
		i++;
	}
	i = 0;
	while (i < fork_index)
	{
		pthread_mutex_destroy(&program->philo_array[i].left_fork);
		i++;
	}
	free(program->philo_array);
	return (0);
}

int	ft_init_fork_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		if (pthread_mutex_init(&program->philo_array[i].left_fork, NULL))
			return (ft_destroy_mutex(6, program, i));
		i++;
	}
	return (1);
}

int	ft_init_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->starting_block, NULL))
		return (ft_destroy_mutex(0, program, 0));
	program->mutex_array[0] = program->starting_block;
	if (pthread_mutex_init(&program->count_mutex, NULL))
		return (ft_destroy_mutex(1, program, 0));
	program->mutex_array[1] = program->count_mutex;
	if (pthread_mutex_init(&program->timestamp_mutex, NULL))
		return (ft_destroy_mutex(2, program, 0));
	program->mutex_array[2] = program->timestamp_mutex;
	if (pthread_mutex_init(&program->last_meal_mutex, NULL))
		return (ft_destroy_mutex(3, program, 0));
	program->mutex_array[3] = program->last_meal_mutex;
	if (pthread_mutex_init(&program->is_dead_mutex, NULL))
		return (ft_destroy_mutex(4, program, 0));
	program->mutex_array[4] = program->is_dead_mutex;
	if (pthread_mutex_init(&program->print_mutex, NULL))
		return (ft_destroy_mutex(5, program, 0));
	program->mutex_array[5] = program->print_mutex;
	return (ft_init_fork_mutexes(program));
}
