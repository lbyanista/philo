/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:24:43 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/18 13:34:21 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*misa(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	while (1)
	{
		// Locking the fork of [id - 1]
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		// Output the log activity
		activity(philo->id, "has taken a fork", &philo->data->quill,
			philo->data->s_point);
		// Locking the fork of [id % philo_nb]
		pthread_mutex_lock(&philo->data->forks[philo->id % \
			philo->data->n_philo]);
		activity(philo->id, "has taken a fork", &philo->data->quill,
			philo->data->s_point);
		activity(philo->id, "is eating", &philo->data->quill,
			philo->data->s_point);
		philo->start_time = current_time();
		// Eating
		ft_usleep(philo->data->time_to_eat);
		// Incrementing the eating times
		philo->t_at++;
		// Releasing the forks
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id % \
			philo->data->n_philo]);
		activity(philo->id, "is sleeping", &philo->data->quill,
			philo->data->s_point);
		ft_usleep(philo->data->time_to_sleep);
		activity(philo->id, "is thinking", &philo->data->quill,
			philo->data->s_point);
	}
	return (NULL);
}
