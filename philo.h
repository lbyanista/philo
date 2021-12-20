/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:16:41 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/20 12:38:09 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 
# define IS_TH "is thinking"
# define IS_SL "is sleeping"
# define IS_EAT "is eating"
# define TK_FRK "has taken a fork"

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

//s_point => (initial date (To be substracted)
//t_at => (how many times the philosopher at)

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	int				s_point;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	eat;
}		t_data;

typedef struct s_philo
{
	int			id;
	int			start_time;
	int			t_ateating;
	pthread_t	p;
	t_data		*data;
}		t_philo;

void	*misa(void *val);
void	activity(int id, char *activity, pthread_mutex_t *writing, int s_time);
int		current_time(void);
int		check_args(char **av);
int		ft_atoi(const char *c);
int		ft_isdigit(int c);
void	ft_usleep(long long s_time);
t_data	*init_data(char **av, int ac);
t_philo	*init_philo(t_data *data);

#endif