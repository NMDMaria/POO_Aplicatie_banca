#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>
#include <iterator>

using namespace std;

ofstream feedback("feedback.txt", std::istream::app);
ofstream print("printUsers.txt");


class data
{
    int zi;
    int luna;
    int an;
public:
    /// Supraincarcari:
    friend ostream& operator<<(ostream&, const data&);
    friend istream& operator>>(istream&, data&);
    data& operator=(data&);
    data& operator=(const data&);
    bool operator==(const data&) const;
    bool operator!=(const data&) const;
    bool operator<(const data&) const;
    bool operator>(const data&) const;
    bool operator>=(const data&) const;
    bool operator<=(const data&) const;
    data operator+(int) const;
    data operator+=(int);
    data operator-(int) const;
    int operator-(const data&) const;
    data operator-=(int);
    const data& operator++();
    const data operator++(int);
    int operator[](int) const;
    explicit operator int*() const;

    /// Setteri si getteri:
    void setZi(int);
    void setLuna(int);
    void setAn(int);
    int getZi() const;
    int getLuna() const;
    int getAn() const;


    /// Altele:
    friend int nrzileLuna(int luna, int an);


    /// Constructori si destructor:
    data(const data&);
    data(int, int, int);
    data(int, int);
    data(int);
    data();
    ~data();
};


/// Altele:
int nrzileLuna(int luna, int an)
{
    int d_aux;
    if (luna == 4 || luna == 6 || luna == 9
        || luna == 11)
            d_aux = 30;
    else if (luna == 2)
    {
        if (an % 4 == 0 && an % 100 != 0)
            d_aux = 29;
        else if (an % 400 == 0)
            d_aux = 29;
        else d_aux = 28;
    }
    else d_aux = 31;
    return d_aux;
}


/// Supraincarcari:
ostream& operator<<(ostream& out, const data& d)
{
    out<<d.zi<<"-"<<d.luna<<"-"<<d.an;
    return out;
}

istream& operator>>(istream& in, data& d)
{
    bool ok = 0;
    int rez = 1;
    while(!ok && rez == 1)
    {
        cout<<"\nIntroduceti ziua: ";
        int z, l, a;
        in>>z;
        cout<<"Introduceti luna: ";
        in>>l;
        cout<<"Introduceti anul: ";
        in>>a;
        if (z > 31 || l > 12 || a > 2021 || a < 1800
            || z < 1 || l < 1)
            cout<<"Ati introdus o data incorecta.\n";
        else
        {
            bool ok1 = true;
            switch(l)
            {
                case 2:
                    {
                        if((a % 4 != 0 && z > 28)|| (a % 4 == 0 && z > 29))
                        {
                            ok1 = false;
                            cout<<"Ati introdus o data incorecta, incercati din nou\n";
                            break;
                        }
                        break;
                    }
                case 4:
                    if (z > 30)
                        {
                            ok1 = false;
                            cout<<"Ati introdus o data incorecta, incercati din nou\n";
                            break;
                        }
                        break;
                case 6:
                    if (z > 30)
                        {
                            ok1 = false;
                            cout<<"Ati introdus o data incorecta, incercati din nou\n";
                            break;
                        }
                        break;
                case 9:
                    if (z > 30)
                        {
                            ok1 = false;
                            cout<<"Ati introdus o data incorecta, incercati din nou\n";
                            break;
                        }
                        break;
                case 11:
                    if (z > 30)
                        {
                            ok1 = false;
                            cout<<"Ati introdus o data incorecta, incercati din nou\n";
                            break;
                        }
                        break;


            }
            if (ok1 == true)
            {
                ok = 1;
                d.setAn(a);
                d.setLuna(l);
                d.setZi(z);
            }
        }
        if (ok == 0)
        {
            cout<<"Apasati 1 pentru a incerca din nou. Daca iesiti se va inititializa data curenta.\n";
            in>>rez;
        }
    }
    if (!ok && rez != 1)
    {
        data aux;
        d = aux;
    }
    return in;
}

data& data::operator=(data& c)
{
    if (this != &c)
    {
        this->an = c.getAn();
        this->luna = c.getLuna();
        this->zi = c.getZi();
    }
    return *this;
}

data& data::operator=(const data& c)
{
    this->an = c.an;
    this->luna = c.luna;
    this->zi = c.zi;
    return *this;
}

data data::operator+(int i) const
{
    int k = i;
    int cont_zi = 0;
    int aux_luna = this->luna;
    int cont_luna = 0;
    int aux_an = this->an;
    int cont_an = 0;

    cont_zi = this -> zi;
    while(k)
    {
        if (cont_zi + k < nrzileLuna(aux_luna, aux_an))
        {
            cont_zi += k;
            k = 0;
        }
        else
        {
            k = k - nrzileLuna(aux_luna, aux_an);
            cont_luna += 1;
            if (aux_luna + 1 >= 13 && cont_luna != 0)
            {
                aux_an += 1;
                cont_an ++;
            }
            aux_luna = (aux_luna + 1)/13 + (aux_luna + 1)%13;
        }
    }
    return data(cont_zi, aux_luna, aux_an);
}

data data::operator-(int i) const
{
    int k = i;
    int cont_zi = 0;
    int aux_luna = this->luna;
    int cont_luna = 0;
    int aux_an = this->an;
    int cont_an = 0;

    cont_zi = this -> zi;
    while(k)
    {
        if (k < cont_zi)
        {
            cont_zi -= k;
            k = 0;
        }
        else
        {
            k -= cont_zi;
            cont_luna += 1;
            if (aux_luna % 13 == 1)
            {
                aux_luna = 12;
                cont_an += 1;
                aux_an -= 1;
            }
            else aux_luna -= 1;
            cont_zi = nrzileLuna(aux_luna, aux_an);
        }

    }
    return data(cont_zi, aux_luna, aux_an);
}

int data::operator-(const data& d) const
{
    if (*this == d)
        return 0;
    if (*this < d)
    {
        int z_aux = this->zi, l_aux = this->luna, an_aux = this->an;
        int nr = 0;
        while (!(z_aux == d.zi && l_aux == d.luna && an_aux == d.an))
        {
            nr++;
            z_aux++;
            if (z_aux > nrzileLuna(l_aux, an_aux))
            {
                z_aux = 1;
                l_aux++;
            }
            if (l_aux > 12)
            {
                l_aux = 1;
                an_aux++;
            }
        }
        return nr;
    }
    else
    {
        int z_aux = d.zi, l_aux = d.luna, an_aux = d.an;
        int nr = 0;
        while (!(z_aux == this->zi && l_aux == this->luna && an_aux == this->an))
        {

            nr++;
            z_aux++;
            if (z_aux > nrzileLuna(l_aux, an_aux))
            {
                z_aux = 1;
                l_aux++;
                if (l_aux > 12)
                {
                    l_aux = 1;
                    an_aux++;
                }
            }
        }
        return nr;
    }
}

data data::operator-=(int i)
{
    int k = i;
    int cont_zi = 0;
    int aux_luna = this->luna;
    int cont_luna = 0;
    int aux_an = this->an;
    int cont_an = 0;

    cont_zi = this -> zi;
    while(k)
    {
        if (k < cont_zi)
        {
            cont_zi -= k;
            k = 0;
        }
        else
        {
            k -= cont_zi;
            cont_luna += 1;
            if (aux_luna % 13 == 1)
            {
                aux_luna = 12;
                cont_an += 1;
                aux_an -= 1;
            }
            else aux_luna -= 1;
            cont_zi = nrzileLuna(aux_luna, aux_an);
        }

    }
    data l(cont_zi, aux_luna, aux_an);
    *this = l;
    return l;
}

data data::operator+=(int i)
{
   int k = i;
    int cont_zi = 0;
    int aux_luna = this->luna;
    int cont_luna = 0;
    int aux_an = this->an;
    int cont_an = 0;

    cont_zi = this -> zi;
    while(k)
    {
        if (cont_zi + k < nrzileLuna(aux_luna, aux_an))
        {
            cont_zi += k;
            k = 0;
        }
        else
        {
            k = k - nrzileLuna(aux_luna, aux_an);
            cont_luna += 1;
            if (aux_luna + 1 >= 13 && cont_luna != 0)
            {
                aux_an += 1;
                cont_an ++;
            }
            aux_luna = (aux_luna + 1)/13 + (aux_luna + 1)%13;
        }
    }
    data l(cont_zi, aux_luna, aux_an);
    *this = l;
    return *this;
}

const data data::operator++(int) //post
{
    int k = 1;
    int cont_zi = 0;
    int aux_luna = this->luna;
    int cont_luna = 0;
    int aux_an = this->an;
    int cont_an = 0;

    cont_zi = this -> zi;
    while(k)
    {
        if (cont_zi + k < nrzileLuna(aux_luna, aux_an))
        {
            cont_zi += k;
            k = 0;
        }
        else
        {
            k = k - nrzileLuna(aux_luna, aux_an);
            cont_luna += 1;
            if (aux_luna + 1 >= 13 && cont_luna != 0)
            {
                aux_an += 1;
                cont_an ++;
            }
            aux_luna = (aux_luna + 1)/13 + (aux_luna + 1)%13;
        }
    }
    data l(cont_zi, aux_luna, aux_an);
    *this = l;
    return *this;
}

const data& data::operator++()//pre
{
    data help(*this);
    int k = 1;
    int cont_zi = 0;
    int aux_luna = this->luna;
    int cont_luna = 0;
    int aux_an = this->an;
    int cont_an = 0;

    cont_zi = this -> zi;
    while(k)
    {
        if (cont_zi + k < nrzileLuna(aux_luna, aux_an))
        {
            cont_zi += k;
            k = 0;
        }
        else
        {
            k = k - nrzileLuna(aux_luna, aux_an);
            cont_luna += 1;
            if (aux_luna + 1 >= 13 && cont_luna != 0)
            {
                aux_an += 1;
                cont_an ++;
            }
            aux_luna = (aux_luna + 1)/13 + (aux_luna + 1)%13;
        }
    }
    data l(cont_zi, aux_luna, aux_an);
    *this = l;
    return help;
}

bool data::operator==(const data& d) const
{
    if (this->zi != d.zi)
        return 0;
    if (this->luna != d.luna)
        return 0;
    if (this->an != d.an)
        return 0;
    return 1;
}

bool data::operator!=(const data& d) const
{
    return !(*this == d);
}

bool data::operator<(const data& d) const
{
    if (this->an < d.an)
        return 1;
    if (this-> an == d.an && this->luna < d.luna)
        return 1;
    if (this-> an == d.an && this->luna == d.luna && this->zi < d.zi)
        return 1;
    return 0;
}

bool data::operator<=(const data& d) const
{
    if (this->an <= d.an)
        return 1;
    if (this-> an == d.an && this->luna <= d.luna)
        return 1;
    if (this-> an == d.an && this->luna == d.luna && this->zi <= d.zi)
        return 1;
    return 0;
}

bool data::operator>(const data& d) const
{
    if (this->an > d.an)
        return 1;
    if (this-> an == d.an && this->luna > d.luna)
        return 1;
    if (this-> an == d.an && this->luna == d.luna && this->zi > d.zi)
        return 1;
    return 0;
}

bool data::operator>=(const data& d) const
{
    if (this->an > d.an)
        return 1;
    if (this-> an == d.an && this->luna >= d.luna)
        return 1;
    if (this-> an == d.an && this->luna == d.luna && this->zi >= d.zi)
        return 1;
    return 0;
}

int data::operator[](int idx) const
{
    if(idx < 0 || idx > 2)
    {
        cout<<"\nIndex introdus gresit.\n";
        return -1;
    }
    else
    {
        switch(idx)
        {
            case 0: return this->zi; break;
            case 1: return this->luna; break;
            case 2: return this->an; break;
        }
    }
}

data::operator int*() const
{
    int* aux = new int[3];
    aux[0] = this->zi;
    aux[1] = this->luna;
    aux[2] = this->an;
    return aux;
}
/// Setteri si getteri
int data::getZi() const
{
    return this->zi;
}

int data::getLuna() const
{
    return this->luna;
}

int data::getAn() const
{
    return this->an;
}

void data::setZi(int z)
{
    this->zi = z;
}

void data::setLuna(int l)
{
    this->luna = l;
}

void data::setAn(int a)
{
    this->an = a;
}


/// Constructori si destructor:
data::data(const data& d)
{
    this->zi = d.zi;
    this->luna = d.luna;
    this->an = d.an;
}

data::data(int z, int l, int a)
{
    this->zi = z;
    this->luna = l;
    this->an = a;
}

data::data(int z, int l)
{
    this->zi = z;
    this->luna = l;
    time_t now = time(0);
    tm *t = localtime(&now);
    this->an = 1900 + t->tm_year;
}

data::data(int z)
{
    this->zi = z;
    time_t now = time(0);
    tm *t = localtime(&now);
    this->luna = 1 + t->tm_mon;
    this->an = 1900 + t->tm_year;
}

data::data()
{
    time_t now = time(0);
    tm *t = localtime(&now);
    this->zi = t->tm_mday;
    this->luna = 1 + t->tm_mon;
    this->an = 1900 + t->tm_year;
}

data::~data()
{

}


class tranzactie
{
     const int id_tranz;
     data date;
     string trimite;
     string primeste;
     double suma;
     bool credit;
     bool retragere;
     bool depunere;
public:
    static int contor_id_tranz;

    /// Supraincarcari:

    friend ostream& operator<<(ostream&, const tranzactie&);
    friend istream& operator>>(istream&, tranzactie&);
    tranzactie& operator=(tranzactie&);
    bool operator==(const tranzactie&) const;
    tranzactie operator+(double) const;
    tranzactie& operator+=(double);
    tranzactie operator-=(double);
    tranzactie& operator-(double) const;
    string operator[](int) const;

    /// Setteri si getteri:
    string getPrimeste() const;
    string getTrimite() const;
    double getSuma() const;
    int getId_tranz() const;
    data getDate() const;
    bool getRetragere() const;
    bool getCredit() const;
    bool getDepunere() const;

    void setDate(const data&);


    /// Constructori si destructor:
    tranzactie();
    tranzactie(const data, string, string, double);
    tranzactie(const data, string, double, int);
    tranzactie(const tranzactie&);
    ~tranzactie();
};

/// Supraincarcari:
ostream& operator<<(ostream& out, const tranzactie& t)
{
    out<<"\n---------------Tranzactie---------------\n";
    out<<"Data: "<<t.date<<"\n"
        <<"Cod: "<<t.id_tranz<<"\n";

    if (t.credit)
    {
        out<<"-----Credit bancar\n"
            <<"Beneficiar: "<<t.primeste<<"\n";
    }
    else if (t.depunere)
    {
        out<<"-----Depunere\n"
            <<"Beneficiar: "<<t.primeste<<"\n";
    }
    else if (t.retragere)
    {
        out<<"-----Retragere\n"
            <<"Din: "<<t.trimite<<"\n";
    }
    else
    {
        out<<"-----Transfer\n"
            <<"Beneficiar: "<<t.primeste<<"\n"
            <<"Din: "<<t.trimite<<"\n";
    }
    out<<t.suma<<" lei\n";
    return out;
}

istream& operator>>(istream& in, tranzactie& t)
{
    data aux;
    cout<<"\n"<<char(254)<<"    Citire tranzactie    "<<char(254)<<"\n";
    in>>aux;
    cout<<"Ce tip de tranzactie este: \n"
    <<"1. Credit bancar \n2. Retragere suma\n3. Depunere suma\n4. Transfer\n";
    int option;
    in>>option;
    switch(option)
    {
    case 1:
        t.credit = 1;
        t.retragere = 0;
        t.depunere = 0;
        cout<<"\nIntroduceti iban-ul contului: ";
        in>>t.primeste;
        cout<<"\nIntroduceti suma: ";
        in>>t.suma;
        break;
    case 2:
        t.retragere = 1;
        t.credit = 0;
        t.depunere = 0;
        cout<<"\nIntroduceti iban-ul contului: ";
        in>>t.trimite;
        cout<<"\nIntroduceti suma: ";
        in>>t.suma;
        break;
    case 3:
        t.depunere = 1;
        t.credit = 0;
        t.retragere = 0;
        cout<<"\nIntroduceti iban-ul contului: ";
        in>>t.primeste;
        cout<<"\nIntroduceti suma: ";
        in>>t.suma;
        break;
    case 4:
        t.credit = 0;
        t.depunere = 0;
        t.retragere = 0;
        cout<<"\nIntroduceti iban-ul contului din care se transfera suma: ";
        in>>t.trimite;
        cout<<"\nIntroduceti iban-ul contului care primeste suma: ";
        in>>t.primeste;
        cout<<"\nIntroduceti suma: ";
        in>>t.suma;
        break;
    default:
        cout<<"Optiune invalida\n";
    }
    return in;
}

tranzactie& tranzactie::operator=(tranzactie& t)
{
    if (this != &t)
    {
        this->date = t.date;
        this->trimite = t.trimite;
        this->primeste = t.primeste;
        this->suma = t.suma;
        this->credit = t.credit;
        this->depunere = t.depunere;
        this->retragere = t.retragere;
    }
    return *this;
}

bool tranzactie::operator==(const tranzactie& t) const
{
    if (this->id_tranz != t.id_tranz)
        return 0;
    if (this->date != t.date)
        return 0;
    if (this->trimite != t.trimite)
        return 0;
    if (this->primeste != t.primeste)
        return 0;
    if (this->suma != t.suma)
        return 0;
    if (this->credit != t.credit)
        return 0;
    if (this->retragere != t.retragere)
        return 0;
    if (this->depunere != t.depunere)
        return 0;
    return 1;
}

tranzactie tranzactie::operator+(double s) const
{
    tranzactie aux(*this);
    aux.suma += s;
    return aux;
}

tranzactie& tranzactie::operator+=(double s)
{
    this->suma += s;
    return *this;
}

tranzactie tranzactie::operator-=(double s)
{
    this->suma -= s;
    return *this;
}

tranzactie& tranzactie::operator-(double s) const
{
    tranzactie aux(*this);
    aux.suma -= s;
    return aux;
}

string tranzactie::operator[](int idx) const
{
    if (idx == 0)
        return this->trimite;
    if (idx == 1)
        return this->primeste;
    cout<<"\nIndex invalid.\n";
}


/// Setteri si getteri:

string tranzactie::getPrimeste() const
{
    return this->primeste;
}

string tranzactie::getTrimite() const
{
    return this->trimite;
}

double tranzactie::getSuma() const
{
    return this->suma;
}

int tranzactie::getId_tranz() const
{
    return this->id_tranz;
}

bool tranzactie::getRetragere() const
{
    return this->retragere;
}
bool tranzactie::getCredit() const
{
    return this->credit;
}
bool tranzactie::getDepunere() const
{
    return this->depunere;
}

data tranzactie::getDate() const
{
    data aux;
    aux = this->date;
    return aux;
}

void tranzactie::setDate(const data& d)
{
    this->date = d;
}


/// Constructori si destructor:
int tranzactie::contor_id_tranz = 0;

tranzactie::tranzactie(const tranzactie& t):id_tranz(t.id_tranz)
{
    this->date = t.date;
    this->trimite = t.trimite;
    this->primeste = t.primeste;
    this->suma = t.suma;
    this->credit = t.credit;
    this->retragere = t.retragere;
    this->depunere = t.depunere;
}

tranzactie::tranzactie():id_tranz(contor_id_tranz++)
{
    data aux;
    this->date = aux;
    this->credit = 0;
    this->depunere = 0;
    this->retragere = 0;
    this->primeste = "";
    this->trimite = "";
    this->suma = 0;
}

tranzactie::tranzactie(const data date, string iban1, string iban2, double suma):id_tranz(contor_id_tranz++)
{
    this->date = date;
    this->trimite = iban1;
    this->primeste = iban2;
    this->suma = suma;
    this->retragere = 0;
    this->depunere = 0;
    this->credit = 0;
}

tranzactie::tranzactie(const data date, string iban1, double suma, int type):id_tranz(contor_id_tranz++)
{
    this->date = date;
    this->suma = suma;
    switch (type)
    {
    case 1:
        this->credit = 1;
        this->depunere = 0;
        this->retragere = 0;
        this->primeste = iban1;
        break;
    case 2:
        this->depunere = 1;
        this->primeste = iban1;
        this->credit = 0;
        this->retragere = 0;
        break;
    case 3:
        this->retragere = 1;
        this->trimite = iban1;
        this->credit = 0;
        this->depunere = 0;
        break;
    }

}

tranzactie::~tranzactie()
{
}

class cont
{
    const int id_cont;
    double sold;
    string IBAN;
    int nr_carduri;
    string *carduri;
    float procent_taxe;
    int id_titular;
    float* bilant_pozitiv_lunar;
    float* bilant_negativ_lunar;
    int nr_tranzactii;
    tranzactie* istoric; // HAS A
public:
    static int contor_id_cont;

    /// Supraincarcari:
    cont& operator=(const cont&);
    friend ostream& operator<<(ostream&, const cont&);
    friend istream& operator>>(istream&, cont&);
    bool operator==(const cont&) const;
    cont operator+(const tranzactie&) const;
    cont& operator+=(const tranzactie&);
    tranzactie operator[](int) const;


    /// Setteri si getteri:
    double getSold() const;
    string getIBAN() const;
    int getId_cont() const;
    int getNr_tranzactii() const;
    string* getCarduri() const;
    int getId_titular() const;
    void setSold(double);
    void setIBAN(string);
    void setCarduri(string*, int);
    void setNr_carduri(int);
    void setId_titular(int);
    void setProcent_taxe(float);
    void setNr_tranzactii(int);
    void setIstoric(tranzactie*, int);


    /// Altele:
    void checkAppendtranzactii(tranzactie*, int);
    void appendtranzactie(const tranzactie&);
    void soldAdd(double);
    void soldTake(double);
    void cardAdd(string);
    void modifyBalance(const tranzactie&);
    void checkIstoric();
    double nouTranzactie();


    /// Constructori si destructor:
    cont(double, string, int, string*, float, int, float*, float*, int, tranzactie*, int);
    cont(double, string, int);
    cont(int, int);
    cont(int);
    cont();
    cont(const cont&);
    ~cont();
};

/// Supraincarcari:
cont& cont::operator=(const cont& c)
{
    if (this != &c)
    {
        this->sold = c.sold;
        this->IBAN = c.IBAN;

        this->nr_carduri = c.nr_carduri;
        if (this->carduri != NULL)
            delete []this->carduri;
        this->carduri = new string[c.nr_carduri];
        for(int i = 0; i < c.nr_carduri; ++i)
            this->carduri[i] = c.carduri[i];

        this->procent_taxe = c.procent_taxe;
        if (c.bilant_negativ_lunar != NULL)
        {
            if (this->bilant_negativ_lunar != NULL)
                delete []this->bilant_negativ_lunar;
            for(int i = 0; i < 12; ++i)
                this->bilant_negativ_lunar[i] = c.bilant_negativ_lunar[i];
        }
        else
        {
            if (this->bilant_negativ_lunar != NULL)
                delete []this->bilant_negativ_lunar;
        }
        if (c.bilant_pozitiv_lunar != NULL)
        {
              if (this->bilant_pozitiv_lunar != NULL)
                delete []this->bilant_pozitiv_lunar;
            for(int i = 0; i < 12; ++i)
                this->bilant_pozitiv_lunar[i] = c.bilant_pozitiv_lunar[i];
        }
        else
        {
            if (this->bilant_pozitiv_lunar != NULL)
                delete []this->bilant_pozitiv_lunar;
        }
        this->nr_tranzactii = c.nr_tranzactii;
        if (this->istoric != NULL)
            delete[] this->istoric;
        if (c.istoric != NULL)
        {
            this->istoric = new tranzactie[c.nr_tranzactii];
            for(int i = 0; i < c.nr_tranzactii; ++i)
            {
                this->istoric[i] = c.istoric[i];
            }
        }

        this->id_titular = c.id_titular;
    }
    return *this;
}

ostream& operator<<(ostream& out, const cont& c)
{
    out<<"\n"<<char(254)<<"    Detalii cont    "<<char(254)<<"\n";
    if (c.id_titular != 0)
        out<<"Titular: "<<c.id_titular<<"\n";
    out<<"Sold: "<<c.sold<<" lei\n"
        <<"IBAN: "<<c.IBAN<<"\n"
        <<"Numar carduri asociate: "<<c.nr_carduri<<"\n"
        <<"Procent taxe: "<<c.procent_taxe<<"%\n"
        <<"Numar tranzactii: "<<c.nr_tranzactii<<"\n";
    if(c.nr_tranzactii > 0)
    {
        out<<"Apasati 1 pentru a vedea istoricul tranzactiilor\n"
        <<"Apasati 0 pentru iesire\n";
        int rez;
        cin>>rez;
        if(rez == 1)
            for(int i = 0; i < c.nr_tranzactii; ++i)
                out<<c.istoric[i];
    }
    out<<"\n";
    return out;
}

istream& operator>>(istream& in, cont& c)
{
    cout<<"\nIntroduceti IBAN: ";
    string iban_aux;
    in>>iban_aux;
    c.setIBAN(iban_aux);
    cout<<"\nIntroduceti numarul de carduri asociate: ";
    int nr_card_aux;
    in>>nr_card_aux;
    c.setNr_carduri(nr_card_aux);
    if (nr_card_aux > 0)
    {
        cout<<"\nIntroduceti pe rand numarul fiecarui card.";
        string* carduri_aux = new string[nr_card_aux];
        for (int i = 1; i <= nr_card_aux; ++i)
        {
            cout<<"\n"<<i<<". ";
            in>>carduri_aux[i];
        }
        // dau delete si aloc iar memorie in setter
        c.setCarduri(carduri_aux, nr_card_aux);
    }
    else
    {
        delete[] c.carduri;
    }
    cout<<"Introduceti procent taxe: ";
    float procent_taxe_aux;
    in>>procent_taxe_aux;
    c.setProcent_taxe(procent_taxe_aux);
    cout<<"Introduceti numarul de tranzactii asociate: ";
    int nr_tranzactii_aux;
    in>>nr_tranzactii_aux;
    c.setNr_tranzactii(nr_tranzactii_aux);
    if (nr_tranzactii_aux > 0)
    {
        tranzactie* istoric_aux = new tranzactie[nr_tranzactii_aux];
        for (int i = 0; i < nr_tranzactii_aux; ++i)
            in>>istoric_aux[i];

        // Dezalocarea memoriei se face in setter!
        c.setIstoric(istoric_aux, nr_tranzactii_aux);
    }
}

bool cont::operator==(const cont& c) const
{
    if (this->id_cont != c.id_cont)
        return 0;
    if (this->id_titular != c.id_titular)
        return 0;
    if (this->sold != c.sold)
        return 0;
    if (this->IBAN != c.IBAN)
        return 0;
    if (this->procent_taxe != c.procent_taxe)
        return 0;
    if (this->nr_tranzactii != c.nr_tranzactii)
        return 0;
    return 1;
}

cont cont::operator+(const tranzactie& t) const
{
    cont no(this->id_cont, this->id_titular);
    no = (*this);
    tranzactie* aux = new tranzactie[this->nr_tranzactii + 1];
    for(int i = 0; i < nr_tranzactii; ++i)
        aux[i] = this->istoric[i];
    tranzactie a_t(t);
    aux[this->nr_tranzactii] = a_t;
    if (no.istoric)
        delete[] no.istoric;
    no.setIstoric(aux, this->nr_tranzactii + 1);
    return no;
}

cont& cont::operator+=(const tranzactie& t)
{
    tranzactie* aux = new tranzactie[this->nr_tranzactii + 1];
    for(int i = 0; i < this->nr_tranzactii; ++i)
        aux[i] = this->istoric[i];
    tranzactie a_t(t);
    aux[this->nr_tranzactii] = a_t;
    if (this->istoric)
        delete[] this->istoric;

    this->istoric = new tranzactie[this->nr_tranzactii + 1];
    for(int i = 0; i <= this->nr_tranzactii; ++i)
        aux[i] = this->istoric[i];

    this->nr_tranzactii += 1;
    return *this;
}

tranzactie cont::operator[](int idx) const
{
    ostream& out = cout;
    if (idx < 0 || idx >= this->nr_tranzactii)
        out<<"\nIndex introdus gresit.\n";
    else
        return this->istoric[idx];
}

/// Setteri si getteri:
double cont::getSold() const
{
    return this->sold;
}

string cont::getIBAN() const
{
    return this->IBAN;
}

int cont::getId_titular() const
{
    return this->id_titular;
}

int cont::getId_cont() const
{
    return this->id_cont;
}

int cont::getNr_tranzactii() const
{
    return this->nr_tranzactii;
}

string* cont::getCarduri() const
{
    return this->carduri;
}

void cont::setSold(double s)
{
    this->sold = s;
}

void cont::setIBAN(string i)
{
    this->IBAN = i;
}

void cont::setNr_carduri(int n)
{
    this->nr_carduri = n;
}

void cont::setCarduri(string* s, int n)
{
    // Dezalocarea memoriei care este necesara la operator>>
    if (this->carduri)
        delete[] this->carduri;
    this->carduri = new string[n]; // alocare noua
    this->setNr_carduri(n);
    for (int i = 0; i < n; ++i)
        this->carduri[i] = s[i];
}

void cont::setProcent_taxe(float t)
{
    this->procent_taxe = t;
}

void cont::setNr_tranzactii(int n)
{
    this->nr_tranzactii = n;
}

void cont::setIstoric(tranzactie* t, int n)
{
    // Dezalocarea memoriei care este necesara la operator>>
    if (this->istoric)
        delete[] this->istoric;
    this->istoric = new tranzactie[n]; // Alocare noua
    this->setNr_tranzactii(n);
    for (int i = 0; i < n; ++i)
        istoric[i] = t[i];
}

void cont::setId_titular(int id)
{
    this->id_titular = id;
}

/// Altele:
void cont::modifyBalance(const tranzactie& t)
{
    if(t.getCredit() || t.getDepunere())
    {
        this->soldAdd(t.getSuma());
    }

    if (t.getRetragere())
    {
        this->soldTake(t.getSuma());
    }

}

void cont::cardAdd(string nr_card)
{
    string* aux = new string[this->nr_carduri + 1];
    for(int i = 0; i < this->nr_carduri; ++i)
    {
        aux[i] = this->carduri[i];
    }
    this->nr_carduri += 1;
    delete[] this->carduri;
    this->carduri = new string[this->nr_carduri];
    for(int i = 0; i < this->nr_carduri; ++i)
    {
        this->carduri[i] = aux[i];
    }
    this->carduri[this->nr_carduri - 1] = nr_card;
}

void cont::appendtranzactie(const tranzactie& t)
{
    tranzactie* aux = new tranzactie[this->nr_tranzactii + 1];
    for(int i = 0; i < nr_tranzactii; ++i)
        aux[i] = this->istoric[i];
    tranzactie a_t(t);
    aux[this->nr_tranzactii] = a_t;
    if (this->istoric)
        delete[] this->istoric;
    this->istoric = new tranzactie[this->nr_tranzactii + 1];
    for (int i = 0; i <= nr_tranzactii; ++i)
        this->istoric[i] = aux[i];
    this->nr_tranzactii += 1;
    this->modifyBalance(a_t);
}

void cont::checkAppendtranzactii(tranzactie* t, int nr)
{
    for(int i = 0; i < nr; ++i)
    {
        if(t[i].getTrimite() == this->IBAN || t[i].getPrimeste() == this->IBAN)
        {
            this->appendtranzactie(t[i]);
            this->modifyBalance(t[i]);
        }
    }
}

void cont::checkIstoric()
{
    for (int i = 0; i < this->nr_tranzactii; ++i)
        this->modifyBalance(this->istoric[i]);
}

void cont::soldAdd(double s)
{
    this->sold += s - s * this->procent_taxe;
}
void cont::soldTake(double s)
{
    this->sold -= s;
    this->sold -= s * this->procent_taxe;
}

double cont::nouTranzactie()
{
    tranzactie t;
    cin>>t;
    this->appendtranzactie(t);
    if (t.getRetragere())
        return -t.getSuma();
    if (t.getCredit() || t.getDepunere())
        return t.getSuma();
}


/// Constructori si destructor:
int cont::contor_id_cont = 100;

cont::cont(int id, int id_tit):id_cont(id), id_titular(id_tit)
{
    this->sold = 0;
    this->IBAN = "";
    this->nr_carduri = 0;
    this->carduri = NULL;
    this->procent_taxe = 0;
    this->bilant_negativ_lunar = NULL;
    this->bilant_pozitiv_lunar = NULL;
    this->nr_tranzactii = 0;
    this->istoric = NULL;
}

cont::cont(int id_tit):id_cont(contor_id_cont++), id_titular(id_tit)
{
    this->sold = 0;
    this->IBAN = "";
    this->nr_carduri = 0;
    this->carduri = NULL;
    this->procent_taxe = 0;
    this->bilant_negativ_lunar = NULL;
    this->bilant_pozitiv_lunar = NULL;
    this->nr_tranzactii = 0;
    this->istoric = NULL;
}

cont::cont(const cont& c):id_cont(c.id_cont), id_titular(c.id_titular)
{
    this->sold = c.sold;
    this->IBAN = c.IBAN;
    this->nr_carduri = c.nr_carduri;

    if (this->carduri)
        delete []this->carduri;
    this->carduri = new string[c.nr_carduri];
    for (int i = 0; i < c.nr_carduri; ++i)
        this->carduri[i] = c.carduri[i];


    this->procent_taxe = c.procent_taxe;


    if (this->bilant_negativ_lunar)
        delete []this->bilant_negativ_lunar;
    this->bilant_negativ_lunar = new float[12];
    for (int i = 0; i < 12; ++i)
        this->bilant_negativ_lunar[i] = c.bilant_negativ_lunar[i];

    if (this->bilant_pozitiv_lunar)
        delete []this->bilant_pozitiv_lunar;
    this->bilant_pozitiv_lunar = new float[12];
    for (int i = 0; i < 12; ++i)
        this->bilant_pozitiv_lunar[i] = c.bilant_pozitiv_lunar[i];

    this->nr_tranzactii = c.nr_tranzactii;
    if (this->istoric)
        delete []this->istoric;
    this->istoric = new tranzactie[c.nr_tranzactii];
    for (int i = 0; i < c.nr_tranzactii; ++i)
        this->istoric[i] = c.istoric[i];
}

cont::cont(double a_sold, string a_IBAN, int a_nr_carduri, string* a_carduri, float a_procent_dobanda, int a_nr_luni, float* a_bilant_negativ_lunar, float* a_bilant_pozitiv_lunar, int a_tranz, tranzactie* t, int tit):id_cont(contor_id_cont++), id_titular(tit)
{
    this->sold = a_sold;
    this->IBAN = a_IBAN;
    this->nr_carduri = a_nr_carduri;
    if (this->nr_carduri == 0)
        this->carduri = NULL;
    else
    {
        this->carduri = new string [nr_carduri];
        for(int i = 0; i < nr_carduri; ++i)
        {
            this->carduri[i] = a_carduri[i];
        }
    }
    this->procent_taxe = a_procent_dobanda;
    if(a_nr_luni == 0)
    {
        this->bilant_negativ_lunar = NULL;
        this->bilant_pozitiv_lunar = NULL;
    }
    else
    {
        this->bilant_pozitiv_lunar = new float[a_nr_luni];
        this->bilant_negativ_lunar = new float[a_nr_luni];
        for(int i = 0; i < a_nr_luni; ++i)
        {
            this->bilant_negativ_lunar[i] = a_bilant_negativ_lunar[i];
            this->bilant_pozitiv_lunar[i] = a_bilant_pozitiv_lunar[i];
        }
    }
    this->nr_tranzactii = a_tranz;
    if (this->nr_tranzactii == 0)
        this->istoric = NULL;
    else
    {
        this->istoric = new tranzactie[this->nr_tranzactii];
        for(int i = 0; i < this->nr_tranzactii; ++i)
        {
            this->istoric[i] = t[i];
        }
    }
}

cont::cont(double m, string ban, int tit):id_cont(contor_id_cont++), id_titular(tit)
{
    this->sold = m;
    this->IBAN = ban;
    this->nr_carduri = 0;
    this->carduri = NULL;
    this->procent_taxe = 0;
    this->bilant_negativ_lunar = NULL;
    this->bilant_pozitiv_lunar = NULL;
    this->nr_tranzactii = 0;
    this->istoric = NULL;
}

cont::cont():id_cont(contor_id_cont++)
{
    this->id_titular = 0;
    this->sold = 0;
    this->IBAN = "-";
    this->nr_carduri = 0;
    this->carduri = NULL;
    this->procent_taxe = 0;
    this->bilant_negativ_lunar = NULL;
    this->bilant_pozitiv_lunar = NULL;
    this->nr_tranzactii = 0;
    this->istoric = NULL;
}

cont::~cont()
{
    if (this->bilant_negativ_lunar != NULL)
        delete []bilant_negativ_lunar;
    if (this->bilant_pozitiv_lunar != NULL)
        delete []bilant_pozitiv_lunar;
    if (this->carduri != NULL)
        delete []carduri;
    if (this->istoric != NULL)
        delete []istoric;
}

class client
{
    const int id_client;
    string nume;
    string prenume;
    long CNP;
    data start_date;
    int nr_initiale;
    char* initiale;
    char initiala_tatalui;
    int nr_cetatenii;
    string* cetatenie;
    double venit_anual;
    float* venit_lunar;
    int nr_conturi;
    cont* conturi; // HAS A
    double total_cash;
public:
    static int counter_id_client;


    /// Supraincarcari:
    friend ostream& operator<<(ostream&, const client&);
    friend istream& operator>>(istream&, client&);
    client& operator=(const client&);
    bool operator==(const client&) const;
    client operator+(const cont&) const;
    client& operator+=(const cont&);
    bool operator<(const client&) const;
    const cont& operator[](int) const;

    /// Setteri si getteri:
    void setNume(string);
    void setPrenume(string);
    void setVenit_anual(double);
    void setTotal_cash(double);
    void setStart_date(const data&);
    void setInitiala_tata(char);
    void setCetatenii(string*, int);
    void setVenit_lunar(float*);
    void setConturi(int, const cont*);

    int getId_client() const;
    string getNume() const;
    string getPrenume() const;
    int getCNP() const;
    double getTotal_cash() const;
    int getNr_conturi() const;
    cont& getCont(int) const;


    /// Altele:
    string ibanGen();
    void addCont();
    void addCont(const cont&);
    string intToString3(const int);
    void afisareZileMembru();
    void removeCont(int);
    void realizareTranzactie();


    /// Constructori si destructor:
    client(const client&);
    client(long);
    client(long, string, string, data, char, int, string*, double, float*, int, cont*);
    client(long, string, string, data, char, int, string*, double, float*);
    client(int, long);
    client();
    ~client();
};

istream& operator>>(istream& in, client& c)
{
    cout<<"\n"<<char(254)<<"    Citire client    "<<char(254)<<"\n";
    cout<<"Introduceti nume: ";
    string n, p;
    in>>n;
    c.setNume(n);
    cout<<"Introduceti prenume: ";
    in>>p;
    c.setPrenume(p);
    data d;
    cout<<"Introduceti data: ";
    in>>d;
    c.setStart_date(d);
    cout<<"Introduceti initiala tatalui: ";
    char t;
    in>>t;
    c.setInitiala_tata(t);
    int nc;
    cout<<"Introduceti numarul de cetatenii: ";
    in>>nc;
    cout<<"Introduceti cetateniile pe rand.\n";
    string* aux = new string[nc];
    for (int i = 0; i < nc; ++i)
    {
        cout<<i+1<<". ";
        in>>aux[i];
    }
    c.setCetatenii(aux, nc); // dau delete si aloc iar memorie in setter
    double v;
    cout<<"Introduceti venitul anual: ";
    in>>v;
    c.setVenit_anual(v);
    cout<<"Introduceti pe rand venitul lunar.\n";
    float* ac = new float[12];
    for(int i = 0; i < 12; ++i)
    {
        cout<<"Luna "<<i+1<<" : ";
        in>>ac[i];
    }
    c.setVenit_lunar(ac);
    cout << "Introduceti nr. de conturi deschise: ";
    int nr;
    in >> nr;
    cont *auxc = new cont[nr];
    for (int i = 0; i < nr; ++i)
        in >> auxc[i];
    c.setConturi(nr, auxc);
    return in;
}

ostream& operator<<(ostream& out, const client& c)
{

    out<<"\n"<<char(254)<<"    Detalii client    "<<char(254)<<"\n";
    out<<"Nume: "<<c.nume
        <<"\nPrenume: "<<c.prenume
        <<"\nCNP: "<<c.CNP
        <<"\nInitiala tatalui: "<<c.initiala_tatalui;
    if (c.nr_cetatenii > 0)
    {
        out<<"\nCetatenii: ";
        for (int i = 0; i < c.nr_cetatenii - 1; ++i)
            out<<c.cetatenie[i]<<", ";
        out<<c.cetatenie[c.nr_cetatenii - 1]<<"\n";
    }
    else out<<"\nNu au fost introduse cetateniile.\n";
    out<<"Venit anual: "<<c.venit_anual<<" lei\n"
        <<"Nr. conturi deschise: "<<c.nr_conturi<<"\n";
    if (c.nr_conturi != 0)
    {
        out<<"Valoare totala conturi: "<<c.total_cash<<" lei\n";
    }
    return out;
}

client& client::operator=(const client& c)
{
    if (this != &c)
    {
        this->nume = c.nume;
        this->prenume = c.prenume;
        this->nr_initiale = c.nr_initiale;
        if (this->initiale != NULL)
            delete []this->initiale;
        this->initiale = new char[this->nr_initiale];
        for (int i = 0; i < this->nr_initiale; ++i)
            this->initiale[i] = c.initiale[i];
        this->initiala_tatalui = c.initiala_tatalui;
        this->nr_cetatenii = c.nr_cetatenii;
        if (this->cetatenie)
            delete []this->cetatenie;
        this->cetatenie = new string[this->nr_cetatenii];
        for (int i = 0; i < this->nr_cetatenii; ++i)
            this->cetatenie[i] = c.cetatenie[i];

        this->venit_anual = c.venit_anual;
        if (this->venit_lunar)
            delete []this->venit_lunar;
        this->venit_lunar = new float[12];
        for(int i = 0; i < 12; ++i)
            this->venit_lunar[i] = c.venit_lunar[i];

        this->nr_conturi = c.nr_conturi;
        if (this->conturi)
            delete []this->conturi;
        this->conturi = new cont[this->nr_conturi];
        for (int i = 0; i < this->nr_conturi; ++i)
            this->conturi[i] = c.conturi[i];

    }
    return *this;
}

bool client::operator==(const client& c) const
{
    if (this->id_client != c.id_client)
        return 0;
    if (this->CNP != c.CNP)
        return 0;
    if (this->nume != c.nume)
        return 0;
    if (this->prenume != c.prenume)
        return 0;
    if (this->initiala_tatalui != c.initiala_tatalui)
        return 0;
    if (this->nr_cetatenii != c.nr_cetatenii)
        return 0;
    if (this->venit_anual != c.venit_anual)
        return 0;
    if (this->venit_lunar != c.venit_lunar)
        return 0;
    if (this->nr_conturi != c.nr_conturi)
        return 0;
    return 1;
}

client client::operator+(const cont& c) const
{
    client a(this->id_client, this->CNP);
    a = *this;
    if (a.conturi)
    {
        cont* aux = a.conturi;
        delete[] a.conturi;
        a.conturi = new cont[a.nr_conturi + 1];
        for (int i = 0; i < a.nr_conturi; ++i)
            a.conturi[i] = aux[i];
        a.conturi[a.nr_conturi] = c;
        a.nr_conturi++;
    }
    else
    {
        a.conturi = new cont[a.nr_conturi + 1];
        a.conturi[a.nr_conturi] = c;
        a.nr_conturi++;
    }
    a.total_cash += a.conturi[a.nr_conturi - 1].getSold();
    return a;
}

client& client::operator+=(const cont& c)
{
    if (this->conturi)
    {
        cont* aux = this->conturi;
        delete[] this->conturi;
        this->conturi = new cont[this->nr_conturi + 1];
        for (int i = 0; i < this->nr_conturi; ++i)
            this->conturi[i] = aux[i];
        this->conturi[this->nr_conturi] = c;
        this->nr_conturi++;
    }
    else
    {
        this->conturi = new cont[this->nr_conturi + 1];
        this->conturi[this->nr_conturi] = c;
        this->nr_conturi++;
    }
    this->total_cash += this->conturi[this->nr_conturi - 1].getSold();
    return *this;
}


bool client::operator<(const client& c) const
{
    return this->total_cash<c.total_cash;
}

const cont& client::operator[](int idx) const
{
    if (this->nr_conturi != 0 && idx >= 0 && idx < this->nr_conturi)
        return this->conturi[idx];
    if (this->nr_conturi == 0)
        cout<<"Nu exista niciun cont asociat.\n";
    else
        if (idx < 0 || idx >= this->nr_conturi)
        cout<<"Index invalid.\n";
    return cont();
}

/// Setteri si getteri:

void client::setNume(string n)
{
    this->nume = n;
}

void client::setPrenume(string p)
{
    this->prenume = p;
    if (this->initiale)
        delete[] this->initiale;
    this->nr_initiale = 1;
    this->initiale = new char[10];
    this->initiale[0] = this->prenume[0];
    int poz = this->prenume.find("-");
    while(poz != -1)
    {
        this->nr_initiale += 1;
        this->initiale[nr_initiale - 1] = this->prenume[poz + 1];
        poz = prenume.find("-", poz + 1);
    }
}

void client::setVenit_anual(double v)
{
    this->venit_anual = v;
}

void client::setTotal_cash(double s)
{
    this->total_cash += s;
}

void client::setStart_date(const data& d)
{
    this->start_date = d;
}

void client::setCetatenii(string* s, int n)
{
    if (this->cetatenie) // Dezalocare
        delete[] this->cetatenie;
    if (n != 0)
    {
        this->cetatenie = new string[n]; // Alocare noua
        for(int i = 0; i < n; ++i)
            this->cetatenie[i] = s[i];
    }
    this->nr_cetatenii = n;
}

void client::setInitiala_tata(char t)
{
    this->initiala_tatalui = t;
}

void client::setVenit_lunar(float* t)
{
    // nu dealoc memoria pt ca oricum tot 12 o sa fie dimensiunea
    if (!(this->venit_lunar))
        this->venit_lunar = new float[12];
    for (int i = 0; i < 12; ++i)
        this->venit_lunar[i] = t[i];
}


void client::setConturi(int nr, const cont* c)
{
    if (this->conturi) // Dezalocare
        delete[] this->conturi;
    if (nr != 0)
    {
        this->conturi = new cont[nr]; // Alocare noua
        for(int i = 0; i < nr; ++i)
            this->conturi[i] = c[i];
    }
    this->nr_conturi = nr;
}

cont& client::getCont(int index) const
{
    return this->conturi[index];
}

int client::getId_client() const
{
    return this->id_client;
}

int client::getNr_conturi() const
{
    return this->nr_conturi;
}

string client::getNume() const
{
    return this->nume;
}

string client::getPrenume() const
{
    return this->prenume;
}

int client::getCNP() const
{
    return this->CNP;
}

double client::getTotal_cash() const
{
    return this->total_cash;
}


/// Altele:
string client::intToString3(const int x)
{
    int n = 0, k = x;
    while (k)
    {
        n++;
        k/=10;
    }
    if (n < 3)
    {
        int m  = 2;
        char* aux = new char[m + 1];
        k = x;
        int cont = 0;
        for (int i = 0; i < m + 1 - n; ++i)
            aux[i] = char(48);
        while(k)
        {
            int aj = k % 10;
            aux[m - cont] = char(48+aj);
            cont++;
            k/=10;
        }
        string f = "";
        f += aux;
        return f;
    }
    else
    {
        char* aux = new char[n];
        n -= 1;
        k = x;
        int cont = 0;
        while(k)
        {
            int aj = k % 10;
            aux[n - cont] = char(48+aj);
            cont++;
            k/=10;
        }
        string f = "";
        f += aux;
        return f;
    }
}

string client::ibanGen()
{
    string newIban;
    if (cetatenie)
    {
        newIban += cetatenie[0][0];
        newIban += toupper(cetatenie[0][1]);
    }
    else newIban = "RO";
    newIban += this->intToString3(id_client);
    newIban += this->intToString3(rand()%100);
    if (initiale != NULL)
    {
        newIban += initiale[0];
        if (isalpha(initiale[1]))
            newIban += initiale[1];
    }
    else newIban += "AA";
    return newIban;
}

void client::addCont()
{
    if (this->nr_conturi > 0)
    {
        cont* aux = new cont[this->nr_conturi];
        for(int i = 0; i < this->nr_conturi; ++i)
            aux[i] = this->conturi[i];
        delete[] this->conturi;
        this->conturi = new cont[this->nr_conturi + 1];
        for (int i = 0; i < nr_conturi; ++i)
            this->conturi[i] = aux[i];
        this->conturi[this->nr_conturi] = cont(0, this->ibanGen(),this->id_client);
        this->nr_conturi++;
        delete[] aux;
    }
    else
    {
        this->conturi = new cont[this->nr_conturi + 1];
        this->conturi[nr_conturi] = cont(0, this->ibanGen(), this->id_client);
        this->nr_conturi++;
    }
}

void client::addCont(const cont& c)
{
    if (this->conturi != NULL)
    {
        cont* aux = new cont[this->nr_conturi];
        for(int i = 0; i < this->nr_conturi; ++i)
            aux[i] = this->conturi[i];
        delete[] this->conturi;
        this->conturi = new cont[this->nr_conturi + 1];
        for (int i = 0; i < nr_conturi; ++i)
            this->conturi[i] = aux[i];
        this->conturi[this->nr_conturi] = c;
        this->nr_conturi++;
        delete[] aux;
    }
    else
    {
        this->conturi = new cont[this->nr_conturi + 1];
        this->conturi[this->nr_conturi] = c;
        this->nr_conturi++;
    }
    this->total_cash += this->conturi[nr_conturi - 1].getSold();
}

void client::removeCont(int idx)
{
    if (this->nr_conturi < idx || idx < 0)
        cout<<"Index invalid.\n";
    else
    {
        cont* aux = new cont[this->nr_conturi - 1];
        int i_aux = 0;
        for (int i = 0; i < idx; ++i)
        {
            aux[i_aux] = this->conturi[i];
            i_aux ++;
        }
        for (int i = idx + 1; i < this->nr_conturi; ++i)
        {
            aux[i_aux] = this->conturi[i];
            i_aux ++;
        }
        delete[] this->conturi;
        this->conturi = new cont[this->nr_conturi - 1];
        for (int i = 0; i < this->nr_conturi - 1; ++i)
            this->conturi[i] = aux[i];
        this->nr_conturi --;
    }
}

void client::afisareZileMembru()
{
    data azi;
    cout<<"Clientul "<<this->nume<< " " << this->prenume<<" este membru de: "<<azi-this->start_date<<" zile.\n";
}

void client::realizareTranzactie()
{
    system("CLS");
    cout<<"\n\t\t\t\t"<<char(254)<<"    Realizare tranzactie de catre client    "<<char(254)<<"\t\t\t\t\n";
    if (this->nr_conturi > 0)
    {
        int opt;
        do
        {
            cout<<"\nSunt disponibile "<<this->nr_conturi<<" conturi pentru a realiza o tranzactie.\n";
            cout<<"\nApasati 1 pentru a vedea conturile.\nApasati 2 daca doriti sa selectati un cont.\nApasati 0 daca doriti sa renuntati.\n";
            cin>>opt;
            if (opt == 1)
            {
                cout<<"\n";
                for (int i = 0; i < this->nr_conturi; ++i)
                {
                    cout<<"----------------------"<<i+1<<"----------------------\n";
                    cout<<this->conturi[i];
                    cout<<"\n";
                }
            }

        }while(opt!= 0 && opt!= 2);
        if (opt == 2)
        {
            system("CLS");
            cout<<"\n\t\t\t\t"<<char(254)<<"    Realizare tranzactie de catre client    "<<char(254)<<"\t\t\t\t\n";
            int c;
            bool ok = false;
            do
            {
                cout<<"\nIntroduceti numarul de ordine al contului pe care vreti sa il folositi: ";
                cin>>c;
                if (c <= 0 || c > this->nr_conturi)
                    cout<<"\n Numar de ordine invalid incercati din nou.\n";
                else
                {
                    this->total_cash += this->conturi[c-1].nouTranzactie();
                    system("CLS");
                    cout<<"\n\t\t\t\t"<<char(254)<<"    Realizare tranzactie de catre client    "<<char(254)<<"\t\t\t\t\n";
                    cout<<"Tranzactie reusita.\n";
                    cout<<*this;
                    ok = true;
                }
            }while(!ok);
        }
    }
    else
        cout<<"Nu este disponibil niciun cont pentru a realiza o tranzactie.\n";
    cout << "debug finished";
}

/// Constructori si destructor:
int client::counter_id_client = 0;

client::client(int i, long c):id_client(i), CNP(c)
{
    this->nume = "";
    this->prenume = "";
    this->initiale = NULL;
    this->initiala_tatalui = ' ';
    this->nr_cetatenii = 0;
    this->cetatenie = NULL;
    this->venit_anual = 0;
    this->venit_lunar = NULL;
    this->nr_conturi = 0;
    this->conturi = NULL;
    this->total_cash = 0;
}

client::client(const client& c):id_client(c.id_client), CNP(c.CNP)
{
    this->nume = c.nume;
    this->prenume = c.prenume;
    this->nr_initiale = c.nr_initiale;
    this->initiale = c.initiale;
    this->initiala_tatalui = c.initiala_tatalui;
    this->nr_cetatenii = c.nr_cetatenii;
    this->cetatenie = c.cetatenie;
    this->venit_anual = c.venit_anual;
    this->nr_conturi = c.nr_conturi;
    this->conturi = c.conturi;
    this->total_cash = c.total_cash;
}

client::client():id_client(++counter_id_client), CNP(0)
{
    this->nume = "";
    this->prenume = "";
    this->initiale = NULL;
    this->initiala_tatalui = ' ';
    this->nr_cetatenii = 0;
    this->cetatenie = NULL;
    this->venit_anual = 0;
    this->venit_lunar = NULL;
    this->nr_conturi = 0;
    this->conturi = NULL;
    this->total_cash = 0;
}

client::client(long codNP):id_client(++counter_id_client),CNP(codNP)
{
    this->nume = "";
    this->prenume = "";
    this->initiale = NULL;
    this->initiala_tatalui = ' ';
    this->nr_cetatenii = 0;
    this->cetatenie = NULL;
    this->venit_anual = 0;
    this->venit_lunar = NULL;
    this->nr_conturi = 0;
    this->conturi = NULL;
    this->total_cash = 0;
}

client::client(long codNP, string nume, string prenume, data d,
               char initialaT, int nrcetat, string* cetat,
               double venit, float* venitl, int nr_cont, cont* c):id_client(++counter_id_client),CNP(codNP), total_cash(0)
{
    this->nume = nume;
    this->prenume = prenume;
    this->start_date = d;
    this->initiale = new char[10];
    this->initiale[0] = this->prenume[0];
    this->nr_initiale = 1;
    int poz = prenume.find("-");
    while(poz != -1)
    {
        this->nr_initiale += 1;
        this->initiale[nr_initiale - 1] = this->prenume[poz + 1];
        poz = prenume.find("-", poz + 1);
    }
    this->initiala_tatalui = initialaT;
    this->nr_cetatenii = nrcetat;
    this->cetatenie = new string[nr_cetatenii];
    for (int i = 0; i < this->nr_cetatenii; ++i)
        this->cetatenie[i] = cetat[i];
    this->venit_anual = venit;
    this->venit_lunar = NULL;
    this->nr_conturi = nr_cont;
    this->conturi = new cont[this->nr_conturi];
    for (int i = 0; i < this->nr_conturi; ++i)
        this->conturi[i] = c[i];
    this->total_cash = 0;
    for (int i = 0; i < this->nr_conturi; ++i)
        this->total_cash += this->conturi[i].getSold();
}

client::client(long codNP, string nume, string prenume, data d,
               char initialaT, int nrcetat, string* cetat,
               double venit, float* venitl):id_client(++counter_id_client),CNP(codNP),total_cash(0)
{
    this->nume = nume;
    this->prenume = prenume;
    this->start_date = d;
    this->initiale = NULL;
    this->nr_initiale = 0;
    this->initiala_tatalui = initialaT;
    this->nr_cetatenii = nrcetat;
    this->cetatenie = new string[nr_cetatenii];
    for (int i = 0; i < this->nr_cetatenii; ++i)
        this->cetatenie[i] = cetat[i];
    this->cetatenie = cetat;
    this->venit_anual = venit;
    this->venit_lunar = NULL;
    this->nr_conturi = 0;
    this->conturi = NULL;
}

client::~client()
{
    if (this->initiale != NULL)
        delete[] this->initiale;
    if (this->cetatenie != NULL)
        delete this->cetatenie;
    if (this->venit_lunar != NULL)
        delete[] this->venit_lunar;
    if (this->conturi != NULL)
        delete this->conturi;
    this->nume = "";
}



// interfata
class banca
{
public:
    virtual void afisareWelcome() // metoda virtuala
    {
        cout << "\n\t\t\t\t Bun venit!\n";
        cout << "\n\tAstazi este: " << data() << "\n";
        cout << "\n";
    }
    virtual void afisareDetalii() = 0; // metoda virtuala pura
    virtual void afisareOptiuni() = 0;// metoda virtuala pura
    virtual void afisareConectare() = 0;// metoda virtuala pura
    virtual void afisareGoodbye() // metoda virtuala
    {
        cout << "\n\t\t\t\t O zi frumoasa!\n";
    }
    virtual void apasatiRevenire() // metoda virtuala
    {
        cout << "Apasati 0 pentru a reveni.\n";
        char no;
        cin >> no;
    }
};

class userBase:public banca // clasa abstracta
{
protected:
    string username;
    string password;
    string email;
    bool is_connected;
    void conectare(string usern, string pass)
    {
        if (this->checkUsername(usern) && this->checkPassword(pass))
        {
            this->is_connected = true;
        }
        else
            this->is_connected = false;
    }
public:
    string getUsername()
    {
        return this->username;
    }
    string getPassword()
    {
        return this->password;
    }
    string getEmail()
    {
        return this->email;
    }
    virtual void describeUser()
    {
        cout << "this is not yet an user\n";
    }
    virtual void afisareManagerConturi() = 0;// metoda virtuala pura
    virtual void afisareConturi() = 0;// metoda virtuala pura
    virtual void afisareAdaugaCont() = 0;// metoda virtuala pura
    virtual void afisareStergereCont() = 0;// metoda virtuala pura
    bool checkPassword(string check_pass)
    {
        if (this->password.size() != check_pass.size())
            return 0;
        if (this->password == check_pass)
            return 1;
        return 0;
    }
    bool checkUsername(string check_usern)
    {
        if (this->username.size() != check_usern.size())
            return 0;
        if (this->username == check_usern)
            return 1;
        return 0;
    }
    userBase& operator=(const userBase& ad)
    {
        if (this != &ad)
        {
            this->username = ad.username;
            this->password = ad.password;
            this->email = ad.email;
        }
        return *this;
    }
    userBase():is_connected(0)
    {
        this->username = "none";
        this->password = "none";
        this->email = "none";
    }
    userBase(string u, string p, string e):is_connected(0)
    {
        this->username = u;
        this->password = p;
        this->email = e;
    }
    userBase(const userBase& c):is_connected(0)
    {
        this->username = c.username;
        this->password = c.password;
        this->email = c.email;
    }
    ~userBase()
    {

    }
};


int numberOfUsers = 0;


class utilizator: public client, public userBase
{
protected:
    void afisareConturi()
    {
        int option = -1;
        while (option != 0)
        {
            system("CLS");
            cout << "\n\t\t" << char(254) << "  Afisare conturi  " << char(254) << "\n";
            cout << "Sunt: " << this->getNr_conturi() << " disponibile pentru afisare.\n";
            cout << "Alegeti indexul unui dintre conturi pentru afisare sau 0 pentru iesire din meniu.\n";
            cout << "Index: ";

            cin >> option;
            if (option != 0)
            {
                if (option >= 1 && option <= this->getNr_conturi())
                {
                    cout << this->getCont(option - 1);
                    this->apasatiRevenire();
                }
                else
                {
                    cout << "Ati introdus un index gresit. Contul cerut nu exista.\n";
                    this->apasatiRevenire();
                }
            }
        }
    }
    void afisareAdaugaCont()
    {
        int option = -1;
        while (option != 0)
        {
            system("CLS");
            cout << "\n\t\t" << char(254) << "  Adaugare cont  " << char(254) << "\n";
            cout << "(1) Cont initializat automat.\n(2) Cont initializat manual.\n(0) Iesire.\n";
            cout << "Alegeti o optiune\n";
            cin >> option;
            if (option != 0)
            {
                if (option == 1)
                {
                    this->addCont();
                    cout << "\n Contul a fost adaugat cu succes.\n";
                    this->apasatiRevenire();
                }
                else if (option == 2)
                {
                    cont newCont;
                    cin >> newCont;
                    this->addCont(newCont);
                    cout << "\n Contul a fost adaugat cu succes.\n";
                    this->apasatiRevenire();
                }
                else
                {
                    cout << "Ati introdus un index gresit. Contul cerut nu exista.\n";
                    this->apasatiRevenire();
                }
            }
        }
    }
    void afisareStergereCont()
    {
        int option = -1;
        while (option != 0)
        {
            system("CLS");
            cout << "\n\t\t" << char(254) << "  Stergere cont  " << char(254) << "\n";
            cout << "Sunt: " << this->getNr_conturi() << " disponibile pentru stergere.\n";
            cout << "Alegeti indexul unui dintre conturi pentru stergere sau 0 pentru iesire din meniu.\n";
            cout << "Index: ";
            cin >> option;
            if (option != 0)
            {
                if (option >= 1 && option <= this->getNr_conturi())
                {
                    cout << "Va avertizam, contul sters nu poate fi recuperat. Doriti sa continuati cu operatiunea de stergere? (1) DA  (0) NU      ";
                    int validare;
                    cin >> validare;
                    if (validare == 1)
                    {
                        this->removeCont(option - 1);
                        cout << "\nContul a fost sters.\n";
                        this->apasatiRevenire();
                    }
                    else this->apasatiRevenire();
                }
                else
                {
                    cout << "Ati introdus un index gresit. Contul cerut nu exista.\n";
                    this->apasatiRevenire();
                }
            }
        }
    }

public:
    void afisareWelcome() // suprascrierea functiei virtuale din userBase
    {
        cout << "\n\t\t\t\t Bun venit " << this->username << "!\n";
        cout << "\n\tAstazi este: " << data() << "\n";
        cout << "\n";
    }
    void changeStatus()
    {
        this->is_connected = !(this->is_connected);
    }
    void changePassword(string newpass)
    {
        this->password = newpass;
    }
    void changeUsername(string newusername)
    {
        this->username = newusername;
    }
    void changeEmail(string newe)
    {
        this->email = newe;
    }
    void afisareManagerConturi()
    {
        int option = -1;
        while(option != 0)
        {
            system("CLS");
            cout << "\n(1) Vizualizare conturi.\n(2) Adaugare cont.\n(3) Stergere cont.\n(0) Iesire.\n";
            cin >> option;
            switch(option)
            {
                case 1: this->afisareConturi(); break;
                case 2: this->afisareAdaugaCont(); break;
                case 3: this->afisareStergereCont(); break;
                case 0: cout << "\n Iesiti din meniul de administrare conturi.\n"; break;
                default:
                    {
                        cout <<"\nOptiune introdusa gresit.\n";
                        this->apasatiRevenire();
                        break;
                    }
            }
        }
    }
    void afisareConectare()
    {
        system("CLS");
        if (this->is_connected == true)
        {
            cout << "\nUtilizator deja conectat.";
            this->apasatiRevenire();
        }
        else
        {
            cout << "\nIncercare conectare la utilizatorul cu numele: " << this -> username << "\n";
            cout << "Introduceti parola: ";
            string p_aux;
            cin >> p_aux;
            this->conectare(this->username, p_aux);
            if (this -> is_connected == true)
            {
                cout << "\nConectare reusita!\n";
                this->afisareOptiuni();
            }
            else cout << "\nConectare esuata!\n";
            this->apasatiRevenire();
        }
    }
    void tryConectare(string user, string pas)
    {
        if (this->is_connected == true)
        {
            cout << "\nUtilizator deja conectat.";
            this->apasatiRevenire();
        }
        else
        {
            cout << "\nIncercare conectare la utilizatorul cu numele: " << user << "\n";
            this->conectare(user, pas);
            if (this -> is_connected == true)
            {
                cout << "\nConectare reusita!\n";
                this->afisareOptiuni();
                this->is_connected = false;
            }
            else cout << "\nConectare esuata!\n";
            this->apasatiRevenire();
        }
    }
    void describeUser() // suprascrierea functiei virtuale din userBase
    {
        cout << "\nAcest utilizator este un client al bancii.\n";
    }
    void afisareDetalii()
    {
        system("CLS");
        cout << "\n\t\t Detalii utilizator: \n";
        cout << "Nume de utilizator: " << this->username << "\n";
        cout << "Parola: ";
        for (int i = 0; i < this->password.size(); ++i)
            cout << "*";
        if (this -> is_connected == false)
        {
            cout << "\nPentru a vizualiza parola si email-ul este necesara conectare.\n";
            cout << "Doriti sa va conectati? -> introduceti 1 pentru DA, 0 pentru NU\n";
            int con_aux;
            cin >> con_aux;
            if (con_aux == 1)
            {
                afisareConectare();
            }
        }
        else
        {
            cout << "\nPentru a vizualiza parola si email-ul introduceti 1, altfel 0.\n";
            int con_aux;
            cin >> con_aux;
            if (con_aux == 1)
            {
                cout << "\nParola: " << this->password << endl;
                cout << "Email: " << this->email << endl;
                this->apasatiRevenire();
            }
        }
    }
    void afisareOptiuni()
    {
        int option = -1;
        while(option != 0)
        {
            system("CLS");
            this->afisareWelcome();
            for (int i = 0; i <= 6; ++i)
            {
                cout <<"(" << i<<") ";
                switch(i)
                {
                case 1: cout << "Afisare detalii despre utilizator.\n"; break;
                case 2: cout << "Conectare.\n"; break;
                case 3: cout << "Vizualizare detalii despre client.\n"; break;
                case 4: cout << "Administrare conturi.\n"; break;
                case 5: cout << "Realizare tranzactie.\n"; break;
                case 6: cout << "Schimbare parola.\n"; break;
                case 0: cout << "Iesire.\n"; break;
                }
            }
            cout << "\nIntroduceti o optiune: ";
            cin >> option;
            switch(option)
            {
            case 1: this->afisareDetalii(); break;
            case 2: this->afisareConectare(); break;
            case 3:
                {
                    if (this -> is_connected == false)
                    {
                        cout << "\nEste necesara conectarea.\n";
                        this->apasatiRevenire();
                        break;
                    }
                    else
                    {
                        cout << (client&)*this;
                        this->apasatiRevenire();
                        break;
                    }
                }
            case 4:
                {
                    if (this -> is_connected == false)
                    {
                        cout << "\nEste necesara conectarea.\n";
                        this->apasatiRevenire();
                        break;
                    }
                    else
                    {
                        this->afisareManagerConturi();
                        break;
                    }
                }
            case 5:
                {
                    if (this -> is_connected == false)
                    {
                        cout << "\nEste necesara conectarea.\n";
                        this->apasatiRevenire();
                        break;
                    }
                    else
                    {
                        if (this->getNr_conturi() == 0)
                        {
                            cout << "\nTranzactia nu poate fi efectuata: niciun cont deschis.";
                            this->apasatiRevenire();
                            break;
                        }
                        this->realizareTranzactie();
                        break;
                    }
                }
            case 6:
                {
                    if (this -> is_connected == false)
                    {
                        cout << "\nEste necesara conectarea.\n";
                        this->apasatiRevenire();
                        break;
                    }
                    else
                    {
                        cout << "\nIntroduceti parola noua: ";
                        string neww;
                        cin >> neww;
                        cout << "Confirmati schimbarea parolei? (1) DA  (0) NU  \n";
                        int confirm;
                        cin >> confirm;
                        if (confirm == 1)
                        {
                            this->changePassword(neww);
                            cout << "\nParola schimbata cu succes.\n";
                            this->apasatiRevenire();
                        }
                        else this->apasatiRevenire();
                        break;
                    }
                }
            case 0: this->afisareGoodbye(); break;
            default:
                    {
                        cout <<"\nOptiune introdusa gresit.\n";
                        this->apasatiRevenire();
                        break;
                    }
            }
        }
    }

    friend ostream& operator<<(ostream&, utilizator&);
    utilizator(): client(),userBase()
    {
    }
    utilizator(string u, string p, string e): client(),userBase(u, p, e)
    {
    }
    utilizator(string u, string p, string e, long codNP, string nume, string prenume, data d,
               char initialaT, int nrcetat, string* cetat,
               double venit, float* venitl): client(codNP, nume, prenume, d, initialaT, nrcetat, cetat, venit, venitl),userBase(u, p, e)
    {
}
    utilizator(const utilizator& c): client(c),userBase(c)
    {
    }
    ~utilizator()
    {

    }
};

ostream& operator <<(ostream& out, utilizator& u)
{
    u.describeUser();
    out << "Nume de utilizator: " << u.username << "\n";
    out << "Email: " << u.email << endl;
    return out;
}

template <class A, class B, class C>
class trio
{
public:
    A first;
    B second;
    C third;
    trio(A f, B s, C t):first(f), second(s), third(t)
    {}
    trio()
    {}
};


list <utilizator> users;
map <string, trio<char, string, string>> conectare_DB;
set <pair<string, string>> nume_prenume_clienti;
int anonim_clients_nr = 0;

class admin: public userBase
{
protected:
    void accesUtiliz(auto acc)
    {
        acc->changeStatus();
        acc->afisareDetalii();
        acc->afisareOptiuni();
        acc->changeStatus();
    }
public:
    friend ostream& operator <<(ostream& out, admin& u)
    {
        u.describeUser();
        out << "Nume de utilizator: " << u.username << "\n";
        out << "Email: " << u.email << endl;
        return out;
    }
    void afisareDetalii()
    {
        system("CLS");
        cout << "\n\t\t Detalii utilizator: \n";
        this->describeUser();
        cout << "Nume de utilizator: " << this->username << "\n";
        cout << "Parola: ";
        for (int i = 0; i < this->password.size(); ++i)
            cout << "*";
        if (this -> is_connected == false)
        {
            cout << "\nPentru a vizualiza parola si email-ul este necesara conectare.\n";
            cout << "Doriti sa va conectati? -> introduceti 1 pentru DA, 0 pentru NU\n";
            int con_aux;
            cin >> con_aux;
            if (con_aux == 1)
            {
                afisareConectare();
            }
        }
        else
        {
            cout << "\nPentru a vizualiza parola si email-ul introduceti 1, altfel 0.\n";
            int con_aux;
            cin >> con_aux;
            if (con_aux == 1)
            {
                cout << "\nParola: " << this->password << endl;
                cout << "Email: " << this->email << endl;
                this->apasatiRevenire();
            }
        }
    }
    void afisareOptiuni()
    {
        int option = -1;
        while(option != 0)
        {
            system("CLS");
            this->afisareWelcome();
            for (int i = 0; i <= 4; ++i)
            {
                cout <<"(" << i<<") ";
                switch(i)
                {
                case 1: cout << "Afisare detalii despre utilizator.\n"; break;
                case 2: cout << "Conectare.\n"; break;
                case 3: cout << "Modificare utilizatori.\n"; break;
                case 4: cout << "Realizare tranzactie fara cont.\n"; break;
                case 0: cout << "Iesire.\n"; break;
                }
            }
            cout << "\nIntroduceti o optiune: ";
            cin >> option; // try to do error catcher not int etc
            switch(option)
            {
            case 1: this->afisareDetalii(); break;
            case 2: this->afisareConectare(); break;
            case 3:
                {
                    if (this -> is_connected == false)
                    {
                        cout << "\nEste necesara conectarea.\n";
                        this->apasatiRevenire();
                        break;
                    }
                    else
                    {
                        this->afisareManager();
                        this->apasatiRevenire();
                        break;
                    }
                }
            case 4:
                {
                    if (this -> is_connected == false)
                    {
                        cout << "\nEste necesara conectarea.\n";
                        this->apasatiRevenire();
                        break;
                    }
                    else
                    {
                        tranzactie nou;
                        cin >> nou;
                        cout << "\nTranzactie reusita.\n";
                        cout << nou;
                        this->apasatiRevenire();
                    }
                }
            case 0: this->afisareGoodbye(); break;
            default:
                    {
                        cout <<"\nOptiune introdusa gresit.\n";
                        this->apasatiRevenire();
                        break;
                    }
            }
        }
    }
    void afisareConectare()
    {
        system("CLS");
        if (this->is_connected == true)
        {
            cout << "\nUtilizator deja conectat.";
            this->apasatiRevenire();
        }
        else
        {
            cout << "\nIncercare conectare la utilizatorul cu numele: " << this -> username << "\n";
            cout << "Introduceti parola: ";
            string p_aux;
            cin >> p_aux;
            this->conectare(this->username, p_aux);
            if (this -> is_connected == true)
                cout << "\nConectare reusita!\n";
            else cout << "\nConectare esuata!\n";
            this->apasatiRevenire();
        }
    }
    void tryConectare(string user, string pas)
    {
        if (this->is_connected == true)
        {
            cout << "\nUtilizator deja conectat.";
            this->apasatiRevenire();
        }
        else
        {
            cout << "\nIncercare conectare la utilizatorul cu numele: " << user << "\n";
            this->conectare(user, pas);
            if (this -> is_connected == true)
            {
                cout << "\nConectare reusita!\n";
                this->afisareOptiuni();
            }
            else cout << "\nConectare esuata!\n";
            this->apasatiRevenire();
        }
    }
    void describeUser() // suprascrierea functiei virtuale din userBase
    {
        cout << "\nUser de tip admin.\n";
    }
    void afisareManagerConturi() // suprascrierea functiei virtuale din userBase
    {
        cout << "\nAdmin nu are conturi deschise de administrat.\n";
    }
    void afisareManager()
    {
        int option = -1;
        while (option != 0)
        {
            system("CLS");
            cout << "\n\t\tModificare utilizatori\n";
            cout << "\nNr de utilizatori: " << users.size() << endl;
            cout << "Alegeti un index pt utilizatori: ";
            int index;
            cin >> index;
            if (index == 0)
                option = 0;
            else if (index != 0)
            {
                if (index > users.size() || index <= 0)
                {
                    cout << "Index introdus gresit.\n";
                    this ->apasatiRevenire();
                }
                else
                {
                    std::list<utilizator>::iterator k;
                    for (auto i = users.begin(); i != users.end() && index > 0; ++i)
                    {
                        index--;
                        k = i;
                    }
                    cout << *k;
                    cout << "\nExecutati modificari din contul descris? (1) DA  (0) NU\n";
                    int opt;
                    cin >> opt;
                    if (opt == 1)
                    {
                        this->accesUtiliz(k);
                        this->apasatiRevenire();
                    }
                    else
                        this ->apasatiRevenire();
                }
            }
        }

    }
    void afisareConturi()
    {
        cout << "\nNu sunt conturi de afisat.\n";
    }
    void afisareAdaugaCont()
    {
        cout << "\nNu se pot adauga conturi.\n";
    }
    void afisareStergereCont()
    {
        cout << "\nNu se pot sterge conturi.\n";
    }
    admin():userBase()
    {

    }
    admin(string u, string p, string e):userBase(u, p, e)
    {
    }
    admin(const admin& a):userBase(a)
    {
    }
    ~admin()
    {
    }
};

class Exceptie: public exception
{
public:
    virtual const char* what() const throw()
    {
        return "An error has occurred.\n";
    }
}eroare;

vector <admin> admins;

void reads()
{
    ifstream read ("readUsers.txt");
    string type;
    try
    {
        while (read >> type)
        {
            if (type == "A")
            {
                string auxUn, auxP, auxE;
                read >> auxUn >> auxP >> auxE;
                if (conectare_DB.find(auxUn) != conectare_DB.end())
                {
                    feedback << "Username already in system.\n";
                    throw eroare;
                }
                conectare_DB[auxUn] = trio<char, string, string>('A', auxP, auxE);
                admin aux(auxUn, auxP, auxE);
                admins.push_back(aux);
            }
            else if (type == "U")
            {
                string auxUn, auxP, auxE, arecont;
                read >> auxUn >> auxP >> auxE >> arecont;
                if (conectare_DB.find(auxUn) != conectare_DB.end())
                {
                    feedback << "Username already in system.\n";
                    throw eroare;
                }
                conectare_DB[auxUn] = trio<char, string, string>('U', auxP, auxE);
                if (arecont == "-")
                {
                    utilizator aux(auxUn, auxP, auxE);
                    users.push_front(aux);
                    nume_prenume_clienti.insert(pair<string, string>("anonim", "anonim"));
                }
                else
                {
                    data auxDstart;
                    string auxNume, auxPrenume;
                    long auxCNP;
                    char auxIT;
                    int auxNrcet;
                    double auxVenit;
                    float* auxVenitLunar = new float[12];
                    read >> auxCNP >> auxNume >> auxPrenume;
                    nume_prenume_clienti.insert(pair<string, string>(auxNume, auxPrenume));

                    streambuf *old = cout.rdbuf();
                    cout.rdbuf(0);
                    read >> auxDstart;
                    cout.rdbuf(old);

                    read >> auxIT >> auxNrcet;

                    string* auxCetat = NULL;
                    if (auxNrcet != 0)
                    {
                        auxCetat = new string[auxNrcet];
                        for (int i = 0; i < auxNrcet; ++i)
                            read >> auxCetat[i];
                    }
                    read >> auxVenit;
                    for (int i = 0; i < 12; ++i)
                        read >> auxVenitLunar[i];

                    utilizator aux(auxUn, auxP, auxE, auxCNP, auxNume, auxPrenume, auxDstart, auxIT, auxNrcet, auxCetat, auxVenit, auxVenitLunar);

                    int aux_Nrconturi;
                    read >> aux_Nrconturi;

                    if (aux_Nrconturi != 0)
                    {
                        for (int j = 0; j < aux_Nrconturi; ++j)
                        {
                            double readSold;
                            string readIBAN;
                            int readNrCard;
                            read >> readSold >> readIBAN >> readNrCard;
                            string* readCard = NULL;
                            if (readNrCard != 0)
                            {
                                readCard = new string[readNrCard];
                                for (int i = 0; i < readNrCard; ++i)
                                    read >> readCard[i];
                            }
                            float readDob;
                            read >> readDob;
                            if (readDob == 0)
                                readDob = 0.12;

                            int aux_NrTranz;
                            read >> aux_NrTranz;
                            tranzactie *aux_Ist = NULL;


                            if (aux_NrTranz != 0)
                            {
                                aux_Ist = new tranzactie[aux_NrTranz];
                                streambuf *old1 = cout.rdbuf();
                                cout.rdbuf(0);

                                for (int i = 0; i < aux_NrTranz; ++i)
                                    read >> aux_Ist[i];

                                cout.rdbuf(old1);
                            }

                            float* helper = NULL;

                            cont auxToAdd(readSold, readIBAN, readNrCard, readCard, readDob, 0, helper, helper, aux_NrTranz, aux_Ist, aux.getId_client());
                            aux.addCont(auxToAdd);
                        }
                    }
                    users.push_front(aux);
                }
            }
            else throw eroare;
        }
        feedback << "Read users successful.\n";
        cout << "Fisierul a fost citit cu succes.\n";
    }
    catch (Exceptie& e)
    {
        feedback << "An error has occurred while reading users.\n";
        cout << "Este o problema cu fisierul de citire 'readUsers.txt'.\n";
    }
}

void prints()
{
    streambuf *old = cout.rdbuf();
    cout.rdbuf(0);
    if (!admins.empty())
    {
        print << "Administratori: \n";
        for (auto i = admins.begin(); i != admins.end(); ++i)
            print <<*i;
    }
    if (!users.empty())
    {
        print << "\nUtilizatori: \n";
        for (auto i = users.begin(); i != users.end(); ++i)
            print << *i;
    }
    cout.rdbuf(old);
    if (!nume_prenume_clienti.empty())
    {
        print << "\nNume si prenume clienti banca: \n";
        for (auto i = nume_prenume_clienti.begin(); i != nume_prenume_clienti.end(); ++i)
            print << i->first << " " << i->second << "\n";
    }
    feedback << "Printed users successful.\n";
}

void creare()
{
    cout << "\nCreare user"
        << "\nAlegeti tipul de user: 1.Utilizator 2.Admin 0.Iesire";
    int user_type;
    try
    {
        cin >> user_type;
        if (user_type == 0)
            return;
        switch(user_type)
        {
        case 1:
            {
                try
                {
                    string user_username, user_password, user_email;
                    cout << "\nUsername: ";
                    cin >> user_username;
                    cout << "\nPassword: ";
                    cin >> user_password;
                    cout << "\nEmail: ";
                    cin >> user_email;

                    if (conectare_DB.find(user_username) != conectare_DB.end())
                    {
                        feedback << "Username already in system.\n";
                        throw eroare;
                    }

                    utilizator newU(user_username, user_password, user_email);
                    cin >> (client&) newU;
                    conectare_DB[user_username] = trio<char, string, string>('U', user_password, user_email);
                    users.push_back(newU);
                    break;
                }
                catch (Exceptie& e)
                {
                    feedback << "An error has occurred while creating user.\n";
                    cout << "Acest username este deja folosit. Incercati conectare sau alegeti alt username.\n";
                }
                break;
            }
        case 2:
            {
                try
                {
                    string admin_username, admin_password, admin_email;
                    cout << "\nUsername: ";
                    cin >> admin_username;
                    cout << "\nPassword: ";
                    cin >> admin_password;
                    cout << "\nEmail: ";
                    cin >> admin_email;

                    if (conectare_DB.find(admin_username) != conectare_DB.end())
                    {
                        feedback << "Username already in system.\n";
                        throw eroare;
                    }
                    conectare_DB[admin_username] = trio<char, string, string>('A', admin_password, admin_email);
                    admin aux(admin_username, admin_password, admin_email);
                    admins.push_back(aux);
                }
                catch (Exceptie& e)
                {
                    feedback << "An error has occurred while creating user.\n";
                    cout << "Acest username este deja folosit. Incercati conectare sau alegeti alt username.\n";
                }
                break;
            }
        default: throw eroare; break;
        }
    }
    catch (Exceptie& e)
    {
        feedback << "An error has occurred while creating user.\n";
        cout << "Date introduse gresit.\n";
    }
    feedback << "User created successful.\n";
}

pair<char, string> searchingEmail(string email)
{
    for (auto i = conectare_DB.begin(); i != conectare_DB.end(); ++i)
    {
        // username = i->first;
        if (i->second.third == email)
        {
            return pair<char, string>(i->second.first, i->first);
        }
    }
    return pair<char,string>('0',"0");
}

string searchingCNP(long CNP)
{
    for (auto i = users.begin(); i != users.end(); ++i)
    {
        if (i->getCNP() == CNP)
            return i->getUsername();
    }
    return "-";
}

void search()
{
    if (!conectare_DB.empty())
    {
        cout << "\nSelectati criteriul de cautare:";
        cout << "\n1.Nume de utilizator"
            << "\n2. Email" // problem rn
            << "\n3. CNP - pentru utilizatori"
            << "\n0 - Iesire\n";
        int type_search;
        try
        {
            cin >> type_search;
            switch(type_search)
            {
                case 0: return;
                case 1:
                    {
                        cout << "Introduceti numele de utilizator cautat: ";
                        string searching_for_username;
                        cin >> searching_for_username;
                        if (conectare_DB.find(searching_for_username) != conectare_DB.end())
                        {
                            cout << "Utilizatorul " << searching_for_username << " de tipul ";
                            if (conectare_DB.find(searching_for_username)->second.first == 'U')
                                cout <<"client";
                            if (conectare_DB.find(searching_for_username)->second.first == 'A')
                                cout << "administrator";
                            cout << " se afla in sistem.\n";
                        }
                        else
                        {
                            cout << "Utilizatorul " << searching_for_username << " nu se afla in sistem.\n";
                        }
                        break;
                    }
                case 2:
                    {
                        cout << "Introduceti emailul cautat: ";
                        string searching_for_email;
                        cin >> searching_for_email;
                        pair <char, string> search_result = searchingEmail(searching_for_email);
                        if (search_result.first == '0')
                            cout << "Emailul " << searching_for_email << " nu se afla in sistem.\n";
                        else
                        {
                            cout << "Emailul " << searching_for_email << " ii corespunde ";
                            if (search_result.first == 'U')
                                cout << "clientului";
                            else cout << "administratorului";
                            cout <<" cu numele de utilizator " << search_result.second <<".\n";
                        }
                        break;
                    }
                case 3:
                    {
                        cout << "Introduceti CNP-ul cautat: ";
                        long searching_for_CNP;


                        break;
                    }
                default: throw eroare; break;
            }
        }
        catch (Exceptie& e)
        {
            feedback << "An error has occurred while searching for user.\n";
            cout << "Date introduse gresit.\n";
        }
        feedback << "Successful user search.\n";
    }
    else
    {
        feedback << "Empty database nothing to search.\n";
        cout << "Nu exista niciun utilizator in sistem. Incercati citirea/adaugarea de utilizatori.\n";
    }
}

void trying_login_Admins(string username, string password)
{
    for (auto i = admins.begin(); i != admins.end(); ++i)
    {
        if (i->getUsername() == username)
        {
            i->tryConectare(username, password);
            return;
        }
    }
}

void trying_login_Users(string username, string password)
{
    for (auto i = users.begin(); i != users.end(); ++i)
    {
        if (i->getUsername() == username)
        {
            i->tryConectare(username, password);
            return;
        }
    }
}

void conectare()
{
    string username_conect, password_conect;
    cout << "Username:  ";
    cin >> username_conect;
    cout << "Password:  ";
    cin >> password_conect;
    if (conectare_DB.find(username_conect) != conectare_DB.end())
    {
        if (conectare_DB.find(username_conect)->second.first == 'A')
        {
            trying_login_Admins(username_conect, password_conect);
        }
        else
            trying_login_Users(username_conect, password_conect);
    }
    else
    {
        feedback << "Tried to connect to an username not in database.\n";
        cout << "Numele de utilizator nu este in sistem.\n";
    }
}

int main()
{
    feedback << "\n" << data() << " App opened.\n";

    int option = 0;
    do
    {
        //system("CLS");
        cout << "\t\tGestiunea unei banci\n";
        cout << "Optiuni:"
            << "\n 1) Citire utilizatori si administratori din fisierul 'readUsers.txt'"
            << "\n 2) Afisare utilizatori si administratori in fisierul 'printUsers.txt'"
            << "\n 3) Creare user - utilizator sau admin."
            << "\n 4) Cautare user."
            << "\n 5) Conectare";
        cout << "\nPlease enter an option. 0 for exit.\n";

        cin >> option;

        switch(option)
        {
            case 1: reads(); break;
            case 2: prints(); break;
            case 3: creare(); break;
            case 4: search(); break;
            case 5: conectare(); break;
        }

    } while (option != 0);

    ofstream read1 ("export.txt");
    for (auto i = admins.begin(); i != admins.end(); ++i)
    {
        read1 << 'A' << endl;
        read1 << i->getUsername() << endl;
        read1 << i->getPassword() << endl;
        read1 << i->getEmail() << endl;
    }
    for (auto i = users.begin(); i != users.end(); ++i)
    {
        read1 << 'U' << endl;
        read1 << i->getUsername() << endl;
        read1 << i->getPassword() << endl;
        read1 << i->getEmail() << endl;
        if (i->getNume() == "")
            read1 << "-";
        else
        {
            read1 << "1";
            read1 << i->getCNP() << endl;
            read1 << i->getNume() << endl;
            read1 << i->getPrenume() << endl;
        }
    }
    read1.close();
    print.close();
    feedback << "App is closing.\n";
    feedback.close();
    return 0;
}


