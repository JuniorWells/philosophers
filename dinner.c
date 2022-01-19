/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:48:58 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/19 09:13:07 by kchaniot         ###   ########.fr       */
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
		if (pthread_create(&(info->phils[i].th_id), NULL, &dinner_table, \
		(void *)&(info->phils[i])))
			return (error_p("Creating thread failed"));
		i++;
	}
	i = 0;
	usleep(1000);
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
	while (!in->the_end)
	{
		if (in->meals_flag && ph->meals_eaten == in->n_meals)
		{
			printf("Philosopher %d ate %d meals.\n", ph->id, ph->meals_eaten);
			return (NULL);
		}
		if (!ph->meals_eaten)
			ph->last_meal_time = in->start;
		if (check_death(in, ph))
			break ;
		grab_forks(in, ph);
	}
	return (NULL);
}

void	grab_forks(t_info *in, t_philo *ph)
{
	while (1)
	{
		pthread_mutex_lock(&in->f_access);
		if (in->forks[ph->left] && in->forks[ph->right])
		{
			in->forks[ph->left] = 0;
			message(in, ph, FORK);
			in->forks[ph->right] = 0;
			message(in, ph, FORK);
			pthread_mutex_unlock(&in->f_access);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&in->f_access);
			usleep(10);
		}
	}
	eat(in, ph);
}

void	eat(t_info *in, t_philo *ph)
{
	ph->last_meal_time = get_time();
	message(in, ph, EAT);
	usleep(in->t_eat * 1000);
	pthread_mutex_lock(&in->f_access);
	in->forks[ph->left] = 1;
	in->forks[ph->right] = 1;
	pthread_mutex_unlock(&in->f_access);
	ph->meals_eaten++;
	message(in, ph, SLEEP);
	usleep(in->t_sleep * 1000);
	message(in, ph, THINK);
}

int	check_death(t_info *in, t_philo *ph)
{
	if (get_time() - ph->last_meal_time > in->t_die)
	{
		message(in, ph, DEAD);
		pthread_mutex_lock(&in->dead);
		in->the_end = 1;
		pthread_mutex_unlock(&in->dead);
		return (1);
	}
	return (0);
}
