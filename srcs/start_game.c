/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksey <aleksey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:02:24 by aleksey           #+#    #+#             */
/*   Updated: 2019/09/19 17:32:58 by aleksey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "commands.h"

void    action_with_cursor(t_champion* cursor, t_rules* rules)
{
    if (cursor->cycle_before_run == 0)
	{
		cursor->code_operation = rules->battlefield[cursor->position];
    	if (cursor->code_operation >= LIVE_OP &&
				cursor->code_operation <= AFF_OP)
    	{
			cursor->cycle_before_run = g_op_tab[cursor->code_operation].
					cycle_before_run;//Возможно прям здесь нужно будет деинкрементить cycle_before_run
			//ft_printf("Код операции: %d\nЦиклов до исполения: %d\n", cursor->code_operation, cursor->cycle_before_run);
		}
    	else
    		cursor->position = (cursor->position + 1) % MEM_SIZE;

        //Получить номер операции и установить cycle_before_run
        //Если номер операции неверен cycle_before_run = 0, position++
	}
	else
    {
		cursor->cycle_before_run--;
		if (cursor->cycle_before_run == 0)
			exec_command(rules, cursor);
			//Отправляем курсор на валидауию байта типов агументов, аргументов и  выполение команды, Макса функция
	}
}

void	introduction(t_champion** champions, t_rules* rules)
{
	int             current_champion;
	int             count;

	current_champion = 0;
	count = 0;
	ft_printf("Introducing contestants...\n");
	while (++count <= rules->much_players)
	{
		current_champion = select_champion(champions, current_champion);
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				champions[current_champion]->number,
				champions[current_champion]->size,
				champions[current_champion]->name,
				champions[current_champion]->comment);
		current_champion++;
	}
	free(champions);
}

void	start_game(t_champion* cursors, t_rules* rules, t_champion** champions)
{
	introduction(champions, rules);
	int ctd;
	t_champion* cursor;

	ctd = rules->ctd;
	cursor = cursors;
	while (rules->number_cursors)
	{
		rules->number_cycle++;
		ctd--;
		while (cursor)
		{
			action_with_cursor(cursor, rules);
			cursor = cursor->next;
		}
		if (ctd <= 0)
		{
			check_cursors(&cursors, rules);
			// ? участвуют ли в проверке созданые в это м же цикле каретки операциями fork
			// если да, то строку "cursor = rules->cursors" нужно добавить между блоком
			// проверки и блоком действий над курсорами
			ctd = rules->ctd;
		}
		cursor = rules->cursors;
		// Заменил "cursor = cursors" на "cursor = rules->cursors" так как
		// в блоке действий над курсорами может измениться "rules->cursors"
		// доступа к "cursors" там нет
		if (rules->dump == rules->number_cycle)
			end_game(PRINTING_DUMP, rules, cursors);
			//Печать дампа памяти
			//Выход из проги
	}
	end_game(GAME_OVER, rules, cursors);
}