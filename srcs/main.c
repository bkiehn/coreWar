/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiehn <bkiehn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:44:53 by bkiehn            #+#    #+#             */
/*   Updated: 2019/09/20 22:13:27 by bkiehn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			checkNumberChampion(int currentNumberChampion, t_rules* rules, t_champion** champions)
{
	if (currentNumberChampion < 1 || currentNumberChampion > 4)
		return 0; //Не возможный номер петуха
	if (rules->much_players == 4)
		return 0; //Превышенно количество петухов
	rules->much_players++;
	if (champions[currentNumberChampion] != NULL)
		return 0; //Такой петух уже есть
	champions[currentNumberChampion] = ft_memalloc(sizeof(t_champion));
	champions[currentNumberChampion]->number = currentNumberChampion;
	champions[currentNumberChampion]->reg[1] = -currentNumberChampion;

	return currentNumberChampion;
}


int			calcNumberChampion(t_rules* rules, t_champion** champions)
{
	int		currentNumberChampion;

	if (rules->much_players == 4)
		return 0; //Превышенно количество петухов
	rules->much_players++;
	currentNumberChampion = 1;

	while (champions[currentNumberChampion] != NULL)
	{
		currentNumberChampion++;
	}
	
	champions[currentNumberChampion] = ft_memalloc(sizeof(t_champion));
	champions[currentNumberChampion]->number = currentNumberChampion;
	champions[currentNumberChampion]->reg[1] = -currentNumberChampion;
	return currentNumberChampion;
}

int		parseArg(int argc, char** argv, t_rules *rules, t_champion **champions)
{
	int arg;
	int fd;
	int	currentNumberChampion;

	currentNumberChampion = 0;
	arg = 1;
	while (arg < argc)
	{	
		if (!ft_strcmp(argv[arg], "-dump"))
		{
			arg++;
			if (arg <= argc)
				rules->dump = ft_atoi(argv[arg]);
			else
				return 0; //ошибка юзача
		}
		else if (!ft_strcmp(argv[arg], "-n"))
		{
			arg++;
			if (arg <= argc)
			{
				currentNumberChampion = checkNumberChampion(ft_atoi(argv[arg]), rules, champions);
				if (currentNumberChampion == 0)
					return 0; //Что то не то с номером петуха
			}
			else
				return 0; //ошибка юзача
		}
		else
		{
			if ((fd = open(argv[arg], O_RDONLY)) == -1)
				return 0; //ошибка открытия файла
			else
			{
				if (currentNumberChampion == 0)
					if ((currentNumberChampion = calcNumberChampion(rules, champions)) == 0)
						return 0; //С номером петуха что-то не так
				if (!createChampion(champions[currentNumberChampion], rules, fd))
					return 0; //Ошибка при создании разрушителя миров
				currentNumberChampion = 0;
			}
		}
		arg++;
	}
	return 1;
}

void	set_rules(t_rules* rules, t_champion** champions)
{
    int current_champion;

    current_champion = 4;
    while (champions[current_champion] == NULL)
        current_champion--;
    rules->last_alive = current_champion;
	rules->name_winner = ft_strdup(champions[current_champion]->name);
	rules->ctd = CYCLE_TO_DIE;
}

int 	main(int argc, char** argv) {
	t_rules*		rules;
	t_champion**	champions;
	t_champion*     cursors;

	champions = ft_memalloc(sizeof(t_champion*) * 5);
	rules = ft_memalloc(sizeof(t_rules));
	if (!parseArg(argc, argv, rules, champions))
	{
		ft_printf("Ошибка на этапе обнаружения настроек для разрушителей или при их создании.\n");
		exit (0);
	}
	if (rules->much_players != 0)
		set_rules(rules, champions);
	else
	{
		ft_printf("Zdes budet usage\n");
		exit (0);
	}
	create_battlefield(rules, champions);
	/*
	 * Исторически сложилось, что начал работать с массивом
	 * чемпионов и последнии параметры для них устанавливаются в
	 * creat_battlefield, но для удобства реализации процесса игры
	 * чемпионов нужно переделать в список, и обозвать их курсорами
	 * что делается в creat_cursor, но это всё теже структуры.
	 * number_cursor определяется здесь же
	 */
	cursors = create_cursor(champions, rules);
//	print_rules(rules);
//	print_cursors(cursors, 1);
//  print_battlefiled(rules, champions);
	start_game(cursors, rules, champions);
//	Печатать после старт гейма есть смысл только в функции end_game,
//	так как в завершении функции end_game, всё чистится
}

