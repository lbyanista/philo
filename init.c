/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:43:04 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/18 19:28:26 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initialize the writing mutex
// pthread_mutex_init(&philo->quill, NULL);
// pthread_mutex_init(&philo->eat, NULL);
//*********
// initialize the forks
// while (++i < philo->n_philo)
// pthread_mutex_init(&(philo->forks[i]), NULL);

t_data	*init_data(char **av, int ac)
{
	t_data	*philo;
	int		i;

	i = -1;
	philo = (t_data *)malloc(sizeof(t_data));
	philo->n_philo = ft_atoi(av[0]);
	philo->time_to_die = ft_atoi(av[1]);
	philo->time_to_eat = ft_atoi(av[2]);
	philo->time_to_sleep = ft_atoi(av[3]);
	if (ac == 6)
		philo->time_must_eat = ft_atoi(av[4]);
	else
		philo->time_must_eat = -1;
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* philo->n_philo);
	pthread_mutex_init(&philo->quill, NULL);
	pthread_mutex_init(&philo->eat, NULL);
	while (++i < philo->n_philo)
		pthread_mutex_init(&(philo->forks[i]), NULL);
	return (philo);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	while (++i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].start_time = -2;
		philo[i].t_at = 0;
	}
	return (philo);
}
