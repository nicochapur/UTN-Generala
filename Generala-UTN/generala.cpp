#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

void unJugador();
void tirarDados(int vectorDados[5]);
void mostrarDados(int vectorDados[5]);
int dadosIguales(int *vectorDados, bool hayDosIguales, bool hayTresIguales);
bool dosIguales(int c);
bool tresIguales(int c);
bool buscarEscalera(int *vectorDados, int juego);
bool buscarFull(bool hayDosIguales, bool hayTresIguales, int juego);
bool buscarPoker(int c, int juego);
bool buscarGenerala(int c, int juego);
void ordenarNumeros(int *vectorDados);
int jugada(int *vectorDados);
void calcularPuntos(int juego, int puntos);

int main (){
    /// INICIA EL PROGRAMA
    /// MENU PRINCIPAL
    /// 1 O 2 JUGADORES
    /// SOLICITAR NOMBRE/S
    /// TIRAR DADOS
    /// MOSTRAR DADOS
    /// GENERALA SERVIDA?
    /// VUELVE A TIRAR? QUE DADOS?

    ///MENU PRINCIPAL
    int opcion;
    bool seguirJugando;
    char jugador1[10], jugador2[10];
    seguirJugando = true;
    opcion=0;
    while(seguirJugando == true){
        system("cls");
        cout << "1. UN JUGADOR" << endl;
        cout << "2. DOS JUGADORES" << endl;
        cout << "3. PUNTUACION MAS ALTA" << endl;
        cout << "OPCION:" << endl;
        cin >> opcion;
        system("cls");
        switch(opcion){
            case 1: unJugador();
                    break;
            /*case 2: dosJugadores(jugador1, jugador2, puntaje);
                    break;
            case 3: mejorPuntuacion();
                    break;*/
            default:
                    break;
        }
        system("pause");
    }

    return 0;
}

void unJugador(){
    bool seguir;
    int vectorDados[5];
    int tiros, cantDados, posDado, cantRondas, totalPuntos;
    char nuevoTiro;
    totalPuntos = 0;
    string nombre;
    cout << "INGRESA TU NOMBRE:" << endl;
    cin >> nombre;
    cout << "CANTIDAD DE RONDAS A JUGAR:" << endl;
    cin >> cantRondas;
    system("cls");
    if(cantRondas!=0){
        for(int i=1; i<=cantRondas; i++){
            seguir=true;
            tiros=1;
            cout << "PARA EL JUGADOR: " << nombre << " || ";
            cout << "RONDA " << i << " || " << "TIRO " << tiros << endl;

            tirarDados(vectorDados);
            mostrarDados(vectorDados);

            while(seguir==true){
                cantDados=0;
                posDado=0;
                if(tiros<3){
                    cout << endl << "CONTINUAR LANZANDO? S/N" << endl;
                    cin >> nuevoTiro;
                    if (nuevoTiro == 's'){
                        cout << "CUANTOS DADOS?" << endl;
                        cin >> cantDados;
                        for(int i=1; i<=cantDados; i++){
                            cout << "POSICION DADO" << i << endl;
                            cin >> posDado;
                            vectorDados[posDado-1]= rand()%6+1;
                        }
                        mostrarDados(vectorDados);
                        tiros++;
                    } else {
                        seguir = false;
                    }

                } else {
                    seguir = false;
                }
            }
            totalPuntos+=jugada(vectorDados);
        }
    }
}

void mostrarDados(int *vectorDados){
    for(int i=0; i<5; i++){
        cout << vectorDados[i] << "\t";
    }
}

void tirarDados(int *vectorDados){
    for(int i=0; i<5; i++){
        vectorDados[i] = (rand()%6+1);
    }
}

int jugada(int *vectorDados){
    int c, juego, puntos;
    bool hayDosIguales=false, hayTresIguales=false;
    puntos=0;
    juego=0;

    c = dadosIguales(vectorDados, hayDosIguales, hayTresIguales);
    hayTresIguales = tresIguales(c);
    buscarEscalera(vectorDados,juego);
    buscarFull(hayDosIguales, hayTresIguales, juego);
    buscarPoker(c, juego);
    buscarGenerala(c, juego);
    calcularPuntos(juego,puntos);
    cout << c;
    cout << hayDosIguales;
    cout << hayTresIguales;
    return puntos;
}

int dadosIguales(int *vectorDados, bool hayDosIguales, bool hayTresIguales){
    int c, num, M;
    num = 0;
    M = 0;

      for(int x=0; x<5; x++){
        c=0;
        for(int y=0; y<5; y++){
            if(vectorDados[y] == vectorDados[x]){
                c++;
                num = vectorDados[x];
            }
        }
        if(c>M){
            M=c;
        }
    }
    return M;
}
bool dosIguales(int c){
    if(c==2){
        return true;
    }
    return false;
}

bool tresIguales(int c){
    if(c==3){
        return true;
    }
    return false;
}

bool buscarEscalera(int *vectorDados, int juego){
    ordenarNumeros(vectorDados);
    int i=0;
    while(vectorDados[i]+1 == vectorDados[i+1] && i<4){
        i++;
    }
    if(i==4)
    {
        juego = 1;

        return true;
    }

    return false;
}

bool buscarFull(bool hayDosIguales, bool hayTresIguales, int juego){
    if(hayDosIguales && hayTresIguales){
        juego = 2;
        return true;
    }

    return false;
}

bool buscarPoker(int c, int juego){
    if(c==4){
        juego = 3;
        return true;
    }
    return false;
}

bool buscarGenerala(int c, int juego){
    if(c==5){
        juego = 4;
        return true;
    }
    return false;
}

void ordenarNumeros(int *vectorDados){
    int aux = 0;
    for(int x=0; x<5; x++){
        for(int y=1; y<5; y++){
            if(vectorDados[x] < vectorDados[y]){
                aux = vectorDados[x];
                vectorDados[x] = vectorDados[y];
                vectorDados[y] = aux;
            }
        }
    }
}

int sumarIguales(int c, int num){
    int puntos = c * num;
    return puntos;
}

void calcularPuntos(int juego, int puntos){

    switch(juego){
        case 1:
            cout << "ESCALERA" << endl;
            puntos = 25;
            break;
        case 2:
            cout << "FULL" << endl;
            puntos = 30;
            break;
        case 3:
            cout << "POKER" << endl;
            puntos = 40;
            break;
        case 4:
            cout << "GENERALA" << endl;
            puntos = 50;
            break;
        default:
            //sumarIguales();
            break;
    }
}

///NECESITO FUNCION JUEGO QUE RETORNE EL NOMBRE DE LA JUGADA QUE REALIZO
