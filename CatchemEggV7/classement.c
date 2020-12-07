
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "classement.h"


void classement(){

	int sortie = 0;
	int x, y, j;
	int i = 0;
	char c;
	char data[100] = {0};

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

    	/******************** Les données *************************/

  		fichier = fopen("save.txt", "r");

  		do{

  			c = fgetc(fichier); /* on lit le premier caractère */

  			if(c == "*"){

  				data[i] = fgetc(fichier);

  				while(data[i] != "§"){ /* Tant que != § */

  					i++; 
  				}

  				i++; /* § */

  				data[i] = " ";
  				i++;
  				data[i] = " ";
  				i++;
  				data[i] = " ";
  				i++;
  				data[i] = " ";
  				i++;
  				data[i] = " ";
  				i++;

  				while(data[i] = fgetc(fichier) != "\n"){ /* Tant que != § */

  					i++; 
  				}
  			}

  			/* Un score entier a été lu */

  			MLV_draw_text(80, 200, data, MLV_COLOR_WHITE);

  			for(j=0; j<= i; j++){
  				data[j] = "0";
  			}

  			i = 0;

  		}while(c != EOF);

  	}while(!sortie);

  	return;

}