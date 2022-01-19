/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:48:58 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/17 13:27:15 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner_init(t_info *info)
{
	int	i;

	i = 0;
	info->start = get_time();
	while (i < info->n_phil)
	{
		info->phils[i].last_meal_time = get_time();
		if (pthread_create(&(info->phils[i].th_id), NULL, &dinner_table, \
		(void *)&(info->phils[i])))
			return (error_p("Creating thread failed"));
		i++;
	}
	i = 0;
	usleep(500);
	while (i < info->n_phil)
	{
		if (pthread_join(info->phils[i].th_id, NULL))
			return (error_p("Joining thread failed"));
		i++;
	}
	return (0);
}

void	*dinner_table(void *philo)
{
	t_philo	*ph;
	t_info	*in;

	ph = (t_philo *) philo;
	in = ph->info;
	if (!(ph->id % 2))
		usleep(500);
	while (!in->the_end)
	{
		if (check_death(in, ph))
			return (NULL);
		if (in->meals_flag && ph->meals_eaten == in->n_meals)
		{
			printf("Philosopher %d ate %d meals.\n", ph->id, ph->meals_eaten);
			return (NULL);
		}
		grab_forks(in, ph);
	}
	return (NULL);
}

void	grab_forks(t_info *in, t_philo *ph)
{
	pthread_mutex_lock(&(in->forks[ph->id - 1]));
	message(in, ph, FORK);
	pthread_mutex_lock(&(in->forks[ph->id % in->n_phil]));
	message(in, ph, FORK);
	eat(in, ph);
	ph->meals_eaten++;
	pthread_mutex_unlock(&(in->forks[ph->id - 1]));
	pthread_mutex_unlock(&(in->forks[ph->id % in->n_phil]));
	//check_death(in, ph);
	message(in, ph, SLEEP);
	usleep(in->t_sleep * 1000);
	//check_death(in, ph);
	message(in, ph, THINK);
}

void	eat(t_info *in, t_philo *ph)
{
	pthread_mutex_lock(&(ph->dead));
	ph->last_meal_time = get_time();
	message(in, ph, EAT);
	usleep(in->t_eat * 1000);
	pthread_mutex_unlock(&(ph->dead));
}

int	check_death(t_info *in, t_philo *ph)
{
	pthread_mutex_lock(&ph->dead);
	if (get_time() - ph->last_meal_time > in->t_die)
	{
		message(in, ph, DEAD);
		in->the_end = 1;
	}
	pthread_mutex_unlock(&ph->dead);
	return (0);
}
