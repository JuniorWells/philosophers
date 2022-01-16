/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaniot <kchaniot@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:32:28 by kchaniot          #+#    #+#             */
/*   Updated: 2022/01/16 22:20:31 by kchaniot         ###   ########.fr       */
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
	struct s_info	*info;
	pthread_t		th_id;
	pthread_mutex_t	dead;
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
	long long		start;
	t_philo			*phils;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}				t_info;

int			dinner_init(t_info *info);
void		*dinner_table(void *philo);
void		grab_forks(t_info *in, t_philo *ph);
void		eat(t_info *in, t_philo *ph);
void	checker(t_info *in, t_philo *ph);
int			check_death(t_info *in, t_philo *ph, int time);
int			clean_table(t_info *in);
void		message(t_info *info, t_philo *ph, char *mes);
int			is_digit(char **argv);
long long	get_time(void);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
int			init_phil(t_info *input);
int			pass_input(int argc, char **argv, t_info *input);
int			error_p(char *str);
int			error_check(int argc, char **argv, t_info *input);

#endif