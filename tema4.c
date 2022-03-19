#include "utils.h"

#define Role_max_str_len 9
#define Max_location_str_len 20

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

PlayerRoles fromStringtoEnum(char str[]){
	if (strcmp(str, "Rotator") == 0){
		return Rotator;
	}
	if (strcmp(str, "Decoder") == 0){
		return Decoder;
	}
	if (strcmp(str, "Invertor") == 0){
		return Invertor;
	}
	if (strcmp(str, "Impostor") == 0){
		return Impostor;
	}
	return -1;
}


int numar_cifre(int n){
	int nr = 0;
	while(n > 0){
		nr++;
		n /= 10;
	}
	return nr;
}

// Task 1
void *RotateMatrix(void *input)
{
	// TODO

	int n;
	n = *(int *)input;

	int i, j;
	int **matrix;

	matrix = (int **)calloc(n, sizeof(int *));

	if (matrix == NULL){
		exit(303);
	}

	for (i = 0; i < n; i++){
		matrix[i] = (int *)calloc(n, sizeof(int *));
		if (matrix[i] == NULL){
			exit(303);
		}
	}

	//construirea matricei direct rotite
	//mai multe detalii in README
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			matrix[i][j] = (n - j) * pow(10, numar_cifre(i + 1)) + i + 1;
		}
	}

	char *result;
	result = (char *)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (result == NULL){
		exit(303);
	}

	//functia sprintf returneaza numarul de caractere copiate in 
	//result, urmand ca urmatoarea copiere sa se faca de la
	//result + nr (unde nr este numarul de caractere deja copiat in
	//in result)
	int nr = 0;


	for (i = 0; i < n; i++){

		for (j = 0; j < n - 1; j++){
			nr += sprintf(result + nr, "%d ", matrix[i][j]);
		}

		if (i < n - 1){
			nr += sprintf(result + nr, "%d\n", matrix[i][j]);
		} else {
			nr += sprintf(result + nr, "%d", matrix[i][j]);
		}
	}

	for (i = 0; i < n; i++){
		free(matrix[i]);
	}
	free(matrix);

	return (void *)result;
}

// Task 2
void *DecodeString(void *input)
{
	// TODO

	char str[MAX_LEN_STR_LOC];

	strcpy(str, (char *)input);

	int sum = 0;
	char *numar;

	char *result;
	result = (char *)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (result == NULL){
		exit(303);
	}

	numar = strtok(str, "_");
	while (numar != NULL){
		sum += atoi(numar);
		numar = strtok(NULL, "_");
	}

	sprintf(result, "%d", sum);

	return (void *)result;
}

//Task 3
void *InvertArray(void *input)
{
	// TODO
	int i;

	int *vector;
	vector = (int *)input;

	int n;
	n = vector[0];

	//construiesc direct sirul de caractere cu vectorul dorit
	char *result;
	result = (char *)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (result == NULL){
		exit(303);
	}
	int nr = 0;

	if (vector[0] % 2 == 0){

		for (i = 1; i < n - 1; i = i + 2){
			nr += sprintf(result + nr, "%d %d ", vector[i + 1], vector[i]);
		}

		sprintf(result + nr, "%d %d", vector[i + 1], vector[i]);

	} else {

		for (i = n; i > 1; i--){
			nr += sprintf(result + nr, "%d ", vector[i]);
		}

		sprintf(result + nr, "%d", vector[i]);

	}

	return (void *)result;
}

//Task 4
Player *allocPlayer()
{
	// TODO

	Player *player;
	player = (Player *)calloc(1, sizeof(Player));
	if (player == NULL){
		exit(303);
	}

	player->name = (char *)calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (player->name == NULL){
		exit(303);
	}

	player->color = (char *)calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (player->color == NULL){
		exit(303);
	}

	player->hat = (char *)calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (player->hat == NULL){
		exit(303);
	}

	player->alive = 1;

	return player;
}

//Task 4
Game *allocGame()
{
	// TODO

	Game *game;
	game = (Game *)calloc(1, sizeof(Game));
	if (game == NULL){
		exit(303);
	}

	game->name = (char *)calloc(MAX_LEN_STR_ATR, sizeof(char));
	if (game->name == NULL){
		exit(303);
	}

	return game;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{
	// TODO

	Player *player;
	player = allocPlayer();
	fscanf(inputFile, "%s", player->name);
	fscanf(inputFile, "%s", player->color);
	fscanf(inputFile, "%s", player->hat);

	fscanf(inputFile, "%d", &player->numberOfLocations);

	player->locations = (Location *)calloc(player->numberOfLocations, 
	sizeof(Location));
	if (player->locations == NULL){
		exit(303);
	}


	int i;

	char str_location[Max_location_str_len];
	for (i = 0; i < player->numberOfLocations; i++){
		fscanf(inputFile, "%s", str_location);
		player->locations[i].x = atoi(strtok(str_location, "(,) "));
		player->locations[i].y = atoi(strtok(NULL, "(,) "));
	}


	char str[Role_max_str_len];
	fscanf(inputFile, "%s", str);
	player->playerRole = fromStringtoEnum(str);

	return player;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	// TODO
	Game *game;
	game = allocGame();
	fscanf(inputFile, "%s", game->name);
	fscanf(inputFile, "%d", &game->killRange);
	fscanf(inputFile, "%d", &game->numberOfCrewmates);

	int i;

	game->crewmates = (Player **)calloc(game->numberOfCrewmates, 
	sizeof(Player *));
	if (game->crewmates == NULL){
		exit(303);
	}

	for (i = 0; i < game->numberOfCrewmates; i++){
		game->crewmates[i] = ReadPlayer(inputFile);
	}

	game->impostor = ReadPlayer(inputFile);
	
	return game;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{
	// TODO

	fprintf(outputFile, "Player %s ", player->name);
	fprintf(outputFile, "with color %s, ", player->color);
	fprintf(outputFile, "hat %s and role ", player->hat);

	char *output = fromEnumtoString(player->playerRole);
	fprintf(outputFile, "%s ", output);
	free(output);

	fprintf(outputFile, "has entered the game.\n");

	int i;
	fprintf(outputFile, "Player's locations: ");
	for (i = 0; i < player->numberOfLocations; i++){
		fprintf(outputFile, "(%d,%d) ", player->locations[i].x, 
		player->locations[i].y);
	}
	fprintf(outputFile,"\n");
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	// TODO

	fprintf(outputFile, "Game %s has just started!\n", game->name);
	fprintf(outputFile, "	Game options:\n");
	fprintf(outputFile, "Kill Range: %d\n", game->killRange);
	fprintf(outputFile, "Number of crewmates: %d\n\n", game->numberOfCrewmates);

	fprintf(outputFile, "	Crewmates:\n");

	int i;
	for (i = 0; i < game->numberOfCrewmates; i++){
		WritePlayer(game->crewmates[i], outputFile);
	}

	fprintf(outputFile, "\n");

	fprintf(outputFile, "	Impostor:\n");
	WritePlayer(game->impostor, outputFile);
}


int Manhattan_distance(Location a, Location b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}


//Task 7
void *KillPlayer(void *input)
{
	// TODO

	Game *game = (Game *)input;

	//devine 1 in momentul in care gaseste un crewmate care
	//este la o distanta mai mica decat killRange
	int KILL = 0;

	int kill_range = game->killRange;

	int min_dist = game->killRange + 1;

	//dist = distanta Manhattan dintre impostor si crewmate
	int distance = 0;

	//se retine indicele acelui crewmate de la distanta minima
	int crewmate_min_dist;

	int i;
	for (i = game->numberOfCrewmates - 1; i >= 0; i--){

		if (game->crewmates[i]->alive){
			distance = Manhattan_distance(
			game->impostor->locations[game->impostor->indexOfLocation], 
			game->crewmates[i]->locations[game->crewmates[i]->indexOfLocation]);

			if (distance <= kill_range){
				KILL = 1;

				if (distance < min_dist){
					min_dist = distance;
					crewmate_min_dist = i;
				}
			}
		}
	}

	int nr = 0;
	char *result;
	result = (char *)calloc(MAX_LEN_STR_OUT, sizeof(char));
	if (result == NULL){
		exit(303);
	}

	if (KILL){

		nr += sprintf(result + nr, "Impostor %s has just ",
		 game->impostor->name);

		nr += sprintf(result + nr, "killed crewmate %s ", 
		game->crewmates[crewmate_min_dist]->name);

		sprintf(result + nr, "from distance %d.", min_dist);

		game->crewmates[crewmate_min_dist]->alive = 0;

	} else {
		sprintf(result, "Impostor %s couldn't kill anybody.", 
		game->impostor->name);
	}

	return (void *)result;
}


// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	// TODO

	int i;
	Player *player;
	int *current_loc;

	char *output_crewmate;

	for (i = 0; i < game->numberOfCrewmates; i++){

		player = game->crewmates[i];
		current_loc = &player->indexOfLocation;

		if (player->alive){

			//muta un crewmate la locatia urmatoare
			(*current_loc)++;
			*current_loc = (*current_loc) % player->numberOfLocations;

			
			fprintf(outputFile, "Crewmate %s went to location (%d,%d).\n",
			 player->name, player->locations[*current_loc].x,
			 player->locations[*current_loc].y);
			

			fprintf(outputFile, "Crewmate %s's output:\n", player->name);

			output_crewmate = (char *)Abilities[player->playerRole](inputMatrix[i]);

			fprintf(outputFile, "%s\n", output_crewmate);

			free(output_crewmate);

		} else {
			fprintf(outputFile, "Crewmate %s is dead.\n", player->name);
		}
	}

	player = game->impostor;

	current_loc = &player->indexOfLocation;

	//muta impostorul la locatia urmatoare
	(*current_loc)++;
	*current_loc = (*current_loc) % player->numberOfLocations;

	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n",
	 player->name, player->locations[*current_loc].x,
	 player->locations[*current_loc].y);
	

	fprintf(outputFile, "Impostor %s's output:\n", player->name);

	char *output = (char *)Abilities[player->playerRole](inputMatrix[i]);

	fprintf(outputFile, "%s\n", output);

	free(output);

}

// Task 9
void FreePlayer(Player *player)
{
	// TODO
	
	free(player->name);
	free(player->color);
	free(player->hat);
	free(player->locations);
	free(player);
}

// Task 9
void FreeGame(Game *game)
{
	// TODO

	free(game->name);

	int i;
	for (i = 0; i < game->numberOfCrewmates; i++){
		FreePlayer(game->crewmates[i]);
	}

	free(game->crewmates);

	FreePlayer(game->impostor);
	
	free(game);
	return;
}