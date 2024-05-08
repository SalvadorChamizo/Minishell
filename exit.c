/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:17:30 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/03 12:24:47 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	printf(CYAN"╦╔╗╔  ╔╦╗╔═╗╔╦╗╔═╗╦═╗╦ ╦  ╔═╗╔═╗\n");
	printf("║║║║  ║║║║╣ ║║║║ ║╠╦╝╚╦╝  ║ ║╠╣ \n");
	printf("╩╝╚╝  ╩ ╩╚═╝╩ ╩╚═╝╩╚═ ╩   ╚═╝╚  \n");
	printf("  _  _   ___    ┌─┐┬  ┬┌─┐┬  ┬ ┬┌─┐┌┬┐┌─┐┬─┐┌─┐ \n");
	printf(" | || | |__ \\   ├┤ └┐┌┘├─┤│  │ │├─┤ │ │ │├┬┘└─┐ \n");
	printf(" | || |_   ) |  └─┘ └┘ ┴ ┴┴─┘└─┘┴ ┴ ┴ └─┘┴└─└─┘\n");
	printf(" |__   _| / / \n");
	printf("    | |  / /_ \n");
	printf("    |_| _____|\n"RESET);
}

void	first_part(void)
{
	printf(GREYM2"¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶       ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶                         ¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶¶¶¶"GREYM"    ¶¶    ");
	printf("  ¶¶  ¶¶       ¶¶    "GREYM2"¶¶¶¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶"GREYM"    ¶¶¶¶       ");
	printf("¶¶¶¶¶¶        ¶¶¶¶    "GREYM2"¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶  "GREYM" ¶¶¶¶¶¶        ");
	printf("¶¶¶¶¶¶¶       ¶¶¶¶¶¶¶  "GREYM2" ¶¶¶¶\n");
	printf("¶¶¶¶  "GREYM" ¶¶¶¶¶¶¶¶¶     ");
	printf("¶¶¶¶¶¶¶¶       ¶¶¶¶¶¶¶¶¶  "GREYM2"¶¶¶\n");
	printf("¶¶¶ "GREYM"¶¶¶¶¶¶¶¶¶¶¶¶¶   ");
	printf("¶¶¶¶¶¶¶¶¶¶¶   ¶¶¶¶¶¶¶¶¶¶¶¶"GREYM2"   ¶\n");
	printf("¶¶ "GREYM"¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"GREYM2"  ¶\n");
	printf("¶  "GREYM"¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"GREYM2" ¶\n");
	printf("¶  "GREYM"¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"GREYM2" ¶\n");
	printf("¶  "GREYM"¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"GREYM2" ¶\n");
	printf("¶  "GREYM"¶¶¶¶¶¶¶¶¶");
	printf(MAGENTA"saroca-f"GREYM"¶¶¶¶¶¶¶¶¶¶¶");
	printf(MAGENTA"schamizo"GREYM"¶¶¶¶¶¶¶¶¶"GREYM2" ¶\n");
}

void	ft_enter(void)
{
	first_part();
	printf("¶¶ "GREYM"¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"GREYM2" ¶\n");
	printf("¶¶  "GREYM"¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"GREYM2"  ¶\n");
	printf("¶¶¶  "GREYM"¶¶¶¶¶¶     ¶¶    ¶¶¶");
	printf("¶¶¶¶    ¶¶     ¶¶¶¶¶¶"GREYM2"  ¶¶\n");
	printf("¶¶¶¶   "GREYM"¶¶¶¶            ¶¶");
	printf("¶¶             ¶¶¶¶"GREYM2"   ¶¶¶\n");
	printf("¶¶¶¶¶¶   "GREYM"¶¶¶            ¶");
	printf("¶             ¶¶¶"GREYM2"   ¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶¶                                   ¶¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶                           ¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶               ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf("¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶\n");
	printf(YELLOW" __  __ ___ _   _ ___ ____  _   _ _____ _     _     \n");
	printf("|  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |    \n");
	printf("| |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | | \n");
	printf("| |  | || || |\\  || | ___) | |-| | |___| |___| |___ \n");
	printf("|_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____|\n");
}
/***
 *      __  __ ___ _   _ ___ ____  _   _ _____ _     _     
 *     |  \/  |_ _| \ | |_ _/ ___|| | | | ____| |   | |    
 *     | |\/| || ||  \| || |\___ \| |_| |  _| | |   | |    
 *     | |  | || || |\  || | ___) | |-| | |___| |___| |___ 
 *     |_|  |_|___|_| \_|___|____/|_| |_|_____|_____|_____|
 *                                                         
 */