/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:16:41 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/17 12:04:27 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H 

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// typedef struct s_philo
// {
//         int id;
//         int d;
//         pthread_mutex_t *mutex;

// }       t_philo;

// // typedef struct s_ret
// // {
// //         int d;
// // }       t_ret;

// typedef struct s_time
// {
//         int time_to_eat;
//         int time_to_sleep;
//         int time_to_die;
//         int time_must_eat;
// }       t_time;

// newww

typedef struct s_philo
{
	int	id; 
	int	start_time;
	int	t_at; // (how many times the philosopher ate)
	pthread_t p;
	t_data *data;
}		t_philo;

typedef struct s_data
{
    int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_must_eat;
	int	s_point; // initial date (To be substracted)
	pthread_mutex_t *forks;
	pthread_mutex_t quill;
	pthread_mutex_t eat;
}	t_data;

//fineww


void    *misa(void *val);
int     check_args(char **av);
int     ft_isdigit(int c);
int	ft_atoi(const char *c);

#endif