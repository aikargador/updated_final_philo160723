/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:53:22 by aikram            #+#    #+#             */
/*   Updated: 2023/05/12 15:34:41 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pp.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*str;

	i = 0;
	str = malloc(count * size);
	if (!str)
		return (0);
	while (i < (count * size))
		((char *)str)[i++] = '\0';
	return (str);
}

bool	valid_arg_utl(char *str)
{
	if (!chk_numeric(str))
		return (false);
	if (!str[0])
	{
		write(1, "\e[38;5;202mphilosophers: cricket chirps\e[0m", 43);
		usleep(200000);
		write(1, ".", 1);
		usleep(200000);
		write(1, ".", 1);
		usleep(200000);
		write(1, ".\n", 2);
		return (false);
	}
	return (true);
}

int	look_out_for_the_dead(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->table->printm);
	if (philo->table->death_certificate)
		i = 1;
	pthread_mutex_unlock(&philo->table->printm);
	return (i);
}

int	printer(t_philo *philo, char *clr, int ded, char *msg)
{
	gettimeofday(&philo->curnt_ime, NULL);
	if (ded)
	{
		printf("%s%ld \e[9m\e[2m%d\e[29m\e[22m %s", clr, \
			((philo->curnt_ime.tv_sec * 1000 + philo->curnt_ime.tv_usec / 1000) \
			- philo->table->initime), philo->id, msg);
	}
	else
	{
		printf("%s%ld %d %s", clr, \
			((philo->curnt_ime.tv_sec * 1000 + philo->curnt_ime.tv_usec / 1000) \
			- philo->table->initime), philo->id, msg);
	}
	return (0);
}

int	free_hand(t_philo *philo, int which_lock)
{
	if (which_lock)
		pthread_mutex_unlock(&philo->the_hand->cuffs);
	else
		pthread_mutex_unlock(&philo->the_neighbours_hand->cuffs);
	return (1);
}
