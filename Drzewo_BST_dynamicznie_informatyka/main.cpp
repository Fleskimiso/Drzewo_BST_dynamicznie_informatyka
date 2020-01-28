#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class wierzcholek{
public:
    wierzcholek<T> * lewy_sasiad;
    wierzcholek<T> * prawy_sasiad;
    T wartosc;
    int glebokosc;
    //methods...
    wierzcholek(T value,int depth);
    void dodaj(T wartosc);
    void usun_drzewo();
    T znajdz_maksimum();
    T znajdz_minimum();
    void zmien_zasade();
   static void wypisz(wierzcholek<T>* root);
};

int main()
{
    wierzcholek<int> * root = new wierzcholek<int>(0,1);
    int tablica_danych[9] = {5,56,2,4,7,8,3,1,33};
    root->wartosc = tablica_danych[0];
    for(int i=1; i<9; i++){
        root->dodaj(tablica_danych[i]);
    }
    cout << "Maksimum: " << root->znajdz_maksimum() << endl;
    cout << "Minimum: " << root->znajdz_minimum() << endl;

    /** wypisanie wszerz**/
    cout << "Wypisanie wartosci drzewa w szersz" << endl;
    wierzcholek<int>::wypisz(root);
    cout << endl;
    cout << "Wypisanie ze zmieniona kolejnoscia" << endl;
    root->zmien_zasade();
    wierzcholek<int>::wypisz(root);
    cout << endl;
    root->usun_drzewo();

    return 0;
}
template <typename T>
wierzcholek<T>::wierzcholek(T value,int depth){
    this->lewy_sasiad = nullptr;
    this->prawy_sasiad = nullptr;
    wartosc = value;
    glebokosc = depth;
}
template <typename T>
void wierzcholek<T>::dodaj(T wartosc){
    if(wartosc >= this->wartosc){
        if(this->prawy_sasiad == nullptr){
            this->prawy_sasiad = new wierzcholek<T>(wartosc,this->glebokosc +1);
        }else{
            this->prawy_sasiad->dodaj(wartosc);
        }
    }else{
        if(this->lewy_sasiad == nullptr){
            this->lewy_sasiad = new wierzcholek<T>(wartosc,this->glebokosc +1);
        }else{
            this->lewy_sasiad->dodaj(wartosc);
        }
    }

}
template<typename T>
void wierzcholek<T>::usun_drzewo(){
    if(this->lewy_sasiad == nullptr && this->prawy_sasiad == nullptr){
        cout << "Usuwanie wierzcholka o wartosci: " << this->wartosc << " glebokosci: " << this->glebokosc << endl;
        delete this;
    }else{
        if(this->prawy_sasiad != nullptr){
            this->prawy_sasiad->usun_drzewo();
        }
        if(this ->lewy_sasiad != nullptr){
            this->lewy_sasiad->usun_drzewo();
        }
        cout << "Usuwanie wierzcholka o wartosci: " << this->wartosc << " glebokosci: " << this->glebokosc << endl;
        delete this;
    }
}
template <typename T>
T wierzcholek<T>::znajdz_maksimum(){
    if(this->prawy_sasiad != nullptr){
        return this->prawy_sasiad->znajdz_maksimum();
    }else{
        return this->wartosc;
    }
}
template <typename T>
T wierzcholek<T>::znajdz_minimum(){
    if(this->lewy_sasiad != nullptr){
        return this->lewy_sasiad->znajdz_minimum();
    }else{
        return this->wartosc;
    }
}
template <typename T>
void wierzcholek<T>::zmien_zasade(){
    /**
    TODO: uatualnic o zasade inne funkcje
    **/
    wierzcholek<T> * chwilowy_wierzcholek = this->lewy_sasiad;
    this->lewy_sasiad = this->prawy_sasiad;
    this->prawy_sasiad = chwilowy_wierzcholek;
    if(this->prawy_sasiad != nullptr){
        this->prawy_sasiad->zmien_zasade();
    }
    if(this->lewy_sasiad != nullptr){
        this->lewy_sasiad->zmien_zasade();
    }
}
template <typename T>
void wierzcholek<T>::wypisz(wierzcholek<T>* root){
    queue<wierzcholek<T>*> kolejka_drzewa;
    kolejka_drzewa.push(root);
    int chwilowa_glebokosc = kolejka_drzewa.front()->glebokosc;
    while(!kolejka_drzewa.empty()){
        wierzcholek<int>*chwilowy_wierzcholek = kolejka_drzewa.front();
        if(chwilowy_wierzcholek->lewy_sasiad != nullptr){
            kolejka_drzewa.push(chwilowy_wierzcholek->lewy_sasiad);
        }
        if(chwilowy_wierzcholek->prawy_sasiad != nullptr){
            kolejka_drzewa.push(chwilowy_wierzcholek->prawy_sasiad);
        }
        if(chwilowy_wierzcholek->glebokosc != chwilowa_glebokosc){
            chwilowa_glebokosc = chwilowy_wierzcholek->glebokosc;
            cout << endl;
        }
        cout << chwilowy_wierzcholek->wartosc << ", ";
        kolejka_drzewa.pop();
        //todo
    }
}

