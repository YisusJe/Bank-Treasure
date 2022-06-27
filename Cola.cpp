#include <iostream>
#include <stdlib.h>
#include "Cola.h"
#include "Nodo.h"


using namespace std;

Cola::Cola()
{
    m_front = NULL;
    m_back = NULL;
}

Cola::~Cola()
{
    Nodo *x = NULL;
    Nodo *y = NULL;
    x = m_back;
    while (x->siguiente() != NULL)
    {
        y = x->siguiente();
        delete x;
        x = y;
    }
    delete x;
}

void Cola::encolar(int dato)
{
    if (m_back == NULL && m_front == NULL)
    {
        m_back = new Nodo;
        m_back->setDato(dato);
        m_front = m_back;
    }
    else
    {
        Nodo *anterior = new Nodo;
        anterior->setDato(dato);
        m_back->setAnterior(anterior);
        anterior->setSiguiente(m_back);
        m_back = anterior;
    }
}

void Cola::desencolar()
{
	if (m_back == m_front) {
		Nodo *anterior = NULL;
        delete m_front;
        m_front = NULL;
	} else if (!(m_back == NULL && m_front == NULL)) {
        Nodo *anterior = m_front->anterior();
        anterior->setSiguiente(NULL);
        delete m_front;
        m_front = anterior;
    }
}

void Cola::imprimir() const
{
    Nodo *x = m_front;
    while (x != NULL)
    {
        cout << x->dato() << endl;
        x = x->anterior();
    }
}

Nodo *Cola::front() const
{
    return m_front;
}

Nodo *Cola::back() const
{
    return m_back;
}
