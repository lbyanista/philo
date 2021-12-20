/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:24:43 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/19 18:30:23 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Locking the fork of [id - 1] line 29
// Output the activity line 30
// Locking the fork of [id % philo_nb] line 31
// Eating line 36 ft_sleep
// Incrementing the eating times line 37
// Releasing the forks line 38 39

void	*misa(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		activity(philo->id, TK_FRK, &philo->data->writing,
			philo->data->s_point);
		pthread_mutex_lock(&philo->data->forks[philo->id % \
			philo->data->n_philo]);
		activity(philo->id, TK_FRK, &philo->data->writing,
			philo->data->s_point);
		activity(philo->id, IS_EAT, &philo->data->writing,
			philo->data->s_point);
		philo->start_time = current_time();
		ft_usleep(philo->data->time_to_eat);
		philo->t_ateating++;
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id % \
			philo->data->n_philo]);
		activity(philo->id, IS_SL, &philo->data->writing, philo->data->s_point);
		ft_usleep(philo->data->time_to_sleep);
		activity(philo->id, IS_TH, &philo->data->writing, philo->data->s_point);
	}
	return (NULL);
}
