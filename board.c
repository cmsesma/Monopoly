#include "board.h"
#include <stdlib.h>
//#include <ctype.h>
//#include <stdio.h>
#include <string.h>
//#include <stdbool.h>

//#define maxSze 100
//#define maxChar 15

//#define DEBUG


GameState setup(char* rules_file, char* board_file, char* random_nums_file){ // function specifies board & rules
  //printf("In setup function\n");
  //printf("rules file = %s\n", rules_file);
  //printf("board file = %s\n", board_file);
  //printf("random nums file = %s\n", random_nums_file);
  GameState game_state;
  //game_state = (GameState*)malloc(sizeof(GameState));


  (game_state).rules = read_rules_file(rules_file, board_file,random_nums_file);
  (game_state).board = read_board_file(rules_file,board_file,random_nums_file);
  (game_state).randoms = read_random_nums_file(rules_file,board_file,random_nums_file);
  (game_state).players = read_players(rules_file);


  game_state.player_turn = 0;

  game_state.randoms->count = 0;
  //printf("Whose move it is: %d\n", game_state.players->whose_move_is_it);

  //game_state.num_turns_so_far = (int)malloc(sizeof(game_state));

  return game_state;
}

struct Players_Struct* read_players(char* rules_file){
  #ifdef DEBUG
  printf("inside player function\n");
  #endif

  GameState game_state;

  //struct GameState_struct *gamestate;
  //gamestate = (*gamestate)malloc(sizeof(gamestate));
  //gamestate->players = malloc(sizeof(struct Players_Struct));

  //game_state.players = malloc(sizeof(Players));

  int num_players = 0;
  printf("How many players will be playing: ");
  scanf("%d", &num_players);
  //Players *gplayers;
  //gplayers = (Players*)malloc(sizeof(Players) * num_players);

  game_state.players = (Players*)malloc(sizeof(Players) * num_players);
  game_state.players->num_players = num_players;
  game_state.players->min_player_name = 0;
  game_state.players->max_player_name = ((game_state.players->num_players ) -1);

#ifdef DEBUG
  printf("printing the number of players here:%d\n", game_state.players->num_players);
  printf("this: %d\n",game_state.players->num_players);
  //game_state.players = (*Players)malloc(game_state.players->num_players * sizeof(Players));
#endif

  //game_state.players->num_players = (int)malloc(sizeof(Players));

  //printf("How many players?\n");
  //scanf("%d", &game_state.players->num_players);
  //gamestate.current_num_players = gamestate.num_players_to_start;

  game_state.num_turns_so_far = 0;
  //game_state.players->whose_move_is_it = 0;

  /*printf("number of players =%d\n", game_state.players->num_players);

  for(int i = 0; i < game_state.players->num_players; i++) {
    printf("makes it here\n");
    game_state.players[i].player_name = (int)malloc(sizeof(Players));
    game_state.players[i].cash_have =(int)malloc(sizeof(Players));
    game_state.players[i].properties_owned = (char)malloc(sizeof(Players));
    game_state.players[i].player_position = (int)malloc(sizeof(Players));
    game_state.players[i].turn_number_for_player_turn = (int)malloc(sizeof(Players));
  }*/

  //EDIT PROPERTIES OWNED, organized by set then within set by their instraset ID

  FILE *fp;
  fp = fopen(rules_file,"r");
  if( fp == NULL ) {
    printf("Error if statement of read rules file\n");
    exit(0);
  }

  int starting_cash = 0;
  fscanf(fp, "Starting Cash: %d\n", &starting_cash);
  fclose(fp);
  #ifdef DEBUG
  printf("STARTING CASH = %d\n",starting_cash);
  #endif

  //game_state.players->prop = (Property*)malloc(sizeof(Property));
  //working on this, own multiple properties & each prop has own characteristics


  char starting_properties_owned =' ';
  int starting_position = 0;
#ifdef DEBUG
  printf("Here\n");
  printf("!! starting cash = %d\n", starting_cash);
#endif
  //for(int i = 0; i < game_state.players->num_players; i++){
  for (int i = 0; i < num_players; i++){
#ifdef DEBUG
    printf("In for loop about player info\n");
    printf("Value of i = %d\n", i);
#endif
    game_state.players[i].player_name = i;
    //game_state.players[i].have_rolled_or_not = false;
    game_state.players[i].turn_number_for_player_turn = 0;
    game_state.players[i].cash_have = starting_cash ;
    game_state.players[i].properties_owned= starting_properties_owned ;
    game_state.players[i].player_position= starting_position;
#ifdef DEBUG
    printf("Player %d name: %d\n",i, game_state.players[i].player_name );
    printf("Amount cash they have: %d\n", game_state.players[i].cash_have);
    printf("Properties they have: %s\n", &game_state.players[i].properties_owned);
    printf("Position of player: %d\n", game_state.players[i].player_position);
#endif
  }

  game_state.players->amount_money_in_properties = 0; //initializing
  game_state.players->total_amount_of_money = 0; //initializing
  game_state.players->in_game_or_not = 0; //initializing, if 0 in game if -1 not in game


  return game_state.players;

}


struct Rules_Struct* read_rules_file(char* rules_file, char* board_file, char* random_nums_file){
#ifdef DEBUG
  printf("inside read rules function\n");
#endif
  //printf("rules file = %s\n", rules_file);
  GameState game_state;

  //struct GameState_struct *gamestate;
  //gamestate = malloc(sizeof(*gamestate));
  //gamestate->rules = malloc(sizeof(struct Rules_Struct));

  game_state.rules = (Rules*)malloc(sizeof(Rules));

  FILE *fp;
  fp = fopen(rules_file,"r");
  if( fp == NULL ) {
    printf("Error if statement of read rules file\n");
    exit(0);
  }

  /*game_state.rules->starting_cash =(int)malloc(sizeof(Rules));
  game_state.rules->turn_limit =(int)malloc(sizeof(Rules));
  game_state.rules->num_players_to_end =(int)malloc(sizeof(Rules));
  game_state.rules->property_multiplier =(int)malloc(sizeof(Rules));
  game_state.rules->num_houses_before_hotel =(int)malloc(sizeof(Rules));
  game_state.rules->houses_evenly =(char)malloc(sizeof(Rules));
  game_state.rules->money_free_parking =(char)malloc(sizeof(Rules));
  game_state.rules->auction_properties =(char)malloc(sizeof(Rules));
  game_state.rules->salary_multiplier_go =(int)malloc(sizeof(Rules));
*/
  //printf("%c", ch);

  fscanf(fp, "Starting Cash: %d\n", &game_state.rules->starting_cash);
  fscanf(fp, "Turn Limit (-1 for no turn limit): %d\n", &game_state.rules->turn_limit);
  fscanf(fp, "Number of Players Left To End Game: %d\n", &game_state.rules->num_players_to_end);
  fscanf(fp, "Property Set Multiplier: %d\n", &game_state.rules->property_multiplier);

  fscanf(fp, "Number of Houses Before Hotels: %d\n", &game_state.rules->num_houses_before_hotel); //not using
  fscanf(fp, "Must Build Houses Evenly: %s\n", &game_state.rules->houses_evenly); //not using
  fscanf(fp, "Put Money In Free Parking: %s\n", &game_state.rules->money_free_parking); //not using
  fscanf(fp, "Auction Properties: %s\n", &game_state.rules->auction_properties); //not using

  fscanf(fp, "Salary Multiplier For Landing On Go: %d\n", &game_state.rules->salary_multiplier_go);

#ifdef DEBUG
  printf("Starting Cash = %d\n", game_state.rules->starting_cash);
  printf("turn limit = %d\n", game_state.rules->turn_limit);
#endif
  //printf("players to end = %d\n", gamestate->rules->num_players_to_end);
  //printf("property mult = %d\n", gamestate->rules->property_multiplier);

  //printf("houses before hotel = %d\n", rules.num_houses_before_hotel);
  //printf("houses evenly = %s\n", &rules.houses_evenly);
  //printf("money free parking = %s\n", &rules.money_free_parking);
  //printf("auction props = %s\n", &rules.auction_properties);

  //printf("salary mult at go = %d\n", gamestate->rules->salary_multiplier_go);


  fclose(fp);
  return game_state.rules;
}


struct Board_Struct* read_board_file(char* rules_file, char* board_file, char* random_nums_file) {
#ifdef DEBUG
  printf("inside read board function\n");
#endif
  //printf("board file = %s\n", board_file);

  //Board board;
  GameState game_state;

  //when initialized it causes seg fault
  //printf("printing this to check %d", game_state.board->owned_by);



  FILE *boardFile;
  boardFile = fopen(board_file, "r");
  if (boardFile == NULL) { //fp == NULL
    printf("In error if statement\n");
    exit(0);
  }

  //game_state.board->num_spaces_on_board =(int)malloc(sizeof(Board));

  int num_spaces_on_board;
  //fscanf(boardFile,"Number of Spaces,%d,,,,,,,,\n", &game_state.board->num_spaces_on_board);
  fscanf(boardFile,"Number of Spaces,%d,,,,,,,,\n", &num_spaces_on_board);
  fscanf(boardFile,",,,,,,,,,\n");
  fscanf(boardFile,",,,,,,,,,\n");
  fscanf(boardFile,"Type,Set Id,Intraset Id,Name,Property Cost,House Cost,Hotel Cost,Rent,Rent with House,Rent With Hotel\n");


  game_state.board = (Board*)malloc(sizeof(Board) * num_spaces_on_board);

  game_state.board->num_spaces_on_board = num_spaces_on_board;

  /*for(int i = 1; i < game_state.board->num_spaces_on_board; i++) {
    game_state.board[i].set_ID =(int)malloc(sizeof(Board));
    game_state.board[i].intraset_ID = (int)malloc(sizeof(Board));
    game_state.board[i].name = (char)malloc(sizeof(maxChar));
    game_state.board[i].property_cost = (int)malloc(sizeof(Board));
    game_state.board[i].house_cost = (int)malloc(sizeof(Board));
    game_state.board[i].hotel_cost = (int)malloc(sizeof(Board));
    game_state.board[i].rent = (int)malloc(sizeof(Board));
    game_state.board[i].rent_with_house = (int)malloc(sizeof(Board));
    game_state.board[i].rent_with_hotel = (int)malloc(sizeof(Board));
  }*/

  /*for(int i = 0; i < 1; i++){
    game_state.board[i].name = (char)malloc(sizeof(maxChar));
  }*/
  for(int i = 0; i < 1; i++) {
    fscanf(boardFile, "Go,%d,%[^,],,,,,,,\n", &game_state.board[i].rent, game_state.board[i].name);
  }
#ifdef DEBUG
  printf("num spaces = %d\n", game_state.board->num_spaces_on_board);
  printf("amount to collect at go = %d\n", game_state.board[0].rent);
  printf("board name = %s\n", game_state.board[0].name);
#endif

  int maxTxtSize = 5;
  int currentTxtSize = 0;
  for (int i = 1; i < game_state.board->num_spaces_on_board; i++) {
    //printf("In read board for loop\n");
    fscanf(boardFile, "Property,%d,%d,", &game_state.board[i].set_ID, &game_state.board[i].intraset_ID);

    //char temp[15];

    fscanf(boardFile, "%[^,],", (game_state.board[i].name));
    currentTxtSize = strlen(game_state.board[i].name);
    if (currentTxtSize > maxTxtSize){
      maxTxtSize = currentTxtSize;
    }

    fscanf(boardFile,"%d,%d,%d,%d,%d,%d\n", &game_state.board[i].property_cost, &game_state.board[i].house_cost, &game_state.board[i].hotel_cost, &game_state.board[i].rent, &game_state.board[i].rent_with_house, &game_state.board[i].rent_with_hotel);
#ifdef DEBUG
    printf("%d\n", game_state.board[i].set_ID);
    printf("%d\n", game_state.board[i].intraset_ID);
    printf("%s\n", game_state.board[i].name);
    printf("%d\n", game_state.board[i].property_cost);
    printf("%d\n", game_state.board[i].house_cost);
    printf("%d\n", game_state.board[i].hotel_cost);
    printf("%d\n", game_state.board[i].rent);
    printf("%d\n", game_state.board[i].rent_with_house);
    printf("%d\n", game_state.board[i].rent_with_hotel);
#endif
  }
  game_state.board->maxTxtSize = maxTxtSize;



  game_state.board->set = (Set*)malloc(sizeof(Set) * ((game_state.board[(game_state.board->num_spaces_on_board) - 1].set_ID)+1) );

  //printf("THIS %d\n", game_state.board[(game_state.board->num_spaces_on_board) - 1].set_ID);

  //int set0 = 0, set1 = 0, set2 = 0, set3 = 0, set4 = 0, set5 = 0, set6 = 0, set7 = 0;
  for (int i = 1; i < game_state.board->num_spaces_on_board; i ++) {
    for (int j = 0; j <= game_state.board[(game_state.board->num_spaces_on_board) - 1].set_ID; j++) {
      //printf("value of i: %d, value of j: %d\n",i,j);
      if (game_state.board[i].set_ID == j) {
        //printf("in if statement\n");
        game_state.board->set[j].set_num++;
        break;
      }
    }
  }
  for (int i = 0; i < game_state.board->num_spaces_on_board; i ++) {
    game_state.board[i].owned_by = -1; //initializing, if -1 then not owned
  }

  //printf("# of props in set 0: %d\n",game_state.board->set[0].set_num);
  //printf("# props in set 1: %d\n",game_state.board->set[1].set_num);
  //printf("# props in set 2: %d\n",game_state.board->set[2].set_num);
  //sometimes correct sometimes not??

  fclose(boardFile);
  return game_state.board;
}


struct Random_Nums_Struct* read_random_nums_file(char* rules_file, char* board_file, char* random_nums_file){
#ifdef DEBUG
  printf("inside read random nums function\n");
#endif
  GameState game_state;
  FILE *fp;
  fp = fopen(random_nums_file,"r");
  if( fp == NULL ) {
    exit(0);
  }


  int x = 1;
  int y = 0;
  fscanf(fp,"%d", &y);
  while(!feof(fp)) {
#ifdef DEBUG
    printf("Reached while read random numbers file loop\n");
    printf("this value: %d\n", y);
#endif
    //fscanf(fp,"%d", &game_state.randoms[i].num);
    x++;
    fscanf(fp,"%d", &y);
  }
  game_state.max_random_num = x;
  fclose(fp);



  fp = fopen(random_nums_file,"r");
  if( fp == NULL ) {
    exit(0);
  }

  game_state.randoms = (Randoms*)malloc(sizeof(Randoms) * game_state.max_random_num);

  int i = 0;
  fscanf(fp,"%d", &game_state.randoms[i].num);
#ifdef DEBUG
  printf("random number %d = %d\n", i, game_state.randoms[i].num);
#endif
  while(!feof(fp)) {
#ifdef DEBUG
    printf("Reached second while read random numbers file loop\n");
    //game_state.randoms[i].num =(int)malloc(sizeof(Randoms));
#endif
    //fscanf(fp,"%d", &game_state.randoms[i].num);
    i++;
    fscanf(fp,"%d", &game_state.randoms[i].num);
#ifdef DEBUG
    printf("random number %d = %d\n", i, game_state.randoms[i].num);
#endif
  }

#ifdef DEBUG
  printf("testing random number %d = %d\n", 0, game_state.randoms[0].num);
  printf("testing random number %d = %d\n", 1, game_state.randoms[1].num);
  printf("testing random number %d = %d\n", 2, game_state.randoms[2].num);
  printf("max random number = %d\n", game_state.max_random_num);
#endif

  game_state.randoms->max_random = game_state.max_random_num;
#ifdef DEBUG
  printf("max random number checking again = %d\n", game_state.randoms->max_random);
#endif
  fclose(fp);
  return game_state.randoms;
}




GameState display_game_state(GameState* game_state){
#ifdef DEBUG
  printf("inside display game function\n");
#endif  //GameState gamestate;
  //Board board;

  //printf("num spaces on board = %d\n", game_state->board->num_spaces_on_board);
  //printf("testing %s\n",game_state->board[0].name);
  //printf("testing%s\n",game_state->board[1].name);

  int print_at_least = game_state->board->maxTxtSize+1;
  int len_name = 0;
  char mak = ' ';

  for (int i = 0; i < game_state->board->num_spaces_on_board; i++) {
    //printf("In for loop of display game function\n");
    printf("%d | %s", i,game_state->board[i].name);
    len_name = print_at_least - (strlen(game_state->board[i].name));
    printf("%*c|     ",len_name, mak);
    for (int x = game_state->players->min_player_name; x <= game_state->players->max_player_name; x++){
      if (game_state->players[x].in_game_or_not != -1 && game_state->players[x].player_position == i) { //if it doesnt equal -1, it equals 0 which means theyre in the game

        printf("%d ", game_state->players[x].player_name);
      }
    }
    printf("\n");
  }

  return *game_state;
}

GameState declare_winners(GameState* game_state){
#ifdef DEBUG
  printf("inside declare winners function\n");
#endif
  //Players players;


  if(game_state->players->num_players == 1){
    printf("The winners are\n");
    //printf("testing: %d\n", game_state->player_turn);
    printf("Player %d\n", game_state->players[game_state->player_turn].player_name); //print only players name
  }else {

#ifdef DEBUG
    printf("Inside else statement bc more than one player left\n");
#endif

    if (game_state->rules->turn_limit == 0){
      printf("The winners are\n");
      for (int x = game_state->players->min_player_name; x <= game_state->players->max_player_name; x++){
      printf("Player %d\n",game_state->players[x].player_name);
      }
      return *game_state;
    }



    for (int i = 0; i < game_state->board->num_spaces_on_board; i++) { //looping thru all spaces on the board
      for (int x = game_state->players->min_player_name; x <= game_state->players->max_player_name; x++) { //looping thru all players
        if (game_state->players[x].in_game_or_not != -1) { //makes sure if valid or not
          if(game_state->board[i].owned_by == game_state->players[game_state->player_turn].player_name) {
            game_state->players[x].amount_money_in_properties = game_state->players[x].amount_money_in_properties + game_state->board[i].property_cost;

          }
        }
      }
    }

    for (int x = game_state->players->min_player_name; x <= game_state->players->max_player_name; x++) {
      if (game_state->players[x].in_game_or_not != -1) {
        game_state->players[x].total_amount_of_money = game_state->players[x].cash_have + game_state->players[x].amount_money_in_properties;
      }
    }

#ifdef DEBUG
    printf("Makes it here in declare winner function\n");
#endif

    int i = 0;
    int most_money = game_state->players[game_state->players->min_player_name].total_amount_of_money; //most money set to amount of first player's money amount
    int index_of_person_with_most_money[game_state->players->num_players];

#ifdef DEBUG
    printf("Makes it farther in declare winner function\n");
    printf("The number of total players are: %d\n", game_state->players->num_players);
#endif

    for (int i = 0; i < game_state->players->num_players;i++){ //initializing every space in array
      index_of_person_with_most_money[i] = 0;
    }

#ifdef DEBUG
    printf("Makes it more in declare winner function\n");
#endif

    for (int x = game_state->players->min_player_name; x <= game_state->players->max_player_name; x++){ //for every player
      if (game_state->players[x].total_amount_of_money >= most_money) { //if current person's amount of money is larger then saved most money
        most_money =game_state->players[x].total_amount_of_money; //replace most money amount with new most amount
        index_of_person_with_most_money[i] = x;  //save player name into an index
        i++;
      }
    }

    printf("The winners are\n");

    for (int x = game_state->players->min_player_name; x <= game_state->players->max_player_name; x++) {//for every player
      if (game_state->players[x].in_game_or_not != -1) {
        printf("Player %d\n", game_state->players[index_of_person_with_most_money[x]].player_name); //print all players name
      }
    }
    //MAKE IT SO IT PRINTS THE PERSON WITH THE LARGEST AMOUNT OF MONEY


    // Net worth is the sum of all of the players cash plus the purchase price of all of the properties they own.
    //calculate net worth and print players name
    // if more than one w/ same net worth, declare in ascending order
  }
  return *game_state;
}


Move get_move(Players* players){
  //GameState game_state;
  Move move;

  //printf("whose move it is:%d\n", players->whose_move_is_it);

#ifdef DEBUG
  printf("In get move function\n");
  printf("printing name of the player whose turn it is: %d\n", players->player_name);

  //printf("printing the name of the zero player:%d\n", players[0].player_name);
  //printf("printing the name of the third player:%d\n", players[3].player_name);


  printf("Printing this in get move function, number of turns for select player %d :%d\n", players->player_name,  players->turn_number_for_player_turn);
#endif

  /*if (players->in_game_or_not != -1){
    move.rolls_dice = 0;
    move.ends_turn = 0;
    move.inspect_player = 0;
    move.leave_game = 1;
    return move;
  }*/

  if (players->turn_number_for_player_turn == 0) { //its the chosen player's first turn or if they've only been inspecting players
    //printf("inside first if loop of get move function\n");
    // int move_chosen = 0;
    printf("Player %d please choose an action\n", players->player_name);
    printf("1: Roll Dice\n");
    printf("2: Inspect Player\n");
    printf("3: Leave Game\n");
    scanf("%d", &players->chosen_action);
    //printf("player turn input = %d\n", players->chosen_action);

    //&gamestate.players[gamestate.player_turn]
    if(players->chosen_action == 1){
      //printf("hit 1 \n");
      move.rolls_dice = 1;
      move.ends_turn = 0;
      move.inspect_player = 0;
      move.leave_game = 0;
      //printf("printing :%d\n", move.rolls_dice);
    }
    if(players->chosen_action == 2){
      //printf("hit 2\n");
      move.inspect_player = 1;
      move.rolls_dice = 0;
      move.ends_turn = 0;
      move.leave_game = 0;
      //printf("%d\n",move.inspect_player);
    }
    if(players->chosen_action == 3){
      //printf("hit 3\n");
      printf("Your action: ");
      move.leave_game = 1;
      move.rolls_dice = 0;
      move.ends_turn = 0;
      move.inspect_player = 0;
    }

  } else { //the chosen's player's 2nd/+ turn
    //printf("inside else loop of get move function bc its players 2nd/+ turn \n");
    printf("Player %d please choose an action\n", players->player_name);
    printf("1: End Turn\n");
    printf("2: Inspect Player\n");
    printf("3: Leave Game\n");
    scanf("%d", &players->chosen_action);
    //printf("player turn input = %d\n", players->chosen_action);
    if(players->chosen_action == 1){
      //printf("hit 1 \n");
      //move[1] = move.ends_turn;
      printf("Your action: ");
      move.ends_turn = 1;
      move.rolls_dice = 0;
      move.inspect_player = 0;
      move.leave_game = 0;
      //printf("printing :%d\n", move.rolls_dice);
    }
    if(players->chosen_action == 2){
      //printf("hit 2\n");
      move.inspect_player = 1;
      move.rolls_dice = 0;
      move.ends_turn = 0;
      move.leave_game = 0;
      //printf("%d\n",move.inspect_player);
    }
    if(players->chosen_action == 3){
      //printf("hit 3\n");
      printf("Your action: ");
      move.leave_game = 1;
      move.rolls_dice = 0;
      move.ends_turn = 0;
      move.inspect_player = 0;
    }
  }

  //print statements to check
  //printf("ends turn move %d\n", move.ends_turn);
  //printf("leave turn move %d\n", move.leave_game);
  //printf("inspect player move %d\n", move.inspect_player);
  //printf("rolling dice move %d\n", move.rolls_dice);
  return move;
}

Move make_move(Move* move, GameState* game_state){ //only to inspect or to roll dice
#ifdef DEBUG
  printf("inside make move function\n");
#endif
  int player_to_inspect = 0;
  int die_roll;


  game_state->move = (Move*)malloc(sizeof(Move));


  //printf("player chosen input = %d\n",game_state->players->chosen_action);

  if (move->rolls_dice == 1){
    game_state->num_turns_so_far++;
    game_state->players[game_state->player_turn].turn_number_for_player_turn++;
    //figure out dice roll
    die_roll =rollDice(game_state);
    printf("Your action: You rolled a %d!\n", die_roll);

    /*int before_dice_positon = 0;
    before_dice_positon = game_state->players[game_state->player_turn].player_position;*/
    //printf("before dice roll positon = %d\n", before_dice_positon);

    game_state->players[game_state->player_turn].player_position = game_state->players[game_state->player_turn].player_position + die_roll;
#ifdef DEBUG
    printf("new player positon = %d\n", game_state->players[game_state->player_turn].player_position);
#endif
    if (game_state->players[game_state->player_turn].player_position > ((game_state->board->num_spaces_on_board)-1)){ //if new combined position w/ dice is off the board
      game_state->players[game_state->player_turn].player_position = (game_state->players[game_state->player_turn].player_position - (game_state->board->num_spaces_on_board));
      game_state->players[game_state->player_turn].cash_have = game_state->players[game_state->player_turn].cash_have +  game_state->board[0].rent;
#ifdef DEBUG
      printf("%d cash now have\n", game_state->players[game_state->player_turn].cash_have);
#endif
      if (game_state->players[game_state->player_turn].player_position > ((game_state->board->num_spaces_on_board)-1)){
        game_state->players[game_state->player_turn].cash_have = game_state->players[game_state->player_turn].cash_have +  game_state->board[0].rent;
        game_state->players[game_state->player_turn].player_position = (game_state->players[game_state->player_turn].player_position - (game_state->board->num_spaces_on_board));
#ifdef DEBUG
        printf("%d cash now have\n", game_state->players[game_state->player_turn].cash_have);
#endif
        if (game_state->players[game_state->player_turn].player_position > ((game_state->board->num_spaces_on_board)-1)){
          game_state->players[game_state->player_turn].player_position = (game_state->players[game_state->player_turn].player_position - (game_state->board->num_spaces_on_board));
          if (game_state->board[game_state->players[game_state->player_turn].player_position].name != game_state->board[0].name){
            game_state->players[game_state->player_turn].cash_have = game_state->players[game_state->player_turn].cash_have +  game_state->board[0].rent;

          }
#ifdef DEBUG
          printf("%d cash now have\n", game_state->players[game_state->player_turn].cash_have);
#endif
        }
      }
#ifdef DEBUG
      printf("Roll is off the board if statement\n");
      printf("adjusted player positon = %d\n", game_state->players[game_state->player_turn].player_position);
#endif
      //if off the board then they have passed go
      //collect money bc passed go

    } else { //not off the board so keep combined w/ dice position
      //printf("not adjusted player positon = %d\n", game_state->players[game_state->player_turn].player_position);
    }

    if (game_state->board[game_state->players[game_state->player_turn].player_position].name == game_state->board[0].name){ //if the position theyre on if the go spot
#ifdef DEBUG
      printf("In if statement bc you landed on a go space\n");
#endif
      //exception for go spot
      game_state->players[game_state->player_turn].cash_have = game_state->players[game_state->player_turn].cash_have +  ((game_state->board[0].rent) * game_state->rules->salary_multiplier_go);
      //if land on go mult by salary mult for go
      //printf("Amount of money they now have = %d\n", game_state->players[game_state->player_turn].cash_have); //collecting salary
      //ask to end turn, inspect player, or leave

    } else { // not the go spot
#ifdef DEBUG
      printf("In else statement bc not on a go space\n");
#endif

      if (game_state->board[game_state->players[game_state->player_turn].player_position].owned_by == game_state->players[game_state->player_turn].player_name){
        //printf("Inside statement bc the spot theyre on is owned by themselves");
      }

      else if (game_state->board[game_state->players[game_state->player_turn].player_position].currently_owned == true ){  //if the property is owned
        //make a call to calculate/pay rent
#ifdef DEBUG
        printf("if statement bc property is owned\n");
#endif
        int rent = 0;
        rent = calcRent(game_state);


        //want to return rent, THEN check if rent if more than the money they have.
        //if so then bankrupt & all money/property goes to other player

        //printf("rent = %d\n", rent);
        //printf("cash they have = %d\n", game_state->players[game_state->player_turn].cash_have);
        //printf("player = %d\n",game_state->players[game_state->player_turn].player_name);


        if (rent > game_state->players[game_state->player_turn].cash_have ) {//they dont have enough money to pay rent

          printf("Player %d went bankrupt to Player %d\n", game_state->players[game_state->player_turn].player_name, game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].player_name);

          game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].cash_have += game_state->players[game_state->player_turn].cash_have;
          //rent = game_state->players[game_state->player_turn].cash_have; //if they dont have enough money, bankrupt & all money/prop to player owned that prop

          //giving property to designated owner/player
          for (int i = 1; i < game_state->board->num_spaces_on_board; i++){
            if (game_state->board[i].owned_by == game_state->players[game_state->player_turn].player_name){
              game_state->board[i].owned_by = game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].player_name;
            }
          }

          //game_state->board[game_state->players[game_state->player_turn].player_position].owned_by = game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].player_name;

          game_state->players[game_state->player_turn].in_game_or_not = -1;

          //if they go bankrupt then do they leave the game or change the turn?
          move->leave_game = 1;
          move->ends_turn = 1;

          //decreasing the total num players
          game_state->players->num_players--;


          //CHECK TO MAKE SURE THIS CAUSES THE PLAYER TO LEAVE THE GAME
          return *move;
        } else {  //they have enough money to pay, rent smaller
          // keep same rent value
        }
        //subtracting rent from current player (could be all money or part)
        game_state->players[game_state->player_turn].cash_have = game_state->players[game_state->player_turn].cash_have - rent;
        //adding rent to designated owner/player
        game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].cash_have = game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].cash_have + rent;
        printf("Player %d payed Player %d $%d for landing on %s\n",game_state->players[game_state->player_turn].player_name, game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].player_name, rent, game_state->board[game_state->players[game_state->player_turn].player_position].name);
      }else {
        //only reaches this only if not owned
        if (game_state->players[game_state->player_turn].cash_have >= game_state->board[game_state->players[game_state->player_turn].player_position].property_cost) {
          //if they have enough money to afford it
          char y_or_n;
          //if not owned, purchase/not
          printf("Player %d would you like to buy %s for $%d?\n",
                 game_state->players[game_state->player_turn].player_name,
                 game_state->board[game_state->players[game_state->player_turn].player_position].name,
                 game_state->board[game_state->players[game_state->player_turn].player_position].property_cost);
          printf("The rent on this property is $%d\n",
                 game_state->board[game_state->players[game_state->player_turn].player_position].rent);
          printf("You currently have $%d\n", game_state->players[game_state->player_turn].cash_have);
          printf("Y for yes, N for no: ");
          scanf("%s", &y_or_n);
#ifdef DEBUG
          printf("YOU CHOSE: %s\n", &y_or_n);
#endif
          if (y_or_n == 'y' || y_or_n == 'Y') {

            game_state->board[game_state->players[game_state->player_turn].player_position].currently_owned = true; //not saved that space is owned
            game_state->board[game_state->players[game_state->player_turn].player_position].owned_by = game_state->players[game_state->player_turn].player_name; //says owned by player name
            //purchased it, put in properties own struct
            //ask to end turn, inspect player, or leave

            //printf("checking this %d\n", game_state->players[game_state->player_turn].player_name);
            //printf("checking this name: %s", game_state->board[game_state->players[game_state->player_turn].player_position].name);

            game_state->players[game_state->player_turn].cash_have -= game_state->board[game_state->players[game_state->player_turn].player_position].property_cost;

          } else {
            //decided not to purchase it
            //ask to end turn, inspect player, or leave
          }

        } else {
          //dont have enough money to buy it
          printf("Player %d you do not have enough money to purchase %s\n",
                 game_state->players[game_state->player_turn].player_name,
                 game_state->board[game_state->players[game_state->player_turn].player_position].name);
          printf("%s costs $%d, but you only have $%d\n",
                 game_state->board[game_state->players[game_state->player_turn].player_position].name,
                 game_state->board[game_state->players[game_state->player_turn].player_position].property_cost,
                 game_state->players[game_state->player_turn].cash_have);
                 //displays board, asks if they want to end turn, inspect player, or leave game
        }
      }
    }
    //after they roll they can end turn, inspect player, or leave game
  }


  if (move -> inspect_player == 1){ //after inspect once can end turn, inspect player, or leave game
    game_state->num_turns_so_far++;
    //game_state->players[game_state->player_turn].turn_number_for_player_turn++;

    printf("Your action: Which player would you like to inspect?\n");
    //printf("%d\n", gamestate.players->num_players);
    for(int i = game_state->players->min_player_name; i <= game_state->players->max_player_name; i++ ) {
      if (game_state->players[i].in_game_or_not != -1 ){
      printf("%d for Player %d\n", i, i);
      }
    }
    scanf("%d", &player_to_inspect);

#ifdef DEBUG
    printf("player you are inspecting is %d\n", player_to_inspect);
    printf("player name is: %d\n", game_state->players[player_to_inspect].player_name);
    printf("player you are inspecting amount of cash they have is: %d\n", game_state->players[player_to_inspect].cash_have);

#endif

    printf("Your choice: Player %d\n", player_to_inspect);
    printf("  Cash: $%d\n", game_state->players[player_to_inspect].cash_have);
    printf("  Properties owned\n");

    int winner = 0;

    int tempVar1 = game_state->board[(game_state->board->num_spaces_on_board)-1].set_ID;
    int tempVar2 = game_state->board[(game_state->board->num_spaces_on_board)-3].set_ID;

    if (tempVar1 > tempVar2){
      winner = tempVar1;
    } else {
      winner = tempVar2;
    }

    for (int i = 0; i <= winner; i++) { //the number of set ID's //before was: game_state->board[(game_state->board->num_spaces_on_board)-1].set_ID
      printf("    %d: ", i);
      bool foundOne = false;
      //for (int x = 0; x <= game_state->board->set[i].set_num; x++){ //number of intraset ID's in the corresponding set ID
        for (int y = 0; y < game_state->board->num_spaces_on_board; y++){
          if (i == game_state->board[y].set_ID) {
            if(game_state->board[y].owned_by == player_to_inspect) {

              if (foundOne == true){
                printf(" | ");
              }
              foundOne = true;

              printf("%s", game_state->board[y].name);
            }
          }
        //if (game_state->players[x].player_position == i) {
#ifdef DEBUG
          //printf("space name %s\n", game_state->board[y].name);
          //printf("who space is owned by:%d\n",game_state->board[y].owned_by);
#endif
        }
      //}
      printf("\n");
    }
    //after they inspect they can roll dice, inspect, leave game
  }

  if (move -> leave_game == 1){//player chooses to leave game
    //all properties they owned is now unowned
    game_state->board[game_state->players[game_state->player_turn].player_position].currently_owned = false;
    game_state->board[game_state->players[game_state->player_turn].player_position].owned_by = -1;


    // use to bool to say that player left the game


    //they have no money
    game_state->players[game_state->player_turn].cash_have = 0;

    if (game_state->players[game_state->player_turn].player_name == game_state->players->max_player_name){
      //printf("IN THIS IF STATEMENT\n ");
      game_state->players->max_player_name = game_state->players->max_player_name -1;
      //printf("%d", game_state->players->max_player_name);

    }
    else if (game_state->players[game_state->player_turn].player_name == game_state->players->min_player_name){
      //printf("IN THIS ELSE IF STATEMENT\n ");
      game_state->players->min_player_name = game_state->players->min_player_name +1;
      //printf("%d", game_state->players->min_player_name);

    }

    //decrease the number of players in the game
    game_state->players->num_players--;

    move->ends_turn = 1; //ending the players turn


    //delete the player, in other functions if the player's name is -1 its not included
    game_state->players[game_state->player_turn].in_game_or_not = -1;

#ifdef DEBUG
    printf("Checking the new number of players: %d\n",game_state->players->num_players);
    printf("Checking the players name who left the game: %d\n",game_state->players[game_state->player_turn].player_name);
    printf("Checking the players turn in this section: %d\n",game_state->player_turn);
    printf("Checking value of in game_or_not = %d\n", game_state->players[game_state->player_turn].in_game_or_not);

#endif

  }
  //printf("which player #'s turn it is %d\n", game_state->player_turn);
  //printf("How many turns have occured total: %d\n", game_state->num_turns_so_far);
  return *move;

}

int rollDice(GameState* game_state) {
#ifdef DEBUG
  printf("inside roll dice function\n");
#endif
  int diceRoll1, diceRoll2;
  int min_val = 1;
  int max_val = 6;

#ifdef DEBUG
  printf("Value of random number 1: %d\n",game_state->randoms[game_state->randoms->count].num);
  printf("Value of random number count 1: %d\n",game_state->randoms->count);
  printf("Print max num: %d\n",game_state->randoms->max_random);

#endif

//printf("first here %d\n",game_state->randoms[game_state->randoms->count].num);

  diceRoll1 = min_val + (game_state->randoms[game_state->randoms->count].num % (1 + max_val - min_val));
//game_state->randoms->count++;
//printf("here %d\n",game_state->randoms[game_state->randoms->count].num);

/*if (game_state->randoms->count + 1 >= game_state->max_random_num){
  game_state->randoms->count = 0;
} else {
  game_state->randoms->count++;
}*/


  if(game_state->randoms->count < game_state->randoms->max_random){
#ifdef DEBUG
    printf("Reached in if statement\n");
#endif
    game_state->randoms->count++;
  } else {
#ifdef DEBUG
    printf("Reached in else statement\n");
#endif
    game_state->randoms->count = 0;
  }

#ifdef DEBUG
  printf("Value of random number count 2: %d\n",game_state->randoms->count);
  printf("Value of random number 2: %d\n",game_state->randoms[game_state->randoms->count].num);
#endif
  diceRoll2 = min_val + (game_state->randoms[game_state->randoms->count].num % (1 + max_val - min_val));
//game_state->randoms->count++;
/*if (game_state->randoms->count + 1 > game_state->max_random_num){
  game_state->randoms->count = 0;
} else {
  game_state->randoms->count++;
}*/

  if(game_state->randoms->count < game_state->randoms->max_random){
    game_state->randoms->count++;
  } else {
    game_state->randoms->count = 0;
  }

#ifdef DEBUG
  printf("Value of dice roll 1: %d\n",diceRoll1 );
  printf("Value of dice roll 2: %d\n", diceRoll2);
  printf("Value of dice roll 1+2: %d\n", diceRoll1 + diceRoll2);
#endif


  return diceRoll1 + diceRoll2;
}

GameState change_turn(GameState* game_state){ //if turn was ended, change turn to next player
#ifdef DEBUG
  printf("In change turn function\n");
  printf("num players = %d\n", (game_state->players->num_players));
  printf("Before change turn it is %d turn\n", game_state->player_turn);
#endif

  //printf("In change turn function\n");
  //printf("num players = %d\n", (game_state->players->num_players));
  //printf("Before change turn it is %d turn\n", game_state->player_turn);


  game_state->players[game_state->player_turn].turn_number_for_player_turn = 0; //reset the current players turn number to zero

  game_state->player_turn ++; //move to next players turn
  //int count_of_unmatched = 0; //intialize to zero
  //printf("After change turn it is %d turn\n", game_state->player_turn);

#ifdef DEBUG
  printf("After change turn it is now %d turn\n",game_state->player_turn);
#endif


  if(game_state->players[game_state->player_turn].in_game_or_not == -1) { //if this nxt player is no longer in the game, move to next player
    //printf("Reached if statement bc player name of current is -1\n");

#ifdef DEBUG
    printf("Reached if statement bc player name of current is -1\n");
#endif
    game_state->player_turn ++;
  }

  bool found  = false;
  for (int i = game_state->players->min_player_name; i <= game_state->players->max_player_name; i++) {
    if (game_state->player_turn == game_state->players[i].player_name) {
      found = true;
      break;
    }
  }
  if(found == false){
    int currentPlayer = game_state->player_turn;
    bool located = false;
    for(int i = currentPlayer + 1 ; i <= game_state->players->max_player_name; i++){
      for (int j = game_state->players->min_player_name; j <= game_state->players->max_player_name; j++) {
        if (i == game_state->players[j].player_name) {
          located = true;
          game_state->player_turn = i;
          break;
        }
      }
      if(located){
        break;
      }
    }

    for(int i =  game_state->players->min_player_name ; i <= currentPlayer; i++){
      for (int j = game_state->players->min_player_name; j <= game_state->players->max_player_name; j++) {
        if (i == game_state->players[j].player_name) {
          located = true;
          game_state->player_turn = i;
          break;
        }
      }
      if(located){
        break;
      }
    }

  }

 /* if (game_state->player_turn > ((game_state->players->max_player_name))){ //if the player's name/num whos turn it is is larger than the biggest name/num of playesr
    printf("---------------------in if statement here\n");
    //printf("this value is:%d\n", game_state->players->max_player_name);
    game_state->player_turn = ((game_state->players->min_player_name));
    printf("checking min value %d", game_state->players->min_player_name);

    for (int i = game_state->players->min_player_name; i < game_state->players->max_player_name; i++) { //for all the players in the range
      if (game_state->player_turn != game_state->players[i].player_name) {
        count_of_unmatched++;
      }
    }
    if (count_of_unmatched == game_state->players->num_players) {
      game_state->player_turn++;
    }

  } else {
    printf("-------------------in else statement here\n");
    bool found  = false;
    for (int i = game_state->players->min_player_name; i <= game_state->players->max_player_name; i++) {
      if (game_state->player_turn == game_state->players[i].player_name) {
        found = true;
        break;
      }
    }
    if(found == false) {
      game_state->player_turn++;
    }
    *//*printf("count of unmatched %d\n", count_of_unmatched);
    if (count_of_unmatched == game_state->players->num_players) {
      game_state->player_turn++;*//*
    //}
  }*/
#ifdef DEBUG
  printf("This value is: %d\n", game_state->player_turn);
#endif

  if(game_state->players[game_state->player_turn].in_game_or_not == -1) { //if this nxt player is no longer in the game, move to next player
#ifdef DEBUG
    printf("Reached if statement bc player name of current is -1\n");
#endif
    game_state->player_turn ++;
  }
  //printf("NOW player %d turn\n", game_state->player_turn);

#ifdef DEBUG
  printf("Value of whose turn it is leaving the function is: %d\n", game_state->player_turn);
#endif
  //printf("Value of whose turn it is leaving the function is: %d\n", game_state->player_turn);


  return *game_state;

}

bool is_game_over(GameState* game_state){
#ifdef DEBUG
  printf("inside game over function\n");
  printf("checking this number of turns so far value in game over function: %d\n", game_state->num_turns_so_far);
  printf("checking this rules turn limit value in game over function: %d\n", game_state->rules->turn_limit);


  if (game_state->rules->turn_limit == 0){
  //printf("reached here");
      return true;
   }



#endif
  //printf("current num players = %d\n", game_state->players->num_players);
  //printf("num players to end = %d\n", game_state->rules->num_players_to_end);
  //printf("total num turns = %d\n", game_state->num_turns_so_far);
  //printf("turn limit = %d\n", game_state->rules->turn_limit);
  //printf("MADE IT RIGHT HERE\n");

  if((game_state->players->num_players == game_state->rules->num_players_to_end) || (game_state->num_turns_so_far == game_state->rules->turn_limit)) {
#ifdef DEBUG
    printf("In first if statement of game over function\n");
#endif
    return true;

  } else {
#ifdef DEBUG
    printf("In else statement of game over function\n");
#endif
    return false;
  }
}


GameState delete_game_state(GameState* game_state){ //free everything
#ifdef DEBUG
  printf("inside delete game state function\n");
#endif
  free(game_state->rules);
  free(game_state->board->set);
  free(game_state->board);
  free(game_state->players);
  free(game_state->randoms);
  free(game_state->move);
  //free(game_state);

  return *game_state;
}


int calcRent(GameState* game_state){
#ifdef DEBUG
  printf("inside calc rent function\n");
#endif
  int rent = 0;

  int setIDnum =0;
  setIDnum = game_state->board[game_state->players[game_state->player_turn].player_position].set_ID;

  //int countSpacesOwned = 0;
  int countPropInSetOwned = 0;
  //looping thru all spaces on the board
  //loop thru to see which are owned by the player
  // out of what is owned, loop thru to set if setID matches

  for (int i = 1; i < game_state->board->num_spaces_on_board; i++) { //looping thru all spaces on the board
    //if(game_state->board[i].owned_by == game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].player_name){ //if the space is owned by the player who owns the other spots
      //printf("This spot %s\n", game_state->board[i].name);//printing name of spaces owned by player
      //countSpacesOwned ++;
      //for (int x = 0; x <= countSpacesOwned;x++){ //go thru spaces owned by player to check setID
        if ( game_state->board[i].set_ID == setIDnum && game_state->board[i].owned_by == game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].player_name){ //CHECK IF THIS LINE IS CORRECTLY SPECIFYING RIGHT BOARD
          //printf("This spot's set ID %d\n", game_state->board[i].set_ID);
          countPropInSetOwned++; //keep count of how many with same set ID are owned
        }
      //}
    //}
  }

#ifdef DEBUG

  printf("check name: %d\n", game_state->players[game_state->board[game_state->players[game_state->player_turn].player_position].owned_by].player_name);
  printf("checking count spaces owned in set own value : %d \n", countSpacesOwned);

  printf("checking prop in set own value : %d \n", countPropInSetOwned);
  printf("checking total number in set out of value : %d \n",game_state->board->set[setIDnum].set_num );

#endif

  /*printf("value of count prop in set owed: %d\n", countPropInSetOwned);
  printf("value of total they would need:%d\n", game_state->board->set[setIDnum].set_num);
  printf("value of set id num: %d\n", setIDnum);
*/

  if (countPropInSetOwned == game_state->board->set[setIDnum].set_num){  //if owns all the properties in a set : rent = (property set multiplier * rent)
    //printf("---------------in if statement of rent calc bc they own all properties in a set\n");

#ifdef DEBUG
    printf("in if statement of rent calc bc they own all properties in a set\n");
#endif

    rent = ( game_state->board[game_state->players[game_state->player_turn].player_position].rent) * (game_state->rules->property_multiplier);
    //printf("checking prop mult: %d\n", game_state->rules->property_multiplier);
    //printf("checking rent: %d\n", game_state->board[game_state->players[game_state->player_turn].player_position].rent);

  }else {//if not own all properties in set just pay rent
#ifdef DEBUG
    printf("in else statement of rent calc bc they don't own all properties in a set\n");
#endif
    rent = game_state->board[game_state->players[game_state->player_turn].player_position].rent;
  }

  return rent;
}

