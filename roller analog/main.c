#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcp4822.h"
#include "I2C.h"
#include <math.h>
#include <stdbool.h>
#include "control.h"
#include <bcm2835.h>
#include <sched.h>
#include "thread.h"

bool init_gen();
bool deinit_gen(pthread_t);

int main ()
{
    pthread_t thread_control;

    //je demande grace a la fonction init_gen d'initialiser tout ce qui doit l'être
   if(!init_gen())
         {
            printf("erreur initialisation général\n");
          exit(error_code);
      }

    /* lance la fonction qui crée le thread pour utiliser la fonction control*/
    thread_control = thread_param ();

    if( thread_control= error_code)
    {
        printf("erreur dans la fonction thread_param\n");
          exit(error_code);
    }
        pthread_join(thread_control,NULL);

        deinit_gen();

        system("sudo shutdown -h now");

}

}


/* fonction qui me sert a initiliser tout ce qui a besoin de lêtre au démarrage des roller */
bool init_gen() // peut-être un probleme sur le type de la fonction
{
    bool ereur_init = true;

        // j'initialise le GPIO
        if (!bcm2835_init())
        {
            ereur_init=false;
        }

        // j'utillise la pin GPIO 4 en INPUT
        bcm2835_gpio_fsel(INTERRUPTEUR, BCM2835_GPIO_FSEL_INPT);

        // j'initialise le canal A de la raspberry pour la connection SPI pour le convertisseur digital/analogique
    if(!mcp4822_initialize())
      {

       ereur_init=false;
      }

        // j'initiliasie ma connection I2C
              bcm2835_i2c_begin();



    return (ereur_init);

}

bool deinit_gen()
{
     bool ereur_deinit = true;



    // je termine l'utilisation du port SPI
    mcp4822_deinitialize();

    // je termine l'uitlisation des broches I2C en les rebasculant en fonctionement pra default.

        i2c_init();

        // je libére la mémoire  et je ferme /dev/mem
        if (!bcm2835_close())
        {
            ereur_deinit=false;
        }

    return (ereur_deinit);

}
