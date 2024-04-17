
#include <iostream>
#include <bits/stdc++.h>
#include<fstream>
using namespace std;
ifstream r("abce.in");
ofstream w("abce.out");

class Treap{

    struct nodtreap{
        int key,prioritate;
        nodtreap *st,*dr;

    };
    nodtreap *radacina;
    nodtreap  *Rotiridreapta (nodtreap* n){
        nodtreap* s = n->st;
        nodtreap* d = s->dr;
        s->dr=n;
        n->st=d;
        return s;
    }


    nodtreap  *Rotiristanga(nodtreap*n ){
        nodtreap* m = n->dr;
        nodtreap* p = m->st;
        m->st=n;
        n->dr=p;
        return m;
    }

    nodtreap *cautare(nodtreap*n, int x)
    {
        if (n == NULL or n->key == x)
            return n;
        if (n->key < x)
            return cautare(n->dr, x);


        return cautare(n->st, x);
    }
    nodtreap* newnode(int x){
        nodtreap* n = new nodtreap;
        n->key = x;
        n->prioritate = rand();
        n->st = n->dr = NULL;
        return n;

    }

    nodtreap  *inserare(nodtreap *n , int x)
    {
        if (!n)
            return newnode(x);

        if (x <= n->key)
        {
            n->st = inserare(n->st, x);
            if (n->st->prioritate > n->prioritate)
                n = Rotiridreapta(n);
        }
        else
        {
            n->dr = inserare(n->dr, x);
            if (n->dr->prioritate > n->prioritate)
                n = Rotiristanga(n);
        }
        return n;

    }

    nodtreap *stergere(nodtreap *n,int x){
        if (n == NULL)
            return n;

        if (x < n->key)
            n->st = stergere(n->st, x);
        else if (x > n->key)
            n->dr = stergere(n->dr, x);
        else if (n->st == NULL)
        {   nodtreap *y = n->dr;
            delete(n);
            n = y;
        }
        else if (n->dr == NULL)
        {
            nodtreap *y = n->st;
            delete(n);
            n= y;
        }
        else if (n->st->prioritate < n->dr->prioritate)
        {
            n = Rotiristanga(n);
            n->st = stergere(n->st, x);
        }
        else
        {
            n = Rotiridreapta(n);
            n->dr = stergere(n->dr, x);
        }

        return n;
    }

    int maxY(int x, nodtreap*n )
    {   int max=-1000000000;
        while(n){
            if(x<n->key)//un fel de parcurgere inorder
                n=n->st;
            else
            if(x>n->key)
            {if(n->key>max)
                    max=n->key;
                n=n->dr;
            }
            else
                return x;
        }
        return max;
    }
    int minY(int x, nodtreap*n )
    {   int min=1000000000;
        while(n){
            if(x>n->key)
                n=n->dr;
            else
            if(x<n->key)
            {if(n->key<min)
                    min=n->key;
                n=n->st;
            }
            else
                return x;
        }
        return min;
    }

    void cerinta6i(nodtreap *n, int x, int y) {
        if (n) {
            cerinta6i(n->st, x, y);
            if (n->key >= x and n->key <= y)
                w << n->key << " ";
            cerinta6i(n->dr, x, y);
        }}

public:
    Treap() {
        radacina=NULL;
    }
    void cerinta3(int x){
        if(cautare(radacina,x))
            w<<"1"<<endl;
        else
            w<<"0"<<endl;

    }
    void cerinta1(int x){
        radacina=inserare(radacina,x);
    }
    void cerinta2(int x){
        radacina=stergere(radacina,x);
    }
    void cerinta4(int x)
    { int y;
        y=maxY( x, radacina);
        if(y>-1000000000)
            w<<y<<endl;
        else
            w<<endl;
    }

    void cerinta5(int x)
    { int y;
        y=minY( x, radacina);
        if(y<1000000000)
            w<<y<<endl;
        else
            w<<endl;
    }

    void cerinta6( int x, int y) {
        cerinta6i(radacina,x,y);
    }

};
int main() {
    srand(time(NULL));
    int cerinta,n,x,y,i;
    r>>n;
    Treap treap;
    for(i=0;i<n;i++)
    {
        r>>cerinta;
        if(cerinta==1){
            r>>x;
            treap.cerinta1(x);
        } else if (cerinta==2){
            r>>x;
            treap.cerinta2(x);
        }else if(cerinta==3){
            r>>x;
            treap.cerinta3(x);
        } else if(cerinta==4){
            r>>x;
            treap.cerinta4(x);
        }else if(cerinta==5){
            r>>x;
            treap.cerinta5(x);
        }else{
            r>>x>>y;
            treap.cerinta6(x,y);
            w<<endl;
        }

    }
    return 0;
}