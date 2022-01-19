/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:56:25 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/19 14:01:35 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	input;

	if (ingredients_check(argc, argv, &input))
		return (1);
	if (catering_check(&input))
		return (2);
	dinner_init(&input);
	if (clean_table(&input))
		return (3);
	return (0);
}
