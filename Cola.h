#ifndef COLA_H
#define COLA_H

class Nodo;

class Cola {
public:
    explicit Cola();
    virtual ~Cola();
    void encolar(int dato);
    void desencolar();
    void imprimir() const;
    Nodo *front() const;
    Nodo *back() const;
private:
    Nodo *m_front;
    Nodo *m_back;
};

#endif // COLA_H
