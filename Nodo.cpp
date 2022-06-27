#include "Nodo.h"

#include <iostream>

using namespace std;

Nodo::Nodo()
{
    m_dato = 0;
    m_siguiente = NULL;
    m_anterior = NULL;
}

Nodo::~Nodo()
{
    cout << "eliminado: " << m_dato << endl;
}

void Nodo::setDato(int dato)
{
    m_dato = dato;
}

void Nodo::setSiguiente(Nodo *siguiente)
{
    m_siguiente = siguiente;
}

void Nodo::setAnterior(Nodo *anterior)
{
    m_anterior = anterior;
}

int Nodo::dato() const
{
    return m_dato;
}

Nodo *Nodo::siguiente() const
{
    return m_siguiente;
}

Nodo *Nodo::anterior() const
{
    return m_anterior;
}
