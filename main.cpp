#include <iostream>

using namespace std;

#include <iostream>


const int BLACK=0;
const int RED=1;



using namespace std;



template <class T>
class arboreBinar;

template <class T>
class redBlack;


//-------------------------------------------------------------clasa nod------------------------------------------------------
template<class T>
class nod{
    friend class arboreBinar<T>;
    friend class redBlack<T>;
private:
    T info;
    int culoare;
    nod*left;
    nod*right;
    nod*padre;
public:
    nod* getRight();
    nod* getLeft();
    void setLeft(nod<T>*);
    void setRight(nod<T>*);
    void setPadre(nod<T>*);
    nod* getPadre();
    nod() : culoare(-1),left(NULL),right(NULL){}
    nod(T n) : info(n),left(NULL),right(NULL){}
    nod (T n,int m) : info(n),culoare(m),left(NULL),right(NULL){}
    T iaInfo();
    void schimbaInfo(int);
    void setCuloare(int);
    int getCuloare();
};
//-------------------------------------------------------------clasa nod------------------------------------------------------


template <class T>
void nod<T>::setRight(nod<T>*n){
    right=n;
}

template <class T>
void nod<T>::setLeft(nod<T>*n){
    left=n;
}

template <class T>
void nod<T>::setCuloare(int n){
    culoare=n;
}

template <class T>
int nod<T>::getCuloare(){
    return culoare;
}

template<class T>
void nod<T>::setPadre(nod<T>*a){
    padre=a;
}


template<class T>
nod<T>* nod<T>::getPadre(){
    return padre;
};

template <class T>
nod<T>* nod<T>::getLeft(){
    return left;
}

template <class T>
nod<T>* nod<T>::getRight(){
    return right;
}

template <class T>
T nod<T>::iaInfo(){
    return info;
}

template <class T>
void nod<T>::schimbaInfo(int n){
    info=n;
}


//-------------------------------------------------------------clasa ABC------------------------------------------------------

template <class T>
class arboreBinar{
    nod<T> *root;
    int inaltime;
public:
    arboreBinar() : root(NULL),inaltime(0){}
    arboreBinar(nod<T>* a,int n) : root(a),inaltime(n){}
    nod<T>* iaRadacina();
    void setRoot(nod<T>*);
    virtual arboreBinar operator+ (T);
    template <class Ta>
    friend istream& operator>> (istream&,arboreBinar&);
    template <class Ta>
    friend ostream& operator<< (ostream&,nod<T>*);
    virtual void stergereNod(T);
    virtual void inaltimeM(nod<T>*,int);
    void listaFrunzelor(nod<T>*);
    int iaInaltime();
    void setInaltime(int);
};


//-------------------------------------------------------------clasa ABC------------------------------------------------------

template <class T>
void arboreBinar<T>::setInaltime(int c){
    inaltime=c;
}

template <class T>
void arboreBinar<T>::setRoot(nod<T>* n){
    root=n;
}

template <class T>
int arboreBinar<T>::iaInaltime(){
    return inaltime;
}

template <class T>
void arboreBinar<T>::stergereNod(T n){
    nod<T>*p=root;
        if(p==NULL){
            cout<<"Arborele e gol"<<endl;
        }else{
            nod<T>*a;
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
                nod<T>*q=p;
                nod<T>*d=p;
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

template <class T>
void arboreBinar<T>::listaFrunzelor(nod<T>* r){
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


template <class T>
void arboreBinar<T>::inaltimeM(nod<T>* r,int b){
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


template <class T>
nod<T>* arboreBinar<T>::iaRadacina(){
    return root;
}


template <class T>
arboreBinar<T> arboreBinar<T>::operator+(T n){
    nod<T>*t;
    t=new nod<T>(n);
    if(root==NULL){
        t->setPadre(NULL);
        root=t;
    }else{
        nod<T>*p=root;
        nod<T>*padre;
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
            t->setPadre(padre);
            padre->right=t;
        }else{
            t->setPadre(padre);
            padre->left=t;
        }
    }
    return *this;
}

template <class T>
istream& operator>>(istream& in,arboreBinar<T>& a){
    T n;
    int v;
    cout<<"\nScrieti numarul de noduri de inserat:";
    cin>>v;
    for(int i=1;i<=v;i++){
    cout<<"\nScrieti elementul "<<i<<":";
    cin>>n;
    a+n;
    }
    return in;
}

template <class T>
ostream& operator<<(ostream& out,nod<T>* a){
    if(a->getLeft()){
        operator<<(out,a->getLeft());
    }
    if(a){
        out<<a->iaInfo()<<" "<<a->getCuloare()<<" ";
    }
    if(a->getRight()){
        operator<<(out,a->getRight());
    }
    return out;
}


//-------------------------------------------------------------clasa redBlack------------------------------------------------------

template <class T>
class redBlack : public arboreBinar<T> {
    void insCaz1(nod<T>*);
    void insCaz2(nod<T>*);
    void insCaz3(nod<T>*);
    void insCaz4(nod<T>*);
    void insCaz5(nod<T>*);
    void rotatieStanga(nod<T>*);
    void rotatieDreapta(nod<T>*);
    nod<T>* grandPadre(nod<T>*);
    nod<T>* uncle(nod<T>*);
    void recolorare(nod<T>*);
public:
    redBlack(){}
    redBlack(nod<T>* a,int n) : arboreBinar<T>(a,n){}
    arboreBinar<T> operator+ (T);
    void stergereNod(T);
    void rB(nod<T>* n){insCaz1(n);}
    void inaltimeM(nod<T>*,int);
};

//-------------------------------------------------------------clasa redBlack------------------------------------------------------

template <class T>
void redBlack<T>::inaltimeM(nod<T>* r,int b){
    if(r->getCuloare()==BLACK)
        b++;
    if(b>this->iaInaltime())
        this->setInaltime(b);
    if(r->getLeft()){
        inaltimeM(r->getLeft(),b);
    }
}


template <class T>
void redBlack<T>::recolorare(nod<T>* n){
    rB(n);
    if(n->getLeft())
        recolorare(n->getLeft());
    if(n->getRight())
        recolorare(n->getRight());
}

template <class T>
void redBlack<T>::stergereNod(T n){
    nod<T>*p=this->iaRadacina();
        if(p==NULL){
            cout<<"Arborele e gol"<<endl;
        }else{
            nod<T>*a;
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
                nod<T>*q=p;
                nod<T>*d=p;
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
    recolorare(this->iaRadacina());
}


template <class T>
arboreBinar<T> redBlack<T>::operator+(T n){
    nod<T>*t;
    t=new nod<T>(n);
    t->setCuloare(RED);
    if(this->iaRadacina()==NULL){
        t->setPadre(NULL);
        this->setRoot(t);
    }else{
        nod<T>*p=this->iaRadacina();
        nod<T>*padre;
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
            t->setPadre(padre);
            padre->right=t;
        }else{
            t->setPadre(padre);
            padre->left=t;
        }
    }
    rB(t);
    return *this;
}

template<class T>
nod<T>* redBlack<T>::grandPadre(nod<T>* n){
    if ((n != NULL) && (n->getPadre() != NULL))
        return n->getPadre()->getPadre();
    else
        return NULL;
}

template<class T>
nod<T>* redBlack<T>::uncle(nod<T>* n){
    nod<T>* gP = grandPadre(n);
    if (gP == NULL)
        return NULL; //no grandpadre => no uncle
    if (n->getPadre() == gP->getLeft())
        return gP->getRight();
    else
        return gP->getLeft();
}

template <class T>
void redBlack<T>::rotatieStanga(nod<T>*nodus){
    nod<T>* padre=nodus->getPadre(),*q=nodus->getRight(),*p=q->getLeft();
    q->setLeft(nodus);
    nodus->setRight(p);
    if(padre!=NULL && padre->getLeft()==nodus){
        padre->setLeft(q);
    }else if(padre!=NULL){
        padre->setRight(q);
    }
    q->setPadre(nodus->getPadre());
    nodus->setPadre(q);
}

template <class T>
void redBlack<T>::rotatieDreapta(nod<T>*nodus){
    nod<T>* padre=nodus->getPadre(),*q=nodus->getLeft(),*p=q->getRight();
    q->setRight(nodus);
    nodus->setLeft(p);
    if(padre!=NULL && padre->getRight()==nodus){
        padre->setRight(q);
    }else if(padre!=NULL){
        padre->setLeft(q);
    }
    q->setPadre(nodus->getPadre());
    nodus->setPadre(q);
}

template <class T>
void redBlack<T>::insCaz1(nod<T>* n){
    if (n->getPadre() == NULL){
        n->setCuloare(BLACK);
    }else
        insCaz2(n);
}

template <class T>
void redBlack<T>::insCaz2(nod<T>* n){
    if (n->getPadre()->getCuloare() == BLACK)
        return;
    else
        insCaz3(n);
}

template <class T>
void redBlack<T>::insCaz3(nod<T>* n){
    nod<T> *u = uncle(n), *g;

    if ((u != NULL) && (u->getCuloare() == RED)) {
       n->getPadre()->setCuloare(BLACK);
       u->setCuloare(BLACK);
       g = grandPadre(n);
       g->setCuloare(RED);
       insCaz1(g);
    } else {
       insCaz4(n);
    }
}

template <class T>
void redBlack<T>::insCaz4(nod<T>* n){
    nod<T> *g = grandPadre(n);

    if ((n == n->getPadre()->getRight()) && (n->getPadre() == g->getLeft())) {
        rotatieStanga(n->getPadre());
        n=n->getLeft();
    }else if ((n == n->getPadre()->getLeft()) && (n->getPadre() == g->getRight())) {
        rotatieDreapta(n->getPadre());
        n = n->getRight();
    }
 insCaz5(n);
}

template <class T>
void redBlack<T>::insCaz5(nod<T>* n){
    nod<T> *g = grandPadre(n);

    n->getPadre()->setCuloare(BLACK);
    g->setCuloare(RED);
    if (n == n->getPadre()->getLeft())
        rotatieDreapta(g);
    else
        rotatieStanga(g);
}

int main()
{
 
}
