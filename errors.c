/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:12:31 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/17 12:17:11 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ingredients_check(int argc, char **argv, t_info *input)
{
	if (argc != 5 && argc != 6)
		return (error_p("Invalid number of arguments"));
	if (!is_digit(argv))
		return (error_p("We accept only integers"));
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) \
	< 60 || ft_atoi(argv[4]) < 60 || (argc == 6 && ft_atoi(argv[5]) <= 0) || \
	!ft_atoi(argv[1]))
		return (error_p("Invalid arguments"));
	if (!pass_input(argc, argv, input))
		return (error_p("Forks memory allocation failed"));
	if (ft_atoi(argv[1]) == 1)
		return (error_p("Philosopher starved to death. \
		Unable to eat with a fork."));
	return (0);
}

int	pass_input(int argc, char **argv, t_info *input)
{
	input->n_phil = ft_atoi(argv[1]);
	input->t_die = ft_atoi(argv[2]);
	input->t_eat = ft_atoi(argv[3]);
	input->t_sleep = ft_atoi(argv[4]);
	input->n_meals = 0;
	input->meals_flag = 0;
	input->the_end = 0;
	if (argc == 6)
	{
		input->n_meals = ft_atoi(argv[5]);
		input->meals_flag = 1;
	}
	input->forks = malloc(sizeof(pthread_mutex_t) * input->n_phil);
	if (!input->forks)
		return (0);
	return (1);
}

int	error_p(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	clean_table(t_info *in)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&in->print_mutex))
		return (error_p("Mutex is indestructible"));
	while (i < in->n_phil)
	{
		if (pthread_mutex_destroy(&in->forks[i]))
			return (error_p("Adamantine forks"));
		if (pthread_mutex_destroy(&in->phils[i].dead))
			return (error_p("Eating forever is an option"));
		i++;
	}
	free(in->forks);
	free(in->phils);
	return (0);
}
