
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "init.h"
#include "game.h"

int menu(){

  int width = 446, height = 676;
  int x, y, sortie_joueur;

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

	      gameOnePlayer();

	      MLV_free_window();

	      return 1;

	    }

	    /* Si bouton 2 Joueur */

	    if(x >= 75 && x <= 372 && y >= 118 && y <= 190){
	      

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



      }

      /* Si bouton classement */

      if(x >= 75 && x <= 372 && y >= 210 && y <= 280){



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



      }
    }
  } while(!sortie_menu);
}
