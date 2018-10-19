#ifndef HOARDING_HOARDING_H
#define HOARDING_HOARDING_H

#endif //HOARDING_HOARDING_H
#include "typedefs.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Players_Struct{
  int num_players;
  int turn_number_for_player_turn;
  int max_player_name;
  int min_player_name;


  int player_name;
  int cash_have;
  char properties_owned;
  int player_position;

  int in_game_or_not;

  int amount_money_in_properties;
  int total_amount_of_money;

  //bool have_rolled_or_not;


  //int whose_move_is_it;
  //int player_turn;
  int chosen_action;

}Players;


typedef struct Board_Struct{

  int num_spaces_on_board;
  //int set;

  int set_ID;
  int intraset_ID;
  char name[25];
  int property_cost;
  int house_cost;
  int hotel_cost;
  int rent;
  int rent_with_house;
  int rent_with_hotel;
  bool currently_owned;
  int owned_by;

  struct Set_Struct *set;

  int maxTxtSize;


}Board;


typedef struct Set_Struct{
  int set_num;

}Set;

typedef struct GameState_struct{
  //int player_turn;
  //int whose_move_is_it;
  int num_turns_so_far;

  int player_turn;

  struct Rules_Struct *rules;
  struct Board_Struct *board;
  struct Players_Struct *players;

  struct Random_Nums_Struct *randoms;
  int max_random_num;

  struct Move_struct *move;

}GameState;

typedef struct Move_struct{
  int ends_turn;
  //int total_num_turns;
  int rolls_dice;
  int inspect_player;
  int leave_game;

  //struct GameState_struct *game_state;

}Move;

typedef struct Rules_Struct{
  int starting_cash;
  int turn_limit;
  int num_players_to_end;
  int property_multiplier;
  int num_houses_before_hotel; //not using
  char houses_evenly; //not using
  char money_free_parking; //not using
  char auction_properties; //not using
  int salary_multiplier_go;

}Rules;

typedef struct Random_Nums_Struct{
  int count;
  int num;

  int max_random;


}Randoms;

struct Players_Struct* read_players(char* rules_file);


struct Board_Struct* read_board_file(char* rules_file,char* board_file, char* random_nums_file);
struct Rules_Struct* read_rules_file(char* rules_file,char* board_file, char* random_nums_file);
struct Random_Nums_Struct* read_random_nums_file(char* rules_file,char* board_file, char* random_nums_file);
GameState setup(char* rules_file,char* board_file, char* random_nums_file);


GameState display_game_state(GameState* game_state);
GameState declare_winners(GameState* game_state);
GameState delete_game_state(GameState* game_state);

Move get_move(Players* players);

Move make_move(Move* move, GameState* game_state);
bool is_game_over(GameState* game_state);
GameState change_turn(GameState* game_state);

int rollDice(GameState* game_state);

int calcRent(GameState* game_state);