#ifndef _UTILIDADES_
#define _UTILIDADES_

#include <stdlib.h>

class Utilidades{
    public:
        static void limpaTela(){
            if(system("clear")){
                system("cls");
            }  
        }
};

#endif