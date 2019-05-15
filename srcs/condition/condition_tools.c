#include <doom.h>

void add_events(t_game * game, t_entity e_actif, t_condition condi , t_entity e_passif)
{
	t_game_event * elem = (t_game_event *)malloc(sizeof(t_game_event));

	*elem = (t_game_event){
			(t_pelem) {NULL, NULL},
			(t_trigger){
				e_actif, condi, e_passif // Game event : list event wanted
				}
			};

	lppush(&game->waiting_events, elem);
}