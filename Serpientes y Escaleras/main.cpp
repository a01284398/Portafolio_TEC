#include <iostream>
using namespace std;
#include "Jugador.h"
#include "Dado.h"
#include "Tablero.h"
#include "InvalidConfigurationException.h"
#include "InvalidOptionException.h"
#include <ctime>
#include <cstdlib>


void skipLine() {
  for(int i = 0; i < 5; i++){
    cout<<endl;
  }
}

int main() {
  //Variables
  int game = 0;
  int status = 0;
  int counter = 0;
  int numJugadores, prompt, valor, prompt2, valorDado;
  string nombre;


  //Crear tablero
  int tiles = 20;
  Tablero tablero[tiles];
  Die dadoTablero(4);
  dadoTablero.start();
  //excepción
  try{
    if(tiles < 20){
      status = 1;
      throw invconfex; 
    }
  }
  catch (exception& e){
    cout<<e.what() << "\n";
  }
if (status < 1){
  
  //Agregar un identificador a cada casilla y un bonus aleatorio
  for(int i = 0; i < 30; i++){
    tablero[i].setId(i);
    tablero[i].setBonus(dadoTablero.rollDieTablero());
  }


  //Iniciar el dado del juego
  Die dado(6);
  dado.start();


  //Bienvenida y entrada de jugadores
  cout<<"¡Bienvenido a Serpientes y Escaleras! ¿Cuantos jugadores van a jugar?"<<endl;
  cin >> numJugadores;
  Jugador jugadores[numJugadores];


  //Ingresar nombres de los jugadores
  for(int i = 0; i < numJugadores; i++){
    cout<<"Ingresa el nombre del jugador #"<<i + 1<<endl;
    cin>>nombre;
    jugadores[i].setNombre(nombre);
  }
  skipLine();

  //
  while (game == 0) {
    prompt = 0;
    //Menu
    cout<<"1. Empezar el juego."<<endl;
    cout<<"2. Ver puntuaciones."<<endl;
    cout<<"3. Jugadores."<<endl;
    cout<<"4. Cambiar valor maximo del dado (default = 6)."<<endl;
    cout<<"5. Salir."<<endl;
    cin>>prompt;
    skipLine();
    if(prompt >= 1 && prompt <= 5){
      switch(prompt){
      case 1: 
        game = true;
        while(game){
        for(int i = 0; i < numJugadores; i++){
          //Generar numero aleatorio
          valor = dado.rollDie();

          cout<<jugadores[i].getNombre()<<" es tu turno, teclea 1 para lanzar el dado: ";
          cin>>prompt2;
          skipLine();
          if(prompt2 == 1) {
            cout<<jugadores[i].getNombre()<<" lanzaste un: "<<valor;
            skipLine();
            jugadores[i].move(valor);
            if(jugadores[i].getCasilla() >= 30){
              cout<<"¡Felicidades! "<<jugadores[i].getNombre()<<", ganaste esta ronda de serpientes y escaleras."<<endl;
              jugadores[i].setPuntuacion(1);
              game = false;
              for(int i = 0; i < numJugadores; i++){
                jugadores[i].restart();
              }
              break;
          }
            cout<<jugadores[i].getNombre()<<" te encuentras en la casilla #"<<jugadores[i].getCasilla();
            skipLine();
            cout<<"Esta casilla tiene un bonus de: "<<tablero[jugadores[i].getCasilla()].getBonus();
            skipLine();
            jugadores[i].move(tablero[jugadores[i].getCasilla()].getBonus());
            cout<<jugadores[i].getNombre()<<" ahora te encuentras en la casilla #"<<jugadores[i].getCasilla();
            skipLine();
          }
          else{
            throw invOpt;
        }
      }
      break;
    case 2:{
      for(int i = 0; i < numJugadores; i++){
            cout<<jugadores[i].getNombre()<<": "<<jugadores[i].getPuntuacion()<<" Puntos."<<endl;
        }
        skipLine();
        break;
    }
      
    case 3: {
      for(int i = 0; i < numJugadores; i++){
        cout<<"Jugador #"<<i+1<<": "<<jugadores[i].getNombre()<<endl;
        }
        skipLine(); break;
    }       
    case 4: {
      cout<<"Ingresa el valor maximo del dado: ";
        cin>>valorDado;
        dado.setDieSize(valorDado);
        skipLine(); break;
    }
    case 5: {
    cout<<"Gracias por jugar!"<<endl;
    game = 1 ;break;
    }
    }
    }
  }
  else{
    cout<<"Invalid option, try again"<<endl;
  }
}
}
return 0;
}