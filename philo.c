/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:19:55 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/17 12:25:11 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_data *init_data(char **av, int ac)
{
	t_data *philo;
	int i;

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

t_philo *init_philo(t_data *data)
{
	t_philo *philo;
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
	struct timeval tv;

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

void 	*routine_fortest(void *val)
{
	t_philo *philo = (t_philo *)val;

	int	i = 0;
	while (1)
	{
		// Locking the fork of [id - 1]

		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		// Output the log activity
		log_activity(philo->id, PH_FORK, &QUILL_MTX, S_TIME);
		// Locking the fork of [id % philo_nb]
		pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->philo_nb]);
		// Output the log activity
		log_activity(philo->id, PH_FORK, &QUILL_MTX, S_TIME);
		log_activity(philo->id, PH_EAT, &QUILL_MTX, S_TIME);
		philo->s_time = ft_curr_time();
		// Eating
		ft_usleep(EAT_T);
		// Incrementing the eating times
		philo->t_ate++;
		// Releasing the forks
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->philo_nb]);
		// Output the log activity
		log_activity(philo->id, PH_SLEEP, &QUILL_MTX, S_TIME);
		// Sleeping
		ft_usleep(SLEEP_T);
		// Thinking
		log_activity(philo->id, PH_THINK, &QUILL_MTX, S_TIME);
	}
	return (NULL);
}

void	start_prog(t_data *data, t_philo *philo)
{
	struct timeval tv;
	int				i;

	i = 0;
	begin_round(philo, data->n_philo);
	while (i < data->n_philo)
	{
		pthread_create(&(philo[i].p), NULL, &routine_test, &philo[i]);
		i += 2;
	}
	ft_usleep(20);
	i = 1;
	while (i < data->n_philo)
	{
		pthread_create(&(philo[i].p), NULL, &routine_test, &philo[i]);
		i += 2;
	}
	// for (int i = 0; i != data->philo_nb; i++)
		// pthread_create(&(philos[i].p), NULL, &routine_test, &philos[i]);	
}

int	main(int ac, char **av)
{
	/* old */
	// pthread_t		*philo;
	// pthread_mutex_t	*mutex;
	// t_philo			*p;
	// int				i;
	//------------------

	t_data *data;
	t_philo *philo;
	
	data = init_data(av + 1, ac);
	philo = init_philo(data);
	start_prog(data, philo);
	
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
