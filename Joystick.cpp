#ifndef _JOYSTICK_ 
#define _JOYSTICK_

#include <iostream>

#include "GPIO.cpp"

using namespace std;

#define ANGULO_MIN 18
#define ANGULO_MAX 82

class Joystick{
    private:
        
    public:
        
        Joystick(){
            
	    GPIO::setup(PORTNUMBER::P9_39);			//Porta analógica do potenciômetro
	    GPIO::setup(PORTNUMBER::P9_40);			//Porta analógica do fotosensor	
	    GPIO::setup(PORTNUMBER::P9_14,DIRECTION::IN); 	//Porta digital do botão
        }
        
        int valorBotao(){
            return GPIO::input(PORTNUMBER::P9_14);
        }
        
        int valorFotossensor(){
            if(GPIO::input(PORTNUMBER::P9_14)<1024){
	    	return VALUE::LOW;	
	    }else{
	    	return VALUE::HIGH;
	    }
        }
        
        int escolherAngulo(){
            int intervalo = 2048/(ANGULO_MAX - ANGULO_MIN);

	    return (GPIO::input(PORTNUMBER::P9_14)/intervalo) + ANGULO_MIN; 
        }
        
};
#endif
