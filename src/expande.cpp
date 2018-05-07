#include <string.h>
#include <iostream>
#include <map>
#include <utility>

using namespace std;


typedef struct no{
	string estado;
	no *pai;
	string acao;
	string pais;
	int custo;
}nodo;

typedef struct par{
	string acao;
	string estado;
	int valido;
}par;



// 0 -> esquerda // 1 -> diretia // 2 -> cima // 3 -> baixo
map<int, par> sucessor(string nome){
	int pos , dir;
	par aux;
	map<int, par> pares;
	for(int i = 0 ; i < nome.size() ; i++){
		if(nome[i] == '_') pos = i;
	}

	//pares = cria();	
	
	aux.valido = 0;
	for(int i = 0 ; i < 4 ; i ++){
		pares[i] = aux;
	}
	
	if(pos < 6){
		pares[3].acao = "abaixo";
		pares[3].valido =1;
		pares[3].estado = nome;
		pares[3].estado[pos] = nome[pos+3];
		pares[3].estado[pos+3] = '_';
		/*/cout << pares[3].estado;
		cin >> dir;*/
	}
	/*cout << nome << " " << pos;
	return pares;*/
	if(pos>2){
		pares[2].acao = "acima";
		pares[2].valido =1;
		pares[2].estado = nome;
		pares[2].estado[pos] = nome[pos-3];
		pares[2].estado[pos-3] = '_';
	}
	if(pos!=2 and pos!= 5 and pos!= 8){
		pares[1].acao = "direita";
		pares[1].valido =1;
		pares[1].estado = nome;
		pares[1].estado[pos] = nome[pos+1];
		pares[1].estado[pos+1] = '_';
	}
	if(pos!= 0 and pos != 3 and pos!= 6){
		pares[0].acao = "esquerda";
		pares[0].valido =1;
		pares[0].estado = nome;
		pares[0].estado[pos] = nome[pos-1];
		pares[0].estado[pos-1] = '_';
	}
	return pares;
}

nodo crianodo(string estado , nodo pai , string acao , int custo){
	nodo aux;
	aux.pais = pai.estado;
	aux.estado  = estado;
	aux.pai = &pai;
	aux.acao = acao;
	aux.custo = custo;
	return aux;
}

map<int , nodo> expande(nodo a){
	map<int, par> pares = sucessor(a.estado);
	map<int, nodo> nodos;
	nodo aux;
	for(int i = 0 ; i < 4 ; i ++){
		if(pares[i].valido==1){
			aux = crianodo(pares[i].estado , a , pares[i].acao , a.custo+1);
			nodos[i] =  aux;
		}
	}
	return nodos;
}



int main(int argc, char *argv[]){

	nodo a;
	map<int , nodo> nodos;
	
	a.estado=argv[1];
	a.pai=NULL;
	a.acao="";
	a.custo=0;
	nodos = expande(a);
	
	
	for(map<int,nodo>::iterator ii=nodos.begin(); ii!=nodos.end(); ++ii)
	{
       cout << "(" << (*ii).second.acao << ","<< (*ii).second.estado << "," << (*ii).second.custo << "," << (*ii).second.pais << ") ";
    }
    return 0;
}
