#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

#include "funciones.h"
using namespace std;

void cuadroDeJuego(int index, string jugadorActual, int totalPuntos1, int totalPuntos2);
void unJugador(string &ganador, int &puntaje);
void dosJugadores(string &ganador, int &puntaje);
void tirarDados(int vectorDados[5]);
void mostrarDados(int vectorDados[5]);
int buscarJugada(int *vectorDados, int &tiros);
int dadosIguales(int *vectorDados, bool &hayDosIguales, bool &hayTresIguales, int &num);
//bool dosIguales(int c);
//bool tresIguales(int c);
bool buscarEscalera(int *vectorDados, int &juego);
bool buscarFull(bool &hayDosIguales, bool &hayTresIguales, int &juego);
bool buscarPoker(int c, int &juego);
bool buscarGenerala(int c, int &juego, int &tiros);
void ordenarNumeros(int *vaux);
void sumarIguales(int c, int num, int &puntos);
int calcularPuntos(int &juego, int c, int n);

int main (){
    ///MENU PRINCIPAL
    int opcion, puntaje, pos, P, M;
    bool seguirJugando;
    string ganador, histGanadores[10];
    int histPuntajes[10]={0};

    seguirJugando = true;
    puntaje = 0;
    opcion = 0;
    pos = 0;
    M = 0;
    P = 0;

    while(seguirJugando == true){
        textcolor(0,0);
        clrscr();
        recuadro(8, 1, 30, 16, cAMARILLO, cGRIS);
        gotoxy(10,3);
        cout << "1. UN JUGADOR" << endl;
        gotoxy(10,4);
        cout << "2. DOS JUGADORES" << endl;
        gotoxy(10, 5);
        cout << "3. PUNTUACION MAS ALTA" << endl;
        gotoxy(10, 6);
        cout << "0. SALIR" << endl;
        gotoxy(10, 8);
        cout << "OPCION:";
        gotoxy(20, 8);
        cin >> opcion;
        system("cls");

        switch(opcion){
            case 1:
                unJugador(ganador, puntaje);
                histGanadores[pos] = ganador;
                histPuntajes[pos] = puntaje;
                pos++;
                break;
            case 2:
                dosJugadores(ganador, puntaje);
                histGanadores[pos] = ganador;
                histPuntajes[pos] = puntaje;
                pos++;
                break;
            case 3:
                textcolor(cBLANCO);
                clrscr();
                for(int h=0; h<10; h++){
                    if(histPuntajes[h]>M){
                        M = histPuntajes[h];
                        P = h;
                    }
                }
                cout << "MAJOR PUNTAJE JUGADOR: " << histGanadores[P] << " CON " << histPuntajes[P] << " PUNTOS." << endl;
                break;
            case 0:
                return 0;
                break;
            default:
                gotoxy(9, 15);
                textcolor(cROJO_CLARO);
                cout << "Opcion de menu invalida";
                break;
        }
        system("pause");
    }

    return 0;
}

void unJugador(string &ganador, int &puntaje){
    textcolor(cBLANCO);
    clrscr();
    bool seguir, generalaServida;
    int vectorDados[5], esGenerala, tiros, cantDados, posDado, cantRondas, totalPuntos;
    char nuevoTiro;
    string nombre;

    esGenerala = 0;
    totalPuntos = 0;
    generalaServida = false;

    cout << "INGRESA TU NOMBRE:" << endl;
    cin >> nombre;
    cout << "CANTIDAD DE RONDAS A JUGAR:" << endl;
    cin >> cantRondas;

    system("cls");
    for(int index=1; index<=cantRondas; index++){
        if(generalaServida == false) {
            seguir=true;
            tiros=1;
            cout << "PARA EL JUGADOR: " << nombre << endl;
            cout << "RONDA " << index << " || " << "TIRO " << tiros << " || " << "PUNTOS " << totalPuntos << endl;
            cout << endl;

            tirarDados(vectorDados);
            mostrarDados(vectorDados);
            cout << endl;

            esGenerala = buscarJugada(vectorDados,tiros);
            while(seguir==true){
                if(esGenerala >= 1000){
                    cout<<"GENERALA SERVIDA!"<<endl;
                    cout<<"GANASTE EL JUEGO"<<endl;
                    generalaServida = true;
                    seguir = false;
                }
                if(tiros < 3 && esGenerala < 1000){
                        cout << endl << "CONTINUAR LANZANDO? S/N" << endl;
                        cin >> nuevoTiro;
                        if (nuevoTiro == 's' || nuevoTiro == 'S'){
                            cout << "CUANTOS DADOS?" << endl;
                            cin >> cantDados;
                            for(int y = 1; y <= cantDados; y++){
                                cout << "POSICION DADO" << y << endl;
                                cin >> posDado;
                                srand(time(NULL));
                                vectorDados[posDado-1] = rand()%6+1;
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
            totalPuntos += buscarJugada(vectorDados,tiros);
            system("pause");
            system("cls");
        }
    }
    puntaje = totalPuntos;
    ganador = nombre;

    cout << "RESUMEN DE PARTIDA" << endl;
    cout << endl;
    cout << "JUGADOR: " << ganador << " PUNTOS " << puntaje << endl;
}

void cuadroDeJuego(int index, string jugadorActual, int totalPuntos1, int totalPuntos2){
    cout << "NUM DE RONDA: " << index << endl;
    cout << "PROXIMO A JUGAR: " << jugadorActual << endl;
    cout << "PUNTAJE JUGADOR NUM 1: " << totalPuntos1 << endl;
    cout << "PUNTAJE JUGADOR NUM 2: " << totalPuntos2 << endl;

    system("pause");
    system("cls");
}

void dosJugadores(string &ganador, int &puntaje){
    textcolor(cBLANCO);
    clrscr();
    bool seguir, generala1, generala2, generalaServida;
    int tiros, cantDados, posDado, cantRondas, totalPuntos1, totalPuntos2, puntosActuales, vectorDados[5], esGenerala;
    char nuevoTiro;
    string primerJugador, segundoJugador, jugadorActual;

    puntosActuales = 0;
    totalPuntos1 = 0;
    totalPuntos2 = 0;
    puntaje = 0;
    esGenerala = 0;
    generala1 = false;
    generala2 = false;
    generalaServida = false;

    cout << "INGRESA EL PRIMER JUGADOR:" << endl;
    cin >> primerJugador;
    cout << "INGRESA EL SEGUNDO JUGADOR:" << endl;
    cin >> segundoJugador;
    cout << "CANTIDAD DE RONDAS A JUGAR:" << endl;
    cin >> cantRondas;
    jugadorActual = primerJugador;
    puntosActuales = totalPuntos1;
    system("cls");
    for(int index=1; index<=cantRondas; index++){
        if(generalaServida == false){
            for(int x=0; x<2; x++){
                seguir=true;
                tiros = 1;
                cuadroDeJuego(index, jugadorActual, totalPuntos1, totalPuntos2);
                puntosActuales = 0;
                cout << "PARA EL JUGADOR: " << jugadorActual << endl;
                cout << "RONDA " << index << " || " << "TIRO " << tiros << " || " << "PUNTOS " << puntosActuales << endl;
                cout << endl;

                tirarDados(vectorDados);
                mostrarDados(vectorDados);

                cout << endl;

                esGenerala = buscarJugada(vectorDados,tiros);
                while(seguir==true){
                    if(esGenerala >= 1000){
                        cout<<"GENERALA SERVIDA!"<<endl;
                        if(x == 0){
                            generala1=true;
                        } else {
                            generala2=true;
                        }
                        generalaServida = true;
                        seguir = false;
                    }
                    if(tiros < 3 && esGenerala<1000){
                        cantDados=0;
                        posDado=0;
                        cout << endl << "CONTINUAR LANZANDO? S/N" << endl;
                        cin >> nuevoTiro;
                        if (nuevoTiro == 's' || nuevoTiro == 'S'){
                            cout << "CUANTOS DADOS?" << endl;
                            cin >> cantDados;
                            for(int y = 1; y <= cantDados; y++){
                                cout << "POSICION DADO" << y << endl;
                                cin >> posDado;
                                srand(time(NULL));
                                vectorDados[posDado-1] = rand()%6+1;
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
                puntosActuales += buscarJugada(vectorDados,tiros);
                if(jugadorActual == primerJugador){
                    jugadorActual = segundoJugador;
                    totalPuntos1 = puntosActuales;
                    puntosActuales = totalPuntos2;
                } else {
                    jugadorActual = primerJugador;
                    totalPuntos2 = puntosActuales;
                    puntosActuales = totalPuntos1;
                }
                system("pause");
                system("cls");
            }
        }
    }
    if((generala1 && generala2) || (totalPuntos1 == totalPuntos2)){
        cout << "EMPATE!" << endl;
    } else if(totalPuntos1>totalPuntos2){
        ganador = primerJugador;
        puntaje = totalPuntos1;
        cout << "GANADOR JUGADOR: " << ganador << " PUNTOS: " << puntaje << endl;
    } else {
        ganador = segundoJugador;
        puntaje = totalPuntos2;
        cout << "GANADOR JUGADOR: " << ganador << " PUNTOS: " << puntaje << endl;
    }
}


void mostrarDados(int *vectorDados){
    for(int i=0; i<5; i++){
        cout << vectorDados[i] << "\t";
    }
}

void tirarDados(int *vectorDados){
    srand(time(NULL));
    for(int i=0; i<5; i++){
        vectorDados[i] = (rand()%6+1);
    }
//    vectorDados[0]=4;
//    vectorDados[1]=4;
//    vectorDados[2]=5;
//    vectorDados[3]=3;
//    vectorDados[4]=1;
}

int buscarJugada(int *vectorDados, int &tiros){
    int c, num, juego, puntos,ganaPartida;
    bool hayDosIguales=false, hayTresIguales=false;
    num = 0;
    juego = 0;
    ganaPartida=0;

    c = dadosIguales(vectorDados, hayDosIguales, hayTresIguales, num);
  //  hayTresIguales = tresIguales(c);
    buscarEscalera(vectorDados,juego);
    buscarFull(hayDosIguales, hayTresIguales, juego);
    buscarPoker(c, juego);
    buscarGenerala(c, juego, tiros);
    puntos = calcularPuntos(juego, c, num);

    return puntos;
}

int dadosIguales(int *vectorDados, bool &hayDosIguales, bool &hayTresIguales, int &num){
    int c, b, M;
    M = 0;
    b = 0;

    for(int x=0; x<5; x++){
        c = 0;
        for(int y=0; y<5; y++){
            if(vectorDados[y] == vectorDados[x]){
                c++;
            }
        }
        if(c==2){
            hayDosIguales = true;
        }
        if(c>=M){
            M=c;
            if(vectorDados[x]>num){
                num = vectorDados[x];
            }
        }
    }
    if(M==3){
        hayTresIguales = true;
    }
    return M;
}

//bool dosIguales(int c){
//    if(c==2){
//        return true;
//    }
//    return false;
//}
//
//bool tresIguales(int c){
//    if(c==3){
//        return true;
//    }
//    return false;
//}

bool buscarEscalera(int *vectorDados, int &juego){
    int vaux[5]={0};
    for(int f=0; f<5; f++){
        vaux[f] = vectorDados[f];
    }
    ordenarNumeros(vaux);
    int i = 0;
    while(vaux[i]+1 == vaux[i+1] && i<4){
        i++;
    }
    if(i==4)
    {
        juego = 1;

        return true;
    }
    return false;
}

void ordenarNumeros(int *vaux){
    int aux;
    for(int t=0;t<5;t++){
        for(int j=0;j<4;j++){
            if(vaux[j]>vaux[j+1]){
                aux=vaux[j];
                vaux[j]=vaux[j+1];
                vaux[j+1]=aux;
            }
        }
    }
}

bool buscarFull(bool &hayDosIguales, bool &hayTresIguales, int &juego){
    if(hayDosIguales && hayTresIguales){
        juego = 2;
        return true;
    }
    return false;
}

bool buscarPoker(int c, int &juego){
    if(c==4){
        juego = 3;
        return true;
    }
    return false;
}

bool buscarGenerala(int c, int &juego, int &tiros){
    if(c==5){
        juego = 4;
        if(tiros==1)
        {
         juego = 5;
        }
        return true;
    }
    return false;
}

void sumarIguales(int c, int num, int &puntos){
    puntos = c * num;
}

int calcularPuntos(int &juego, int c, int n){
    int puntos = 0;
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
        case 5:
            puntos = 1000;
            break;
        default:
            sumarIguales(c, n, puntos);
            break;
    }
    return puntos;
}
