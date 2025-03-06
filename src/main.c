#include "ft_header.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int	main(int argc, char **argv)
{
	t_game *game;
	WINDOW *wind;
	int	count;
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

	if(argc > 1)
		count = 10 * atoi(argv[1]);
	else
		count = 10 * 10;
	while(count--){
		if(!update_game(game))
			goto clean;
		render_game(game);
		nanosleep(&duration,  NULL);
	}
clean:
	free_game(game);
	endwin();
	delwin(wind);
}
