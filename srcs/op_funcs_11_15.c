/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_funcs_11_15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiehn <bkiehn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 01:06:21 by bkiehn            #+#    #+#             */
/*   Updated: 2019/09/26 01:06:22 by bkiehn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "commands.h"

void			sti_func(t_rules *rules, t_champion *cursor, unsigned char *t_args)
{
	int arg1;
    int arg2;
    int arg3;
    int final_position;


	arg1 = get_arg(rules, cursor, t_args, 0);
	arg2 = get_arg(rules, cursor, t_args, 1);
	arg3 = get_arg(rules, cursor, t_args, 2);
	if (t_args[1] == IND_CODE)
		arg2 = (short)get_value_from_battlefield(rules, cursor->position,
										  arg2 % IDX_MOD, REG_SIZE);
	else if (t_args[1] == REG_CODE)
		arg2 = cursor->reg[arg2];
	if (t_args[2] == REG_CODE)
		arg3 = cursor->reg[arg3];
	final_position = cursor->position + (arg2 + arg3) % IDX_MOD;
	set_value_in_battlefield(rules, final_position, REG_SIZE, cursor->reg[arg1]);
}

void			fork_func(t_rules *rules, t_champion *cursor, unsigned char *t_args)
{
	int				arg1;
	t_champion*		copy_cursor;
	int				registr;

	registr = REG_NUMBER + 1;
	t_args[0] = DIR_CODE;
	// zjmp не имеет кода типа, следовательно t_args не заполнялся
	// плюс задействуем t_args что бы не ругался компилятор, из-за неиспользования переменной
	arg1 = get_arg(rules, cursor, t_args, 0);
	copy_cursor = ft_memalloc(sizeof(t_champion));
	copy_cursor->position = ((cursor->position + arg1) % IDX_MOD) % MEM_SIZE;
	while (--registr != 0) {
		copy_cursor->reg[registr] = cursor->reg[registr];
	}
	copy_cursor->carry = cursor->carry;
	copy_cursor->last_live_in_cycle = cursor->last_live_in_cycle;
	copy_cursor->color = ft_strdup(cursor->color);
	copy_cursor->name = ft_strdup(cursor->name);
	rules->cursors = add_cursor_in_start(rules->cursors, copy_cursor);
}

void			lld_func(t_rules *rules, t_champion *cursor, unsigned char *t_args)
{
	int arg1;
	int arg2;

	arg1 = get_arg(rules, cursor, t_args, 0);
	arg2 = get_arg(rules, cursor, t_args, 1);

	if (t_args[0] == IND_CODE)
		arg1 = (int)get_value_from_battlefield(rules, cursor->position,
										  arg1, REG_SIZE);
	cursor->reg[arg2] = arg1;
	cursor->carry = (cursor->reg[arg1] == 0) ? 1 : 0;
}

void			lldi_func(t_rules *rules, t_champion *cursor, unsigned char *t_args)
{
	int arg1;
	int arg2;
	int arg3;

	arg1 = get_arg(rules, cursor, t_args, 0);
	arg2 = get_arg(rules, cursor, t_args, 1);
	arg3 = get_arg(rules, cursor, t_args, 2);
	if (t_args[0] == IND_CODE)
		arg1 = (int)get_value_from_battlefield(rules, cursor->position,
										  arg1 % IDX_MOD, REG_SIZE);
	else if (t_args[0] == REG_CODE)
		arg1 = cursor->reg[arg1];
	if (t_args[1] == REG_CODE)
		arg2 = cursor->reg[arg2];
	cursor->reg[arg3] = (int)get_value_from_battlefield(rules, cursor->position,
												   arg1 + arg2, REG_SIZE);
}

void			lfork_func(t_rules *rules, t_champion *cursor, unsigned char *t_args)
{
	int				arg1;
	t_champion*		copy_cursor;
	int				registr;

	registr = REG_NUMBER + 1;
	t_args[0] = DIR_CODE;
	// zjmp не имеет кода типа, следовательно t_args не заполнялся
	// плюс задействуем t_args что бы не ругался компилятор, из-за неиспользования переменной
	arg1 = get_arg(rules, cursor, t_args, 0);
	copy_cursor = ft_memalloc(sizeof(t_champion));
	copy_cursor->position = (cursor->position + arg1) % MEM_SIZE;
	while (--registr != 0) {
		copy_cursor->reg[registr] = cursor->reg[registr];
	}
	copy_cursor->carry = cursor->carry;
	copy_cursor->last_live_in_cycle = cursor->last_live_in_cycle;
	copy_cursor->color = ft_strdup(cursor->color);
	copy_cursor->name = ft_strdup(cursor->name);
	rules->cursors = add_cursor_in_start(rules->cursors, copy_cursor);
}