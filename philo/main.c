/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:22:58 by ksainte           #+#    #+#             */
/*   Updated: 2024/09/30 12:07:11 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*ft_calloc_philo_array(t_program *program)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * program->philo_count);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < program->philo_count)
	{
		philo[i].own_id = i + 1;
		(*(philo + i)).time_to_die = program->philo_array->time_to_die;
		philo[i].time_to_eat = program->philo_array->time_to_eat;//comme philo est un pointeur de base ,cette notation descend de 2 niveaux, 1 sur l'adresse pointee, l'autre sur les valeurs a cette adresse
		philo[i].time_to_sleep = program->philo_array->time_to_sleep;
		philo[i].num_times_to_eat = program->philo_array->num_times_to_eat;
		(*(philo + i)).program = program;
		// if (i != program->philo_count - 1)
		// 	philo[i].next_right_fork = &philo[i + 1].left_fork;                  OR ONE CAN ALSO WRITE
		if (i != program->philo_count - 1)
			(*(philo + i)).next_right_fork = &(*(philo + i + 1)).left_fork; // left fork est declare tel que pthread_mutex_t left_fork; et on veut choper son adresse, et pas la valeur a cette derniere
		i++;
	}
	philo[i - 1].next_right_fork = &philo[0].left_fork;
	return (philo);
}

void	*thread_routine(void *data)
{
	t_philo	*philo;
	int		dead;

	dead = 0;
	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->program->starting_block);
	pthread_mutex_unlock(&philo->program->starting_block);
	if (philo->own_id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->program->is_dead_mutex);
		dead = philo->program->is_dead;
		pthread_mutex_unlock(&philo->program->is_dead_mutex);
		if (dead == 1)
			break ;
		ft_try_to_eat(philo);
	}
	return (NULL);
}

void	ft_join_threads(t_program *program, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_join(program->philo_array[i].tid, NULL);
		i++;
	}
}

int	ft_launch_philo_threads(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&program->starting_block);
	while (i < program->philo_count)
	{
		if (pthread_create(&program->philo_array[i].tid, NULL, thread_routine,
				(void *)&program->philo_array[i]))
		{
			ft_init_philo_tslm(program, i);
			pthread_mutex_unlock(&program->starting_block);
			pthread_mutex_lock(&program->is_dead_mutex);
			program->is_dead = 1;
			pthread_mutex_unlock(&program->is_dead_mutex);
			ft_join_threads(program, i);
			return (0);
		}
		i++;
	}
	ft_init_philo_tslm(program, program->philo_count);
	pthread_mutex_unlock(&program->starting_block);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_program	program;

	program.is_dead = 0;
	program.eating_count = 0;
	program.philo_array = &philo;
	if (!ft_check_args(argc, argv, &program))
		return (0);
	if (program.philo_count == 1)
		return (ft_program_error(0, &program));
	program.philo_array = ft_calloc_philo_array(&program);
	if (!program.philo_array)
		return (ft_program_error(1, &program));
	if (!ft_init_mutexes(&program))
		return (ft_program_error(2, &program));
	if (!ft_launch_philo_threads(&program))
		return (ft_program_error(3, &program));
	if (!ft_dead_flag(&program))
		ft_join_threads(&program, program.philo_count);
	ft_destroy_mutex(6, &program, program.philo_count);
	return (0);
}
