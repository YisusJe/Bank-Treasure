#include "Lista.h"
#include "User.h"
#include "Archivo.h"
Lista::Lista()
{
	inicio = NULL;
	fin = NULL;
}

void Lista::agregar(int valor)
{
	Nodo* nuevo = new Nodo();
	nuevo->setDato(valor);
	//Agregar el primer elemento
	if (inicio == NULL) {
		inicio = nuevo;
		fin = inicio;
	}
	else {
		//Cuando ya elementos dentro de la lista
		fin->setSiguiente(nuevo);
		fin = nuevo;
	}
}

//void Lista::mostrar()
//{
//	//veficar si la lista esta vacia 
//	if (inicio == NULL) {
//		cout << "Lita vacia" << endl;
//	}
//	else {
//		//Cuando la lista tiene elemenetos
//		Nodo* reco = inicio;
//		int i = 0;
//		while (reco != NULL) {
//			i++;
//			cout << i <<" - " <<reco->dato() << endl;
//			reco = reco->siguiente();
//		}
//	}
//}

void Lista::borrar(int pos)
{	
	//Variables 
	Nodo* reco;
	Nodo* ante = inicio;
	//veficar si la lista esta vacia 
	if (inicio == NULL) {
		cout << "Lita vacia" << endl;
	}
	else if (pos == 0) {
		cout << "No existe no existe el elemento 0 inicia en 1" << endl;
	}
	else if (pos > tamano()) {
		cout << "la posicion " << pos << " excede el tanano de lista que es " << tamano() << endl;
	}
	else if (pos == 1) {
		// Eliminar el primer elemento
		Nodo* borrar;
		borrar = inicio;
		inicio = inicio->siguiente();
		delete borrar;
	}
	else if (pos == tamano()) {
		Nodo* borrarUltimo;
		// Eliminar el último elemento
		reco = inicio;
		cout << "Valor del primer a elemento " << reco->dato() << endl;
		int i = 0;
		while (reco != NULL) {
			i++;
			if (i == pos - 1) {
				fin = reco;
				fin->setSiguiente(NULL);
			}
			else if (i==pos){
				borrarUltimo = reco;
				delete borrarUltimo;
			}
			reco = reco->siguiente();	
		}
	}
	else {
		reco = inicio->siguiente();
		Nodo* borrarMedio;
		int i = 1;
		while (reco != NULL)
		{
			i++;
			//cout << i<< "-" <<reco->info << endl;
			if (i == pos) {
				cout << "Posicion " << i << " con valor de " << reco->dato() << endl;
				borrarMedio = reco;
				ante->setSiguiente(reco->siguiente());
				delete borrarMedio;
				break;
			}
			else {
				ante = ante->siguiente();
				reco = reco->siguiente();
			}

		}
	}
}

int Lista::tamano()
{
	if (inicio == NULL) {
		return 0;
	}
	else {
		Nodo* reco = inicio;
		int i = 0;
		while (reco != NULL)
		{
			i++;
			reco = reco->siguiente();
		}
		return i;
	}
}

void Lista::ordenar()
{
	Nodo* p = inicio;
	while(p != NULL){
		Nodo *j = p->siguiente();
		while(j != NULL){
			if(p->dato() > j->dato()){
				int aux = j->dato();
				j->setDato(p->dato());
				p->setDato(aux);
			}
			j = j->siguiente();
		}
		p = p->siguiente();
	}
} 

int * Lista::imprimir(bool isFullList, bool typeReturn) const
{
	static int array[100];
	User usersArray[100];
	int i = 0, k = 0;
    Nodo *x = inicio;
    User useraux;
    int depositos = 0, retiros = 0;
    if(isFullList){
    	bool ward = true;
    	TArchivo<User>file("User.dat");
		file.open("User.dat", ios::in | ios::binary);
		if(file.fail() || file.bad()) ward = false;
		while(ward){
			file.read((char *)&useraux, sizeof(useraux));
			if(file.eof()) break;
			usersArray[k] = useraux;
			k++;
			if(useraux.getTransaction() == 1){
				depositos++;
			} else {
				retiros++;
			}
		}
	}
	
    while (x != NULL)
    {
    	if(isFullList){
	    	for(int j = 0; j < 100; j++){
	    		if(x->dato() == usersArray[j].getCode()){
	    			usersArray[j].Print();
	    			break;
				}
			}
		}
		if(!typeReturn && !isFullList){
	        cout << x->dato() << endl;
		}
        array[i] = x->dato();
        x = x->siguiente();
        i++;
    }
    if(isFullList){
    	cout<<endl<<"Depositos: "<<depositos<<endl;
    	cout<<endl<<"Retiros: "<<retiros<<endl;
	}
    return array;
}
