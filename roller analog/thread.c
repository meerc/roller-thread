
#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "control.h"


 /* sert a paramettrer et créé mon thread, amélioration possible: mettre en place
    des entrer de fonction pour automatisé la création de thread avec différent parramettre.
    demander l'avis du profésseur sur la sécurité pour un systéme embarqué                 */

pthread_t thread_param ()
{
   /*je crée ma structure pour mes paramettre;
     je crée une classe attr pour y stocker mes paramétre de thread;
     je créed un "identifiant" pour mon thread;*/

    struct sched_param param;
        pthread_attr_t attr;
        pthread_t thread;

        //je crée une variable pour verifier le fonctionnement du paramétrage mes threads
        int thr_erreur = 1;

    /*  je vérouille la mémoire ram utilisé par mon programme maintenant et
        pour les future ressource utilsé                                    */

    if (mlockall(MCL_CURRENT|MCL_FUTURE)==-1)
        {
        printf("probleme véroulliage mémoire\n");
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

        // je paramettre la priorité du thread ans le file de processus de l'ordonnace donnée
         param.sched_priority = 99 ;
        thr_erreur = pthread_attr_setschedparam(&attr, &param);

         if (thr_erreur != 0)
        {
            printf("probleme parrametrage de la priorité du thread\n");
            exit(-1);
        }

        /* maintenant que j'ai paraméttrer le thread je le crée*/

        thr_erreur = pthread_create(&thread,&attr,control,NULL);

        if (thr_erreur != 0)
        {
            printf("probleme dans la création du thread\n");
            exit(-1);
        }                                               // ne pas oublier de le joindre l'ors de l'extictinon des roller

        return(thread);
}
