/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:19:55 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/18 13:50:31 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// check overflow before continuing to the next line.
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* philo->n_philo);
	// initialize the writing mutex
	pthread_mutex_init(&philo->quill, NULL);
	pthread_mutex_init(&philo->eat, NULL);
	// initialize the forks
	while (++i < philo->n_philo)
		pthread_mutex_init(&(philo->forks[i]), NULL);
	// for (int i = 0; i < philo->n_philo; i++)
	// 	pthread_mutex_init(&(philo->forks[i]), NULL);
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

int	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

void	ft_usleep(long long s_time)
{
	long long	start;

	start = current_time();
	usleep((s_time - 10) * 1000);
	while ((current_time() - s_time) < start)
		;
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
	// for (int i = 0; i != data->philo_nb; i++)
		// pthread_create(&(philos[i].p), NULL, &routine_test, &philos[i]);	
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
			// if ((philo[i].start_time - current_time()) - data->t_to_die > 0)
			// printf("[Time to die]: %d\n",philo[i].start_time - current_time());
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

	/* old */
	// pthread_t		*philo;
	// pthread_mutex_t	*mutex;
	// t_philo			*p;
	// int				i;
	//------------------
	if (ac != 5 && ac != 6)
		return (printf("waa ghi zid wla n9es args baliz\n"));
	if (check_args(av + 1))
		return (printf("dkhel valid numbers bruuh :(\n"));
	data = init_data(av + 1, ac);
	philo = init_philo(data);
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
	//------------------
	/* old */
	// if (ac != 5 && ac != 6)
	// 	return (printf("waa ghi zid wla n9es args baliz\n"));
	// if (check_args(av + 1))
	// 	return (printf("dkhel valid numbers bruuh :(\n"));
	// p = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	// philo = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	// mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	// i = 0;
	// while (i < ft_atoi(av[1]))
	// 	pthread_mutex_init(&mutex[i++], NULL);
	// i = 0;
	// while (i < ft_atoi(av[1]))
	// {
	// 	p[i].id = i;
	// 	p[i++].mutex = mutex;
	// }
	// i = -1;
	// while (++i < ft_atoi(av[1]))
	// 	pthread_create(&philo[i], NULL, misa, &p[i]);
	// i = 0;
	// while (i < ft_atoi(av[1]))
	// 	pthread_join(philo[i++], NULL);
	// return (0);
}
