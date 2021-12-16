/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:19:55 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/16 14:53:15 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    pthread_t *philo;
    pthread_mutex_t *mutex;
    t_philo *p;
    // t_time *time;
    // void *r;
    if (ac != 5 && ac != 6)
    {
        printf("waa ghi zid wla n9es args baliz\n");
        return (1);
    }
    if (check_args(av + 1))
    {
        printf("dkhel valid numbers bruuh :(\n");
        return (1);
    }
    // time = malloc(sizeof(t_time) * 200);
    // time->time_to_die = ft_atoi(av[2]);
    // printf("--time to reat %d--\n", time->time_to_eat);
    // time->time_to_eat = ft_atoi(av[3]);
    // time->time_to_sleep = ft_atoi(av[4]);
    // time->time_must_eat = ft_atoi(av[5]);
    // int n_philo = ft_atoi(av[1]);
    // printf("%d\n\n", n_philo);
    p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    // r = malloc(sizeof(t_ret) * 3);
    philo = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
    mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
    int i = 0;
    while(i < ft_atoi(av[1]))
        pthread_mutex_init(&mutex[i++], NULL);
    i = 0;
    while(i < ft_atoi(av[1]))
    {
        p[i].id = i;
        p[i++].mutex = mutex;
    }
    i = -1;
    while(++i < ft_atoi(av[1]))
        pthread_create(&philo[i], NULL, misa, &p[i]);
    i = 0;
    while(i < ft_atoi(av[1]))
        pthread_join(philo[i++], NULL);
    return 0;
}