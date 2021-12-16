/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrayj <mlabrayj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:31:34 by mlabrayj          #+#    #+#             */
/*   Updated: 2021/12/16 12:45:22 by mlabrayj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(int c)
{
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}

int check_args(char **av)
{
    int		i;
	int		j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
        {
			if (!ft_isdigit(av[i][j]))
				return (1);
            j++;
        }
        i++;
	}
	return (0);
}
