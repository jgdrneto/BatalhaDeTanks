#ifndef _JOGO_
#define _JOGO_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>

#include "Jogador.cpp"

using namespace std;

enum ACAO{
    
    ATACAR = 1,
    MOVER = 2,

};

class Jogo{
    private:
        
        //Atributos
        Jogador* j1;
        Jogador* j2;
        bool terminou;
        
        /*  Descrição : Definir nomes de um jogador
         *
         *  @param int : Número correspondente ao jogador
         *  
         *  @return string : Nome do jogador informado
         */
        string definirNome(int i){
            string nome;
            
            Utilidades::limpaTela();
            
            cout << "Qual o nome do jogador " << i << " : ";
            cin >> nome;
            
            return nome;
        }
        /*  Descrição : Troca o jogador
         *
         *  @return Jogador : Jogador da Vez
         *  
         */
        Jogador* trocaDeJogador(Jogador* jogadorDaVez){
                    
            //Comparando referências de jogador
            if(&*(jogadorDaVez)==&*(this->j1)){
		return &*(this->j2);
            }else{
		return &*(this->j1);
            }
        }
        
        /*  Descrição : Definir posição possivel
         *  
         *  return int : Nova posição aleatória 
         */
        int novaPosicao(){
            
             //Definindo semente do algoritmo randômico de acordo com a hora local da execução 
            srand( (unsigned)time(NULL) );
            
            return (rand() % (ANGULO_MAX+1-ANGULO_MIN)) + ANGULO_MIN;
        } 
        
        /*  Descrição : Verifica a ação escolhida do usuário
         *
	 *  @param Jogador* : Ponteiro do jogador atual 
	 * 	
         *  @return int : Valor correspondente a ação escolhida 
         */
        ACAO escolherAcao(Jogador* jogadorDaVez){
	    
	    Utilidades::limpaTela();	
	
	    cout << jogadorDaVez->getNome() << " o que você deseja fazer: " << endl; 
	    cout << "Cubra o fotosensor para escolher se mover" << endl;
	    cout << "Não cubra o fotosensor para escolher atacar" << endl;
	    cout << "Você tem 5 segundos para decidir" << endl;
	    
	    //Tempo para verificar o sensor
	    usleep(5000000);
	    
	    ACAO ac;
            		
            if(jogadorDaVez->getJoystick().valorFotossensor()==VALUE::LOW){
	    	ac = ACAO::MOVER;
	    }else{
	    	ac = ACAO::ATACAR;
	    }

            return ac;
        }
        /*  Descrição : Verifica condição de vitória
         *
         *  @param Jogador& : Endereço do jogador que pode ter perdido
         *  
         *  @return boolean : TRUE caso houve vitória, FALSE caso contrário 
         */
        bool verificarVitoria(Jogador& jAdversario){
            return jAdversario.getEstado()==ESTADO::MORTO;
        }
        
    public:
        
        /*  Descrição: Construtor da classe
         *
         */
        Jogo(){
            
            //Definindo nome do jogador 1
            string nomeJ1 = definirNome(1);
            
            //Definindo posicao do jogador 1
            int pJ1 = novaPosicao();
            
            //Definindo nome do jogador 2
            string nomeJ2 = definirNome(2);
            
             //Definindo posicao do jogador 2
            int pJ2 = novaPosicao();
                
            j1 = new Jogador(nomeJ1, pJ1);
            j2 = new Jogador(nomeJ2,pJ2); 
            
            //Condição de término do jogo
            terminou=false;
        }
        
        
        /*  Descrição : Laço principal do jogo
         */
        void iniciar(){
            
            Jogador* jogadorDaVez = NULL;  
            Jogador* jogadorAdversario = NULL;
            
            jogadorDaVez = &*(this->j2);
            jogadorAdversario = &*(this->j1);

            //GameLoop
            while(!terminou){
                //Troca a vez do jogador    
                jogadorDaVez = trocaDeJogador(jogadorDaVez);
                
		jogadorAdversario = trocaDeJogador(jogadorDaVez);
                		
		ACAO acao = escolherAcao(jogadorDaVez);
                
                switch(acao){
                    case ACAO::ATACAR :
                        // Jogador da Vez ataca o jogador Adversário
                        jogadorDaVez->atacar(*(jogadorAdversario));    
                    break;
                    case ACAO::MOVER :
                        
                        bool seMover = false;
                        
                        //Enquanto jogador não se mover
                        while(!seMover){
                            seMover = jogadorDaVez->mover(novaPosicao());
                        }
                        
                    break;
                }
                
		//Tempo entre interações
		usleep(5000000);

                //Verifica condição de vitória 
                terminou = verificarVitoria(*(jogadorAdversario));
                        
            }
            
            cout << "Parabêns " << jogadorDaVez->getNome() << " pela vitória" << endl;
            
        }
        
};

#endif
