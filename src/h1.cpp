#include <string.h>
#include <iostream>
#include <map>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <set>
#include <math.h>

using namespace std;


typedef struct no
{
    string estado;
    no *pai;
    string acao;
    string pais;
    int custo;
    int custonormal;
} nodo;

typedef struct par
{
    string acao;
    string estado;
    int valido;
} par;

typedef struct fronteira
{
    int tam;
    multiset<nodo> heap;
} fronteira;

int calculacusto(nodo a)
{
    int custo=0;
    int x , y;
    for(int i = 0 ; i < 9 ; i++)
    {
        if(i==0)
        {
            x = 0 ;
            y = 0;
        }
        else if(i==1)
        {
            x = 1 ;
            y = 0;
        }
        else if(i==2)
        {
            x = 2 ;
            y = 0;
        }
        else if(i==3)
        {
            x = 0 ;
            y = 1;
        }
        else if(i==4)
        {
            x = 1 ;
            y = 1;
        }
        else if(i==5)
        {
            x = 2 ;
            y = 1;
        }
        else if(i==6)
        {
            x = 0 ;
            y = 2;
        }
        else if(i==7)
        {
            x = 1 ;
            y = 2;
        }
        else if(i==8)
        {
            x = 2 ;
            y = 2;
        }

        if(a.estado[i]=='1')
        {
            custo += fabs(x-0) + fabs(y-0);
        }
        else if(a.estado[i]=='2')
        {
            custo += fabs(x-1) + fabs(y-0) ;
        }
        else if(a.estado[i]=='3')
        {
            custo += fabs(x-2) + fabs(y-0);
        }
        else if(a.estado[i]=='4')
        {
            custo += fabs(x-0) + fabs(y-1);
        }
        else if(a.estado[i]=='5')
        {
            custo += fabs(x-1) + fabs(y-1);
        }
        else if(a.estado[i]=='6')
        {
            custo += fabs(x-2) + fabs(y-1);
        }
        else if(a.estado[i]=='7')
        {
            custo += fabs(x-0) + fabs(y-2);
        }
        else if(a.estado[i]=='8')
        {
            custo += fabs(x-1) + fabs(y-2);
        }
    }
    return custo;
}

// 0 -> esquerda // 1 -> diretia // 2 -> cima // 3 -> baixo
map<int, par> sucessor(string nome)
{
    int pos ;
    par aux;
    map<int, par> pares;
    for(int i = 0 ; i < (int) nome.size() ; i++)
    {
        if(nome[i] == '_') pos = i;
    }

    aux.valido = 0;
    for(int i = 0 ; i < 4 ; i ++)
    {
        pares[i] = aux;
    }

    if(pos < 6)
    {
        pares[3].acao = "abaixo";
        pares[3].valido =1;
        pares[3].estado = nome;
        pares[3].estado[pos] = nome[pos+3];
        pares[3].estado[pos+3] = '_';

    }
    if(pos>2)
    {
        pares[2].acao = "acima";
        pares[2].valido =1;
        pares[2].estado = nome;
        pares[2].estado[pos] = nome[pos-3];
        pares[2].estado[pos-3] = '_';
    }
    if(pos!=2 and pos!= 5 and pos!= 8)
    {
        pares[1].acao = "direita";
        pares[1].valido =1;
        pares[1].estado = nome;
        pares[1].estado[pos] = nome[pos+1];
        pares[1].estado[pos+1] = '_';
    }
    if(pos!= 0 and pos != 3 and pos!= 6)
    {
        pares[0].acao = "esquerda";
        pares[0].valido =1;
        pares[0].estado = nome;
        pares[0].estado[pos] = nome[pos-1];
        pares[0].estado[pos-1] = '_';
    }
    return pares;
}

nodo crianodo(string estado , nodo pai , string acao , int custo)
{
    nodo aux;
    aux.pais = pai.estado;
    aux.estado  = estado;
    aux.pai = &pai;
    aux.acao = acao;
    aux.custo = calculacusto(aux);
    aux.custonormal = custo+1;
    return aux;
}

map<int , nodo> expande(nodo a)
{
    map<int, par> pares = sucessor(a.estado);
    map<int, nodo> nodos;
    nodo aux;
    for(int i = 0 ; i < 4 ; i ++)
    {
        if(pares[i].valido==1)
        {
            aux = crianodo(pares[i].estado , a , pares[i].acao , a.custonormal);
            nodos[i] =  aux;
        }
    }
    return nodos;
}

bool operator <(nodo a , nodo b)
{
    return (a.custo+a.custonormal) < (b.custo+b.custonormal);
}
bool operator >(nodo a , nodo b)
{
    return (a.custo+a.custonormal) > (b.custo+b.custonormal);
}
bool operator ==(nodo a , nodo b)
{
    return ((a.custo+a.custonormal) == (b.custo+b.custonormal));
}
bool operator !=(nodo a , nodo b)
{
    return ((a.custo+a.custonormal)!=(b.custo+b.custonormal));
}
void adiciona(fronteira *p , nodo a)
{
    p->heap.insert(a);
}
void imprimeresultado(nodo *a , nodo inicial, vector<nodo> myvector)
{
    stack<string> direcoes;
	if(a->estado==inicial.estado) return;
    int num=1;
    direcoes.push(a->acao);
    string p = a->pais;
    while(p!=inicial.estado)
    {
        for (vector<nodo>::iterator itt = myvector.begin() ; itt != myvector.end(); ++itt)
        {
            if(itt->estado == p)
            {
                direcoes.push(itt->acao);
                p = itt->pais ;
                break;
            }
        }
    }
    while (!direcoes.empty())
    {
     cout << direcoes.top() <<" ";
     direcoes.pop();
     num++;
    }
}

void buscaresultado(fronteira a , nodo inicial)
{
    std::set<nodo>::iterator it;
    int cont= 0;
    int flag;
    map<int , nodo> nodos;
    map<int , string> fechado;
    vector<nodo> myvector;
    nodo aux;
    int tamfechado =0;
    a.heap.insert(inicial);
    a.tam=0;
    a.tam++;
    while(a.tam!=0)
    {
        cont++;
        flag = 0;
        it = a.heap.begin();
        a.tam--;
        aux = *it;
        a.heap.erase(it);
        if(aux.estado=="12345678_")
        {
            imprimeresultado(&aux,inicial , myvector);
            return;
        }

        for (vector<nodo>::iterator itt = myvector.begin() ; itt != myvector.end(); ++itt)
        {

            if(itt->estado == aux.estado)
            {
                flag = 1 ;
                break;
            }
        }

        if(!flag)
        {
            tamfechado++;
            myvector.push_back(aux);
            nodos = expande(aux);

            for(map<int,nodo>::iterator ii=nodos.begin(); ii!=nodos.end(); ++ii)
            {
                aux = (*ii).second;
                a.heap.insert((*ii).second);
                a.tam++;
            }
            nodos.clear();
        }
    }
}



int main(int argc, char *argv[])
{

    nodo a;
    map<int , nodo> nodos;
    fronteira b;
    a.estado=argv[1];
    a.pai=NULL;
    a.acao="";
    a.custo=calculacusto(a);
    a.custonormal=0;
    buscaresultado(b,a);

    return 0;
}
