#ifndef _JOYSTICK_ 
#define _JOYSTICK_

#include <iostream>

using namespace std;

#define ANGULO_MIN 20
#define ANGULO_MAX 80

class Joystick{
    private:
        
    public:
        
        Joystick(){
            
        }
        
        int valorBotao(){
            return 0;
        }
        
        int valorFotossensor(){
            return 0;
        }
        
        int valorPotenciometro(){
            return 0;
        }
        
        int escolherAngulo(){
            
            while(true){
            
                cout << "Escolha o ângulo: " << endl;
            
                
            }
            return -1;
        }
};

#endif