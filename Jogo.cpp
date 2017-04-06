#ifndef _JOGO_
#define _JOGO_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

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
         *  @return int : Valor correspondente a ação escolhida 
         */
        ACAO escolherAcao(){

            int i=-1;

            do{
                
                Utilidades::limpaTela();
                
                cout << "O que deseja fazer: " << endl; 
                cout << "1 - Atacar" << endl;
                cout << "2 - Se mover" << endl;  
                cout << "--> ";
                cin >> i;
            }while(i<1 && i>2);
            
            ACAO ac;
            
            switch(i){
                case 1 :
                    ac = ACAO::ATACAR;
                break;
                case 2 :
                    ac = ACAO::MOVER;
                break;
                default:
                    ac = ACAO::MOVER;
                break;
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
            j1 = new Jogador(nomeJ2,pJ2); 
            
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
                
		ACAO acao = escolherAcao();
                
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
                
                //Verifica condição de vitória 
                terminou = verificarVitoria(*(jogadorAdversario));
                        
            }
            
            cout << "Parabêns " << jogadorDaVez->getNome() << "pela vitória" << endl;
            
        }
        
};

#endif
