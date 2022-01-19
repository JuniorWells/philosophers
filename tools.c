/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:56:38 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/19 15:04:57 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_info *info, t_philo *ph, char *mes)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (!info->the_end)
		printf("%lld Philosopher %d %s\n", get_time(), ph->id, mes);
	pthread_mutex_unlock(&(info->print_mutex));
}

void	my_sleep(int time, t_info *in, t_philo *ph)
{
	long long moment;

	moment = get_time();
	while (get_time() <= moment + time)
	{
		usleep(500);
		check_death(in, ph);
	}
}

int	check_death(t_info *in, t_philo *ph)
{
	if (get_time() - ph->last_meal_time >= in->t_die)
	{
		message(in, ph, DEAD);
		pthread_mutex_lock(&in->dead);
		in->the_end = 1;
		pthread_mutex_unlock(&in->dead);
		return (1);
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
