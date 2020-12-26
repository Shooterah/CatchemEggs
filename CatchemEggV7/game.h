
	
#ifndef GAME_H
#define GAME_H


typedef struct{

  char pseudo[20];
  int score;
  int x,y;
  int fail;
  
}Player;

typedef struct{

	int coord[2];


}Position2;



void gameOnePlayer(int charge);

void gameTwoPlayer(int charge);

void gameThreePlayer(int charge);

void gameFourPlayer(int charge);

int fallEggs(MLV_Image *background, Player joueur1);

int fallEggs2(MLV_Image *background, Player joueur1, Player joueur2);

int posOeuf(void);

void posOeuf2(int x_Oeuf[2]);

int getPose(MLV_Image *background, MLV_Image *posJoueur1);

int getPose2(MLV_Image *background, MLV_Image *posJoueur1, MLV_Image *posJoueur2, int coord[2]);


#endif