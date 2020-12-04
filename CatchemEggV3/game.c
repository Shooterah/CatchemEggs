
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "game.h"
#include "init.h"
#include <time.h>


void gameOnePlayer(finish){

  int sortie_jeu = 0;
  int x, y;

  /* On initialise le Joueur 1 */

  Player joueur1;

  strcpy(joueur1.pseudo, "Joueur 1");

  joueur1.score = 0;

  /* On charge le fond et la fenêtre du jeu */

  MLV_Image *background;
  MLV_Image *posJoueur;

  /* On créer et affiche la fenêtre de jeu */

  MLV_create_window("CatchemEgg - 1 Joueur", "Background_1J", 320, 720);

  /* On charge en mémoire le background du jeu */

  background = MLV_load_image("1Joueur.jpg");

  /* On affiche l'image */
  
  MLV_draw_image(background, 0, 0);
  
  /* Met à jour l'affichage */
  
  MLV_actualise_window();

  while(!sortie_jeu){

    fallEggs(background, posJoueur, joueur1, sortie_jeu); 

  }

  finish = 1;

}


void fallEggs(MLV_Image *background, MLV_Image *posJoueur, Player joueur1, int sortie_jeu){

  MLV_Image *Oeuf1;

  int i, x_Oeuf, x_Joueur;

  int sortie = 0;

  char score1[10];

  x_Oeuf = posOeuf();

  while(!sortie){


  for(i=0; i<720; i = i+4){

    if(joueur1.score >= 50){
      exit(1);
	 sortie = 1;
       }

    sprintf(score1, "%d", joueur1.score);
    
    x_Joueur = getPose(background, posJoueur);

    Oeuf1 = MLV_load_image("Oeuf.png");

    MLV_draw_image(Oeuf1, x_Oeuf, i);

    MLV_draw_adapted_text_box(160, 10, score1, 20, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);

    MLV_actualise_window();

    MLV_free_image(Oeuf1);

    MLV_free_image(posJoueur);

    MLV_free_image(background);

    background = MLV_load_image("1Joueur.jpg");

    /* Si hauteur des main */

    if(x_Oeuf == x_Joueur && i >= 615 && i <= 645){

       x_Oeuf = posOeuf();

       i = 0;

       joueur1.score = joueur1.score + 5;

    }

  }
  x_Oeuf = posOeuf();
  }

  sortie_jeu = 1;
  
}


int getPose(MLV_Image *background, MLV_Image *posJoueur){

  int x_Joueur;

  if(MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED){

      /* Position du joueur a gauche */

      MLV_draw_image(background, 0, 0);

      posJoueur = MLV_load_image("Leveinard_gauche_penche.png");

      MLV_draw_image(posJoueur, 0, 570);

      x_Joueur = 26;

      return x_Joueur;

    }

    /* Si on appuie sur alt gauche */
    
    else if(MLV_get_keyboard_state(MLV_KEYBOARD_LALT) == MLV_PRESSED){

      /* Position du joueur a droite */

      MLV_draw_image(background, 0, 0);

      posJoueur = MLV_load_image("Leveinard_droite_penche.png");

      MLV_draw_image(posJoueur, 170, 570);

      x_Joueur = 240;

      return x_Joueur;

    }

    /* Si on appuie sur aucune des deux touches */
    
    else{

      /* Position du joueur au centre */

      MLV_draw_image(background, 0, 0);

      posJoueur = MLV_load_image("Leveinard_middle.png");

      /* On affiche l'image du joueur au centre */
  
      MLV_draw_image(posJoueur, 85, 570);

      x_Joueur = 133;

      return x_Joueur;

    }
}

int posOeuf(){

  int pos, x_Oeuf;

  srand(time(NULL));

  pos = (rand() % (3 - 1 + 1)) + 1;

  if(pos == 1){
    x_Oeuf = 26;
  }
  if(pos == 2){
    x_Oeuf = 133;
  }
  if(pos == 3){
    x_Oeuf = 240;
  }

  return x_Oeuf;

}

