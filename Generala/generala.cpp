#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

void unJugador();
void dosJugadores();
void tirarDados(int vectorDados[5]);
void mostrarDados(int vectorDados[5]);
int buscarJugada(int *vectorDados, int &tiros);
int dadosIguales(int *vectorDados, bool &hayDosIguales, bool &hayTresIguales, int &num);
bool dosIguales(int c);
bool tresIguales(int c);
bool buscarEscalera(int *vectorDados, int &juego);
bool buscarFull(bool &hayDosIguales, bool &hayTresIguales, int &juego);
bool buscarPoker(int c, int &juego);
bool buscarGenerala(int c, int &juego, int &tiros);
void ordenarNumeros(int *vectorDados);
void sumarIguales(int c, int num, int &puntos);
int calcularPuntos(int &juego, int c, int n);

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
            case 2: dosJugadores();
                    break;
//            case 3: mejorPuntuacion();
//                    break;
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
    for(int i=1; i<=cantRondas; i++){
        seguir=true;
        tiros=1;
        cout << "PARA EL JUGADOR: " << nombre << endl;
        cout << "RONDA " << i << " || " << "TIRO " << tiros << " || " << "PUNTOS " << totalPuntos << endl;
        cout << endl;

        tirarDados(vectorDados);
        mostrarDados(vectorDados);

        cout << endl;
        totalPuntos += buscarJugada(vectorDados,tiros);
        while(seguir==true){
            cantDados=0;
            posDado=0;
        if(totalPuntos >= 1000){
            cout<<"GANASTE EL JUEGO"<<endl;
            seguir = false;
        }
        if(tiros < 3 && totalPuntos < 1000){
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
        system("pause");
        system("cls");
    }
}

void cuadroDeJuego(int &i, string &jugadorActual, int &totalPuntos1, int &totalPuntos2){
    cout << "NUM DE RONDA: " << i << endl;
    cout << "PROXIMO A JUGAR: " << jugadorActual << endl;
    cout << "PUNTAJE JUGADOR NUM 1: " << totalPuntos1 << endl;
    cout << "PUNTAJE JUGADOR NUM 2: " << totalPuntos2 << endl;
    system("pause");
    system("cls");
}

void dosJugadores(){
    bool seguir;
    int vectorDados[5];
    int tiros, cantDados, posDado, cantRondas, totalPuntos1, totalPuntos2, puntosActuales;
    char nuevoTiro;
    bool generala1, generala2;
    totalPuntos1 = 0;
    totalPuntos2 = 0;
    string primerJugador, segundoJugador, jugadorActual;
    cout << "INGRESA EL PRIMER JUGADOR:" << endl;
    cin >> primerJugador;
    cout << "INGRESA EL SEGUNDO JUGADOR:" << endl;
    cin >> segundoJugador;
    cout << "CANTIDAD DE RONDAS A JUGAR:" << endl;
    cin >> cantRondas;
    jugadorActual = primerJugador;
    puntosActuales = totalPuntos1;
    system("cls");
    for(int i=1; i<=cantRondas; i++){
        for(int x=0; x<2; x++){
            seguir=true;
            tiros = 1;
            cuadroDeJuego(i, jugadorActual, totalPuntos1, totalPuntos2);

            cout << "PARA EL JUGADOR: " << jugadorActual << endl;
            cout << "RONDA " << i << " || " << "TIRO " << tiros << " || " << "PUNTOS " << puntosActuales << endl;
            cout << endl;

            tirarDados(vectorDados);
            mostrarDados(vectorDados);

            cout << endl;
            puntosActuales += buscarJugada(vectorDados,tiros);
            while(seguir==true){
                cantDados=0;
                posDado=0;
            if(puntosActuales >= 1000){
                if(jugadorActual == primerJugador){
                    generala1=true;
                } else {
                    generala2=true;
                }
                seguir = false;
            }
            if(tiros < 3){
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
                            cout << nuevoTiro << endl;
                            cout << cantDados << endl;
                            cout << posDado << endl;
                            cout << vectorDados[posDado-1] << endl;
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
        if(generala1 || generala2){
            if (generala1 && generala2){
                cout << "EMPATE";
            } else if(generala1){
                cout << "GANA JUGADOR 1";
            } else {
                cout << "GANA JUGADOR 2";
            }
        }
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
//    vectorDados[1]=2;
//    vectorDados[2]=4;
//    vectorDados[3]=6;
//    vectorDados[4]=4;
}

int buscarJugada(int *vectorDados, int &tiros){
    int c, num, juego, puntos,ganaPartida;
    bool hayDosIguales=false, hayTresIguales=false;
    num = 0;
    juego = 0;
    ganaPartida=0;

    c = dadosIguales(vectorDados, hayDosIguales, hayTresIguales, num);
    hayTresIguales = tresIguales(c);
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
            hayDosIguales = dosIguales(c);
        }
        if(c>M){
            M=c;
            num = vectorDados[x];
        }
    }
    if(M==3){
        hayTresIguales = tresIguales(M);
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

bool buscarEscalera(int *vectorDados, int &juego){
    ordenarNumeros(vectorDados);
    int i = 0;
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

void ordenarNumeros(int *vectorDados){
    int aux;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(vectorDados[j]>vectorDados[j+1]){
                aux=vectorDados[j];
                vectorDados[j]=vectorDados[j+1];
                vectorDados[j+1]=aux;
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
            cout<<"GENERALA SERVIDA!"<<endl;
            puntos = 1000;

            break;
        default:
            sumarIguales(c, n, puntos);
            break;
    }
    return puntos;
}

///NECESITO FUNCION JUEGO QUE RETORNE EL NOMBRE DE LA JUGADA QUE REALIZO
