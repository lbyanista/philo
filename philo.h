/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:16:41 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/16 14:51:06 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H 

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_philo
{
        int id;
        int d;
        pthread_mutex_t *mutex;

}       t_philo;

// typedef struct s_ret
// {
//         int d;
// }       t_ret;

typedef struct s_time
{
        int time_to_eat;
        int time_to_sleep;
        int time_to_die;
        int time_must_eat;
}       t_time;


void    *misa(void *val);
int     check_args(char **av);
int     ft_isdigit(int c);
int	ft_atoi(const char *c);

#endif