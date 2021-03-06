#ifndef _JOGADOR_ 
#define _JOGADOR_

#include <string>
#include <vector>
#include <thread>

#include "Joystick.cpp"
#include "Utilidades.cpp"

using namespace std;

enum ESTADO{
  VIVO,
  MORTO,
};

void botao(int& b, int j){
    b = j;
}

void potenciometro(int& v, int j){
    v = j;
} 

//Classe representativa do jogador
class Jogador{
  private:
  	//Atributos
  	string nome;
  	vector<int> atingido;
  	int posicao;
    	ESTADO estado;
    	Joystick j;
    
  public:
  
    /*  Descrição : Construtor da classe
     *
     *  @param nome : Posição do jogador 
     *  @param int : Posição do jogador 
     */
  	Jogador(string nNome,int nPosicao){
  		this->nome = nNome;
  		this->posicao = nPosicao;
  		this->estado = ESTADO::VIVO;
  	}

    /*  Descrição : Obter a posição do jogador
     *
     *  @return int : Posição do jogador
     */
  	int getPosicao(){
  		return this->posicao;	
  	}


    /*  Descrição : Lista com os campos ja atingidos
     *
     *  @return vector<int> : Vetor com os campos que foram atingidos
     */
  	vector<int> getAtingido(){
  		return this->atingido;
  	}
  	
  	 /*  Descrição : Obter o nome do jogador
     *
     *  @return string : retorna o nome
     */
    string getNome(){
  		return this->nome;
  	}


    /*  Descrição : Adicionar nova posição
     *
     *  @param int : Nova Posição do jagador
     */  
    void setPosicao(int nPosicao){
      this->posicao = nPosicao;
    }
    
    /*  Descrição : Adicionar o nome do jogador
     *
     *  @param string : Nome
     */  
    void setNome(string nNome){
      this->nome = nNome;
    }
  
    /*  Descrição : Movimenta o jogador
     *  
     *  @param int : Posição que se deseja se mover
     *  
     *  @return boolean : TRUE para caso ele tenha se movido e FALSE para caso contrário;
     */  
    bool mover(int nPosicao){
      
      for(int p : this->atingido){
        if(p==nPosicao){
          return false;
        }
      }
      
      this->posicao = nPosicao;
      
      Utilidades::limpaTela();	
      
      cout << this->nome <<" se mexeu para um novo lugar" << endl;
  	
      return true;
    }
    
     /* Descrição : Jogador ataca adversário
     *  
     *  @param Jogador : Posição que se deseja se mover
     */  
    void atacar(Jogador& jAdversario){
      
      int i=0;
      
      int valorBotao = -1;	
      int valorPotenciometro=-1;
      
      thread tPot(potenciometro,ref(valorPotenciometro),j.escolherAngulo());	      
      thread tBot(botao,ref(valorBotao),j.valorBotao());
      
      tPot.join();
      tBot.join();
      
      while(valorPotenciometro==-1){
      	usleep(100000);
      }

      while(valorBotao==-1){
      	usleep(100000);
      }
      
      thread* valorP = NULL;	
      thread* valorB = NULL;
 				
      while(valorBotao==VALUE::LOW){
      	
        Utilidades::limpaTela();
      
	//Impressão das posições dos tiros ja realizados	
	cout << "Posições já atiradas por você : { ";
      
      	for(unsigned int c=0;c< jAdversario.atingido.size();c++){
	   if(c+1<jAdversario.atingido.size()){        
	       cout << jAdversario.atingido[c] << ", "; 
  	   }else{
	       cout << jAdversario.atingido[c] << " ";	
	   }    
        }	 	
        cout << "}" << endl;
      	
	valorP = new thread(potenciometro,ref(valorPotenciometro),j.escolherAngulo());

	valorP->join();
	
      	cout << this->nome <<" escolha o ângulo do tiro: ";
        cout << valorPotenciometro << endl;
	
	if(i==valorPotenciometro){
	    valorB = new thread(botao,ref(valorBotao),j.valorBotao());	
	    valorB->join();		
	}
	
	i=valorPotenciometro;

	usleep(200000);
      }
	
      cout << "Botão pressionado, mudando vez para o adversário" << endl;		
	
      bool jaExiste=false;	

      for(int p : jAdversario.atingido){
      	if(p==i){
	   jaExiste=true; 	
	}
      }
 			
      //Adicioanando valor aos locais que ele não pode mais ir
      if (jaExiste==false){
	jAdversario.atingido.push_back(i);
      }      
   	
      //cout << "Valor da sua posição: " << this->posicao << endl;
	
      //Verificar se o ataque acertou o advsário
      if(i==jAdversario.posicao){
        jAdversario.estado = ESTADO::MORTO;
      }	
    }
    
    /*  Descrição : Retorna o estado atual do jogador
     *
     *  @param ESTADO : ESTADO atual do jogador (Olhar enum de nome ESTADO)
     */  
    ESTADO getEstado(){
      return this->estado;
    }

    /*  Descrição : Retorna o joystic do jogador
     *
     *  @return Joystick : Joystick do jogador
     */  
    Joystick getJoystick(){
      return this->j;
    }
  
};	


#endif
