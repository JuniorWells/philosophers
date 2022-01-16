/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:58:35 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/16 20:54:41 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((9 <= (*str) && (*str) <= 13) || (*str == ' '))
		str++;
	if ((*str) == '+' || (*str) == '-')
	{
		if (*(str++) == '-')
			sign *= -1;
	}
	while (*str >= 48 && *str <= 57)
	{
		res = (res * 10) + (*str - 48);
		if (res < -2147483649 || res > 2147483648)
			return (0);
		str++;
	}
	return ((int)(res * sign));
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (time);
}

int	is_digit(char **argv)
{	
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			++j;
		}
		i++;
	}
	return (1);
}

void	message(t_info *info, t_philo *ph, char *mes)
{
	pthread_mutex_lock(&(info->print_mutex));
	printf("%lld Philosopher %d %s\n", get_time(), ph->id, mes);
	pthread_mutex_unlock(&(info->print_mutex));
}