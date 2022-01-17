/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:37:12 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/17 12:20:52 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	catering_check(t_info *in)
{
	if (!init_phil(in))
		return (error_p("Phils initialisation failed"));
	if (!init_mutants(in))
		return (error_p("Fatal"));
	return (0);
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
		if (pthread_mutex_init(&input->phils[i].dead, NULL))
		{
			free(input->phils);
			return (!error_p("Philosophers won't join this table"));
		}
		i++;
	}
	return (1);
}

int	init_mutants(t_info *in)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(in->print_mutex), NULL))
		return (!error_p("Mutex init failed"));
	while (i < in->n_phil)
	{
		if (pthread_mutex_init(&(in->forks[i++]), NULL))
		{
			pthread_mutex_destroy(&in->print_mutex);
			return (!error_p("Forks mutex init failed"));
		}
	}
	return (1);
}
