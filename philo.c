/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:19:55 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/18 17:12:17 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	begin_round(t_philo *philo, int t_end)
{
	int	i;

	i = -1;
	philo[0].data->s_point = current_time();
	while (++i < t_end)
		philo[i].start_time = philo[0].data->s_point;
}

void	activity(int id, char *activity, pthread_mutex_t *quill, int s_time)
{
	pthread_mutex_lock(quill);
	printf("%d %d %s\n", current_time() - s_time, id, activity);
	pthread_mutex_unlock(quill);
}

void	start_prog(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	begin_round(philo, data->n_philo);
	while (i < data->n_philo)
	{
		pthread_create(&(philo[i].p), NULL, &misa, &philo[i]);
		i += 2;
	}
	ft_usleep(20);
	i = 1;
	while (i < data->n_philo)
	{
		pthread_create(&(philo[i].p), NULL, &misa, &philo[i]);
		i += 2;
	}	
}

int	supervisor(t_data *data, t_philo *philo)
{
	int	i;
	int	count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->n_philo)
		{
			if (data->time_to_die - (current_time() - philo[i].start_time) < 0)
			{
				printf("RIP: %d died cuz: %d passed\n", i + 1,
					(philo[i].start_time - data->s_point));
				return (2);
			}
			if (data->time_must_eat > 0 && philo[i].t_at >= data->time_must_eat)
				count++;
			if (count >= data->n_philo)
				return (1);
			i++;
		}
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	if (check_args(av + 1))
		return (printf("dkhel valid numbers bruuh :(\n"));
	if (ac != 5 && ac != 6)
		return (printf("waa ghi zid wla n9es args baliz\n"));
	data = init_data(av + 1, ac);
	philo = init_philo(data);
	// printf("** n_philo = %d \n time to die = %d \n time to eat = %d\n time to sleep = %d \n time must eat = %d\n s_point= %d\n", data->n_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->time_must_eat, data->s_point);
	start_prog(data, philo);
	if (supervisor(data, philo))
		return (0);
	i = -1;
	while (++i != data->n_philo)
	{
		pthread_join(philo[i].p, NULL);
		usleep(100);
	}
	return (0);
}
