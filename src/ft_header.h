#ifndef FT_HEADER_H
# define FT_HEADER_H

typedef struct s_snakelist
{
	struct s_snakelist *next;
	struct s_snakelist *previous;
	int	position[2];
} t_snakelist;

typedef struct s_game
{
	t_snakelist	*snake_head;
	t_snakelist	*snake_tail;
	int		dir;
	int		apple[2];
	int		score;
	int		previous_tail[2];
} t_game;


t_game *start_game(t_game *game);
void	render_game(t_game *game);
int	update_game(t_game *game);
void	free_game(t_game *game);


#endif
