#include <iostream>

using namespace std;

class User {
	private: 
		int id;
		float amount;
		int transaction, code;
	public:
		User (){
			this->id=0;
			this->amount=0;
			this->transaction=0;
			this->code=0;
		}
		User (int id, float amount, int transaction, int code){
			this->id=id;
			this->amount=amount;
			this->transaction=transaction;
			this->code=code;
		}
		int getCode(){
			return code;
		}
		int getTransaction(){
			return transaction;
		}
		void Print (){
			cout<<"Cedula: "<<id<<" cantidad: "<<amount;
			if(transaction == 1){
				cout<<" Transaccion: Deposito"<<" Codigo: "<<code<<endl;
			} else {
				cout<<" Transaccion: Retiro"<<" Codigo: "<<code<<endl;
			}
		}
};
