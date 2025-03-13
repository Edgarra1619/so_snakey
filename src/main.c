#include "ft_header.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


int	main(void)
{
	t_game *game;
	WINDOW *wind;
	const struct timespec duration = {0, 100000000};

	game = NULL;
	wind = initscr();
	if(!wind)
		goto clean;
	start_color();
	cbreak();
	curs_set(0);
	noecho();
	game = start_game(NULL);
	if(!game)
		goto clean;
	while(1){
		game = update_game(game);
		if(!game)
			goto clean;
		render_game(game);
		nanosleep(&duration,  NULL);
	}
clean:
	free_game(game);
	endwin();
	delwin(wind);
}
