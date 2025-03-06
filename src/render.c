#include "ft_header.h"
#include <ncurses.h>

void	put_fillchar(	int x, int y, chtype c, unsigned char color)
{
	mvaddch(y,x, c);
}
void	render_game(t_game *game)
{
	static _Bool	first_render = 1;
	t_snakelist	*current;

	if(first_render)
	{
		first_render = 0;
		current = game->snake_head;
		while(current)
		{
			put_fillchar(current->position[0], current->position[1],ACS_BLOCK, 0);
			current = current->next;
		}
		refresh();
		return ;
	}
	put_fillchar(game->snake_head->position[0], game->snake_head->position[1],ACS_BLOCK, 0);
	put_fillchar(game->previous_tail[0], game->previous_tail[1],' ', 0);
	refresh();
}
