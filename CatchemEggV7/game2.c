
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "game.h"
#include "init.h"
#include <time.h>

void gameTwoPlayer(int charge){

  FILE *fichier1;
	int sortie_jeu = 0;
  int nb_joueur;
  Player joueur1;
  Player joueur2;
  MLV_Image *background;

  /* On créer et affiche la fenêtre de jeu */

  MLV_create_window("CatchemEgg - 2 Joueurs", "Background_2J", 640, 720);

  if(charge == 0){ /********* Si on ne charge pas de partie ********/

  	/* On initialise le Joueur 1 et 2 */

  	strcpy(joueur1.pseudo, "Joueur1");
  	strcpy(joueur2.pseudo, "Joueur2");

  	joueur1.score = 0;
  	joueur1.fail = 5;
  	joueur2.score = 0;
  	joueur2.fail = 5;

  	/* On charge en mémoire le background du jeu */

  	background = MLV_load_image("2Joueur.png");

  	/* On affiche l'image */
  
  	MLV_draw_image(background, 0, 0);
  
  	/* Met à jour l'affichage */
  
  	MLV_actualise_window();

  	while(1){

    if(!sortie_jeu){

      sortie_jeu = fallEggs2(background, joueur1, joueur2);

    }

    else{

      return;

    }

  }

}

else{ /********* Si on charge une partie *********/

      fichier1 = fopen("save.txt", "r");

      if(fscanf(fichier1, "%d %s %d %d %s %d %d", &nb_joueur, joueur1.pseudo, &joueur1.score, &joueur1.fail, joueur2.pseudo, &joueur2.score, &joueur2.fail) != 7){
        return;
      }
     
      fclose(fichier1);

     /* On charge en mémoire le background du jeu */

     background = MLV_load_image("2Joueur.png");

     /* On affiche l'image */
  
     MLV_draw_image(background, 0, 0);
  
      /* Met à jour l'affichage */
    
     MLV_actualise_window();

      while(1){

        if(!sortie_jeu){

        sortie_jeu = fallEggs2(background, joueur1, joueur2);

       }

        else{

          return;

        }
      }
    }

}

int fallEggs2(MLV_Image *background, Player joueur1, Player joueur2){

  FILE *fichier;
	MLV_Image *Oeuf1;
	MLV_Image *Oeuf2;
  MLV_Image *posJoueur1 = NULL;
  MLV_Image *posJoueur2 = NULL;

	int i, sortie_jeu, xs, ys;

	int sortie = 0;
	int speed = 0;
	int tmp = 0;
	int test = 0;

	char score1[12];
  	char fail1[12];
  	char score2[12];
  	char fail2[12];

  	int coord[2] = {0, 0};
  	int x_Oeuf[2] = {0, 0};


  	while(!sortie){

  		sprintf(score1, "%d", joueur1.score); /* On transforme INT en CHAR */
    	sprintf(fail1, "%d", joueur1.fail);
    	sprintf(score2, "%d", joueur2.score);
    	sprintf(fail2, "%d", joueur2.fail);

    	posOeuf2(x_Oeuf);

    	for(i=0; i<720; i = i + 1 + speed){ /* Chute des oeufs avec la vitesse */

      /***************** Sauvegarde *******************/

      MLV_get_mouse_position(&xs, &ys);

      if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

        if(xs >= 246 && xs <= 400 && ys >= 670 && ys <= 710){

        /* Ouvrir en écriture = éffacer l'ancienne sauvegarde */

        fichier = fopen("save.txt", "w");
        fputc('2', fichier);  /* Cb de joueur */
        fputc(' ', fichier); /* Délimiteur des paramètres */
        fputs(joueur1.pseudo, fichier); /* Pseudos du joueur1 */
        fputc(' ', fichier); /* Délimiter des paramètres */
        fputs(score1, fichier); /* Score du joueur1 */
        fputc(' ', fichier); /* Délimiter des paramètres */
        fputs(fail1, fichier); /* Nb de fail du joueur1 */
        fputc(' ', fichier); /* Délimiteur des paramètres */
        fputs(joueur2.pseudo, fichier); /* Pseudos du joueur2 */
        fputc(' ', fichier); /* Délimiter des paramètres */
        fputs(score2, fichier); /* Score du joueur2 */
        fputc(' ', fichier); /* Délimiter des paramètres */
        fputs(fail2, fichier); /* Nb de fail du joueur2 */
        fclose(fichier);

        return 1;

        }

      }

    		getPose2(background, posJoueur1, posJoueur2, coord); /* Position J1 et J2 par rapport aux touche */

    		Oeuf1 = MLV_load_image("Oeuf.png"); /* On charge les oeufs */
    		Oeuf2 = MLV_load_image("Oeuf.png");

    		MLV_draw_image(Oeuf1, x_Oeuf[0], i); /* On affiche les oeufs */
    		MLV_draw_image(Oeuf2, x_Oeuf[1], i);

    		MLV_draw_text(60, 50, score1, MLV_COLOR_WHITE); /* On affiche les scores */
    		MLV_draw_text(380, 50, score2, MLV_COLOR_WHITE);

    		MLV_draw_text(265, 50, fail1, MLV_COLOR_WHITE); /* On affiche les vie */
    		MLV_draw_text(585, 50, fail2, MLV_COLOR_WHITE);

    		MLV_actualise_window();

    		MLV_free_image(Oeuf1);
    		MLV_free_image(Oeuf2);
    		MLV_free_image(background);

    		background = MLV_load_image("2Joueur.png");

    		/* Si hauteur des main d'un des 2 joueurs */

    			if(x_Oeuf[0] == coord[0] && x_Oeuf[1] == coord[1] && i >= 615 && i <= 635){ /* Si les 2 joueurs ont l'oeuf */

    				joueur1.score = joueur1.score + 5;
    				joueur2.score = joueur2.score + 5;
    				tmp = tmp + 5;
    				tmp = tmp + 5;

    				sprintf(score1, "%d", joueur1.score);
	     			sprintf(fail1, "%d", joueur1.fail);
	     			sprintf(score2, "%d", joueur2.score);
	     			sprintf(fail2, "%d", joueur2.fail);

	     			if(tmp >= 100){
	        			speed = speed + 1;
	        			tmp = 0;
	     			}

	     			posOeuf2(x_Oeuf);
	     			i = 0;
    			}

    			else if(x_Oeuf[0] == coord[0] && x_Oeuf[1] != coord[1] && i >= 615 && i <= 635){ /* Si seulement joueur 1 a l'oeuf*/

    				joueur1.score = joueur1.score + 5;
    				tmp = tmp + 5;
    				joueur2.fail = joueur2.fail - 1;

    				sprintf(score1, "%d", joueur1.score);
	     			sprintf(fail1, "%d", joueur1.fail);
	     			sprintf(score2, "%d", joueur2.score);
	     			sprintf(fail2, "%d", joueur2.fail);

	     			if(tmp >= 100){
	        			speed = speed + 1;
	        			tmp = 0;
	     			}

	     			posOeuf2(x_Oeuf);
	     			i = 0;
    			}

    			else if(x_Oeuf[0] != coord[0] && x_Oeuf[1] == coord[1] && i >= 615 && i <= 635){ /* Si seulement joueur 2 a l'oeuf*/

    				joueur2.score = joueur2.score + 5;
    				tmp = tmp + 5;
    				joueur1.fail = joueur1.fail - 1;

    				sprintf(score1, "%d", joueur1.score);
	     			sprintf(fail1, "%d", joueur1.fail);
	     			sprintf(score2, "%d", joueur2.score);
	     			sprintf(fail2, "%d", joueur2.fail);

	     			if(tmp >= 100){
	        			speed = speed + 1;
	        			tmp = 0;
	     			}

	     			posOeuf2(x_Oeuf);
	     			i = 0;
    			}

    			else if(x_Oeuf[0] != coord[0] && x_Oeuf[1] != coord[1] && i >= 615 && i <= 635){

    				joueur1.fail = joueur1.fail - 1;
    				joueur2.fail = joueur2.fail - 1;

            sprintf(score1, "%d", joueur1.score);
            sprintf(fail1, "%d", joueur1.fail);
            sprintf(score2, "%d", joueur2.score);
            sprintf(fail2, "%d", joueur2.fail);

    				posOeuf2(x_Oeuf);

    				i = 0;

    			}
    	

    		/******************** GAME OVER Egalité *******************/

    		if(joueur1.fail <= 0 && joueur2.fail <= 0){

    			MLV_free_image(background);

      			background = MLV_load_image("GameOver_2Joueur_Eg.png");

      			MLV_draw_image(background, 0, 0);

      			MLV_draw_text(160, 600, score1, MLV_COLOR_WHITE);
      			MLV_draw_text(480, 600, score2, MLV_COLOR_WHITE);
       
      			MLV_actualise_window();

      			do{

	     			/* Position de la souris */

	     			MLV_get_mouse_position(&xs, &ys);

	     			/* Si on clique */
    
	     			if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

	       				/* Si bouton quitter */

	       				if(xs >= 0 && xs <= 130 && ys >= 673 && ys <= 720){

	         				sortie = 1;
	     
	         				xs = 750;
	     
	         				ys = 750;

	         				test = 1;

                  return 1; /* On retourne au menu */

	       				}

	       				/* Si bouton rejouer */

	       				if(xs >= 185 + 320 && xs <= 320 + 320 && ys >= 673 && ys <= 720){ /* On remet tout a 0 */

	         				xs = 750;
	     
	         				ys = 750;

	         				joueur1.score = 0;
	         				joueur2.score = 0;
	         				tmp = 0;
	         				speed = 0;
	         				joueur1.fail = 5;
	         				joueur2.fail = 5;

                  sprintf(score1, "%d", joueur1.score);
                  sprintf(fail1, "%d", joueur1.fail);
                  sprintf(score2, "%d", joueur2.score);
                  sprintf(fail2, "%d", joueur2.fail);
	     
	         				test = 1;
	         				sortie_jeu = 0;
	       				}  
	     			}
	
      			}while(!test);

      			test = 0;
    		}

    		/******************** GAME OVER Victoire J1 *******************/

    		if(joueur1.fail > 0 && joueur2.fail <= 0){

    			MLV_free_image(background);

      			background = MLV_load_image("GameOver_2Joueur_Vj1.png");

      			MLV_draw_image(background, 0, 0);

      			MLV_draw_text(160, 600, score1, MLV_COLOR_WHITE);
      			MLV_draw_text(480, 600, score2, MLV_COLOR_WHITE);
       
      			MLV_actualise_window();

      			do{

	    	 		/* Position de la souris */

	     			MLV_get_mouse_position(&xs, &ys);

	     			/* Si on clique */
    
	     			if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

	       				/* Si bouton quitter */

	       				if(xs >= 0 && xs <= 130 && ys >= 673 && ys <= 720){

	         				sortie = 1;
	     
	         				xs = 750;
	     
	         				ys = 750;

	         				test = 1;

                  return 1; /* On retourne au menu */

	       				}

	       				/* Si bouton rejouer */

	       				if(xs >= 185 + 320 && xs <= 320 + 320 && ys >= 673 && ys <= 720){ /* On remet tout a 0 */

	         				xs = 750;
	     
	         				ys = 750;

	         				joueur1.score = 0;
	         				joueur2.score = 0;
	         				tmp = 0;
	         				speed = 0;
	         				joueur1.fail = 5;
	         				joueur2.fail = 5;

                  sprintf(score1, "%d", joueur1.score);
                  sprintf(fail1, "%d", joueur1.fail);
                  sprintf(score2, "%d", joueur2.score);
                  sprintf(fail2, "%d", joueur2.fail);
	     
	         				test = 1;
	         				sortie_jeu = 0;
	       				}  
	     			}
	
      			}while(!test);

      			test = 0;
    		}

    		/******************** GAME OVER Victoire J2 *******************/

    		if(joueur1.fail <= 0 && joueur2.fail > 0){

    			MLV_free_image(background);

      			background = MLV_load_image("GameOver_2Joueur_Vj2.png");

      			MLV_draw_image(background, 0, 0);

      			MLV_draw_text(160, 600, score1, MLV_COLOR_WHITE);
      			MLV_draw_text(480, 600, score2, MLV_COLOR_WHITE);
       
      			MLV_actualise_window();

      			do{

	     			/* Position de la souris */

	     			MLV_get_mouse_position(&xs, &ys);

	     			/* Si on clique */
    
	     			if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

	      	 			/* Si bouton quitter */

	       				if(xs >= 0 && xs <= 130 && ys >= 673 && ys <= 720){

	         				sortie = 1;
	     
	         				xs = 750;
	     		
	         				ys = 750;

	         				test = 1;

                  return 1; /* On retourne au menu */

	       				}

	       				/* Si bouton rejouer */

	       				if(xs >= 185 + 320 && xs <= 320 + 320 && ys >= 673 && ys <= 720){ /* On remet tout a 0 */

	         				xs = 750;
	     
	         				ys = 750;

	         				joueur1.score = 0;
	         				joueur2.score = 0;
	         				tmp = 0;
	         				speed = 0;
	         				joueur1.fail = 5;
	         				joueur2.fail = 5;

                  sprintf(score1, "%d", joueur1.score);
                  sprintf(fail1, "%d", joueur1.fail);
                  sprintf(score2, "%d", joueur2.score);
                  sprintf(fail2, "%d", joueur2.fail);
	     
	         				test = 1;
	         				sortie_jeu = 0;
	       				}  
	     			}
	
      			}while(!test);

      			test = 0;
    		}
 	 	}

    	posOeuf2(x_Oeuf);

  	}

  	return sortie_jeu;
}


int getPose2(MLV_Image *background, MLV_Image *posJoueur1, MLV_Image *posJoueur2, int coord[2]){

  	/* Position du joueur 1 et 2 a gauche */

  	if((MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_gauche_penche.png");
      posJoueur2 = MLV_load_image("Leveinard_gauche_penche.png");

      MLV_draw_image(posJoueur1, 0, 570);
      MLV_draw_image(posJoueur2, 320, 570);

      coord[0] = 26;
      coord[1] = 346;

    }

  	/* Position du joueur 1 a gauche et joueur 2 milieu */

  	else if((MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) != MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_gauche_penche.png");
      posJoueur2 = MLV_load_image("Leveinard_middle.png");

      MLV_draw_image(posJoueur1, 0, 570);
      MLV_draw_image(posJoueur2, 404, 570);

      coord[0] = 26;
      coord[1] = 453;

    }

    /* Position du joueur 1 a gauche et joueur 2 a droite */

  	else if((MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) == MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_gauche_penche.png");
      posJoueur2 = MLV_load_image("Leveinard_droite_penche.png");

      MLV_draw_image(posJoueur1, 0, 570);
      MLV_draw_image(posJoueur2, 490, 570);

      coord[0] = 26;
      coord[1] = 560;

    }

    /* Position du joueur 1 au millieu et joueur 2 a gauche */

  	else if((MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LALT) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_middle.png");
      posJoueur2 = MLV_load_image("Leveinard_gauche_penche.png");

      MLV_draw_image(posJoueur1, 85, 570);
      MLV_draw_image(posJoueur2, 320, 570);

      coord[0] = 133;
      coord[1] = 346;

    }

    /* Position du joueur 1 et 2 au millieu */

  	else if((MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LALT) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) != MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_middle.png");
      posJoueur2 = MLV_load_image("Leveinard_middle.png");

      MLV_draw_image(posJoueur1, 85, 570);
      MLV_draw_image(posJoueur2, 404, 570);

      coord[0] = 133;
      coord[1] = 453;

    }

    /* Position du joueur 1 au millieu et joueur 2 a droite */

  	else if((MLV_get_keyboard_state(MLV_KEYBOARD_LCTRL) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LALT) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_middle.png");
      posJoueur2 = MLV_load_image("Leveinard_droite_penche.png");

      MLV_draw_image(posJoueur1, 85, 570);
      MLV_draw_image(posJoueur2, 490, 570);

      coord[0] = 133;
      coord[1] = 560;

    }

    /* Position du joueur 1 a droite et 2 a gauche */

  	if((MLV_get_keyboard_state(MLV_KEYBOARD_LALT) == MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_droite_penche.png");
      posJoueur2 = MLV_load_image("Leveinard_gauche_penche.png");

      MLV_draw_image(posJoueur1, 170, 570);
      MLV_draw_image(posJoueur2, 320, 570);

      coord[0] = 240;
      coord[1] = 346;

    }

    /* Position du joueur 1 a droite et 2 au millieu */

  	if((MLV_get_keyboard_state(MLV_KEYBOARD_LALT) == MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) != MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) != MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_droite_penche.png");
      posJoueur2 = MLV_load_image("Leveinard_middle.png");

      MLV_draw_image(posJoueur1, 170, 570);
      MLV_draw_image(posJoueur2, 404, 570);

      coord[0] = 240;
      coord[1] = 453;

    }

    /* Position du joueur 1 et 2 a droite */

  	if((MLV_get_keyboard_state(MLV_KEYBOARD_LALT) == MLV_PRESSED) && (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)){

      MLV_draw_image(background, 0, 0);

      posJoueur1 = MLV_load_image("Leveinard_droite_penche.png");
      posJoueur2 = MLV_load_image("Leveinard_droite_penche.png");

      MLV_draw_image(posJoueur1, 170, 570);
      MLV_draw_image(posJoueur2, 490, 570);

      coord[0] = 240;
      coord[1] = 560;

    }
  return 0;
}


void posOeuf2(int x_Oeuf[2]){

  int pos;

  srand(time(NULL));

  pos = (rand() % (3 - 1 + 1)) + 1;

  if(pos == 1){
  	x_Oeuf[0] = 26;
    x_Oeuf[1] = 346;
  }
  if(pos == 2){
  	x_Oeuf[0] = 133;
    x_Oeuf[1] = 453;
  }
  if(pos == 3){
  	x_Oeuf[0] = 240;
    x_Oeuf[1] = 560;
  }

}