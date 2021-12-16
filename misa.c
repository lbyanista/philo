/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:24:43 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/16 12:49:05 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *misa(void *val)
{
    t_philo *t;
    // t_time *time;
    // printf("**** from misa , time to eat %d**\n", time->time_to_eat);
    t = (t_philo *)val;
    printf("--%d--\n", t->id);
    if (t->id % 2)
        usleep(200);
    pthread_mutex_lock(&t->mutex[t->id]);
    printf("%d has taken a fork\n", t->id + 1);
    pthread_mutex_lock(&(t->mutex[(t->id + 1) % 3]));
    printf("%d has taken a fork\n", t->id + 1);
    printf("%d is eating\n", t->id + 1);
    usleep(200 * 1000);
    pthread_mutex_unlock(&t->mutex[t->id]);
    pthread_mutex_unlock(&(t->mutex[(t->id + 1) % 3]));
    printf("%d is sleeping\n", t->id + 1);
    usleep(200 * 1000);
    printf("%d is thinking\n", t->id + 1);
    t->d = t->id + 10;
    return (void *)t;
}
