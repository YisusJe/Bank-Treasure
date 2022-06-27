#include <iostream>
#include <fstream>

#include "Archivo.h"
#include "Pila.h"
#include "Cola.h"
#include "Nodo.h"
#include "Lista.h"
#include "User.h"

using namespace std;
void menu();

Cola *userCola = new Cola;
Lista *lista1 = new Lista;
Lista *lista2 = new Lista;
Lista *lista3 = new Lista;

int specialCode;

void generateCode(int id, int originalId){
	TArchivo<User>file("User.dat");
	User user;
	int i = 0;
	int a,b,c;
	bool ward = true, ward2=false;
	a = id % 10;
	b = (id / 10) % 10;
	c = (id / 100) % 10;
	int code = (c * 100) + (b * 10) + a;
	Pila *pila = new Pila;
	file.open("User.dat", ios::in | ios::binary);	
		if(file.fail() || file.bad()) ward = false;
		while(ward){
			file.read((char *)&user, sizeof(user));
			if(file.eof()) break;
//			cout<<"code: "<<code<<endl;
//			cout<<"user code: "<<user.getCode()<<endl;
			if(user.getCode() == code){
				// invertir
				if((id / 10) <= 99){
					int idAux = originalId, reversed_number = 0, remainder;
					while(idAux != 0){
						remainder = idAux % 10;
						reversed_number = reversed_number * 10 + remainder;
						idAux /= 10;
						pila->apilar(reversed_number);
					}
					Nodo *nodo = pila->top();
					file.close();
					generateCode(reversed_number, nodo->dato());
				} else {
					file.close();
					generateCode(id / 10, id);
				}
				ward2 = true;
			}
		}
	if(!ward2){
		specialCode = code;
	}
	file.close();
}

void AddUser(){
	int id;
	float amount;
	int transaction = 0;
	int code;
	TArchivo<User>file("User.dat");
	cout<<"Ingrese la cedula"<<endl;
	fflush(stdin);
	cin>>id;
	cout<<"Ingrese el monto"<<endl;
	fflush(stdin);
	cin>>amount;
	cout<<"Tipo de Transaccion"<<endl;
	fflush(stdin);
	cout<<"Presione 1 para hacer un Deposito o 2 para hacer un Retiro"<<endl;
	while(true){
		if(kbhit()){
			char key = getch();
			switch(int(key)){
				case 49:
					transaction = 1;
					break;
				case 50:
					transaction = 2;
					break;
			}
		}
		if(transaction == 1 || transaction == 2) break;
	}
	fflush(stdin);
	generateCode(id, id);
	User user(id,amount, transaction, specialCode);
	file.insertar(user);
	userCola->encolar(specialCode);
	cout<<"Usuario creado "<<endl;
//	cout<<"----Cola actual----"<<endl;
//	userCola->imprimir();
	system("pause");
	system("cls");
	menu();
}

void CustomerAttend(int position){ // 1, 2 o 3
	Nodo *nodo = userCola->front();
	switch(position){
		case 1:
			lista1->agregar(nodo->dato());
			cout<<"usuario a taquilla 1: "<<nodo->dato()<<endl;
			break;
		case 2:
			lista2->agregar(nodo->dato());
			cout<<"usuario a taquilla 2: "<<nodo->dato()<<endl;
			break;
		case 3:
			lista3->agregar(nodo->dato());
			cout<<"usuario a taquilla 3: "<<nodo->dato()<<endl;
			break;
	}
	userCola->desencolar();
//	cout<<"----Cola actual----"<<endl;
//	userCola->imprimir();
	system("pause");
	system("cls");
	menu();
}

void showUsers(bool press){
	int * array1, *array2, *array3;
	cout<<"--------USUARIOS EN COLA---------"<<endl;
	userCola->imprimir();
	cout<<endl<<"-------USUARIOS EN TAQUILLA 1-------"<<endl;
	lista1->imprimir(false, false);
	cout<<endl<<"-------USUARIOS EN TAQUILLA 2-------"<<endl;
	lista2->imprimir(false, false);
	cout<<endl<<"-------USUARIOS EN TAQUILLA 3-------"<<endl;
	lista3->imprimir(false, false);
	if(!press){
		system("pause");
		system("cls");
		menu();	
	}
	
}

void EndProgram(){
	int * array1, *array2, *array3;
	int length1 = 0, length2 = 0, length3 = 0;
	Lista *full = new Lista;
	int length = 0;
	bool ward = true;
	User useraux;
	cout<<"Clientes en cola despachados"<<endl;
	delete userCola;
	cout<<endl<<"-------USUARIOS EN TAQUILLA 1-------"<<endl;
	lista1->ordenar(); 
	array1 = lista1->imprimir(true, true);
	cout<<endl<<"-------USUARIOS EN TAQUILLA 2-------"<<endl;
	lista2->ordenar();
	array2 = lista2->imprimir(true, true);
	cout<<endl<<"-------USUARIOS EN TAQUILLA 3-------"<<endl;
	lista3->ordenar();
	array3 = lista3->imprimir(true, true);
//	length = lista1->tamano() + lista2->tamano() + lista3->tamano();
//	cout<<"LENGTH: "<<lista1->tamano()<<lista2->tamano()<<lista3->tamano();
//	for(int i = 0; i < lista1->tamano(); i++){
//		full->agregar(array1[i]);
//	}
//	for(int i = 0; i < lista2->tamano(); i++){
//		full->agregar(array2[i]);
//	}
//	for(int i = 0; i < lista3->tamano(); i++){
//		full->agregar(array3[i]);
//	}
//	full->ordenar();
//	full->imprimir(true, false);
}

void menu() {	
	showUsers(true);
	cout<<"A- Ingreso de usuario"<<endl;
	cout<<"1- Enviar usuario a taquilla 1"<<endl;
	cout<<"2- Enviar usuario a taquilla 2"<<endl;
	cout<<"3- Enviar usuario a taquilla 3"<<endl;
	cout<<"C- Mostrar cola virtual y clientes en cada taquilla"<<endl;
	cout<<"F- Finalizar entrada"<<endl;
	while(true){
		if(kbhit()){
			char key = getch();
			switch(int(key)){
				case 97:
					AddUser();
					break;
				case 49:
					CustomerAttend(1);
					break;
				case 50:
					CustomerAttend(2);
					break;
				case 51:
					CustomerAttend(3);
					break;
				case 99:
					showUsers(false);
					break;
				case 102:
					EndProgram();
			}
		}
	}
}

int main()
{
	TArchivo<User>file("User.dat");
	bool ward = true;
	User useraux;
	file.open("User.dat", ios::in | ios::binary);	
	if(file.fail() || file.bad()) ward = false;
		while(ward){
			file.read((char *)&useraux, sizeof(useraux));
			if(file.eof()) break;
			userCola->encolar(useraux.getCode());
		}
	if(ward) {
		file.close();
	}
	menu();
   
    return 0;
}
