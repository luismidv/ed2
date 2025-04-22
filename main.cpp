#include <iostream>
#include <cstdlib>
#include <queue>
#include "arbin.h"
#include "abb.h"
#include "Excep_Ej6.h"

// Recorridos

template <typename T>
void inorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        inorden(a, a.subIzq(r));
        cout << r.observar() << " ";
        inorden(a, a.subDer(r));
    }
}
template <typename T>
void preorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        cout << r.observar() << " ";
        preorden(a, a.subIzq(r));
        preorden(a, a.subDer(r));
    }
}

template <typename T>
void postorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        postorden(a, a.subIzq(r));
        postorden(a, a.subDer(r));
        cout << r.observar() << " ";
    }
}

template <typename T>
void anchura(const Arbin<T>& a) {
    if (!a.esVacio()) {
        queue<typename Arbin<T>::Iterador> c;
        typename Arbin<T>::Iterador ic = a.getRaiz();
        c.push(ic);
        while (!c.empty()) {
             ic = c.front();
             c.pop();
             cout << ic.observar() << " ";
             if (!a.subIzq(ic).arbolVacio())
                c.push(a.subIzq(ic));
             if (!a.subDer(ic).arbolVacio())
                c.push(a.subDer(ic));
        }
    }
}


/***************************************************************************/
/****************************** EJERCICIOS *********************************/
/***************************************************************************/

//Ejercicio 1

template <typename T>
int numHojas(const Arbin<T> a){
    return numHojas(a, a.getRaiz());
}

template <typename T>
int numHojas(const Arbin<T> a, const typename Arbin<T>::Iterador r){
    if (!r.arbolVacio()){
        if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()){
            return 1;
        }else{
            return numHojas(a,a.subIzq(r)) + numHojas(a,a.subDer(r));
        }
    }else{
        return 0;
    }
}

/****************************************************************************/

//Ejercicio 2
template <typename T>
Arbin<T> simetrico(const Arbin<T> a){
    return simetrico(a, a.getRaiz());
}

template <typename T>
Arbin<T> simetrico(const Arbin<T> a, const typename Arbin<T>::Iterador r){
    if (!r.arbolVacio()){
        if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()){
            return Arbin<T>(r.observar(), Arbin<T>(), Arbin<T>());
        }else{
            return Arbin<T>(r.observar(), simetrico(a, a.subDer(r)), simetrico(a,a.subIzq(r)));
        }
    }else{
        return Arbin<T>();
    }
}



/****************************************************************************/
//Ejercicio 3

template <typename T>
void recorridoZigzag(const Arbin<T> a, char sentido){
    return recorridoZigzag(a, a.getRaiz(), sentido);
}

template <typename T>
void recorridoZigzag(const Arbin<T> a, const typename Arbin<T>::Iterador r, char sentido){
    if (!r.arbolVacio()){
        cout << r.observar() << " ";
        if (sentido == 'I'){
            return recorridoZigzag(a, a.subIzq(r), 'D');
        }else{
            return recorridoZigzag(a, a.subDer(r), 'I');
        }
    }else{
        return;
    }
}
/******************************************************************************/
//Ejercicio 4
template <typename T>
int numNodos(const Arbin<T> a, const typename Arbin<T>::Iterador r){
    if (r.arbolVacio()){
        return 0;
    }else{
        return (1 + numNodos(a,a.subIzq(r)) + numNodos(a,a.subDer(r)));
    }
}
template <typename T>
bool compensado (const Arbin<T> a){
    return compensado(a, a.getRaiz());
}

template <typename T>
bool compensado(const Arbin<T> a, const typename Arbin<T>::Iterador r){
    if (r.arbolVacio() || (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio())){
        return true;
    }else{
        if ( (abs(numNodos(a,a.subIzq(r))- numNodos(a,a.subDer(r))) <=1)
            &&compensado(a,a.subIzq(r))
            &&compensado(a,a.subDer(r)))
        {
            return true;

        }else{

            return false;
        }
    }
}


/*****************************************************************************/
//Ejercicio 5

template <typename T>
void palabras ( const Arbin<T> a){
    string palabra = "";
    return palabras(a, a.getRaiz(), palabra);
}

template <typename T>
void palabras(const Arbin<T> a, const typename Arbin<T>::Iterador r, string palabra){
    if (r.arbolVacio()){
        cout << "Vacio" << endl;
    }else{
        palabra+=r.observar();
        if (!a.subIzq(r).arbolVacio()){
            palabras(a,a.subIzq(r), palabra);
        }
        if (!a.subDer(r).arbolVacio()){
            palabras(a,a.subDer(r), palabra);
        }

        if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()){
            cout << palabra << endl;
        }
    }
}
/******************************************************************************/
//Ejercicio 6

template<typename T>
int siguienteMayor(const Arbin<T> a, int buscado) throw (NoHaySiguienteMayor){

    int mayor = siguienteMayor(a, a.getRaiz(), buscado, mayor);
    if ( mayor == 0){
        throw NoHaySiguienteMayor();
    }
    return mayor;
}
template<typename T>
int siguienteMayor(const Arbin<T> a, const typename Arbin<T>::Iterador r, int buscado, int mayor){
    if (r.arbolVacio()){
        return mayor;
    }else{
        if (r.observar() <= buscado){
            return siguienteMayor(a,a.subDer(r), buscado, mayor);
        }else{
            mayor = r.observar();
            return siguienteMayor(a,a.subIzq(r), buscado, mayor);
        }

    }
}

/******************************************************************************/
//Ejercicio 7


template<typename T>
int posicionInOrden(const Arbin<T> a, int elemento){
    return posicionInOrden(a, a.getRaiz(), elemento);
}

template<typename T>
int posicionInOrden(const Arbin<T> a, const typename Arbin<T>::Iterador r, int elemento){
    if (!r.arbolVacio()){
        if (r.observar() == elemento){
            int nodos = numNodos(a, a.subIzq(r)) + 1;
            return nodos;
        }else if (r.observar() < elemento){
            int nodos = numNodos(a,a.subIzq(r)) + 1;
            return posicionInOrden(a,a.subDer(r), elemento) + nodos;

        }else{
            return posicionInOrden(a, a.subIzq(r), elemento);
        }
    }else{
        return 0;
    }
}



/******************************************************************************/
//Ejercicio 8
template <typename T>
bool haySumaCamino(const Arbin<T> a, int elemento){
    int suma = 0;
    return haySumaCamino(a, a.getRaiz(), elemento, suma);
}

template <typename T>
bool haySumaCamino(const Arbin<T> a, const typename Arbin<T>::Iterador r, int elemento, int suma){
    if (!r.arbolVacio()){
        suma+=r.observar();


        if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()){
            if (suma == elemento){
                return true;
            }else{
                return false;
            }
        }else if(!a.subIzq(r).arbolVacio() && !a.subDer(r).arbolVacio()){
            return haySumaCamino(a,a.subIzq(r), elemento,suma) || haySumaCamino(a,a.subDer(r), elemento,suma);

        }else if(!a.subIzq(r).arbolVacio()){
            return haySumaCamino(a,a.subIzq(r), elemento, suma);

        }else{
            return haySumaCamino(a,a.subDer(r), elemento ,suma);
        }
    }else{
        return false;
    }
}


/****************************************************************************/

int main(int argc, char *argv[]){

    Arbin<char> A('t', Arbin<char>('m', Arbin<char>(),
                                        Arbin<char>('f', Arbin<char>(), Arbin<char>())),
                       Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>()));

    Arbin<char> B('t', Arbin<char>('n', Arbin<char>(),
                                        Arbin<char>('d', Arbin<char>('e', Arbin<char>(), Arbin<char>()),
                                                         Arbin<char>())),
                       Arbin<char>('m', Arbin<char>('f', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>('n', Arbin<char>(), Arbin<char>())));

    Arbin<char> D('t', Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>()),
                       Arbin<char>('m', Arbin<char>(),
                                        Arbin<char>('f', Arbin<char>(), Arbin<char>())));

    Arbin<char> E('o', Arbin<char>('r', Arbin<char>(),
                                        Arbin<char>('o', Arbin<char>(), Arbin<char>())),
                       Arbin<char>('l', Arbin<char>('a', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>('e', Arbin<char>(), Arbin<char>())));

    Arbin<int> F(2, Arbin<int>(7, Arbin<int>(2, Arbin<int>(), Arbin<int>()),
                                  Arbin<int>(6, Arbin<int>(5, Arbin<int>(), Arbin<int>()),
                                                Arbin<int>(11, Arbin<int>(), Arbin<int>()))),
                    Arbin<int>(5, Arbin<int>(),
                                  Arbin<int>(9, Arbin<int>(),
                                                  Arbin<int>(4, Arbin<int>(), Arbin<int>()))));

    ABB<int> BB6, BB7;



    //NUMERO HOJAS
    cout << "Num. hojas del arbol B: " << numHojas(B) << endl;
    cout << "Num. hojas del arbol E: " << numHojas(E) << endl << endl;


    // COPIA SIMETRICA //
    Arbin<char> C = simetrico(B);
    cout << "Recorrido en inorden del arbol B: " << endl;

    inorden(B, B.getRaiz());
    cout << endl << "Recorrido en inorden del arbol C: " << endl;
    inorden(C, C.getRaiz());
    cout << endl << endl;

    //cout << "Numero de nodos del arbol: " << numNodos(B) << endl;



    // RECORRIDO EN ZIG-ZAG //

    cout << "Recorrido en zigzag I de B:\n";
    recorridoZigzag(B, 'I');
    cout << endl;
    cout << "Recorrido en zigzag D de B: \n";
    recorridoZigzag(B, 'D');
    cout << endl;
    cout << "Recorrido en zigzag D de C:\n";
    recorridoZigzag(C, 'D');
    cout << endl << endl;



    // COMPENSADO //
    cout << "Esta A compensado?:";
    cout << (compensado(A) ? " SI" : " NO") << endl;
    cout << "Esta B compensado?:";
    cout << (compensado(B) ? " SI" : " NO") << endl << endl;


    // PALABRAS DE UN ARBOL //
    cout << "PALABRAS DE A:\n";
    palabras(E);
    cout << "PALABRAS DE B:\n";
    palabras(B);
    cout << endl;



    // SIGUIENTE MAYOR
    BB6.insertar(8); BB6.insertar(3); BB6.insertar(10); BB6.insertar(1); BB6.insertar(6);
    BB6.insertar(14); BB6.insertar(4); BB6.insertar(7); BB6.insertar(13);
    try
    {
        cout << "Siguiente mayor en BB6 de 5: " << siguienteMayor(BB6, 5) << endl;
        cout << "Siguiente mayor en BB6 de 8: " << siguienteMayor(BB6, 8) << endl;
        cout << "Siguiente mayor en BB6 de 13: " << siguienteMayor(BB6, 13) << endl;
        cout << "Siguiente mayor en BB6 de 14: " << siguienteMayor(BB6, 14) << endl;
    }
    catch(const NoHaySiguienteMayor& e)
    {
        cout << e.Mensaje() << endl << endl;
    }


    // POSICION INORDEN //

    BB7.insertar(5); BB7.insertar(1); BB7.insertar(3); BB7.insertar(8); BB7.insertar(6);

    inorden(BB7, BB7.getRaiz());

    cout << "Posicion Inorden en BB7 de 3: ";
    cout << posicionInOrden(BB7, 3);

    cout << endl << "Posicion Inorden en BB7 de 8: ";
    cout << posicionInOrden(BB7, 8);
    cout << endl << "Posicion Inorden en BB7 de 7: ";
    cout << posicionInOrden(BB7, 7);
    cout << endl << endl;

    // SUMA CAMINO
    cout << "Hay un camino de suma 26 en F?:";
    cout << (haySumaCamino(F, 26) ? " SI" : " NO") << endl;

    cout << "Hay un camino de suma 9 en F?:";
    cout << (haySumaCamino(F, 9) ? " SI" : " NO") << endl;


    bool resultado = haySumaCamino(F,9);

    system("PAUSE");
    return 0;

}



