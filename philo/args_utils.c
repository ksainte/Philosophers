/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:23:31 by ksainte           #+#    #+#             */
/*   Updated: 2024/09/30 12:09:15 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str, t_args *args)
{
	args->nb = 0;
	args->mod = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			args->mod *= -1;
		str++;
	}
	if (!*str)
		return (2147483648);
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (2147483648);
		args->nb = args->nb * 10 + (*str - 48);
		str++;
	}
	if ((args->mod * args->nb) > args->max || (args->mod
			* args->nb) < args->min)
		return (2147483648);
	return (args->mod * args->nb);
}

void	ft_fill_variables(int i, int nb, t_program *program)
{
	if (i == 1)
		program->philo_count = nb;
	if (i == 2)
		program->philo_array->time_to_die = nb;
	if (i == 3)
		program->philo_array->time_to_eat = nb;
	if (i == 4)
		program->philo_array->time_to_sleep = nb;
	if (i == 5)
		program->philo_array->num_times_to_eat = nb;
}

void	ft_change_args_range(int i, t_args *args)
{
	if (i == 1)
	{
		args->max = 200;
		args->min = 1;
	}
	if (i == 2)
	{
		args->max = 60000;
		args->min = 60;
	}
	if (i == 3)
	{
		args->max = 60000;
		args->min = 60;
	}
	if (i == 4)
	{
		args->max = 60000;
		args->min = 60;
	}
	if (i == 5)
	{
		args->max = 100;
		args->min = 1;
	}
}

int	ft_is_valid_number(char **argv, int argc, t_program *program)
{
	int		i;
	long	nb;
	t_args	args;

	i = 1;
	args.min = 1;
	while (i < argc)
	{
		ft_change_args_range(i, &args);
		nb = ft_atoi(argv[i], &args);
		if (nb == 2147483648)
			return (0);
		ft_fill_variables(i, nb, program);
		i++;
	}
	if (argc == 5)
		program->philo_array->num_times_to_eat = -1;
	return (1);
}

int	ft_check_args(int argc, char **argv, t_program *program)
{
	if (argc != 5 && argc != 6)
	{
		write(1, "There should be 5 or at most 6 arguments!\n", 43);
		return (0);
	}
	if (!ft_is_valid_number(argv, argc, program))
	{
		write(1, "Args not in the valid range, or is not a digit!\n", 48);
		return (0);
	}
	return (1);
}
