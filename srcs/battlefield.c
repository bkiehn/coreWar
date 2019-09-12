/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battlefield.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiehn <bkiehn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:04:28 by bkiehn            #+#    #+#             */
/*   Updated: 2019/09/11 20:39:50 by bkiehn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	champion_move_battlefield(t_champion* champion, t_rules* rules, int position)
{
	int	count;

	count = 0;
	champion->position = position;
	while (count < champion->size)
	{
		rules->battlefield[position] = champion->body[count];
		position++;
		count++;
	}
}

void	create_battlefield(t_rules* rules, t_champion** champions)
{
	int current_champion = 1;
	int count;

	count = 0;
	while (count < rules->much_players)
	{
		while (champions[current_champion] == NULL)
			current_champion++;
		champion_move_battlefield(champions[current_champion++], rules, count * (MEM_SIZE / rules->much_players));
		count++;
	}

	
}