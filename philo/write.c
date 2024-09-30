/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:23:51 by ksainte           #+#    #+#             */
/*   Updated: 2024/08/16 13:55:14 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_philo_tslm(t_program *program, int philo_count)
{
	int	i;

	program->start_time = get_current_time();
	i = 0;
	while (i < philo_count)
	{
		program->philo_array[i].time_since_last_meal = program->start_time;
		i++;
	}
}

void	ft_write_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->is_dead_mutex);
	if (!philo->program->is_dead)
	{
		pthread_mutex_lock(&philo->program->timestamp_mutex);
		philo->program->timestamp = get_current_time()
			- philo->program->start_time;
		pthread_mutex_unlock(&philo->program->timestamp_mutex);
		pthread_mutex_lock(&philo->program->print_mutex);
		printf("%ld %d has taken a fork\n", philo->program->timestamp,
			philo->own_id);
		pthread_mutex_unlock(&philo->program->print_mutex);
	}
	pthread_mutex_unlock(&philo->program->is_dead_mutex);
}

void	ft_write_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->is_dead_mutex);
	if (!philo->program->is_dead)
	{
		pthread_mutex_lock(&philo->program->timestamp_mutex);
		philo->program->timestamp = get_current_time()
			- philo->program->start_time;
		pthread_mutex_unlock(&philo->program->timestamp_mutex);
		pthread_mutex_lock(&philo->program->print_mutex);
		printf("%ld %d is eating\n", philo->program->timestamp, philo->own_id);
		pthread_mutex_unlock(&philo->program->print_mutex);
	}
	pthread_mutex_unlock(&philo->program->is_dead_mutex);
}

void	ft_write_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->is_dead_mutex);
	if (!philo->program->is_dead)
	{
		pthread_mutex_lock(&philo->program->timestamp_mutex);
		philo->program->timestamp = get_current_time()
			- philo->program->start_time;
		pthread_mutex_unlock(&philo->program->timestamp_mutex);
		pthread_mutex_lock(&philo->program->print_mutex);
		printf("%ld %d is sleeping\n", philo->program->timestamp,
			philo->own_id);
		pthread_mutex_unlock(&philo->program->print_mutex);
	}
	pthread_mutex_unlock(&philo->program->is_dead_mutex);
}
