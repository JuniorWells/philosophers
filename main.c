/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:56:25 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/16 21:26:55 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	input;

	if (error_check(argc, argv, &input))
		return (1);
	if (dinner_init(&input))
		return (2);
	if (clean_table(&input))
		return (3);
	return (0);
}
