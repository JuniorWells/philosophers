/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:58:35 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/19 15:04:46 by kchaniot         ###   ########.fr       */
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
