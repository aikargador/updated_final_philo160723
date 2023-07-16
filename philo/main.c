/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:06:56 by aikram            #+#    #+#             */
/*   Updated: 2023/05/12 15:54:59 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pp.h"

int	death_reaper(t_philo *dr_phil)
{
	gettimeofday(&dr_phil->curnt_ime, NULL);
	dr_phil->is_pp_dead = ((dr_phil->curnt_ime.tv_sec * 1000 + \
	dr_phil->curnt_ime.tv_usec / 1000) - (dr_phil->reset_ime.tv_sec * 1000 + \
	dr_phil->reset_ime.tv_usec / 1000));
	if (dr_phil->is_pp_dead >= dr_phil->table->info.tt_die)
	{
		pthread_mutex_lock(&dr_phil->table->printm);
		if (dr_phil->table->death_certificate)
			return (simprint_unlock(dr_phil));
		dr_phil->table->death_certificate = 69;
		printer(dr_phil, RED, 1, DED);
		return (simprint_unlock(dr_phil));
	}
	return (0);
}

int	time_stamp(t_philo *philo, char *clr, int ded, char *msg)
{
	pthread_mutex_lock(&philo->table->printm);
	if (philo->table->death_certificate)
		return (simprint_unlock(philo));
	printer(philo, clr, ded, msg);
	pthread_mutex_unlock(&philo->table->printm);
	return (0);
}

void	*simulation(void *args)
{
	t_philo			*philo;
	int				i[2];

	i[0] = 0;
	i[1] = 0;
	philo = (t_philo *)args;
	if (philo->table->info.pp_amt == 1)
		return (lone_wolf(philo));
	while (!(green_light(philo, philo->table->initime)))
		;
	if (!(philo->id % 2))
		usleep(69);
	while (1)
	{
		if (philo->table->info.tpp_meat == 0)
			break ;
		i[1] = bon_appetit(philo, &i[0]);
		if (i[1] == 2)
			break ;
		else if (i[1])
			return ((void *)1);
	}
	return ((void *)0);
}

void	restaurant_with_limited_utensils(t_able *table)
{
	t_hands			*tmp;
	int				i;

	i = -1;
	tmp = table->hands;
	gettimeofday(&table->init_ime, NULL);
	table->initime = (table->init_ime.tv_sec * 1000) \
	+ (table->init_ime.tv_usec / 1000);
	if (table->info.pp_amt > 1)
		table->initime += 369;
	while (++i < table->info.pp_amt)
	{
		table->pps[i].id = i + 1;
		table->pps[i].the_hand = tmp;
		tmp = tmp->next;
		table->pps[i].the_neighbours_hand = tmp;
		table->pps[i].table = table;
		pthread_create(&table->pps[i].birth_certificate, NULL, simulation,
			&table->pps[i]);
	}
	i = -1;
	while (++i < table->info.pp_amt)
		pthread_join(table->pps[i].birth_certificate, NULL);
	return ;
}

int	main(int c, char **v)
{
	t_able	table;

	if (!valid_arg(c, v))
		return (1);
	init_info(c, v, &table.info);
	table.pps = ft_calloc(table.info.pp_amt, sizeof(t_philo));
	if (!table.pps)
		return (1);
	table.hands = cuffs_init(table.info.pp_amt);
	if (!table.hands)
		return (terminate_philos(&table));
	table.death_certificate = 0;
	if (protection_init(&table))
		return (1);
	restaurant_with_limited_utensils(&table);
	pthread_mutex_destroy(&table.printm);
	ultimate_destructor(table.hands);
	terminate_philos(&table);
	return (0);
}
