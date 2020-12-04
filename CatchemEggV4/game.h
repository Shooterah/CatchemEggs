
typedef struct{

  char pseudo[20];
  int score;
  int x,y;
  int fail;
  
}Player;



void gameOnePlayer();

void fallEggs(MLV_Image *background, MLV_Image *posJoueur, Player joueur1, int sortie_jeu);

int posOeuf(void);

int getPose(MLV_Image *background, MLV_Image *posJoueur);


