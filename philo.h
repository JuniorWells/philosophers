/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:32:28 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/18 04:14:54 by kchaniot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "has taken a fork."
# define DEAD "died."
# define EAT "is eating."
# define THINK "is thinking."
# define SLEEP "is sleeping."

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meals_eaten;
	int				left;
	int				right;
	struct s_info	*info;
	pthread_t		th_id;
}				t_philo;

typedef struct s_info
{
	int				n_phil;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				meals_flag;
	int				the_end;
	int				*forks;
	long long		start;
	t_philo			*phils;
	pthread_mutex_t	dead;
	pthread_mutex_t	f_access;
	pthread_mutex_t	print_mutex;
}				t_info;

int			init_mutants(t_info *in);
int			catering_check(t_info *in);
int			dinner_init(t_info *info);
int			check_death(t_info *in, t_philo *ph);
int			clean_table(t_info *in);
int			is_digit(char **argv);
int			ft_atoi(const char *str);
int			init_phil(t_info *input);
int			pass_input(int argc, char **argv, t_info *input);
int			error_p(char *str);
int			ingredients_check(int argc, char **argv, t_info *input);
void		*dinner_table(void *philo);
void		grab_forks(t_info *in, t_philo *ph);
void		eat(t_info *in, t_philo *ph);
void		checker(t_info *in, t_philo *ph);
void		message(t_info *info, t_philo *ph, char *mes);
size_t		ft_strlen(const char *s);
long long	get_time(void);

#endif