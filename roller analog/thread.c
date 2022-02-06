
#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "control.h"


 /* sert a paramettrer et cr�� mon thread, am�lioration possible: mettre en place
    des entrer de fonction pour automatis� la cr�ation de thread avec diff�rent parramettre.
    demander l'avis du prof�sseur sur la s�curit� pour un syst�me embarqu�                 */

pthread_t thread_param ()
{
   /*je cr�e ma structure pour mes paramettre;
     je cr�e une classe attr pour y stocker mes param�tre de thread;
     je cr�ed un "identifiant" pour mon thread;*/

    struct sched_param param;
        pthread_attr_t attr;
        pthread_t thread;

        //je cr�e une variable pour verifier le fonctionnement du param�trage mes threads
        int thr_erreur = 1;

    /*  je v�rouille la m�moire ram utilis� par mon programme maintenant et
        pour les future ressource utils�                                    */

    if (mlockall(MCL_CURRENT|MCL_FUTURE)==-1)
        {
        printf("probleme v�roulliage m�moire\n");
    exit(-1);
    }

    // j'initialise les paramettre au valeur par defaut.

    thr_erreur = pthread_attr_init (&attr);
        if (thr_erreur != 0)
        {
            printf("probleme initialisation attribut thread\n");
            exit(-1);
        }
        /* j'initialise les paramettre de l'ordonnace pour utiliser la FIFO*/

           thr_erreur = pthread_attr_setschedpolicy (&attr, SCHED_FIFO);


        if (thr_erreur != 0)
        {
            printf("probleme initialisation odronnace thread\n");
            exit(-1);
        }

        // je paramettre la priorit� du thread ans le file de processus de l'ordonnace donn�e
         param.sched_priority = 99 ;
        thr_erreur = pthread_attr_setschedparam(&attr, &param);

         if (thr_erreur != 0)
        {
            printf("probleme parrametrage de la priorit� du thread\n");
            exit(-1);
        }

        /* maintenant que j'ai param�ttrer le thread je le cr�e*/

        thr_erreur = pthread_create(&thread,&attr,control,NULL);

        if (thr_erreur != 0)
        {
            printf("probleme dans la cr�ation du thread\n");
            exit(-1);
        }                                               // ne pas oublier de le joindre l'ors de l'extictinon des roller

        return(thread);
}
