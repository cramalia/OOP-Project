#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <cstring>
#include <limits>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

class MateriiPrime
{
	char* denumire = nullptr;
	int cantitate = 0;
public:

	MateriiPrime() {}

	MateriiPrime(const char* denumire, int cantitate)
	{
		if (denumire != nullptr && strlen(denumire) > 0)
		{
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}

		if (cantitate > 0)
			this->cantitate = cantitate;
	}

	MateriiPrime(const MateriiPrime& m)
	{
		if (m.denumire != nullptr && strlen(m.denumire) > 0)
		{
			this->denumire = new char[strlen(m.denumire) + 1];
			strcpy(this->denumire, m.denumire);
		}
		if (m.cantitate > 0)
			this->cantitate = m.cantitate;
	}

	~MateriiPrime() {
		delete[] denumire;
	}

	MateriiPrime& operator=(const MateriiPrime& m)
	{
		if (this != &m)
		{
			delete[] denumire;
			if (m.denumire != nullptr && strlen(m.denumire) > 0)
			{
				this->denumire = new char[strlen(m.denumire) + 1];
				strcpy(this->denumire, m.denumire);
			}
			if (m.cantitate > 0)
				this->cantitate = m.cantitate;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const MateriiPrime& mp)
	{
		if (mp.denumire != nullptr)
		{
			out << mp.denumire << " " << mp.cantitate << "\n";
		}
		else
			out << "Nu are inca nume!\n";
		return out;
	}

	MateriiPrime operator+(int inplus)
	{
		if (inplus > 0)
		{
			MateriiPrime c = *this;
			c.cantitate += inplus;
			return c;
		}
	}

	MateriiPrime& operator++()
	{
		this->cantitate++;
		return *this;
	}
	MateriiPrime operator++(int)
	{
		MateriiPrime copy = *this;
		this->cantitate++;
		return copy;
	}

	MateriiPrime& operator--()
	{
		if (this->cantitate >= 1)
		{
			this->cantitate--;
			return *this;
		}
		else
			cout << "Nu mai este stoc!\n";
	}

	explicit operator int()
	{
		return this->cantitate;
	}

	bool operator!()
	{
		return !(this->cantitate);
	}
	bool operator>(const MateriiPrime& m)
	{
		return this->cantitate > m.cantitate;
	}
	const char* getDenumire()
	{
		return denumire;
	}
	int getCantitate()
	{
		return cantitate;
	}
	void setDenumire(char* denumireNoua)
	{
		if (denumireNoua == nullptr || strlen(denumireNoua) == 0)
		{
			cout << "Numele nu poate fii gol!\n";
		}
		else
		{
			delete[] this->denumire;
			this->denumire = new char[strlen(denumireNoua) + 1];
			strcpy(this->denumire, denumireNoua);
		}
	}
	void setCantitate(int cantitateNoua)
	{
		if (cantitateNoua < 0)
			cout << "Cantitatea trebuie sa fie pozitiva!\n";
	}
	friend istream& operator>>(istream& in, MateriiPrime& m)
	{
		delete[] m.denumire;
		m.denumire = nullptr;
		cout << "\Introduecti denumirea: ";
		char buffer[100];
		in >> buffer;
		in.getline(buffer, sizeof(buffer));
		m.denumire = new char[strlen(buffer) + 1];
		strcpy(m.denumire, buffer);
		cout << "\Introduecti cantitatea: ";
		in >> m.cantitate;
		if (m.cantitate < 0)
			m.cantitate = 0;
		return in;
	}
	friend bool operator==(MateriiPrime& m1, MateriiPrime& m2) {
		return (m1.getDenumire() == m2.getDenumire()) && (m1.getCantitate() == m2.getCantitate());
	}
	void afisare()
	{
		if (this->denumire != nullptr)
			cout << "\nDenumire: " << this->denumire;
		else
			cout << "-";
		cout << "\nCantitate: " << this->cantitate;
	}

	void writeToFile(fstream& f)
	{
		//scriere sir de caractere (char static)
		//scriere lungime
		int lg = strlen(this->denumire) + 1;
		f.write(this->denumire, sizeof(char) * lg);
		//scriere sir de caractere
		f.write(this->denumire, lg);
		//scriere valoare int
		f.write((char*)&this->cantitate, sizeof(int));
	}

	void readFromFile(fstream& f)
	{
		//citire sir de caractere
		//citire lg
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		strcpy(this->denumire, buffer);
		delete[] buffer;
		//citire valori int
		f.read((char*)&this->cantitate, sizeof(int));
	}
};

class Produs
{
	MateriiPrime* materiiprime = nullptr;
	int dimensiune = 0;
	string nume = "";
public:
	Produs() {}
	Produs(MateriiPrime* materiiprime, int dimensiune, string nume)
	{
		if (nume != "")
		{
			this->nume = nume;
		}
		if (materiiprime != nullptr && dimensiune > 0)
		{
			this->dimensiune = dimensiune;
			this->materiiprime = new MateriiPrime[dimensiune];
			for (int i = 0; i < dimensiune; i++)
				this->materiiprime[i] = materiiprime[i];
		}
		else
		{
			this->materiiprime = nullptr;
			this->dimensiune = 0;
		}
	}
	Produs(const Produs& p)
	{
		if (p.nume != "")
		{
			this->nume = p.nume;
		}
		else this->nume = "";
		if (p.materiiprime != nullptr && p.dimensiune > 0)
		{
			this->materiiprime = new MateriiPrime[p.dimensiune];
			for (int i = 0; i < p.dimensiune; i++)
				this->materiiprime[i] = p.materiiprime[i];
			this->dimensiune = p.dimensiune;
		}
		else
		{
			this->materiiprime = nullptr;
			this->dimensiune = 0;
		}
	}
	string getNume()
	{
		return nume;
	}
	void setNume(string numeNou)
	{
		if (numeNou.empty())
		{
			cout << "Numele nu poate fi gol";
		}
		else
			this->nume = numeNou;
	}
	MateriiPrime* getMateriiPrime()
	{
		return this->materiiprime;
	}
	void setMateriiPrime(MateriiPrime* materiiprime, int dimensiune)
	{
		if (this->materiiprime != nullptr)
			delete[] this->materiiprime;
		this->dimensiune = dimensiune;
		this->materiiprime = new MateriiPrime[this->dimensiune];
		for (int i = 0; i < this->dimensiune; i++)
			this->materiiprime[i] = materiiprime[i];
	}
	int getDimensiune()
	{
		return this->dimensiune;
	}
	~Produs()
	{
		if (this->materiiprime != nullptr)
			delete[] this->materiiprime;
	}
	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			if (this->materiiprime != nullptr)
			{
				delete[] this->materiiprime;

			}
		}
		if (p.nume != "")
		{
			this->nume = p.nume;
		}
		else
			this->nume = "";
		if (p.materiiprime != nullptr && p.dimensiune > 0)
		{
			this->dimensiune = p.dimensiune;
			this->materiiprime = new MateriiPrime[p.dimensiune];
			for (int i = 0; i < p.dimensiune; i++)
				this->materiiprime[i] = p.materiiprime[i];
		}
		else
		{
			this->materiiprime = nullptr;
			this->dimensiune = 0;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Produs& p)
	{
		if (p.materiiprime != nullptr)
		{
			out << "Produs: " << p.nume << "\n";
			for (int i = 0; i < p.dimensiune; i++)
				out << p.materiiprime[i];
			out << "\n";
		}
		else out << "\nProdusul inca nu are ingrediente";
		return out;
	}
	void afisare()
	{
		cout << "\n-------------------------------";
		if (this->nume != "")
			cout << "\nNume: " << this->nume;
		else cout << "-";
		cout << "\nNumar ingrediente: " << this->dimensiune;
		cout << "\nIngrediente: ";
		if (this->materiiprime != nullptr)
		{
			for (int i = 0; i < this->dimensiune; i++)
				cout << this->materiiprime[i] << " ";
		}
		else cout << "-";
	}
	void addMateriePrima(MateriiPrime materiiprime)
	{
		MateriiPrime* c = new MateriiPrime[this->dimensiune + 1];
		for (int i = 0; i < this->dimensiune; i++)
			c[i] = this->materiiprime[i];
		c[this->dimensiune] = materiiprime;
		delete[] this->materiiprime;
		this->materiiprime = nullptr;
		this->dimensiune++;
		this->materiiprime = c;
	}
	friend istream& operator>>(istream& in, Produs& p) {
		delete[] p.materiiprime;
		p.materiiprime = nullptr;
		cout << "\nIntroduceti numele: ";
		in >> p.nume;
		cout << "\nIntroduceti numarul de ingrediente: ";
		in >> p.dimensiune;
		if (p.dimensiune <= 0) {
			p.dimensiune = 0;
			p.materiiprime = nullptr;
		}
		else {
			p.materiiprime = new MateriiPrime[p.dimensiune];
			for (int i = 0; i < p.dimensiune; i++) {
				cout << "materiiprime[" << i << "]=";
				in >> p.materiiprime[i];
			}
		}
		return in;
	}
	MateriiPrime operator[](int co) {
		if (co >= 0 && co < this->dimensiune) {
			return this->materiiprime[co];
		}
		else "Indexul nu este bun!";
	}

	void writeToFile(fstream& f)
	{
		// Scriere nume produs
		int lgNume = nume.length() + 1;
		f.write((char*)&lgNume, sizeof(int));
		f.write(nume.c_str(), sizeof(char) * lgNume);

		// Scriere dimensiune
		f.write((char*)&dimensiune, sizeof(int));

		// Scriere vector de MateriiPrime
		for (int i = 0; i < dimensiune; i++)
			materiiprime[i].writeToFile(f);
	}

	void readFromFile(fstream& f)
	{
		// Citire nume produs
		int lgNume = 0;
		f.read((char*)&lgNume, sizeof(int));
		char* bufferNume = new char[lgNume];
		f.read(bufferNume, sizeof(char) * lgNume);
		nume = bufferNume;
		delete[] bufferNume;

		// Citire dimensiune
		f.read((char*)&dimensiune, sizeof(int));

		// Citire vector de MateriiPrime
		materiiprime = new MateriiPrime[dimensiune];
		for (int i = 0; i < dimensiune; i++)
			materiiprime[i].readFromFile(f);
	}
};

class Comanda
{
	const int id;
	Produs* produs = nullptr;
	int nrProduse;
public:
	Comanda() :id(0)
	{
		this->nrProduse = 0;
		this->produs = nullptr;
	}
	Comanda(int id, Produs* produs, int nrProduse) :id(id)
	{
		if (nrProduse > 0 && produs != nullptr)
		{
			this->nrProduse = nrProduse;
			this->produs = new Produs[nrProduse];
			for (int i = 0; i < nrProduse; i++)
				this->produs[i] = produs[i];
		}
		else
		{
			this->produs = nullptr;
			this->nrProduse = 0;
		}
	}
	Produs* getProdus()
	{
		return this->produs;
	}
	int getNrProd()
	{
		return this->nrProduse;
	}
	void setNrProduse(Produs* produs, int nrProduse)
	{
		if (this->produs != nullptr)
		{
			delete[] this->produs;
		}
		this->nrProduse = nrProduse;
		this->produs = new Produs[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->produs[i] = produs[i];
		}
	}
	Comanda& operator=(const Comanda& c)
	{
		if (this != &c)
		{
			delete[] this->produs;
			this->produs = nullptr;

			if (c.nrProduse > 0 && c.produs != nullptr)
			{
				this->nrProduse = c.nrProduse;
				this->produs = new Produs[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->produs[i] = c.produs[i];
			}
		}
		return *this;
	}
	friend istream& operator>>(istream& in, Comanda& c) {

		delete[] c.produs;
		c.produs = nullptr;

		cout << "\nIntroduceti numarul de produse: ";
		in >> c.nrProduse;
		if (c.nrProduse < 0)
		{
			c.nrProduse = 0;
			c.produs = nullptr;
		}

		else {
			c.produs = new Produs[c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++) {
				cout << "\nProdus[" << i << "]=";
				in >> c.produs[i];
			}
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const Comanda& c)
	{
		out << "\n------";
		out << "\nID:" << c.id;
		out << "\nNumar produse:" << c.nrProduse;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << "\nProdus " << i + 1 << ":";
			if (c.produs != nullptr)
			{
				cout << c.produs[i] << " ";
			}
			else
			{
				out << "-";
			}
		}
		return out;
	}
	void afisare()
	{
		cout << "\n------";
		cout << "\nID:" << this->id;
		cout << "\nNumar produse:" << this->nrProduse;

		for (int i = 0; i < this->nrProduse; i++)
		{
			cout << "\nProdus " << i + 1 << ":";
			if (this->produs != nullptr)
			{
				cout << this->produs[i];
			}
			else
			{
				cout << "-";
			}
		}

	}
	Comanda(const Comanda& c) :id(id)
	{
		if (c.nrProduse > 0 && c.produs != nullptr)
		{
			this->nrProduse = c.nrProduse;
			this->produs = new Produs[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->produs[i] = c.produs[i];
		}
	}
	void adaugareProdus(Produs p)
	{
		Produs* aux = new Produs[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
			aux[i] = this->produs[i];
		if (this->produs != nullptr)
			delete[] this->produs;
		this->nrProduse++;
		this->produs = new Produs[nrProduse];

		for (int i = 0; i < this->nrProduse - 1; i++)
			this->produs[i] = aux[i];

		this->produs[this->nrProduse - 1] = p;
	}

	~Comanda()
	{
		delete[] produs;
		this->produs = nullptr;
	}

	void writeToFile(fstream& f)
	{
		// Scrie ID-ul comenzii
		f.write((char*)&id, sizeof(int));

		// Scrie numărul de produse
		f.write((char*)&nrProduse, sizeof(int));

		// Scrie fiecare produs în parte
		for (int i = 0; i < nrProduse; i++)
			produs[i].writeToFile(f);
	}

	void readFromFile(fstream& f)
	{
		// Citește ID-ul comenzii
		f.read((char*)&id, sizeof(int));

		// Citește numărul de produse
		f.read((char*)&nrProduse, sizeof(int));

		// Citește fiecare produs în parte
		produs = new Produs[nrProduse];
		for (int i = 0; i < nrProduse; i++)
			produs[i].readFromFile(f);
	}
};

class Client
{
	Comanda* comanda = nullptr;
	string nume = "";
	bool discout = 1;
	int dimensiune = 0;
public:
	Client() {}
	Client(string nume, int dimensiune, Comanda* comanda, bool discount)
	{
		if (nume != "")
			this->nume = nume;
		this->discout = discount;
		if (comanda != nullptr && dimensiune > 0)
		{
			this->dimensiune = dimensiune;
			this->comanda = new Comanda[this->dimensiune];
			for (int i = 0; i < this->dimensiune; i++)
				this->comanda[i] = comanda[i];
		}
		else {
			this->dimensiune = 0;
			this->comanda = nullptr;
		}
	}
	Client(const string& denumire) :nume(nume)
	{
		discout = (denumire == "Papdopolis");
	}
	Client& operator=(const Client& c)
	{
		if (this != &c)
		{
			delete[] this->comanda;
			this->comanda = nullptr;

			if (c.nume != "")
				this->nume = c.nume;

			this->discout = discout;

			if (dimensiune > 0 && c.comanda != nullptr)
			{
				this->dimensiune = c.dimensiune;
				this->comanda = new Comanda[this->dimensiune];
				for (int i = 0; i < this->dimensiune; i++)
					this->comanda[i] = c.comanda[i];
			}
		}
		return *this;
	}
	void setComandaClient(Comanda* comanda)
	{
		this->comanda = comanda;
	}
	friend istream& operator>>(istream& in, Client& c) {
		delete[] c.comanda;
		c.comanda = nullptr;

		cout << "\nDiscount?";
		in >> c.discout;

		cout << "\nIntroduceti numele: ";
		in >> c.nume;

		cout << "Introduceti numarul de comenzi: ";
		in >> c.dimensiune;
		if (c.dimensiune <= 0) {
			c.dimensiune = 0;
			c.comanda = nullptr;
		}
		else {
			c.comanda = new Comanda[c.dimensiune];
			for (int i = 0; i < c.dimensiune; i++) {
				cout << "comanda[" << i << "]=";
				in >> c.comanda[i];
			}
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const Client& c) {


		out << "\n------";

		out << "\nNume client: " << c.nume;
		out << "\nDiscount: " << c.discout;
		out << "\nNumar comenzi:" << c.dimensiune;
		out << "\nComanda: ";
		if (c.dimensiune > 0) {
			for (int i = 0; i < c.dimensiune; i++)
				out << c.comanda[i] << " ";
		}
		else {
			out << "-";
		}
		return out;
	}
	~Client()
	{
		delete[] this->comanda;
		this->comanda = nullptr;
	}

	void writeToFile(fstream& f)
	{
		// Scrie numele clientului
		int numeLength = nume.length();
		f.write((char*)&numeLength, sizeof(int));
		f.write(nume.c_str(), numeLength);

		// Scrie dacă clientul are discount
		f.write((char*)&discout, sizeof(bool));

		// Scrie dimensiunea array-ului de comenzi
		f.write((char*)&dimensiune, sizeof(int));

		// Scrie fiecare comandă în parte
		for (int i = 0; i < dimensiune; i++)
			comanda[i].writeToFile(f);
	}

	void readFromFile(fstream& f)
	{
		// Citește numele clientului
		int numeLength;
		f.read((char*)&numeLength, sizeof(int));
		char* buffer = new char[numeLength + 1];
		f.read(buffer, numeLength);
		buffer[numeLength] = '\0';
		nume = buffer;
		delete[] buffer;

		// Citește dacă clientul are discount
		f.read((char*)&discout, sizeof(bool));

		// Citește dimensiunea array-ului de comenzi
		f.read((char*)&dimensiune, sizeof(int));

		// Citește fiecare comandă în parte
		comanda = new Comanda[dimensiune];
		for (int i = 0; i < dimensiune; i++)
			comanda[i].readFromFile(f);
	}
};

class Restaurant
{
	int nrComenzi;
	int nrProduse;
	Produs* produse;
public:
	Restaurant(int nrComenzi, int nrProduse)
	{
		this->nrComenzi = nrComenzi;
		this->nrProduse = nrProduse;
		this->produse = new Produs[nrProduse];
	}
	void afiseazaMeniu()
	{
		cout << "---------- Meniu ----------\n";
		for (int i = 0; i < this->nrProduse; i++)
			cout << i + 1 << "." << this->produse[i].getNume() << "\n";
		cout << "----------------------------\n";
	}
	void veziProduse(int index)
	{
		if (index >= 1 && index <= nrProduse)
		{
			cout << "Detalii pentru produsul" << index << ":\n";
			cout << produse[index - 1] << "\n";
		}
		else cout << "Indexul nu este bun\n";
	}

	Produs* getProduse() {
		return this->produse;
	}

	int getNrProduse() {
		return this->nrProduse;
	}

	void setListaProduse(Produs* listaProduse, int nrProduse)
	{
		this->nrProduse = nrProduse;
		if (this->produse != nullptr)
			delete[] this->produse;
		this->produse = new Produs[nrProduse];

		for (int i = 0; i < this->nrProduse; i++)
			this->produse[i] = listaProduse[i];
	}

	~Restaurant()
	{
		delete[] produse;
		this->produse = nullptr;
	}

	void writeToFile(fstream& f)
	{
		// Scrie numărul de comenzi și numărul de produse
		f.write((char*)&nrComenzi, sizeof(int));
		f.write((char*)&nrProduse, sizeof(int));

		// Scrie fiecare produs în parte
		for (int i = 0; i < nrProduse; i++)
			produse[i].writeToFile(f);
	}

	void readFromFile(fstream& f)
	{
		// Citește numărul de comenzi și numărul de produse
		f.read((char*)&nrComenzi, sizeof(int));
		f.read((char*)&nrProduse, sizeof(int));

		// Citește fiecare produs în parte
		produse = new Produs[nrProduse];
		for (int i = 0; i < nrProduse; i++)
			produse[i].readFromFile(f);
	}
};

vector<MateriiPrime> citesteDateFisier(const string& numeFisier) {
	vector<MateriiPrime> materiiPrime;

	try {
		ifstream fisier(numeFisier);
		if (!fisier.is_open()) {
			throw runtime_error("Nu s-a putut deschide fisierul!");
		}

		string linie;
		while (getline(fisier, linie)) {
			istringstream linieStream(linie);
			string denumire;
			int cantitate;

			if (linieStream >> denumire >> cantitate) {
				materiiPrime.push_back(MateriiPrime(denumire.c_str(), cantitate));
			}
			else {
				throw invalid_argument("Formatul liniei din fisier nu este corect!");
			}
		}

		fisier.close();
	}
	catch (const exception& e) {
		cerr << "Eroare: " << e.what() << endl;
	}

	return materiiPrime;
}

int main() {
	vector<MateriiPrime> materiiPrime = citesteDateFisier("MateriiPrime.txt");
	ifstream file("MateriiPrime.txt");

	string line;

	if (materiiPrime.size() >= 2) {
		MateriiPrime ingredient1 = materiiPrime[0];
		MateriiPrime ingredient2 = materiiPrime[1];
		MateriiPrime ingredient3 = materiiPrime[2];
		MateriiPrime ingredient4 = materiiPrime[3];
		MateriiPrime ingredient5 = materiiPrime[4];

		Restaurant restaurant(4, 4);

		MateriiPrime PasteC[]{ ingredient1,ingredient2 };
		MateriiPrime PasteB[]{ ingredient1,ingredient3 };
		MateriiPrime PasteP[]{ ingredient1,ingredient4 };
		MateriiPrime Lasagna[]{ ingredient1,ingredient3, ingredient5 };
		restaurant.getProduse()[0] = Produs(PasteC, 2, "Paste Carbonara");
		restaurant.getProduse()[1] = Produs(PasteB, 2, "Paste Bolognese");
		restaurant.getProduse()[2] = Produs(PasteP, 2, "Paste Pesto");
		restaurant.getProduse()[3] = Produs(Lasagna, 3, "Lasagna");

		int alegere;
		bool iesire = false;
		Comanda c1;
		while (!iesire)
		{
			cout << "Alegeti ce doriti sa faceti:\n";
			cout << "1 - Vezi meniul\n";
			cout << "2 - Adauga produse in comanda\n";
			cout << "3 - Inscrie comanda\n";
			cout << "0 - Iesire\n";
			int alegere;
			while (!(cin >> alegere))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nIntroduceti un numar intreg: ";
			}
			switch (alegere)
			{
			case 1:
			{
				restaurant.afiseazaMeniu();
				break;
			}
			case 2:
			{
				cout << "\nCe preparat doriti sa adaugati in comanda?\n";
				int indexProdus;
				while (!(cin >> indexProdus))
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nIntroduceti un numar intreg: ";
				}
				if (indexProdus >= 1 && indexProdus <= restaurant.getNrProduse())
				{
					c1.adaugareProdus(restaurant.getProduse()[indexProdus - 1]);
					cout << "Preparatul a fost adaugat la comanda!\n";

				}
				else cout << "Indexul nu este bun.\n";
				break;
			}
			case 3:
			{
				cout << "Comanda a fost trimisa cu succes!\n";
				cout << "Ati comandat urmatoarele produse: \n";
				for (int i = 0; i < c1.getNrProd(); i++)
					cout << c1.getProdus()[i] << "\n";
				iesire = true;
				break;
			}
			case 0:
			{
				cout << "Zi buna!\n";
				iesire = true;
				break;
			}
			default:
			{
				cout << "Nu ati ales o optiunee valida. Incercati inca o data.\n";
				break;
			}
			}

		}
		return 0;
	}
}