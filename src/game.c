#include "ft_header.h"
#include <stdlib.h>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>

int	insert_snakepart(t_snakelist **pos)
{
	t_snakelist	*new_part;
	if(pos == NULL)
		return (0);
	new_part = malloc(sizeof (*new_part));
	if(!new_part)
		return (0);
	new_part->next = *pos;
	if(*pos)
		(*pos)->previous = new_part;
	*pos = new_part;
	return (1);
}


void	free_game(t_game *game)
{
	t_snakelist	*temp;
	if(!game)
		return ;

	while (game->snake_head)
	{
		temp = game->snake_head->next;
		free(game->snake_head);
		game->snake_head = temp;
	}
	free(game);
}

t_game*	start_game(t_game *game)
{
	
	struct termios info;
	tcgetattr(0, &info);
	info.c_lflag &= ~ICANON;
	info.c_cc[VMIN] = 0;
	info.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &info);
	
	int	i;
	
	if(game)
		free_game(game);
	game = malloc(sizeof(*game));
	if(!game)
		return (NULL);
	game->score = 0;
	game->snake_head = NULL;
	game->apple[0] = game->apple[0] % (COLS/2);
	game->apple[1] = game->apple[1] % LINES;
	game->previous_tail[0] = 0;
	game->previous_tail[1] = 0;
	game->snake_tail = 0;
	game->dir = 0;
	i = 0;
	while(i++ < 3){
		if(!insert_snakepart(&game->snake_head))
		{
			free(game);
			return (NULL);
		}
		game->snake_head->position[0] = (COLS/2) / 2;
		game->snake_head->position[1] = LINES / 2 - i;
		if (i == 1)
			game->snake_tail = game->snake_head;
	}

	return (game);
}

int	update_game(t_game *game)
{
	int	next_pos[2];
	char	c = 0;
	read(0, &c, 1);
	switch(c)
	{
		case 'a':
			game->dir = 0;
			break;
		case 'd':
			game->dir = 1;
			break;
		case 'w':
			game->dir = 2;
			break;
		case 's':
			game->dir = 3;
			break;
	}

	// TODO check some input
	next_pos[0] = game->snake_head->position[0];
	next_pos[1] = game->snake_head->position[1];
	if(game->dir & 0b01)
		next_pos[(game->dir & 0b010) && 1] += 1;
	else
		next_pos[(game->dir & 0b010) && 1] -= 1;


	if (	   next_pos[0] == game->apple[0]
		&& next_pos[1] == game->apple[1])
	{
		if(!insert_snakepart(&game->snake_head))
			return (0);
		game->snake_head->position[0] = next_pos[0];
		game->snake_head->position[1] = next_pos[1];
		game->apple[0] = rand() % (COLS/2);
		game->apple[1] = rand() % LINES;
	}
	else
	{
		game->previous_tail[0] = game->snake_tail->position[0];
		game->previous_tail[1] = game->snake_tail->position[1];
		game->snake_head->previous = game->snake_tail;
		game->snake_tail->next = game->snake_head;
		game->snake_tail->position[0] = next_pos[0];
		game->snake_tail->position[1] = next_pos[1];
		game->snake_tail->previous->next = NULL;
		game->snake_head = game->snake_tail;
		game->snake_tail = game->snake_head->previous;
		game->snake_head->previous = NULL;
	}
	return (1);
}

