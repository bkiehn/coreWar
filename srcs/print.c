/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiehn <bkiehn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:36:33 by bkiehn            #+#    #+#             */
/*   Updated: 2019/09/20 16:52:25 by aleksey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	print_bytes_hex(unsigned char* bytes, int size)
{
	int count;

	count = 0;
	while (count < size) 
	{
		ft_printf("%.2x", bytes[count]);
		count++;
		ft_printf("%.2x", bytes[count]);
		if (((count + 1) % 32) == 0)
			ft_printf("\n");
		else
			ft_printf(" ");
		count++;
	}
	ft_printf("\n");
}

int		select_champion(t_champion** champions, int current_champion)
{
    if (current_champion > MAX_PLAYERS)
        return 0;
	while (champions[current_champion] == NULL)
	{
        current_champion++;
        if (current_champion > MAX_PLAYERS)
            return 0;
    }
	return current_champion;
}

int     definition_color(t_champion** champions, int number_champion, int count)
{
    if (count == champions[number_champion]->position)
        ft_printf(champions[number_champion]->color);
    if (count == champions[number_champion]->size + champions[number_champion]->position)
    {
//        ft_printf(NO_COLOR);
        number_champion = select_champion(champions, number_champion + 1);
    }

    return number_champion;
}

void	print_battlefiled(t_rules* rules, t_champion** champions)
{
	int count;
	int number_champion;

	count = 0;
	number_champion = select_champion(champions, 1);
	while (count < MEM_SIZE) 
	{
	    if (number_champion != 0)
            number_champion = definition_color(champions, number_champion, count);
		ft_printf("%.2x", rules->battlefield[count]);
		if (((count + 1) % 32) == 0)
			ft_printf("\n");
		else if (((count + 1) % 2) == 0)
			ft_printf(" ");
		count++;
	}
}

/*
 * правки внесены для облегчения сравнивания дампов со стандартной вирт машиной
 */
void	print_dump(t_rules* rules)
{
	int count;

	count = 0;
	while (count < MEM_SIZE)
	{
		if ((count % 64) == 0) // 64 заменить на 32
		{
			if (count == 0)
				ft_printf("0x");
			ft_printf("%#.4x : ", count);
		}
		ft_printf("%.2x ", rules->battlefield[count]); //убрать пробел
		if (((count + 1) % 64) == 0) // 64 заменить на 32
			ft_printf("\n");
//		else if (((count + 1) % 2) == 0)
//			ft_printf(" ");
		count++;
	}
}

void	to_string(t_champion* cursors, char flag_body)
{
	int count;

	count = 1;
	ft_printf("-------------------------\n%s", cursors->color);
	ft_printf("number_cursor: %d\n", cursors->number_cursors);
	ft_printf("number: %d\n", cursors->number);
	ft_printf("name: %s\n", cursors->name);
	ft_printf("comment: %s\n", cursors->comment);
	ft_printf("size: %d\n", cursors->size);
	ft_printf("position: %d\ncarry: %d\ncode_operation: %d\n",
			  cursors->position, cursors->carry, cursors->code_operation);
	ft_printf("last_live_in_cycle: %d\ncycle_before_run: %d\nbytes_for_next_operation: %d\n",
			  cursors->last_live_in_cycle, cursors->cycle_before_run, cursors->bytes_for_next_operation);
	ft_printf("Registers:\n");
	while (count <= REG_NUMBER)
	{
		ft_printf("\tREG_%d: %d\n", count, cursors->reg[count]);
		count++;
	}
	if (flag_body)
	{
		ft_printf("Body:\n");
		print_bytes_hex(cursors->body, cursors->size);
	}
	ft_printf("-------------------------\n");
}

void	print_cursors(t_champion* cursors, char flag_body)
{
	while (cursors != 0)
	{
		cursors->to_string(cursors, flag_body);
		cursors = cursors->next;
	}
}

void	print_rules(t_rules* rules)
{
	ft_printf("---------------------------\n         Rules:            \n"
		   "---------------------------\ndump: %d\nnumber_cursors: %d\n"
		   "much_players: %d\n"
		    "last_alive: %d\nnumber_cycle: %d\nnumber_live_of_ctd: %d\n"
	        "cycles_to_die(ctd): %d\nnumber_check: %d\n"
		    "---------------------------\n",
	        rules->dump, rules->number_cursors,
	        rules->much_players, rules->last_alive,
			rules->number_cycle, rules->number_live_of_ctd, rules->ctd,
			rules->number_check);
}
