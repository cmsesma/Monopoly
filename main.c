//#include <stdio.h>
#include "board.h"

int main(int argc, char** argv) {
  //printf("Beginning of main\n");

  GameState game_state = setup(argv[1], argv[2], argv[3]);
  //printf("After set up in main\n");
  Move move;

  while(!is_game_over(&game_state)){
    do{
      display_game_state(&game_state);
      //printf("Print statement in main checking gamestate.player_turn value: %d\n", game_state.player_turn);
      move = get_move(&game_state.players[game_state.player_turn]);
      make_move(&move, &game_state);
    }while(!move.ends_turn);
    change_turn(&game_state);
  }

  display_game_state(&game_state);
  declare_winners(&game_state);
  delete_game_state(&game_state);


  return 0;
}


