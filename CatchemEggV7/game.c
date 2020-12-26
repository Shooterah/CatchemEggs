
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "game.h"
#include "init.h"
#include <time.h>


void gameOnePlayer(int charge){

  FILE *fichier1;
  int sortie_jeu = 0;
  Player joueur1;
  MLV_Image *background;
  int nb_joueur;

  /* On créer et affiche la fenêtre de jeu */

  MLV_create_window("CatchemEgg - 1 Joueur", "Background_1J", 320, 720);

  if(charge == 0){ /********* Si on ne charge pas de partie ********/

    
    /* On initialise le Joueur 1 */

    strcpy(joueur1.pseudo, "Joueur1");

    joueur1.score = 0;
    joueur1.fail = 5;

    /* On charge en mémoire le background du jeu */

    background = MLV_load_image("1Joueur.png");

    /* On affiche l'image */
  
    MLV_draw_image(background, 0, 0);
  
    /* Met à jour l'affichage */
  
    MLV_actualise_window();

    while(1){

      if(!sortie_jeu){

        sortie_jeu = fallEggs(background, joueur1);

      }

      else{

        return;

      }

    }
  }
  else{ /********* Si on charge une partie *********/

      fichier1 = fopen("save.txt", "r");

      if(fscanf(fichier1, "%d %s %d %d", &nb_joueur, joueur1.pseudo, &joueur1.score, &joueur1.fail) != 4){

        return;
      }
     
      fclose(fichier1);

     /* On charge en mémoire le background du jeu */

     background = MLV_load_image("1Joueur.png");

     /* On affiche l'image */
  
     MLV_draw_image(background, 0, 0);
  
      /* Met à jour l'affichage */
    
     MLV_actualise_window();

      while(1){

        if(!sortie_jeu){

         sortie_jeu = fallEggs(background, joueur1);

       }

        else{

          return;

        }
      }
    }
  }


int fallEggs(MLV_Image *background, Player joueur1){

  FILE *fichier;

  MLV_Image *Oeuf1;
  MLV_Image *posJoueur;

  int i, x_Oeuf, x_Joueur;
  
  int sortie = 0;
  int sortie_jeu;
  int speed = 0;
  int tmp = 0;
  int test = 0;
  int xs, ys;

  char score1[12];
  char fail1[12];

  x_Oeuf = posOeuf(); /* Coordoné random a l'oeuf */

  while(!sortie){

    /************** Jeu *************/

    sprintf(score1, "%d", joueur1.score);
    sprintf(fail1, "%d", joueur1.fail);

    for(i=0; i<720; i = i + 1 + speed){ /* Chute de l'oeuf avec la vitesse */

    /****************** Sauvegarde ********************/

    MLV_get_mouse_position(&xs, &ys);

    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

      if(xs >= 100 && xs <= 245 && ys >= 14 && ys <= 50){

        /* Ouvrir en écriture = éffacer l'ancienne sauvegarde */

        fichier = fopen("save.txt", "w");
        fputc('1', fichier);  /* Cb de joueur */
        fputc(' ', fichier); /* Délimiteur des paramètres */
        fputs(joueur1.pseudo, fichier); /* Pseudos du joueur */
        fputc(' ', fichier); /* Délimiter des paramètres */
        fputs(score1, fichier); /* Score du joueur */
        fputc(' ', fichier); /* Délimiter des paramètres */
        fputs(fail1, fichier); /* Nb de fail du joueur */
        fclose(fichier);

        return 1;

      }

    }
    
      x_Joueur = getPose(background, posJoueur);

      Oeuf1 = MLV_load_image("Oeuf.png");

      MLV_draw_image(Oeuf1, x_Oeuf, i);

      MLV_draw_text(60, 50, score1, MLV_COLOR_WHITE);

      MLV_draw_text(265, 50, fail1, MLV_COLOR_WHITE);

      MLV_actualise_window();

      MLV_free_image(Oeuf1);

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

    joueur1.fail = joueur1.fail - 1;
    
    if(joueur1.fail <= 0){
       
      /******************** Game Over *********************/
  

      MLV_free_image(background);

      background = MLV_load_image("GameOver_1Joueur.png");

      MLV_draw_image(background, 0, 0);

      MLV_draw_text(160, 500, score1, MLV_COLOR_WHITE);
       
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

	         joueur1.fail = 5;
	     
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


int getPose(MLV_Image *background, MLV_Image *posJoueur1){

  int x_Joueur1;

  if(MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED){

      /* Position du joueur a gauche */

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_gauche_penche.png");

      MLV_draw_image(posJoueur1, 0, 570);

      x_Joueur1 = 26;

      return x_Joueur1;

    }

    /* Si on appuie sur alt gauche */
    
    else if(MLV_get_keyboard_state(MLV_KEYBOARD_LALT) == MLV_PRESSED){

      /* Position du joueur a droite */

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_droite_penche.png");

      MLV_draw_image(posJoueur1, 170, 570);

      x_Joueur1 = 240;

      return x_Joueur1;

    }

    /* Si on appuie sur aucune des deux touches */
    
    else{

      /* Position du joueur au centre */

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_middle.png");

      /* On affiche l'image du joueur au centre */
  
      MLV_draw_image(posJoueur1, 85, 570);

      x_Joueur1 = 133;

      return x_Joueur1;

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

