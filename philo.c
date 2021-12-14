/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:19:55 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/14 15:11:01 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    pthread_t *philo;
    pthread_mutex_t *mutex;
    t_philo *p;
    // void *r;

    if (ac != 5 && ac != 6)
    {
        printf("waa ghi zid args baliz\n");
        return 1;
    }
    
    // int n_philo = atoi(av[1]);
    // printf("%d\n\n", n_philo);
    p = malloc(sizeof(t_philo) * atoi(av[1]));
    // r = malloc(sizeof(t_ret) * 3);
    philo = malloc(sizeof(pthread_t) * atoi(av[1]));
    mutex = malloc(sizeof(pthread_mutex_t) * atoi(av[1]));
    for (int i = 0; i < atoi(av[1]); i++)
    {
        pthread_mutex_init(&mutex[i], NULL);
    }
    for (int i = 0; i < atoi(av[1]); i++)
    {
        p[i].id = i;
        p[i].mutex = mutex;
    }
    for (int i = 0; i < atoi(av[1]); i++)
    {
        pthread_create(&philo[i], NULL, misa, &p[i]);
    }
    for (int i = 0; i < atoi(av[1]); i++)
    {
        pthread_join(philo[i], NULL);
        printf("philo->%d\n", i + 1);
    }
}