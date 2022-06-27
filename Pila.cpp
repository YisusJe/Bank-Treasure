#include "Pila.h"
#include "Nodo.h"

#include <iostream>

using namespace std;

Pila::Pila()
{
    m_top = NULL;
    m_bottom = NULL;
}

Pila::~Pila()
{
    Nodo *x = NULL;
    Nodo *y = NULL;
    x = m_bottom;
    while (x->siguiente() != NULL)
    {
        y = x->siguiente();
        delete x;
        x = y;
    }
    delete x;
}

void Pila::apilar(int dato)
{
    if (m_bottom == NULL && m_top == NULL)
    {
        m_bottom = new Nodo;
        m_bottom->setDato(dato);
        m_top = m_bottom;
    }
    else
    {
        Nodo *siguiente = new Nodo;
        siguiente->setDato(dato);
        m_top->setSiguiente(siguiente);
        siguiente->setAnterior(m_top);
        m_top = siguiente;
    }
}

void Pila::desapilar()
{
    if (!(m_bottom == NULL && m_top == NULL))
    {
        Nodo *anterior = m_top->anterior();
        anterior->setSiguiente(NULL);
        delete m_top;
        m_top = anterior;
    }
}

void Pila::imprimir() const
{
    Nodo *x = m_top;
    while (x != NULL)
    {
        cout << x->dato() << endl;
        x = x->anterior();
    }
}

Nodo *Pila::top() const
{
    return m_top;
}

Nodo *Pila::bottom() const
{
    return m_bottom;
}
