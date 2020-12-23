
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "classement.h"


void classement(){

	int sortie = 0;
	int x, y;
	int i = 120;
	char c;
	char data[100];
  int j = 0;
  int tmp = 0;

	FILE* fichier;

	/* On charge le fond du classement */

	MLV_Image *background;

	/* On créer et affiche la fenêtre de classement */

  	MLV_create_window("CatchemEgg - Classement", "Background_Classement", 500, 800);

  	/* On charge en mémoire le background du classement */

  	background = MLV_load_image("Classement.png");

  	/* On resize la taille */

  	MLV_resize_image(background, 500, 800);

  	/* On affiche l'image */
  
 	MLV_draw_image(background, 0, 0);
  
  	/* Met à jour l'affichage */
  
  	MLV_actualise_window();

    /******************** Les données *************************/

    fichier = fopen("classement.txt", "r");

      if(!fichier){

        MLV_actualise_window();

        sortie = 1;

        return;

      }

      else{

      while(fgets(data, 255, fichier) != NULL){

        if(j <= 2){

        i = i + 50;

        MLV_draw_text(150, i, data, MLV_COLOR_BLACK);

        j++;

        }
        
        else{

         i = 530 + tmp;

         tmp = tmp + 50;

         MLV_draw_text(150, i, data, MLV_COLOR_BLACK);

        }

        MLV_actualise_window();

      }
    }




    /******************** La souris *************************/

  	do{

  		/* Position de la souris */

    	MLV_get_mouse_position(&x, &y);

    	/* Si on clique */
    
    	if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){

    		/* Si bouton retour */

      		if(x >= 0 && x <= 230 && y >= 740 && y <= 800){

      			sortie = 1;

      		}

    	}

  	}while(!sortie);

  	return;

}