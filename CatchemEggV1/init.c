
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "init.h"

void menu(){

  int width = 446, height = 676;

  MLV_Image *background;

  /* On créé et affiche le menu */

  MLV_create_window("Menu", "Background", width, height);

  /* On charge en mémoire le background du menu */

  background = MLV_load_image("background.png");

  /* On affiche l'image */
  
  MLV_draw_image(background, 0, 0);
  
  /* Met à jour l'affichage */
  
  MLV_actualise_window();
  
  /* Attend 2 secondes */
  
  MLV_wait_seconds(60);
  
  /* Libère l'image qui a été crée */
  
  MLV_free_image(background);
  
  /* Ferme la fenêtre */
  
  MLV_free_window();

}
