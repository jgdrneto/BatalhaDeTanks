#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <unistd.h> 

#include "Jogo.cpp"

#define MIN_OPCAO 1                   //Número de opções mínimas           
#define MAX_OPCAO 2                   //Número da opção máxima

using namespace std;

int opcoes(){
  
  
  
  int i=-1;

  do{
    
    Utilidades::limpaTela();
    
    cout << "BATALHA DE TANKS" << endl; 
    cout << "1 - Novo Jogo" << endl;
    cout << "2 - Sair" << endl;  
    cout << "--> ";
    cin >> i;
  
  }while(i<MIN_OPCAO && i>MAX_OPCAO);

  return i;
}

void quit(){
	cout << "Obrigado por jogar" << endl;
}

void jogo(){
	cout << "Bora jogar" << endl;
	
	//Crio objeto do jogo
	Jogo jogo;
	
	//Inicia o gameloop do jogo
	jogo.iniciar();
	
	//Finalizando o jogo
	quit();
}

int main(){
  
	switch(opcoes()){
        case 1:
          jogo();
        break;
          
        case 2:
          quit();
        break;
        
        default:
          //Caso se selecione uma opção não suportada
          cout << "Opção não suportada" << endl;
          exit(-1);
        break;
  }
	return 0;
}