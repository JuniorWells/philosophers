/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:37:12 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/19 14:02:28 by kchaniot         ###   ########.fr       */
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
		input->phils[i].left = i;
		input->phils[i].right = (i + 1) % input->n_phil;
		input->phils[i].info = input;
		i++;
	}
	return (1);
}

int	init_mutants(t_info *in)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(in->print_mutex), NULL) || \
	pthread_mutex_init(&(in->dead), NULL) || \
	pthread_mutex_init(&(in->f_access), NULL))
		return (!error_p("Mutex init failed"));
	return (1);
}
