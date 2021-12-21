/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:19:55 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/21 22:52:35 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	begin_round(t_philo *philo, int t_end)
// {
// 	int	j;

// 	j = -1;
// 	philo[0].data->s_point = current_time();
// 	while (++j < t_end)
// 		philo[j].start_time = philo[0].data->s_point;
// }

void	activity(int id, char *activity, pthread_mutex_t *writing, int s_time)
{
	pthread_mutex_lock(writing);
	printf("%d %d %s\n", current_time() - s_time, id, activity);
	pthread_mutex_unlock(writing);
}

	// begin_round(philo, data->n_philo) 40;

int	start_prog(t_data *data, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	philo[0].data->s_point = current_time();
	while (++j < data->n_philo)
		philo[j].start_time = philo[0].data->s_point;
	while (i < data->n_philo)
	{
		if (pthread_create(&(philo[i].p), NULL, &routine, &philo[i]) != 0)
			return (-1);
		i++;
		usleep(200);
	}
	return (1);
}
	// start round progr ^
	// while (i < data->n_philo)
	// {
	// 	pthread_create(&(philo[i].p), NULL, &misa, &philo[i]);
	// 	i += 2;
	// }
	// ft_usleep(20);
	// i = 1;
	// while (i < data->n_philo)
	// {
	// 	pthread_create(&(philo[i].p), NULL, &misa, &philo[i]);
	// 	i += 2;
	// }

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
				pthread_mutex_lock(&data->writing);
				printf("RIP: philo %d died cuz: %d passed\n", i + 1,
					(philo[i].start_time - data->s_point));
				return (2);
			}
			if (data->time_must_eat > 0 && philo[i].t_ateating >= \
				data->time_must_eat)
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
		return (printf("enter a valid number's :(\n"));
	if (ac != 5 && ac != 6)
		return (printf("bad args (+ or - arg) please\n"));
	data = init_data(av + 1, ac);
	philo = init_philo(data);
	if (data->n_philo == 0)
	{
		printf("Please add a philo");
		return(-1);
	}
	if (start_prog(data, philo) == -1)
		return (0);
	if (supervisor(data, philo))
		return (0);
	i = -1;
	while (++i != data->n_philo)
	{
		if (pthread_join(philo[i].p, NULL) != 0)
			return (-1);
		usleep(100);
	}
	return (0);
}
