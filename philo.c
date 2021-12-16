/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:19:55 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/16 17:35:03 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	pthread_t		*philo;
	pthread_mutex_t	*mutex;
	t_philo			*p;
	int				i;

	if (ac != 5 && ac != 6)
		return (printf("waa ghi zid wla n9es args baliz\n"));
	if (check_args(av + 1))
		return (printf("dkhel valid numbers bruuh :(\n"));
	p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philo = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	i = 0;
	while (i < ft_atoi(av[1]))
		pthread_mutex_init(&mutex[i++], NULL);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		p[i].id = i;
		p[i++].mutex = mutex;
	}
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_create(&philo[i], NULL, misa, &p[i]);
	i = 0;
	while (i < ft_atoi(av[1]))
		pthread_join(philo[i++], NULL);
	return (0);
}
