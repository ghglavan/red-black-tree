#include <iostream>

using namespace std;

class arboreBinar;

class nod{
 friend class arboreBinar;
private:
    int info;
    nod*left;
    nod*right;
public:
    nod* getRight();
    nod* getLeft();
    nod() : info(0),left(NULL),right(NULL){}
    nod(int n) : info(n),left(NULL),right(NULL){}
    int iaInfo();
    void schimbaInfo(int);
};

class arboreBinar{
    nod*root;
    int inaltime;
public:
    arboreBinar() : root(NULL),inaltime(0){}
    nod* iaRadacina();
    arboreBinar operator+ (int);
    friend istream& operator>> (istream&,arboreBinar&);
    friend ostream& operator<< (ostream&,nod*);
    void stergereNod(int);
    void inaltimeM(nod*,int);
    void listaFrunzelor(nod*);
    int iaInaltime();
};

int arboreBinar::iaInaltime(){
    return inaltime;
}

void arboreBinar::stergereNod(int n){
    nod*p=root;
        if(p==NULL){
            cout<<"Arborele e gol"<<endl;
        }else{
            nod*a;
            while(p){
                if(p->iaInfo()>n){
                    a=p;
                    p=p->left;
                }else if(p->info<n){
                    a=p;
                    p=p->right;
                }else
                    break;
            }
            if(!p){
                cout<<"Elementul nu exista"<<endl;
            }else{
                nod*q=p;
                nod*d=p;
                if(p->right){
                    q=p->right;
                    if(q->left==NULL){
                        d->right=q->right;
                        d->info=q->info;
                        delete q;
                    }else{
                    while(q->left){
                        d=q;
                        q=q->left;
                    }
                    d->left=q->right;
                    p->info=q->info;
                    delete q;
                    }
                }else if(p->left){
                    q=p->left;
                    if(q->right==NULL){
                        d->left=q->left;
                        d->info=q->info;
                        delete q;
                    }else{
                    while(q->right){
                        d=q;
                        q=q->right;
                    }
                    d->right=q->left;
                    p->info=q->info;
                    delete q;
                    }
                }else{
                    if(a->left->info==n){
                        a->left=NULL;
                        delete p;
                    }else{
                        a->right=NULL;
                        delete p;
                    }
                }
            }
        }
}

void arboreBinar::listaFrunzelor(nod* r){
    if(r->getLeft()){
        listaFrunzelor(r->getLeft());
    }
    if(r && !r->getLeft() && !r->getRight()){
        cout<<r->iaInfo()<<" ";
    }
    if(r->getRight()){
        listaFrunzelor(r->getRight());
    }
}

void arboreBinar::inaltimeM(nod* r,int b){
    if(r->getLeft()){
        b++;
        if(b>inaltime)
            inaltime=b;
        inaltimeM(r->getLeft(),b);
        b--;
    }
    if(r->getRight()){
        b++;
        if(b>inaltime)
            inaltime=b;
        inaltimeM(r->getRight(),b);
        b--;
    }
}

nod* arboreBinar::iaRadacina(){
    return root;
}

arboreBinar arboreBinar::operator+(int n){
    nod*t=new nod(n);
    if(root==NULL){
        root=t;
    }else{
        nod*p=root;
        nod*padre;
        while(p){
            if(p->info<n){
                padre=p;
                p=p->right;
            }else{
                padre=p;
                p=p->left;
            }
        }
        if(padre->info<n){
            padre->right=t;
        }else{
            padre->left=t;
        }
    }
    return *this;
}

istream& operator>>(istream& in,arboreBinar& a){
    int n,v;
    cout<<"\nScrieti numarul de noduri de inserat:";
    cin>>v;
    for(int i=1;i<=v;i++){
    cout<<"\nScrieti elementul "<<i<<":";
    cin>>n;
    a+n;
    }
    return in;
}

nod* nod::getLeft(){
    return left;
}

nod* nod::getRight(){
    return right;
}

int nod::iaInfo(){
    return info;
}
void nod::schimbaInfo(int n){
    info=n;
}


ostream& operator<<(ostream& out,nod* a){
    if(a->getLeft()){
        operator<<(out,a->getLeft());
    }
    if(a){
        out<<a->iaInfo()<<" ";
    }
    if(a->getRight()){
        operator<<(out,a->getRight());
    }
    return out;
}
int main()
{
    int n;
    arboreBinar a;
    //a+3;
    //nod*p;
    //p=a.iaRadacina();
    //cout<<p->iaInfo();
    cin>>a;
    //a.stergereNod(3);

    cout<<a.iaRadacina();
    cout<<"Elementul de sters:";
    cin>>n;
    a.stergereNod(n);
    cout<<a.iaRadacina();
    cout<<"Inaltimea:";
    a.inaltimeM(a.iaRadacina(),1);
    cout<<a.iaInaltime();
    cout<<endl<<"Lista frunzelor:";
    a.listaFrunzelor(a.iaRadacina());
    return 0;
}