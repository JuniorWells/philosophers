/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:12:31 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/16 21:03:23 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_check(int argc, char **argv, t_info *input)
{
	if (argc != 5 && argc != 6)
		return (error_p("Invalid number of arguments"));
	if (!is_digit(argv))
		return (error_p("We accept only integers"));
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) \
	< 60 || ft_atoi(argv[4]) < 60 || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (error_p("Invalid arguments"));
	if (!pass_input(argc, argv, input))
		return (error_p("Forks memory allocation failed"));
	printf("no: %d, t_die: %d, t_eat: %d, t_sleep: %d, n_meals: %d\n", \
	input->n_phil, input->t_die, input->t_eat, \
	input->t_sleep, input->n_meals);
	if (!init_phil(input))
		return (error_p("Phils initialisation failed"));
	//mutex_init
	int i = 0;
	while (i < input->n_phil)
	{
		if (pthread_mutex_init(&(input->forks[i++]), NULL))
			return(error_p("Mutex init failed"));
	}
	if (pthread_mutex_init(&(input->print_mutex), NULL))
		return (error_p("Mutex init failed"));
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
	input->the_end = 1;
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

int	init_phil(t_info *input)
{
	int	i;

	i = 0;
	input->phils = malloc(sizeof(t_philo) * input->n_phil);
	if (!(input->phils))
		return (0);
	while (i < input->n_phil)
	{
		input->phils[i].id = i + 1;
		input->phils[i].last_meal_time = 0;
		input->phils[i].meals_eaten = 0;
		input->phils[i].info = input;
		//input->phils[i].eat_mut = malloc(sizeof(pthread_mutex_t));
		//if (!input->phils[i].eat_mut || pthread_mutex_init\
		//(input->phils[i].eat_mut, NULL))
		//	return (0);
		pthread_mutex_init(&input->phils[i].dead, NULL);
		i++;
	}
	return (1);
}

int	error_p(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	clean_table(t_info *in)
{
	int i;

	i = 0;
	if (pthread_mutex_destroy(&in->print_mutex))
		return (error_p("Mutex is indestructible"));
	while (i < in->n_phil)
	{
		if (pthread_mutex_destroy(&in->forks[i]))
			return (error_p("Adamantine forks cannot be destroyed"));
		if (pthread_mutex_destroy(&in->phils[i].dead))
			return (error_p("Eating forever is an option"));
		i++;
	}
	free(in->forks);
	free(in->phils);
	return (0);
}