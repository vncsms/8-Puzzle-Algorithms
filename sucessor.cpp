#include <string.h>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

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

int main(int argc, char *argv[]){
	map<int, par> pares= sucessor(argv[1]);
	for(int i = 0 ; i < 4 ; i ++){
		if(pares[i].valido==1){
			cout << "("<<pares[i].acao<<","<<pares[i].estado << ") ";
		}
	}
	
}
