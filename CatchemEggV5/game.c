
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "game.h"
#include "init.h"
#include <time.h>


void gameOnePlayer(){

  int sortie_jeu = 0;
  int x, y;

  /* On initialise le Joueur 1 */

  Player joueur1;

  strcpy(joueur1.pseudo, "Joueur 1");

  joueur1.score = 0;
  joueur1.fail = 4;

  /* On charge le fond et la fenêtre du jeu */

  MLV_Image *background;
  MLV_Image *posJoueur;

  /* On créer et affiche la fenêtre de jeu */

  MLV_create_window("CatchemEgg - 1 Joueur", "Background_1J", 320, 720);

  /* On charge en mémoire le background du jeu */

  background = MLV_load_image("1Joueur.png");

  /* On affiche l'image */
  
  MLV_draw_image(background, 0, 0);
  
  /* Met à jour l'affichage */
  
  MLV_actualise_window();

  while(1){

    if(!sortie_jeu){

      sortie_jeu = fallEggs(background, posJoueur, joueur1);

    }

    else{

      return;

    }

  }

}


int fallEggs(MLV_Image *background, MLV_Image *posJoueur, Player joueur1){

  MLV_Image *Oeuf1;

  int i, x_Oeuf, x_Joueur;
  
  int sortie = 0;
  int sortie_jeu;
  int speed = 0;
  int tmp = 0;
  int test = 0;
  int xs, ys;

  char score1[10];
  char fail1[10];

  x_Oeuf = posOeuf(); /* Coordoné random a l'oeuf */

  while(!sortie){

    sprintf(score1, "%d", joueur1.score);
    sprintf(fail1, "%d", joueur1.fail);

    for(i=0; i<720; i = i + 1 + speed){ /* Chute de l'oeuf avec la vitesse */
    
      x_Joueur = getPose(background, posJoueur);

      Oeuf1 = MLV_load_image("Oeuf.png");

      MLV_draw_image(Oeuf1, x_Oeuf, i);

      MLV_draw_text(60, 50, score1, MLV_COLOR_WHITE);

      MLV_draw_text(265, 50, fail1, MLV_COLOR_WHITE);

      MLV_actualise_window();

      MLV_free_image(Oeuf1);

      MLV_free_image(posJoueur);

      MLV_free_image(background);

      background = MLV_load_image("1Joueur.png");

      /* Si hauteur des main */

      if(x_Oeuf == x_Joueur && i >= 615 && i <= 645){

	x_Oeuf = posOeuf();

	i = 0;

	joueur1.score = joueur1.score + 5;

	tmp = tmp + 5;

	sprintf(score1, "%d", joueur1.score);
	sprintf(fail1, "%d", joueur1.fail);
       
	if(tmp == 50){
	  speed = speed + 1;
	  tmp = 0;
	}
      }
    }

    joueur1.fail = joueur1.fail + 1;
    
    if(joueur1.fail >= 5){
       
      /******************** Game Over *********************/
  

      MLV_free_image(background);

      background = MLV_load_image("GameOver_1Joueur.png");

      MLV_draw_image(background, 0, 0);
       
      MLV_actualise_window();

      do{

	/* Position de la souris */

	MLV_get_mouse_position(&xs, &ys);

	/* Si on clique */
    
	if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

	  /* Si bouton quitter */

	  if(xs >= 0 && xs <= 130 && ys >= 673 && ys <= 720){

	    sortie_jeu = 1; /* On retourne au menu */

	    sortie = 1;
	     
	    xs = 750;
	     
	    ys = 750;

	    test = 1;

	  }

	  /* Si bouton rejouer */

	  if(xs >= 185 && xs <= 320 && ys >= 673 && ys <= 720){ /* On remet tout a 0 */

	    xs = 750;
	     
	    ys = 750;

	    joueur1.score = 0;

	    tmp = 0;

	    speed = 0;

	    joueur1.fail = 4;
	     
	    test = 1;

	    sortie_jeu = 0;

	  }
	}
	
      }while(!test);

      test = 0;

    }

  x_Oeuf = posOeuf();
  
  }

  return sortie_jeu;

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

