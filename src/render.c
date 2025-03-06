#include "ft_header.h"
#include <ncurses.h>

void	put_fillchar(int x, int y, chtype c, int color)
{
	color_set(color, NULL);
	mvaddch(y, x * 2, c);
	mvaddch(y, x * 2 + 1, c);
}
void	render_game(t_game *game)
{
	static _Bool	first_render = 1;
	t_snakelist	*current;
	const int	apple_color = 1;
	const int	snake_color = 2;

	if(first_render)
	{
		init_pair(apple_color, COLOR_RED, COLOR_RED);
		init_pair(snake_color, COLOR_GREEN, COLOR_GREEN);
		first_render = 0;
		current = game->snake_head;
		while(current)
		{
			put_fillchar(current->position[0], current->position[1],ACS_BLOCK, snake_color);
			current = current->next;
		}
		refresh();
		return ;
	}
	put_fillchar(game->snake_head->position[0], 
	      game->snake_head->position[1], ' ', snake_color);
	put_fillchar(game->previous_tail[0], game->previous_tail[1],' ', 0);
	put_fillchar(game->apple[0], game->apple[1], ' ', apple_color);
	refresh();
}
