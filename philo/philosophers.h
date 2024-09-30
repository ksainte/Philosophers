/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:33:36 by ksainte           #+#    #+#             */
/*   Updated: 2024/08/16 13:55:08 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int					nb;
	int					mod;
	int					min;
	int					max;
}						t_args;

typedef struct s_philo
{
	int					own_id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					num_times_to_eat;
	pthread_t			tid;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*next_right_fork;
	struct s_program	*program;
	size_t				time_since_last_meal;
}						t_philo;

typedef struct s_program
{
	struct s_philo		*philo_array;
	int					philo_count;
	pthread_mutex_t		starting_block;
	pthread_mutex_t		timestamp_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		is_dead_mutex;
	pthread_mutex_t		print_mutex;
	size_t				start_time;
	size_t				current_time;
	size_t				timestamp;
	int					is_dead;
	int					eating_count;
	pthread_mutex_t		count_mutex;
	pthread_mutex_t		mutex_array[6];
}						t_program;

int						ft_isdigit(int c);
void					ft_init_philo_tslm(t_program *program, int philo_count);
size_t					get_current_time(void);
int						ft_usleep(size_t milliseconds);
void					ft_try_to_eat(t_philo *philo);
void					ft_think(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					ft_eat(t_philo *philo);
void					ft_print_arguments(t_program *program);
int						ft_destroy_mutex(int index, t_program *program,
							int fork_index);
int						ft_init_fork_mutexes(t_program *program);
int						ft_init_mutexes(t_program *program);
int						ft_philos_are_full(t_program *program);
int						ft_a_philo_is_dead(t_program *program, int i);
int						ft_dead_flag(t_program *program);
int						ft_destroy_mutex(int index, t_program *program,
							int fork_index);
int						ft_check_args(int argc, char **argv,
							t_program *program);
int						ft_strlen(char *str);
int						ft_program_error(int error, t_program *program);
size_t					get_current_time(void);
int						ft_usleep(size_t milliseconds);
void					ft_write_fork(t_philo *philo);
void					ft_write_eat(t_philo *philo);
void					ft_write_sleep(t_philo *philo);

#endif