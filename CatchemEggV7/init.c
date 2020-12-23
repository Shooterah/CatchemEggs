
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "init.h"
#include "game.h"
#include "classement.h"

int menu(){

  FILE *fichier;
  char c;

  int width = 446, height = 676;
  int x, y, sortie_joueur, sortie_regle;

  int sortie_menu = 0;

  int finish = 0;

  MLV_Image *background;

  /* On créé et affiche le menu */

  MLV_create_window("Menu", "Background_Menu", width, height);

  /* On charge en mémoire le background du menu */

  background = MLV_load_image("BackgroundMenu.png");

  /* On affiche l'image */
  
  MLV_draw_image(background, 0, 0);
  
  /* Met à jour l'affichage */
  
  MLV_actualise_window();

  /* On suis ce que fait la souris tant qu'elle n'a pas cliqué */

  do{
    
    sortie_joueur = 0;
    sortie_regle = 0;
    
    /* Position de la souris */

    MLV_get_mouse_position(&x, &y);
    
    /* Si on clique */
    
    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

      /* Si bouton jouer */

      if(x >= 75 && x <= 372 && y >= 26 && y <= 100){

		/* On change le fond et on créé et affiche la selection des joueurs */

		MLV_free_image(background); 

		background = MLV_load_image("BackgroundJoueur.png");

		/* On affiche l'image */
  
		MLV_draw_image(background, 0, 0);
  
		/* Met à jour l'affichage */
  
		MLV_actualise_window();

		MLV_wait_milliseconds(1000);

		/* Selection du nb de joueur */

		do{

		  /* Position de la souris */

		  MLV_get_mouse_position(&x, &y);
    
		  /* Si on clique */
    
		  if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

		    /* Si bouton retour */

	  		if(x >= 280 && x <= 433 && y >= 478 && y <= 520){

	      	/* Supprime le background qui a été crée */

	      	MLV_free_image(background);

	    	/* On charge en mémoire le background du menu */

	      	background = MLV_load_image("BackgroundMenu.png");

	      	/* On affiche l'image */
  
	      	MLV_draw_image(background, 0, 0);
  
	      	/* Met à jour l'affichage */
  
	      	MLV_actualise_window();

	      	sortie_joueur = 1;

	    	}

	    	/* Si bouton 1 Joueur */

	    	if(x >= 75 && x <= 372 && y >= 26 && y <= 100){

	      		/* Supprime le background qui a été crée */
  
	      		MLV_free_image(background); 

	   		   	/* Ferme la fenêtre */
  
	  		    MLV_free_window();

	    		gameOnePlayer(0);

	   		   	MLV_free_window();

	      		return 1;

	    	}

		    /* Si bouton 2 Joueur */

		    if(x >= 75 && x <= 372 && y >= 118 && y <= 190){

	  		  	MLV_free_image(background); 

	   			/* Ferme la fenêtre */
  
	  			MLV_free_window();

	   		 	gameTwoPlayer(0);

	   			MLV_free_window();

	   		   	return 1;
	      
	   		}

	   		/* Si bouton 3 Joueur */

	   		if(x >= 75 && x <= 372 && y >= 210 && y <= 280){
	      

	   		}

	    	/* Si bouton 4 Joueur */

	   	    if(x >= 75 && x <= 372 && y >= 304 && y <= 375){
	      

	    	}

	  	}

		}while(!sortie_joueur);

      }

      /* Si bouton charger */

      if(x >= 75 && x <= 372 && y >= 118 && y <= 190){

      	fichier = fopen("save.txt", "r"); /* On regarde pour combien de joueur la partie est */

      	c = fgetc(fichier);

      	fclose(fichier);

      	if(c == '1'){ /* Jeu 1 joueur en chargeant */

      		/* Supprime le background qui a été crée */
  
	      		MLV_free_image(background); 

	   		   	/* Ferme la fenêtre */
  
	  		    MLV_free_window();

	    		gameOnePlayer(1);

	   		   	MLV_free_window();

	      		return 1;

      	}
      	else if(c == '2'){ /* Jeu 2 joueurs en chargeant */

      		MLV_free_image(background); 

	   			/* Ferme la fenêtre */
  
	  			MLV_free_window();

	   		 	gameTwoPlayer(1);

	   			MLV_free_window();

	   		   	return 1;

      	}

      }

      /* Si bouton classement */

      if(x >= 75 && x <= 372 && y >= 210 && y <= 280){

      	/* Supprime le background qui a été crée */
  
	    MLV_free_image(background); 

	   	/* Ferme la fenêtre */
  
	  	MLV_free_window();

	    classement();

	   	MLV_free_window();

	    return 1;

      }

      /* Si bouton quitter */

      if(x >= 75 && x <= 372 && y >= 340 && y <= 410){

		/* Supprime le background qui a été crée */
  
		MLV_free_image(background); 

		/* Ferme la fenêtre */
  
		MLV_free_window();

		return 0;

		sortie_menu = 1;

      }

      /* Si bouton regles */

      if(x >= 280 && x <= 433 && y >= 478 && y <= 520){

  		MLV_free_image(background); 

		background = MLV_load_image("regle.png");

		/* On affiche l'image */
  
		MLV_draw_image(background, 0, 0);
  
		/* Met à jour l'affichage */
  
		MLV_actualise_window();

		do{

		  	/* Position de la souris */

		  	MLV_get_mouse_position(&x, &y);

		  	if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
		

			if(x >= 0 && x <= 140 && y >= 600 && y <= 675){

	      		/* Supprime le background qui a été crée */

	      		MLV_free_image(background);

	    		/* On charge en mémoire le background du regle */

	      		background = MLV_load_image("BackgroundMenu.png");

	      		/* On affiche l'image */
  	
	      		MLV_draw_image(background, 0, 0);
  
	      		/* Met à jour l'affichage */
  
	      		MLV_actualise_window();

	      		sortie_regle = 1;

	    	}
	    }

	    }while(!sortie_regle);

      }
    }
  } while(!sortie_menu);
}
