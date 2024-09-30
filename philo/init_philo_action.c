/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:23:12 by ksainte           #+#    #+#             */
/*   Updated: 2024/08/16 13:55:05 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->last_meal_mutex);
	philo->time_since_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->program->last_meal_mutex);
	ft_write_eat(philo);
	ft_usleep(philo->time_to_eat);
	if (philo->num_times_to_eat != -1)
		philo->num_times_to_eat--;
	if (philo->num_times_to_eat == 0)
	{
		pthread_mutex_lock(&philo->program->count_mutex);
		philo->program->eating_count++;
		pthread_mutex_unlock(&philo->program->count_mutex);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->next_right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_write_sleep(philo);
	ft_usleep(philo->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->is_dead_mutex);
	if (!philo->program->is_dead)
	{
		pthread_mutex_lock(&philo->program->timestamp_mutex);
		philo->program->timestamp = get_current_time()
			- philo->program->start_time;
		pthread_mutex_unlock(&philo->program->timestamp_mutex);
		pthread_mutex_lock(&philo->program->print_mutex);
		printf("%ld %d is thinking\n", philo->program->timestamp,
			philo->own_id);
		pthread_mutex_unlock(&philo->program->print_mutex);
	}
	pthread_mutex_unlock(&philo->program->is_dead_mutex);
}

void	ft_try_to_eat(t_philo *philo)
{
	ft_think(philo);
	pthread_mutex_lock(&philo->left_fork);
	ft_write_fork(philo);
	pthread_mutex_lock(philo->next_right_fork);
	ft_write_fork(philo);
	ft_eat(philo);
	ft_sleep(philo);
}
