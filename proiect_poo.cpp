#include<iostream>   //domeniul: Farmacie
#include<fstream>
#include<string>

using namespace std;

class ElementVanzare {
private:
	int codElement;
	char* descriereSuplimentara;
public:

	ElementVanzare() {
		this->codElement = 100001;
		this->descriereSuplimentara = NULL;
	}

	ElementVanzare(int codNou, const char* descriereSuplimentara) {
		this->codElement = codNou;
		this->descriereSuplimentara = new char[strlen(descriereSuplimentara)+1];
		strcpy_s(this->descriereSuplimentara, strlen(descriereSuplimentara) + 1, descriereSuplimentara);
	}

	ElementVanzare(const ElementVanzare& e) {
		this->codElement = e.codElement;
		if (e.descriereSuplimentara != NULL) {
			this->descriereSuplimentara = new char[strlen(e.descriereSuplimentara) + 1];
			strcpy_s(this->descriereSuplimentara, strlen(e.descriereSuplimentara) + 1, e.descriereSuplimentara);
		}
		else {
			this->descriereSuplimentara = NULL;
		}
	}

	virtual ~ElementVanzare() {
		if (this->descriereSuplimentara != NULL) {
			delete[]this->descriereSuplimentara;
		}
	}

	virtual void afisareDescriere() = 0;

	void setCodElement(int codElement) {
		if (codElement >= 0) {
			this->codElement = codElement;
		}
	}

	int getCodElement() {
		return this->codElement;
	}

	void setDescriereSuplimentara(const char* descriere) {
		if (this->descriereSuplimentara != NULL) {
			delete[]this->descriereSuplimentara;
		}
		this->descriereSuplimentara = new char[strlen(descriere) + 1];
		strcpy_s(this->descriereSuplimentara, strlen(descriere) + 1, descriere);
	}

	char* getDescriereSuplimentara() {
		return this->descriereSuplimentara;
	}

};

class Medicament: public ElementVanzare {
private:
	const int codProdus;
	char* nume;
	float pret;
	bool disponibilitate;
	static int taxaTVA;
public:
	void afisareDescriere() {
		cout << "Medicamentul " << this->nume << " cu codul " << this->codProdus << " costa " << this->pret << " lei" << endl;
	}

	Medicament() :codProdus(1000), ElementVanzare() {
		this->nume = new char[strlen("Paracetamol") + 1];
		strcpy_s(this->nume, strlen("Paracetamol") + 1, "Paracetamol");
		this->pret = 1.00;
		this->disponibilitate = false;
	}

	Medicament(int codNou) :codProdus(codNou), ElementVanzare() {
		this->nume = new char[strlen("Ibuprofen") + 1];
		strcpy_s(this->nume, strlen("Ibuprofen") + 1, "Ibuprofen");
		this->pret = 16.75;
		this->disponibilitate = false;
	}

	Medicament(int codNou, float pretNou) :codProdus(codNou), pret(pretNou), ElementVanzare() {
		this->nume = new char[strlen("Aspirina") + 1];
		strcpy_s(this->nume, strlen("Aspirina") + 1, "Aspirina");
		this->disponibilitate = true;
	}

	Medicament(const Medicament& p) :codProdus(p.codProdus), ElementVanzare(p) {
		this->nume = new char[strlen(p.nume) + 1];
		strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
		this->pret = p.pret;
		this->disponibilitate = p.disponibilitate;
	}

	Medicament operator=(const Medicament& m) {
		if (this != &m) {
			if (this->nume != NULL) {
				delete[]this->nume;
			}
			this->nume = new char[strlen(m.nume) + 1];
			strcpy_s(this->nume, strlen(m.nume) + 1, m.nume);
			this->pret = m.pret;
			this->disponibilitate = m.disponibilitate;
		}
		return *this;
	}

	virtual ~Medicament() {
		if (this->nume != NULL) {
			delete[]this->nume;
		}
	}

	void afisare() {
		cout << this->codProdus << "." << " Nume: "
			<< this->nume << " Pret: " << this->pret << " lei, inclusiv TVA: " << this->taxaTVA << "%. "
			<< (this->disponibilitate ? "Disponibil" : "Indisponibil") << endl;
	}

	static int afisareTaxa() {
		return taxaTVA;
	}

	const int getCodProdus() {
		return this->codProdus;
	}

	char* getNume() {
		return this->nume;
	}

	void setNume(const char* numeNou) {
		if (numeNou != NULL) {
			if (this->nume != NULL) {
				delete[]this->nume;
			}
			this->nume = new char[strlen(numeNou) + 1];
			strcpy_s(this->nume, strlen(numeNou) + 1, numeNou);
		}
	}

	float getPret() {
		return this->pret;
	}

	void setPret(float pretNou) {
		if (pretNou >= 0) {
			this->pret = pretNou;
		}
	}

	bool getDisponibilitate() {
		return this->disponibilitate;
	}

	void setDisponibilitate(bool valoare) {
		this->disponibilitate = valoare;
	}

	static int getTaxaTva() {
		return Medicament::taxaTVA;
	}

	static void setTaxaTva(int taxa) {
		if (taxa >= 0) {
			Medicament::taxaTVA = taxa;
		}
	}

	friend float calculeazaPretCuReducere(const Medicament& medicament, float procentRreducere);
	friend float calculeazaPretFaraTVA(const Medicament& medicament);

	friend ostream& operator<<(ostream& consola, const Medicament& medicament);

	friend istream& operator>>(istream& tastatura, Medicament& medicament) {
		char buffer[100]; // buffer pentru a citi numele medicamentului
		cout << "Nume: ";
		tastatura >> buffer;

		if (medicament.nume != NULL) {
			delete[]medicament.nume;
		}
		medicament.nume = new char[strlen(buffer) + 1];
		strcpy_s(medicament.nume, strlen(buffer) + 1, buffer);

		cout << "Pret: ";
		tastatura >> medicament.pret;
		cout << "Disponibilitate (1 - DA, 0 - NU): ";
		tastatura >> medicament.disponibilitate;

		return tastatura;
	}

	Medicament operator!() const {
		Medicament aux = *this;
		aux.disponibilitate = !aux.disponibilitate;
		return aux;
	}

	friend ofstream& operator<<(ofstream& file, const Medicament& medicament) {
		file << medicament.nume << " " << medicament.pret << " " << medicament.taxaTVA
			<< " " << medicament.disponibilitate << endl;
		return file;
	}

	friend ifstream& operator>>(ifstream& file, Medicament& medicament) {
		char buffer[100];
		//cout << "Nume: ";
		file >> buffer;
		if (medicament.nume != NULL) {
			delete[]medicament.nume;
		}
		medicament.nume = new char[strlen(buffer) + 1];
		strcpy_s(medicament.nume, strlen(buffer) + 1, buffer);

		//cout << "Pret: ";
		file >> medicament.pret;

		file >> medicament.disponibilitate;

		return file;
	}

};
int Medicament::taxaTVA = 9;

float calculeazaPretCuReducere(const Medicament& medicament, float procentReducere) {
	return medicament.pret - (medicament.pret * procentReducere / 100);
}

float calculeazaPretFaraTVA(const Medicament& medicament) {
	return medicament.pret / (1 + (medicament.getTaxaTva() / 100.0f));
}

ostream& operator<<(ostream& consola, const Medicament& medicament) {
	consola << medicament.codProdus << "." << " Nume: "
		<< medicament.nume << " Pret: " << medicament.pret << " lei, inclusiv TVA: " << medicament.taxaTVA << "%. " << endl;
	consola << (medicament.disponibilitate ? "Disponibil" : "Indisponibil") << endl;

	return consola;
}

class Antibiotic : public Medicament {
private:
	string formaFarmaceutica; // ex: comprimate, capsule, sirop, etc.
	char* clasa; //ex: peniciline, macrolide, glicopeptide
	bool necesitaReteta;
public:

	void afisareDescriere() {
		cout << "Antibioticul " << getNume() << " este un medicament din clasa " << this->clasa << endl;
	}

	Antibiotic() :Medicament(10001, 9.99) {
		this->formaFarmaceutica = "Capsule";
		this->clasa = new char[strlen("Macrolide") + 1];
		strcpy_s(this->clasa, strlen("Macrolide") + 1, "Macrolide");
		this->necesitaReteta = 0;
	}

	Antibiotic(string formaFarmaceutica, bool necesitaReteta, int cod) : Medicament(cod) {
		this->formaFarmaceutica = formaFarmaceutica;
		this->clasa = new char[strlen("Macrolide") + 1];
		strcpy_s(this->clasa, strlen("Macrolide") + 1, "Macrolide");
		this->necesitaReteta = necesitaReteta;
	}

	Antibiotic(const Antibiotic& a) :Medicament(a) {
		this->formaFarmaceutica = a.formaFarmaceutica;
		this->clasa = new char[strlen(a.clasa) + 1];
		strcpy_s(this->clasa, strlen(a.clasa) + 1, a.clasa);
		this->necesitaReteta = a.necesitaReteta;
	}

	Antibiotic operator=(const Antibiotic& a) {
		if (this != &a) {
			Medicament::operator=(a);
			this->formaFarmaceutica = a.formaFarmaceutica;
			if (this->clasa != NULL) {
				delete[]this->clasa;
			}
			this->clasa = new char[strlen(a.clasa) + 1];
			strcpy_s(this->clasa, strlen(a.clasa) + 1, a.clasa);
			this->necesitaReteta = a.necesitaReteta;
		}
		return *this;
	}

	~Antibiotic() {
		if (this->clasa != NULL) {
			delete[]this->clasa;
		}
	}

	void setFormaFarmaceutica(string forma) {
		if (forma.length() > 0) {
			this->formaFarmaceutica = forma;
		}
	}

	string getFormaFarmaceutica() {
		return this->formaFarmaceutica;
	}

	void setClasa(const char* clasaNoua) {
		if (clasaNoua != NULL) {
			if (this->clasa != NULL) {
				delete[]this->clasa;
			}
			this->clasa = new char[strlen(clasaNoua) + 1];
			strcpy_s(this->clasa, strlen(clasaNoua) + 1, clasaNoua);
		}
	}

	char* getClasa() {
		return this->clasa;
	}

	void setNecesitaReteta(bool necesitaReteta) {
		this->necesitaReteta = necesitaReteta;
	}

	bool getNecesitaReteta() {
		return this->necesitaReteta;
	}

	friend ostream& operator<<(ostream& out, const Antibiotic& a) {
		out << (Medicament)a;
		out << "Forma farmaceutica: " << a.formaFarmaceutica << ", Clasa: " << a.clasa <<
			(a.necesitaReteta ? ", Necesita reteta." : ", Nu necesita reteta.");
		return out;
	}

	float calcPretEstimativDupaScumpire() {
		//se adauga 10% la pret pentru antibioticele care se elibereaza fara reteta
		float pretNou;
		if (this->necesitaReteta == 0) {
			pretNou = getPret() + getPret() * 0.1;
		}
		else {
			pretNou = getPret();
		}
		return pretNou;
	}

};

class Persoana {
private:
	int codPersoana;
	char* categorie;
public:
	Persoana() {
		this->codPersoana = 100001;
		this->categorie = NULL;
	}

	Persoana(int codPersoana, const char* categorie) {
		this->codPersoana = codPersoana;
		this->categorie = new char[strlen(categorie) + 1];
		strcpy_s(this->categorie, strlen(categorie) + 1, categorie);
	}

	Persoana(const Persoana& e) {
		this->codPersoana = e.codPersoana;
		if (e.categorie != NULL) {
			this->categorie = new char[strlen(e.categorie) + 1];
			strcpy_s(this->categorie, strlen(e.categorie) + 1, e.categorie);
		}
		else {
			this->categorie = NULL;
		}
	}

	virtual ~Persoana() {
		if (this->categorie != NULL) {
			delete[]this->categorie;
		}
	}

	virtual void afisareDescrierePersoana() = 0;

	void setCodPersoana(int codPersoana) {
		if (codPersoana >= 0) {
			this->codPersoana = codPersoana;
		}
	}

	int getCodPersoana() {
		return this->codPersoana;
	}

	void setCategorie(const char* categorie) {
		if (this->categorie != NULL) {
			delete[]this->categorie;
		}
		this->categorie = new char[strlen(categorie) + 1];
		strcpy_s(this->categorie, strlen(categorie) + 1, categorie);
	}

	char* getCategorie() {
		return this->categorie;
	}
};

class Angajat: public Persoana {
private:
	const int id;
	string nume;
	char* adresa;
	float aniExperienta;
	static int nrMaximOreLucrate;
public:
	void afisareDescrierePersoana() {
		cout << " Persoana " << this->nume << " este un angajat cu " << this->aniExperienta << " ani de experienta." << endl;
	}

	Angajat() :id(10000), Persoana() {
		this->nume = "Ana Popescu";
		this->adresa = new char[strlen("Militari") + 1];
		strcpy_s(this->adresa, strlen("Militari") + 1, "Militari");
		this->aniExperienta = 0;
		setCategorie("Angajat");
	}

	Angajat(int idActualizat, string numeNou) :id(idActualizat), nume(numeNou), Persoana() {
		this->adresa = new char[strlen("Calea Vitan") + 1];
		strcpy_s(this->adresa, strlen("Calea Vitan") + 1, "Calea Vitan");
		this->aniExperienta = 5;
		setCategorie("Angajat");
	}

	Angajat(int idActualizat, string numeNou, float ani_experienta, int codPersoana, const char* categorie) :id(idActualizat), nume(numeNou), aniExperienta(ani_experienta), Persoana(codPersoana, categorie) {
		this->adresa = new char[strlen("Dorobanti") + 1];
		strcpy_s(this->adresa, strlen("Dorobanti") + 1, "Dorobanti");
	}

	Angajat(const Angajat& p) :id(p.id), Persoana(p) {
		nume = p.nume;
		this->adresa = new char[strlen(p.adresa) + 1];
		strcpy_s(this->adresa, strlen(p.adresa) + 1, p.adresa);
		aniExperienta = p.aniExperienta;
	}

	Angajat operator=(const Angajat& a) {
		if (this != &a) {
			this->nume = a.nume;
			if (this->adresa != NULL) {
				delete[]adresa;
			}
			this->adresa = new char[strlen(a.adresa) + 1];
			strcpy_s(this->adresa, strlen(a.adresa) + 1, a.adresa);
			this->aniExperienta = a.aniExperienta;
		}
		return *this;
	}

	virtual ~Angajat() {
		if (this->adresa != NULL) {
			delete[]this->adresa;
		}
	}

	void afisare() {
		cout << this->id << ". " << "Nume angajat: " << this->nume << ", Adresa: " << this->adresa << ". " << this->aniExperienta << " ani de experienta." << endl;
		cout << " Nr maxim de ore de lucru permis pe saptamana:" << this->nrMaximOreLucrate << endl;
	}

	static int afisareNrMaximOreLucrate() {
		return nrMaximOreLucrate;
	}

	const int getId() {
		return this->id;
	}

	string getNume() {
		return this->nume;
	}

	void setNume(string numeNou) {
		if (numeNou.length() > 3)
		{
			this->nume = numeNou;
		}
	}

	char* getAdresa() {
		return this->adresa;
	}

	void setAdresa(const char* adresaNoua) {
		if (adresaNoua != NULL) {
			delete[]adresa;
			adresa = new char[strlen(adresaNoua) + 1];
			strcpy_s(adresa, strlen(adresaNoua) + 1, adresaNoua);
		}
	}

	float getAniExperienta() {
		return this->aniExperienta;
	}

	void setAniExperienta(float nrAniExperienta) {
		if (nrAniExperienta >= 0) {
			this->aniExperienta = nrAniExperienta;
		}
	}

	static int getNrMaximOreLucrate() {
		return Angajat::nrMaximOreLucrate;
	}

	static void setNrMaximOreLucrate(int nrMaxOreLucrate) {
		if (nrMaxOreLucrate >= 0) {
			Angajat::nrMaximOreLucrate = nrMaxOreLucrate;
		}
	}

	friend float calculeazaSalariulLunar(const Angajat& angajat, int oreLucrate, float tarifOrar);
	friend float calculeazaBonusAnual(const Angajat& angajat);

	Angajat operator++() {
		this->aniExperienta += 1.5;
		return *this;
	}

	Angajat operator++(int) {
		Angajat stareInitiala = *this;
		this->aniExperienta += 1.5;
		return stareInitiala;
	}

	bool operator>(Angajat a) {
		return this->aniExperienta > a.aniExperienta;
	}

	explicit operator float() {
		return this->aniExperienta;
	}

	friend ostream& operator<<(ostream& consola, const Angajat& angajat) {
		consola << angajat.id << ". " << "Nume angajat: " << angajat.nume << ", Adresa: " << angajat.adresa << ". " << angajat.aniExperienta << " ani de experienta." << endl;
		cout << " Nr maxim de ore de lucru permis pe saptamana:" << angajat.nrMaximOreLucrate << endl;

		return consola;
	}

	friend istream& operator>>(istream& tastatura, Angajat& angajat) {
		cout << "Nume: ";
		tastatura >> angajat.nume;

		char adresa[100];
		cout << "Adresa: ";
		tastatura >> adresa;
		if (angajat.adresa != NULL) {
			delete[]angajat.adresa;
		}
		angajat.adresa = new char[strlen(adresa) + 1];
		strcpy_s(angajat.adresa, strlen(adresa) + 1, adresa);
		cout << "Ani experienta: ";
		tastatura >> angajat.aniExperienta;

		return tastatura;
	}

	friend ofstream& operator<<(ofstream& file, const Angajat& angajat) {
		file << angajat.nume << " " << angajat.adresa << " " << angajat.aniExperienta
			<< " " << angajat.nrMaximOreLucrate << endl;

		return file;
	}

	friend istream& operator>>(ifstream& file, Angajat& angajat) {
		//cout << "Nume: ";
		file >> angajat.nume;

		char adresa[100];
		//cout << "Adresa: ";
		file >> adresa;
		if (angajat.adresa != NULL) {
			delete[]angajat.adresa;
		}
		angajat.adresa = new char[strlen(adresa) + 1];
		strcpy_s(angajat.adresa, strlen(adresa) + 1, adresa);
		//cout << "Ani experienta: ";
		file >> angajat.aniExperienta;

		return file;
	}

	void scrieInFisierBinar(fstream& f) {

		f.write(nume.c_str(), nume.length() + 1);

		int lungime = strlen(this->adresa);
		f.write((char*)&lungime, sizeof(int));
		for (int i = 0;i < lungime;i++) {
			f.write((char*)&this->adresa[i], sizeof(char));
		}

		f.write((char*)&this->aniExperienta, sizeof(float));
		f.write((char*)&this->nrMaximOreLucrate, sizeof(int));
	}

	void citesteDinFisierBinar(fstream& f) {

		getline(f, this->nume, '\0');

		int lungime;
		f.read((char*)&lungime, sizeof(int));
		if (this->adresa != NULL) {
			delete[]this->adresa;
		}
		this->adresa = new char[lungime + 1];
		for (int i = 0;i < lungime;i++) {
			f.read((char*)&this->adresa[i], sizeof(char));
		}
		this->adresa[lungime] = '\0';

		f.read((char*)&this->aniExperienta, sizeof(float));
		f.read((char*)&this->nrMaximOreLucrate, sizeof(int));

	}

};
int Angajat::nrMaximOreLucrate = 40;

float calculeazaSalariulLunar(const Angajat& angajat, int oreLucrate, float tarifOrar) {
	if (oreLucrate <= angajat.getNrMaximOreLucrate()) {
		return oreLucrate * tarifOrar;
	}
	else {  // calculul pentru orele suplimentar
		return(angajat.getNrMaximOreLucrate() * tarifOrar) + ((oreLucrate - angajat.getNrMaximOreLucrate()) * tarifOrar * 1.5);
	}
}

float calculeazaBonusAnual(const Angajat& angajat) {
	float bonus = 0.0;
	if (angajat.aniExperienta >= 5) {
		bonus = 2000.0;
	}
	else if (angajat.aniExperienta >= 3) {
		bonus = 1000.0;
	}
	return bonus;
}

class Reteta: public ElementVanzare {
private:
	const int nrReteta;
	string numePacient;
	char* numeMedic;
	int nrMedicamentePrescrise;
	int* doze;
	string dataEmiterii;
	static int durataValabilitateReteta;
public:
	
	void afisareDescriere() {
		cout << " Reteta cu numarul " << this->nrReteta << " a fost emisa pe data de " << this->dataEmiterii << endl;
	}

	Reteta() :nrReteta(100), ElementVanzare() {
		this->numePacient = "Pacient";
		this->numeMedic = new char[strlen("Medic") + 1];
		strcpy_s(this->numeMedic, strlen("Medic") + 1, "Medic");
		this->nrMedicamentePrescrise = 0;
		this->doze = NULL;
		this->dataEmiterii = "01-01-2021";
	}

	Reteta(int nrReretaNou, string numePacientActualizat, int codElement, const char* descriere) :nrReteta(nrReretaNou), numePacient(numePacientActualizat), ElementVanzare(codElement, descriere) {
		this->numeMedic = new char[strlen("Gabriel Dobre") + 1];
		strcpy_s(this->numeMedic, strlen("Gabriel Dobre") + 1, "Gabriel Dobre");
		this->nrMedicamentePrescrise = 0;
		this->doze = NULL;
		this->dataEmiterii = "01-01-2021";

	}

	Reteta(int nrReretaNou, string numePacientActualizat, int nrMedicamente, int* doze) :nrReteta(nrReretaNou),
		numePacient(numePacientActualizat), nrMedicamentePrescrise(nrMedicamente), ElementVanzare() {
		this->numeMedic = new char[strlen("Florin Georgescu") + 1];
		strcpy_s(this->numeMedic, strlen("Florin Georgescu") + 1, "Florin Georgescu");
		if (nrMedicamentePrescrise != 0) {
			this->doze = new int[nrMedicamentePrescrise];
			for (int i = 0;i < nrMedicamentePrescrise;i++) {
				this->doze[i] = doze[i];
			}
		}
		else this->nrMedicamentePrescrise = NULL;
		this->dataEmiterii = "05-08-2023";
	}

	Reteta(const Reteta& p) :nrReteta(p.nrReteta), ElementVanzare(p) {
		this->numePacient = p.numePacient;
		this->numeMedic = new char[strlen(p.numeMedic) + 1];
		strcpy_s(this->numeMedic, strlen(p.numeMedic) + 1, p.numeMedic);
		this->nrMedicamentePrescrise = p.nrMedicamentePrescrise;
		if (nrMedicamentePrescrise != 0) {
			this->doze = new int[nrMedicamentePrescrise];
			for (int i = 0;i < nrMedicamentePrescrise;i++) {
				this->doze[i] = p.doze[i];
			}
		}
		else this->doze = NULL;
		this->dataEmiterii = p.dataEmiterii;
	}

	Reteta operator=(const Reteta& r) {
		if (this != &r) {
			this->numePacient = r.numePacient;
			if (this->numeMedic != NULL) {
				delete[]numeMedic;
			}
			this->numeMedic = new char[strlen(r.numeMedic) + 1];
			strcpy_s(this->numeMedic, strlen(r.numeMedic) + 1, r.numeMedic);
			this->nrMedicamentePrescrise = r.nrMedicamentePrescrise;
			if (this->doze != NULL) {
				delete[]doze;
			}
			if (nrMedicamentePrescrise != NULL) {
				this->doze = new int[nrMedicamentePrescrise];
				for (int i = 0;i < nrMedicamentePrescrise;i++) {
					this->doze[i] = r.doze[i];
				}
			}
			else this->doze = NULL;
			this->dataEmiterii = r.dataEmiterii;
		}
		return *this;
	}

	virtual ~Reteta() {
		if (this->numeMedic != NULL) {
			delete[]this->numeMedic;
		}
	}

	void afisare() {
		cout << this->nrReteta << ". " << "Pacient:" << this->numePacient << ", Medic: " << this->numeMedic << ". Data emiterii: " << this->dataEmiterii
			<< " cu valabilitatea de " << this->durataValabilitateReteta << " de zile, " << this->nrMedicamentePrescrise << " medicamente prescrise." << endl;
		if (nrMedicamentePrescrise != NULL) {
			cout << "Doze: ";
			for (int i = 0;i < nrMedicamentePrescrise;i++) {
				cout << doze[i] << " mg ";
			}
		}
		else {
			cout << " - ";
		}
		cout << endl;
	}

	static int afisareDurataValabilitate() {
		return durataValabilitateReteta;
	}

	const int getNrReteta() {
		return this->nrReteta;
	}

	string getNumePacient() {
		return this->numePacient;
	}

	void setNumePacient(string numeNou) {
		if (numeNou.length() > 3)
		{
			this->numePacient = numeNou;
		}
	}

	char* getNumeMedic() {
		return this->numeMedic;
	}

	void setNumeMedic(const char* nume) {
		if (nume != NULL) {
			delete[]numeMedic;
			numeMedic = new char[strlen(nume) + 1];
			strcpy_s(numeMedic, strlen(nume) + 1, nume);
		}
	}

	int getnrMedicamentePrescrise() {
		return this->nrMedicamentePrescrise;
	}

	int getDoze(int index) {
		if (index >= 0 && index < this->nrMedicamentePrescrise) {
			return this->doze[index];
		}
	}

	void setMedicamente(int nrMedicamente, int* doza) {
		if (nrMedicamente > 0) {
			this->nrMedicamentePrescrise = nrMedicamente;
			if (this->doze != NULL) {
				delete[]this->doze;
			}
			this->doze = new int[nrMedicamente];
			for (int i = 0;i < nrMedicamente;i++) {
				this->doze[i] = doza[i];
			}
		}
	}

	string getDataEmiterii() {
		return this->dataEmiterii;
	}

	void setDataEmiterii(string dataNoua) {
		if (dataNoua.length() > 3)
		{
			this->dataEmiterii = dataNoua;
		}
	}

	static int getDurataValabilitateReteta() {
		return Reteta::durataValabilitateReteta;
	}

	static void setDurataValabilitateReteta(int durataValabilitate) {
		if (durataValabilitate >= 0) {
			Reteta::durataValabilitateReteta = durataValabilitate;
		}
	}

	friend int calculeazaSumaDozelor(const Reteta& reteta);

	friend bool dozaNedepasesteLimita(const Reteta& reteta, int dozaVerificare);

	int& operator[](int index) {
		if (index >= 0 && index < nrMedicamentePrescrise) {
			return doze[index];
		}
	}

	Reteta operator+(const Reteta& r) {
		Reteta aux = *this;
		aux.nrMedicamentePrescrise = this->nrMedicamentePrescrise + r.nrMedicamentePrescrise;

		if (aux.doze != NULL) {
			delete[]aux.doze;
		}
		if (aux.nrMedicamentePrescrise > 0) {
			aux.doze = new int[aux.nrMedicamentePrescrise];
			for (int i = 0;i < this->nrMedicamentePrescrise;i++) {
				aux.doze[i] = doze[i];
			}
			for (int i = this->nrMedicamentePrescrise;i < aux.nrMedicamentePrescrise;i++) {
				aux.doze[i] = r.doze[i - nrMedicamentePrescrise];
			}
		}
		else {
			aux.doze = NULL;
		}
		return aux;
	}

	int operator()(int start, int stop) {
		if (start >= 0 && start < this->nrMedicamentePrescrise && stop >= 0 && stop < this->nrMedicamentePrescrise && start < stop) {
			int suma = 0;
			for (int i = start;i < stop;i++) {
				suma += this->doze[i];
			}
			return suma;
		}
		else {
			return 0;
		}
	}

	int operator()(int stop) {
		Reteta aux = *this;
		return aux(0, stop);
	}

	friend ostream& operator<<(ostream& consola, const Reteta& reteta) {
		cout << reteta.nrReteta << ". " << "Pacient:" << reteta.numePacient << ", Medic: " << reteta.numeMedic << ". Data emiterii: " << reteta.dataEmiterii
			<< " cu valabilitatea de " << reteta.durataValabilitateReteta << " de zile, " << reteta.nrMedicamentePrescrise << " medicamente prescrise." << endl;
		if (reteta.nrMedicamentePrescrise != NULL) {
			cout << "Doze: ";
			for (int i = 0;i < reteta.nrMedicamentePrescrise;i++) {
				cout << reteta.doze[i] << " mg ";
			}
		}
		else {
			cout << " - ";
		}
		cout << endl;
		return consola;
	}


	friend istream& operator>>(istream& tastatura, Reteta& reteta) {
		cout << "Nume pacient: ";
		tastatura >> reteta.numePacient;
		char numeMedic[100];
		cout << "Nume medic: ";
		tastatura >> numeMedic;
		if (reteta.numeMedic != NULL) {
			delete[]reteta.numeMedic;
		}
		reteta.numeMedic = new char[strlen(numeMedic) + 1];
		strcpy_s(reteta.numeMedic, strlen(numeMedic) + 1, numeMedic);
		cout << "Numar medicamente prescrise: ";
		tastatura >> reteta.nrMedicamentePrescrise;
		if (reteta.doze != NULL) {
			delete[]reteta.doze;
		}
		if (reteta.nrMedicamentePrescrise > 0) {
			reteta.doze = new int[reteta.nrMedicamentePrescrise];
			for (int i = 0;i < reteta.nrMedicamentePrescrise;i++) {
				cout << "Doza " << i + 1 << ": ";
				tastatura >> reteta.doze[i];
			}
		}
		else {
			reteta.doze = NULL;
		}

		cout << "Data emiterii: ";
		tastatura >> reteta.dataEmiterii;

		return tastatura;
	}

	void scrieInFisierBinar(fstream& f) {

		f.write(numePacient.c_str(), numePacient.length() + 1);
		int lungime2 = strlen(this->numeMedic);
		f.write((char*)&lungime2, sizeof(int));
		for (int i = 0;i < lungime2;i++) {
			f.write((char*)&this->numeMedic[i], sizeof(char));
		}

		f.write((char*)&this->nrMedicamentePrescrise, sizeof(int));
		for (int i = 0;i < this->nrMedicamentePrescrise;i++) {
			f.write((char*)&this->doze[i], sizeof(int));
		}

		f.write(dataEmiterii.c_str(), dataEmiterii.length() + 1);

		f.write((char*)&this->durataValabilitateReteta, sizeof(int));
	}

	void citesteDinFisierBinar(fstream& f) {

		getline(f, numePacient, '\0');
		int lungime2;

		f.read((char*)&lungime2, sizeof(int));
		if (this->numeMedic != NULL) {
			delete[]this->numeMedic;
		}
		this->numeMedic = new char[lungime2 + 1];
		for (int i = 0;i < lungime2;i++) {
			f.read((char*)&this->numeMedic[i], sizeof(char));
		}
		this->numeMedic[lungime2] = '\0';

		f.read((char*)&this->nrMedicamentePrescrise, sizeof(int));
		if (this->doze != NULL) {
			delete[]this->doze;
		}
		this->doze = new int[this->nrMedicamentePrescrise];
		for (int i = 0;i < this->nrMedicamentePrescrise;i++) {
			f.read((char*)&this->doze[i], sizeof(int));
		}

		getline(f, dataEmiterii, '\0');

		f.read((char*)&this->durataValabilitateReteta, sizeof(int));
	}
};
int Reteta::durataValabilitateReteta = 90;

int calculeazaSumaDozelor(const Reteta& reteta) {
	int sumaDozelor = 0;
	for (int i = 0;i < reteta.nrMedicamentePrescrise;i++) {
		sumaDozelor += reteta.doze[i];
	}
	return sumaDozelor;
}

bool dozaNedepasesteLimita(const Reteta& reteta, int dozaVerificare) {
	for (int i = 0;i < reteta.nrMedicamentePrescrise;i++) {
		if (reteta.doze[i] > dozaVerificare) {
			return false;
		}
	}
	return true;
}

class Pacient:  public Persoana{
private:
	const int idPacient;
	int nrRetete;
	Reteta* retete;
	bool inTratament;
	static int nrTotalPacienti;
public:

	void afisareDescrierePersoana() {
		cout << " Persoana cu id-ul " << this->idPacient << " este un pacient cu " << this->nrRetete << " retete." << endl;
	}

	Pacient() :idPacient(1000), Persoana() {
		this->nrRetete = 3;
		this->retete = new Reteta[3];
		this->inTratament = 0;
		this->nrTotalPacienti++;
		setCategorie("Pacient");
	}

	Pacient(int idNou, bool eInTratament, int cod, const char* categorie) :idPacient(idNou), inTratament(eInTratament), Persoana(cod, categorie) {
		this->nrRetete = 3;
		this->retete = new Reteta[3];
		this->nrTotalPacienti++;
	}

	Pacient(const Pacient& p) :idPacient(p.idPacient), Persoana(p) {
		this->nrRetete = p.nrRetete;
		if (this->nrRetete > 0) {
			this->retete = new Reteta[p.nrRetete];
			for (int i = 0;i < nrRetete;i++) {
				this->retete[i] = p.retete[i];
			}
		}
		else this->retete = NULL;
		this->inTratament = p.inTratament;
		this->nrTotalPacienti++;
	}

	Pacient operator=(const Pacient& p) {
		if (this != &p) {
			this->nrRetete = p.nrRetete;
			if (this->nrRetete > 0) {
				this->retete = new Reteta[p.nrRetete];
				for (int i = 0;i < nrRetete;i++) {
					this->retete[i] = p.retete[i];
				}
			}
			else this->retete = NULL;
			this->inTratament = p.inTratament;
		}
		return *this;
	}

	~Pacient() {
		if (this->retete != NULL) {
			delete[]this->retete;
		}
	}

	const int getIdPacient() {
		return this->idPacient;
	}

	int getNrRetete() {
		return this->nrRetete;
	}

	Reteta getReteta(int index) {
		if (index > 0 && index < this->nrRetete) {
			return this->retete[index];
		}
	}

	void setRetete(int nrRetete, Reteta* reteta) {
		this->nrRetete = nrRetete;
		if (this->retete != NULL) {
			delete[]this->retete;
		}
		if (nrRetete > 0) {
			retete = new Reteta[nrRetete];
			for (int i = 0;i < this->nrRetete;i++) {
				this->retete[i] = reteta[i];
				cout << endl;
			}
		}
		else {
			this->retete = NULL;
		}
	}

	bool getInTratament() {
		return this->inTratament;
	}

	void setInTratament(bool eInTratament) {
		this->inTratament = eInTratament;
	}

	static int getNrTotalPacienti() {
		return Pacient::nrTotalPacienti;
	}

	static void setNrTotalPacienti(int nrPacienti) {
		Pacient::nrTotalPacienti = nrPacienti;
	}

	Reteta& operator[](int index) {
		if (index >= 0 && index < this->nrRetete) {
			return this->retete[index];
		}
	}

	friend ostream& operator<<(ostream& consola, const Pacient& pacient) {
		consola << pacient.idPacient << (pacient.inTratament ? " Pacientul e in tratament " : " Pacientul nu e in tratament ")
			<< " Nr total de pacienti: " << pacient.nrTotalPacienti << endl;
		consola << " Nr retete ale pacientului: " << pacient.nrRetete << endl;
		if (pacient.nrRetete > 0) {
			for (int i = 0;i < pacient.nrRetete;i++) {
				consola << " Reteta " << i + 1 << ": " << pacient.retete[i] << endl;
			}
		}
		else {
			consola << "Pacientul nu are nicio reteta prescrisa";
		}
		return consola;
	}

	friend istream& operator>>(istream& tastatura, Pacient& pacient) {
		cout << "Numarul de retete ale pacientului: ";
		tastatura >> pacient.nrRetete;
		if (pacient.retete != NULL) {
			delete[]pacient.retete;
		}
		if (pacient.nrRetete > 0) {
			pacient.retete = new Reteta[pacient.nrRetete];
			for (int i = 0;i < pacient.nrRetete;i++) {
				cout << "Reteta " << i + 1 << ": " << endl;
				tastatura >> pacient.retete[i];
			}
		}
		else {
			pacient.retete = NULL;
		}
		cout << "Pacientul este in tratament? (1-DA, 0-NU): ";
		cin >> pacient.inTratament;

		return tastatura;
	}
};
int Pacient::nrTotalPacienti = 0;

class InventarVanzare {
private:
	int nrElemente;
	ElementVanzare** elemente;
public:

	InventarVanzare() {
		this->nrElemente = 10;
		this->elemente = new ElementVanzare * [10];
		for (int i = 0;i < 10;i++) {
			this->elemente[i] = new Medicament();
		}
	}

	ElementVanzare*& operator[](int index) {
		if (index >= 0 && index < this->nrElemente) {
			return this->elemente[index];
		}
	}

	~InventarVanzare() {
		if (this->elemente != NULL) {
			delete[]this->elemente;
		}
	}
};

class RetetaCuCompensare : public Reteta {
private:
	float sumaCompensare;
	char* companieAsigurare;
	const int codAutorizare;
public:
	void afisareDescriere() {
		cout << "Reteta cu numarul " << getNrReteta() << " are o suma de compensare de " << this->sumaCompensare << " lei." << endl;
	}

	RetetaCuCompensare() : Reteta(), codAutorizare(1000) {
		this->sumaCompensare = 100;
		this->companieAsigurare = new char[strlen("RapidAsig") + 1];
		strcpy_s(this->companieAsigurare, strlen("RapidAsig") + 1, "RapidAsig");
	}

	RetetaCuCompensare(float sumaCompensare, int codAutorizare, int nrMedicamente, int* doze) : Reteta(92889, "Maria", nrMedicamente, doze), codAutorizare(codAutorizare) {
		this->sumaCompensare = sumaCompensare;
		this->companieAsigurare = new char[strlen("RapidAsig") + 1];
		strcpy_s(this->companieAsigurare, strlen("RapidAsig") + 1, "RapidAsig");
	}

	RetetaCuCompensare(const RetetaCuCompensare& reteta) :Reteta(reteta), codAutorizare(reteta.codAutorizare) {
		this->sumaCompensare = reteta.sumaCompensare;
		this->companieAsigurare = new char[strlen(reteta.companieAsigurare) + 1];
		strcpy_s(this->companieAsigurare, strlen(reteta.companieAsigurare) + 1, reteta.companieAsigurare);
	}

	RetetaCuCompensare operator=(const RetetaCuCompensare& r) {
		if (this != &r) {
			Reteta::operator=(r);
			this->sumaCompensare = r.sumaCompensare;
			if (this->companieAsigurare != NULL) {
				delete[]this->companieAsigurare;
			}
			this->companieAsigurare = new char[strlen(r.companieAsigurare) + 1];
			strcpy_s(this->companieAsigurare, strlen(r.companieAsigurare) + 1, r.companieAsigurare);
		}
		return *this;
	}

	~RetetaCuCompensare() {
		if (this->companieAsigurare != NULL) {
			delete[]this->companieAsigurare;
		}
	}

	void setSumaCompensare(float suma) {
		if (suma >= 0) {
			this->sumaCompensare = suma;
		}
	}

	float getSumaCoompensare() {
		return this->sumaCompensare;
	}

	void setCompanieAsigurare(const char* companie) {
		if (this->companieAsigurare != NULL) {
			delete[]this->companieAsigurare;
		}
		this->companieAsigurare = new char[strlen(companie) + 1];
		strcpy_s(this->companieAsigurare, strlen(companie) + 1, companie);
	}

	char* getCompanieAsigurare() {
		return this->companieAsigurare;
	}

	const int getCodAutorizare() {
		return this->codAutorizare;
	}

	friend ostream& operator<<(ostream& out, const RetetaCuCompensare& r) {
		out << (Reteta)r;
		out << "Suma compensare: " << r.sumaCompensare << "lei . Companie asigurare: " << r.companieAsigurare
			<< ". Cod autorizare: " << r.codAutorizare << endl;
		return out;
	}

	float calcMediaDozelor(const char* numeCompanieDeAsigurare) { //calc a mediei dozelor din retele cu compensare de la o anumita companie de asigurare
		float media = 0;
		if (strcmp(this->companieAsigurare, numeCompanieDeAsigurare) == 0) {
			int suma = 0;
			for (int i = 0;i < getnrMedicamentePrescrise();i++) {
				suma = suma + getDoze(i);
			}
			media = suma / getnrMedicamentePrescrise();
		}
		else {
			cout << "INVALID" << endl;
		}
		return media;
	}

};

void main() {
	//cout << "MEDICAMENTE:\n" << endl;

	//Medicament medicament1;
	//medicament1.afisare();

	//Medicament medicament2(2123);
	//medicament2.afisare();

	//Medicament medicament3(4211, 21.2);
	//medicament3.afisare();

	//cout << " Valoare TVA: " << Medicament::afisareTaxa() << "%" << endl;

	//cout << "\nCONSTRUCTOR DE COPIERE:" << endl;

	//Medicament medicament4(medicament2);
	//medicament4.afisare();

	//cout << "\nGET-ERI SI SET-ERI: ";

	//cout << medicament4.getCodProdus() << endl;

	//cout << medicament4.getPret() << endl;

	//cout << medicament4.getNume() << endl;

	//cout << (medicament4.getDisponibilitate() ? "Disponibil" : "Indisponibil") << endl;

	//cout << medicament4.getTaxaTva() << "%" << endl;

	//medicament4.setPret(23.10);
	//cout << "Pret nou: " << medicament4.getPret() << endl;

	//const char* numeNou = "Valeriana";
	//medicament4.setNume(numeNou);
	//cout << "Nume nou: " << medicament4.getNume() << endl;

	//medicament4.setDisponibilitate(true);
	//cout << "Disponibilitate actualizata: " << (medicament4.getDisponibilitate() ? "Disponibil" : "Indisponibil") << endl;

	//medicament4.setTaxaTva(5);
	//cout << "Taxa TVA noua: " << medicament4.getTaxaTva() << "%" << endl;

	//cout << "FUNCTII GLOBALE:" << endl;
	//cout << "Calcularea pretului cu reducere" << endl;

	//float procentReducere = 10.0; //10% reducere
	//float pretCuReducere = calculeazaPretCuReducere(medicament4, procentReducere);
	//cout << "Pret cu reducere(10%): " << pretCuReducere << " lei" << endl;

	//cout << "Calcularea pretului fara TVA" << endl;
	//float pretFaraTVA = calculeazaPretFaraTVA(medicament4);
	//cout << "Pret fara TVA: " << pretFaraTVA << " lei" << endl;

	//cout << "OPERATORI:" << endl;

	//cout << "Operatorul = " << endl;

	//Medicament medicament5;
	//medicament5.afisare();

	//medicament5 = medicament2;
	//medicament5.afisare();

	//cout << "Operatorul >> si << " << endl;

	////Medicament medicament7;
	////cin >> medicament7;
	////cout << medicament7;

	//cout << "Operatorul !" << endl;

	//medicament5 = !medicament2;
	//cout << !medicament2;

	//cout << "______________________________________________" << endl;
	//cout << "\nANGAJATI:\n" << endl;

	//Angajat angajat1;
	//angajat1.afisare();

	//Angajat angajat2(42232, "Laura Ungureanu");
	//angajat2.afisare();

	//Angajat angajat3(98722, "Adrian Stan", 1.5, 103090, "Angajat");
	//angajat3.afisare();

	//cout << "Numar maxim de ore lucrate: " << Angajat::afisareNrMaximOreLucrate() << " ore." << endl;

	//cout << "\nCONSTRUCTOR DE COPIERE:" << endl;

	//Angajat angajat4(angajat3);
	//angajat4.afisare();

	//cout << "\nGET-ERI SI SET-ERI: ";

	//cout << angajat4.getId() << endl;

	//cout << angajat4.getNume() << endl;

	//cout << angajat4.getAdresa() << endl;

	//cout << angajat4.getAniExperienta() << endl;

	//cout << angajat4.getNrMaximOreLucrate() << endl;

	//angajat4.setNume("Ioana Stanescu");
	//cout << "Nume nou: " << angajat4.getNume() << endl;

	//const char* adresaNoua = "Pipera";
	//angajat4.setAdresa(adresaNoua);
	//cout << "Adresa noua: " << angajat4.getAdresa() << endl;

	//angajat4.setAniExperienta(5.5);
	//cout << "Ani experienta actualizati: " << angajat4.getAniExperienta() << endl;

	//angajat4.setNrMaximOreLucrate(41);
	//cout << "Nr nou de maxim de ore lucrate: " << angajat4.getNrMaximOreLucrate() << endl;

	//cout << "FUNCTII GLOBALE:" << endl;

	//cout << "Calcularea salariului lunar" << endl;
	//float salariulLunar = calculeazaSalariulLunar(angajat4, 45, 100);
	//cout << "Salariul net: " << salariulLunar << " lei" << endl;

	//cout << "Calcularea bonusului anual in functie de nr de ani de experienta" << endl;
	//float bonusAnual = calculeazaBonusAnual(angajat4);
	//cout << "Bonusul anual: " << bonusAnual << " lei" << endl;

	//cout << "OPERATORI:" << endl;
	//cout << "Operatorul = " << endl;

	//Angajat angajat5;
	//angajat5.afisare();

	//angajat5 = angajat2;
	//angajat5.afisare();

	//cout << "Operatorul >" << endl;
	//cout << angajat2.getAniExperienta() << endl;
	//cout << angajat4.getAniExperienta() << endl;
	//cout << (angajat4 > angajat2 ? "Angajatul2 are mai multi ani de experienta decat angajatul 4" :
	//	"Angajatul2 NU are mai multi ani de experienta decat angajatul 4") << endl;

	//cout << "Operatorul ++" << endl;

	//angajat5 = angajat4++;
	//angajat5.afisare();
	//angajat4.afisare();
	//angajat5 = ++angajat4;
	//angajat5.afisare();
	//angajat4.afisare();

	//cout << "Operatorul de cast:" << endl;

	//float valoareReala = (float)angajat3;
	//cout << valoareReala << endl;

	//cout << "______________________________________________" << endl;
	//cout << "\nReteta:\n" << endl;

	//int* doza;
	//doza = new int[2];
	//doza[0] = 300;
	//doza[1] = 250;
	//Reteta reteta1;
	//reteta1.afisare();

	//const char* descriere = " -------------- ";
	//Reteta reteta2(902, "Maria Mihai", 999, descriere);
	//reteta2.afisare();

	//Reteta reteta3(437, "Daniela Radu", 2, doza);
	//reteta3.afisare();

	//cout << " Durata valabilitate reteta: " << Reteta::afisareDurataValabilitate() << " zile" << endl;

	//cout << "\nCONSTRUCTOR DE COPIERE:" << endl;

	//Reteta reteta4(reteta3);
	//reteta4.afisare();

	//cout << "\nGET-ERI SI SET-ERI: ";

	//cout << reteta4.getNrReteta() << endl;

	//cout << reteta4.getNumePacient() << endl;

	//cout << reteta4.getNumeMedic() << endl;

	//cout << reteta4.getnrMedicamentePrescrise() << endl;

	//cout << reteta4.getDoze(0) << endl << reteta4.getDoze(1) << endl;

	//cout << reteta4.getDataEmiterii() << endl;

	//cout << reteta4.getDurataValabilitateReteta() << endl;

	//reteta4.setNumePacient("Florina Neaga");
	//cout << "Nume pacient actualizat: " << reteta4.getNumePacient() << endl;

	//const char* nume = "Virgil Ionescu";
	//reteta4.setNumeMedic(nume);
	//cout << "Nume medic actualizat: " << reteta4.getNumeMedic() << endl;

	//int* doze = new int[3] {230, 350, 150};

	//reteta4.setMedicamente(3, doze);
	//cout << "Nr medicamente prescrise: " << reteta4.getnrMedicamentePrescrise() << ": \n";
	//for (int i = 0;i < 3;i++) {
	//	cout << reteta4.getDoze(i) << " mg" << endl;
	//}

	//reteta4.setDataEmiterii("04-12-2022");
	//cout << "Data emitere actualizata: " << reteta4.getDataEmiterii() << endl;

	//reteta4.setDurataValabilitateReteta(100);
	//cout << "Durata actualizata a retetei:" << reteta4.getDurataValabilitateReteta() << endl;

	//cout << "FUNCTII GLOBALE:" << endl;
	//cout << "Calcularea sumei tuturor dozelor prescrise" << endl;

	//int sumaDozelor = calculeazaSumaDozelor(reteta4);
	//cout << "Suma dozelor medicamentelor din reteta: " << sumaDozelor << "mg" << endl;

	//cout << "Verificare daca doza prescrisa nu depaseste limita permisa:" << endl;

	//bool rezultat = dozaNedepasesteLimita(reteta4, 600);
	//cout << (rezultat ? "Dozele nu depasesc limita permisa." : "Dozele depasesc limita permisa.") << endl;

	//cout << "OPERATORI:\n" << endl;
	//cout << "Operatorul = " << endl;

	//Reteta reteta5;
	//reteta5.afisare();

	//reteta5 = reteta4;
	//reteta5.afisare();

	//cout << "Operatorul index " << endl;
	//cout << reteta5[2] << " mg" << endl;

	//cout << "Operatorul + " << endl;

	//Reteta reteta6;
	//reteta6 = reteta4 + reteta5;
	//reteta6.afisare();

	//cout << "Operatorul ()" << endl;
	//int sum = reteta6(0, 3);
	//cout << sum << endl;
	//int sum2 = reteta6(3);
	//cout << sum2 << endl;


	//cout << "Vectori si matrici: " << endl;
	//int n;
	//cout << "Numar medicamente: ";
	//cin >> n;

	//Medicament* medicamente = new Medicament[n];
	//for (int i = 0;i < n;i++) {
	//	cin >> medicamente[i];
	//}
	//for (int i = 0;i < n;i++) {
	//	cout << medicamente[i];
	//}

	//cout << "Numar angajati: ";
	//cin >> n;
	//Angajat* angajati = new Angajat[n];
	//for (int i = 0;i < n;i++) {
	//	cin >> angajati[i];
	//}
	//for (int i = 0;i < n;i++) {
	//	cout << angajati[i];
	//}

	//cout << "Numar retete: ";
	//cin >> n;
	//Reteta* retete = new Reteta[n];
	//for (int i = 0;i < n;i++) {
	//	cin >> retete[i];
	//}
	//for (int i = 0;i < n;i++) {
	//	cout << retete[i];
	//}

	//int m, k;
	//cout << "Cate linii are matricea? ";
	//cin >> m;
	//cout << "Cate coloane are matricea? ";
	//cin >> k;

	//Medicament** matriceMedicamente = new Medicament * [m];
	//for (int i = 0;i < m;i++) {
	//	matriceMedicamente[i] = new Medicament[k];
	//	for (int j = 0;j < k;j++) {
	//		cout << "Introduceti datele pentru Medicamentul[" << i << "][" << j << "] ";
	//		cin >> matriceMedicamente[i][j];
	//	}
	//}
	//cout << "Matricea de medicamente: " << endl;
	//for (int i = 0;i < m;i++) {
	//	for (int j = 0;j < k;j++) {
	//		cout<< matriceMedicamente[i][j]<<" ";
	//	}
	//	cout << endl;
	//}

	//for (int i = 0;i < m;i++) {
	//	delete[]matriceMedicamente[i];
	//}

	//cout << "CLASA PACIENT / Relatie has a" << endl;

	//Pacient pacient1;
	//cout << pacient1;

	//Pacient pacient2(pacient1);
	//cout << pacient2;

	//cout << "GET SI SET" << endl;

	//Pacient pacient4;

	//Reteta* listaRetete = new Reteta[3]{ reteta2, reteta3, reteta4 };
	//pacient4.setRetete(2, listaRetete);
	//pacient4.setInTratament(1);
	//pacient4.setNrTotalPacienti(0);
	//cout << pacient4.getIdPacient() << " - " << pacient4.getInTratament() << " - "
	//	<< pacient4.getNrTotalPacienti << " - " << pacient4.getNrRetete() << " - " << pacient4.getReteta(1) << endl;

	//cout << "Operatori:" << endl << endl;

	//cout << "Operatorul index" << endl;
	//pacient1[1] = reteta6;
	//cout << pacient1[1].getNumePacient() << endl;
	//cout << pacient1[1][0] << endl;

	//cout << "Operatorul =" << endl;
	//pacient4 = pacient2;
	//cout << pacient4;

	//cout << "Operatorul >> si <<" << endl;

	////Pacient pacient3;
	////cin >> pacient3;
	////cout << pacient3;

	//cout << " Fisiere text: " << endl;

	//Medicament medicament8(4288, 21);
	//medicament8.setNume("Oticalm");
	//medicament8.setDisponibilitate(1);
	//cout << medicament8;

	//ofstream fisier("medicamente.txt", ios::out);
	//fisier << medicament8;

	//fisier.close();

	//Medicament medicament9;
	//ifstream fis("medicamente.txt", ios::in);
	//fis >> medicament9;
	//cout << medicament9;

	//fis.close();

	//Angajat angajat6(4902, "Marin", 9, 988822, "Angajat");
	//cout << angajat6;

	//ofstream f("angajati.txt", ios::out);
	//f << angajat6;

	//f.close();

	//Angajat angajat7;
	//ifstream g("angajati.txt", ios::in);
	//g >> angajat7;

	//cout << angajat7;

	//g.close();

	////delete[]matriceMedicamente;
	////delete[]retete;
	////delete[]angajati; 
	////delete[]medicamente;
	//delete[]doze;
	//delete[]doza;

	//cout << " Fisiere binare: " << endl;

	//Angajat angajat8(angajat6);
	//cout << angajat8;
	//fstream fisierBinar("angajat.txt", ios::out | ios::binary);
	//angajat8.scrieInFisierBinar(fisierBinar);

	//fisierBinar.close();

	//fstream fisBinar("angajat.txt", ios::in | ios::binary);
	//Angajat angajat9;
	//angajat9.citesteDinFisierBinar(fisBinar);
	//cout << angajat9;
	//fisBinar.close();

	//Reteta reteta7(reteta3);

	//cout << reteta7;

	//fstream fb("reteta.txt", ios::out | ios::binary);
	//reteta7.scrieInFisierBinar(fb);

	//fb.close();

	//fstream fbin("reteta.txt", ios::in | ios::binary);
	//Reteta reteta8;
	//reteta8.citesteDinFisierBinar(fbin);
	//cout << reteta8;

	//fbin.close();

	//cout << "Mostenire: " << endl;

	//Antibiotic a1;
	//a1.setNume("Amoxicilina");
	//Antibiotic a2("Sirop", 1, 40200);
	//cout << a1 << endl << a2 << endl;

	//Antibiotic a3(a2);
	//cout << a3 << endl;

	//a3.setFormaFarmaceutica("Comprimate");

	//const char* clasa = "Sulfonamide";
	//a3.setClasa(clasa);

	//a3.setNecesitaReteta(0);

	//cout << a3.getFormaFarmaceutica() << ". " << a3.getClasa() << ". " << (a3.getNecesitaReteta() ? "Necesita reteta." : "Nu necesita reteta") << endl;
	//a2 = a3;
	//cout << a2 << endl;

	//int* vectorDoze = new int[2] {220, 300};
	//RetetaCuCompensare r1;
	//RetetaCuCompensare r2(250, 9399, 2, vectorDoze);
	//cout << r1 << endl << r2 << endl;

	//RetetaCuCompensare r3(r2);
	//cout << r3 << endl;

	//r3.setSumaCompensare(375);
	//const char* companieAsigurare = "GARANTIE SA";
	//r3.setCompanieAsigurare(companieAsigurare);

	//cout << r3.getSumaCoompensare() << " " << r3.getCompanieAsigurare() << " " << r3.getCodAutorizare() << endl;

	//r1 = r3;
	//cout << r1 << endl;

	//cout << "Pretul actual: " << a3.getPret() << " Pretul estimat dupa scumpire: " << a3.calcPretEstimativDupaScumpire() << endl;
	//a3.setNecesitaReteta(1);
	//cout << "Pretul actual: " << a3.getPret() << " Pretul estimat dupa scumpire: " << a3.calcPretEstimativDupaScumpire() << endl;
	//cout << "Media dozelor: " << r3.calcMediaDozelor("GARANTIE SA") << endl;
	//cout << "Media dozelor: " << r2.calcMediaDozelor("GARANTIE SA") << endl;

	//cout << "Upcasting" << endl;

	//Medicament* medicament10 = &a3;
	//cout << *medicament10 << endl;

	//Reteta* reteta10 = &r1;
	//cout << *reteta10 << endl;

	cout << "Clase abstracte" << endl;
	ElementVanzare* e1 = new Medicament();
	e1->afisareDescriere();
	cout << e1->getCodElement() << endl;
	e1->setDescriereSuplimentara(" DESCRIERE ");
	cout << e1->getDescriereSuplimentara() << endl;

	delete e1;

	InventarVanzare inventarVanzare;

	inventarVanzare[0] = new Medicament(29839, 45.8);
	inventarVanzare[1] = new Antibiotic("Sirop", 0, 12909);
	inventarVanzare[2] = new Reteta(83781, "Ionescu", 7482, " Expirata. ");
	inventarVanzare[3] = new Antibiotic("Comprimate", 1, 94311);
	inventarVanzare[4] = new Medicament(98888, 9.29);
	inventarVanzare[5] = new Antibiotic();
	inventarVanzare[6] = new Medicament(12455, 20.99);
	inventarVanzare[7] = new Antibiotic("Capsule", 1, 96543);
	inventarVanzare[8] = new Reteta();
	inventarVanzare[9] = new Antibiotic();

	for (int i = 0;i < 10;i++) {
		inventarVanzare[i]->afisareDescriere();
	}

	Persoana** persoane;
	persoane = new Persoana * [10];
	persoane[0] = new Angajat(87427, "Cebanu", 1, 93472, "Angajat");
	persoane[1] = new Angajat();
	persoane[2] = new Pacient(74567, 0, 3456, "Client");
	persoane[3] = new Angajat(13800, "Ionescu");
	persoane[4] = new Pacient();
	persoane[5] = new Pacient(20034, 1, 78902, "Client");
	persoane[6] = new Angajat(28883, "Dumitrescu");
	persoane[7] = new Pacient();
	persoane[8] = new Angajat();
	persoane[9] = new Angajat(81882, "Obada", 10, 78900, "Angajat");

	for (int i = 0;i < 10;i++) {
		persoane[i]->afisareDescrierePersoana();
	}

	delete[]persoane;

}