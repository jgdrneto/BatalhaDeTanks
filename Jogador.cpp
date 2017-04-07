#ifndef _JOGADOR_ 
#define _JOGADOR_

#include <string>
#include <vector>

#include "Joystick.cpp"
#include "Utilidades.cpp"

using namespace std;

enum ESTADO{
  VIVO,
  MORTO,
};

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
      
      return true;
    }
    
     /* Descrição : Jogador ataca adversário
     *  
     *  @param Jogador : Posição que se deseja se mover
     */  
    void atacar(Jogador& jAdversario){
      
      int i=0;
      
      while(j.valorBotao()==VALUE::LOW){
      
        Utilidades::limpaTela();
      
        cout << "Escolha o ângulo: ";
        i = j.escolherAngulo();
        cout << i << endl;
      }

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
      cout << "Valor do vetor do advesário: " << jAdversario.atingido.size() << endl;	
      cout << "Valor da sua posição: " << this->posicao << endl;
	
      //Verificar se o ataque acertou o advsário
      if(i==jAdversario.posicao){
        jAdversario.estado = ESTADO::MORTO;
      }
      
      cout << "Posições já atiradas : { ";
      
      for(int p :  jAdversario.atingido){
        cout << p << ", "; 
      }	 	
      cout << "}" << endl;	
    }
    
    /*  Descrição : Retorna o estado atual do jogador
     *
     *  @param ESTADO : ESTADO atual do jogador (Olhar enum de nome ESTADO)
     */  
    ESTADO getEstado(){
      return this->estado;
    }
  
};	


#endif
