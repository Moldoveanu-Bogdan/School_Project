#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class interfata
{
	virtual void afisareAtribut() = 0;
};


class ExceptieFilm :public exception
{
	string eroare;
public:
	ExceptieFilm(string message) {
		this->eroare = message;
	}

	
	const char* afisare()  {
		return this->eroare.c_str();
	}
};






class Film
{

private:
	char* nume;
	int durata; //durata filmului in minute
	int anAparitie;
	int nr_cinematografe;
	float* incasari; //incasarile per fiecare cinematograf in care a fost difuzat filmul(vector alocat dinamic contorizat de nr_cinematografe).
	const int id;
	static int nr_filme;


public:


	Film() :id(100)
	{
		this->nume = new char[11];
		strcpy(this->nume, "Necunoscut");
		this->nr_cinematografe = 0;
		this->incasari = NULL;
		this->anAparitie = -1;
		this->durata = 0;
		Film::nr_filme++;
	}



	static int idCorect(int id)// validarea pentru atributul id
	{
		if (id >= 0) return id;
		else throw new ExceptieFilm("Id incorect.");

	}

	Film(int idNou, const char* numeNou, float* incasariNoi, int nrCinema, int an, int durata) :id(idCorect(idNou))
	{
		if (strlen(numeNou) > 2) {

			this->nume = new char[strlen(numeNou) + 1];
			strcpy(this->nume, numeNou);
		}
		else throw new ExceptieFilm("Nume gresit.");

		if (nrCinema > 0 && incasariNoi != NULL)
		{

			this->nr_cinematografe = nrCinema;
			this->incasari = new float[nrCinema];
			for (int i = 0; i < nrCinema; i++)
			{
				if (incasariNoi[i] > 0)  this->incasari[i] = incasariNoi[i];
				else throw new ExceptieFilm("Input-ul pentru vectorul de incasari este gresit.");
			}

		}
		else throw new ExceptieFilm("Input-ul pentru nr_cinematografe sau vectorul de incasari este gresit.");

		if (an >= 1900 && an <= 2022) this->anAparitie = an;
		else throw new ExceptieFilm("Anul aparitiei este gresit.");
		if (durata > 60) this->durata = durata;
		else throw new ExceptieFilm("Durata filmului a fost introdusa gresit.");
		Film::nr_filme++;
	}

	Film(float* incasariNoi, int nrCinema) :id(100)
	{
		this->nume = new char[11];
		strcpy(this->nume, "Necunoscut");

		if (nrCinema > 0 && incasariNoi != NULL)
		{

			this->nr_cinematografe = nrCinema;
			this->incasari = new float[nrCinema];
			for (int i = 0; i < nrCinema; i++)
			{
				if (incasariNoi[i] > 0)  this->incasari[i] = incasariNoi[i];
				else throw new ExceptieFilm("Input-ul pentru vectorul de incasari este gresit.");
			}

		}
		else throw new ExceptieFilm("Input-ul pentru nr_cinematografe sau vectorul de incasari este gresit.");
		this->durata = 0;
		this->anAparitie = -1;
		Film::nr_filme++;
	}
	
	Film(const Film& sursa) :id(sursa.id)
	{
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);

		this->nr_cinematografe = sursa.nr_cinematografe;

		this->incasari = new float[sursa.nr_cinematografe];
		for (int i = 0; i < sursa.nr_cinematografe; i++)
			this->incasari[i] = sursa.incasari[i];

		this->anAparitie = sursa.anAparitie;
		this->durata = sursa.durata;
		Film::nr_filme++;
	}

	Film& operator=(const Film& sursa)
	{
		if (this != &sursa)
		{
			delete[] this->nume;
			delete[] this->incasari;

			this->nume = new char[strlen(sursa.nume) + 1];
			strcpy(this->nume, sursa.nume);

			this->nr_cinematografe = sursa.nr_cinematografe;

			this->incasari = new float[sursa.nr_cinematografe];
			for (int i = 0; i < sursa.nr_cinematografe; i++)
				this->incasari[i] = sursa.incasari[i];
			this->durata = sursa.durata;
			this->anAparitie = sursa.anAparitie;
		}
		return *this;

	}

	
	~Film()
	{
		if (this->nume != NULL)
			delete[] this->nume;
		if (this->incasari != NULL)
			delete[] this->incasari;
		Film::nr_filme--;
	}

	
	static  int getNrFilme()
	{
		return Film::nr_filme;
	}

	char* getNume()
	{
		return this->nume;
	}

	int getNrCinematografe()
	{
		return this->nr_cinematografe;
	}

	int getAnAparitie()
	{
		return this->anAparitie;
	}

	int getId()
	{
		return this->id;
	}

	int getDurata()
	{
		return this->durata;
	}

	
	void setIncasari(float* incasariNoi, int nrCinema)
	{
		if (nrCinema > 0 && incasariNoi != NULL)
		{
			delete[]this->incasari;
			this->nr_cinematografe = nrCinema;
			this->incasari = new float[nrCinema];
			for (int i = 0; i < nrCinema; i++)
			{
				if (incasariNoi[i] > 0)  this->incasari[i] = incasariNoi[i];
				else throw new ExceptieFilm("Input-ul pentru vectorul de incasari este gresit.");
			}

		}
		else throw new ExceptieFilm("Input-ul pentru nr_cinematografe sau vectorul de incasari este gresit.");

	}

	void setAnAparitie(int an)
	{
		if (an >= 1900 && an <= 2022) this->anAparitie = an;
		else throw new ExceptieFilm("Anul aparitiei este gresit.");
	}

	void setNume(const char* numeNou)
	{

		if (strlen(numeNou) > 2) {
			delete[]this->nume;
			this->nume = new char[strlen(numeNou) + 1];
			strcpy(this->nume, numeNou);
		}
		else throw new ExceptieFilm("Nume gresit.");
	}


	void setDurata(int durata)
	{
		if (durata > 60) this->durata = durata;
		else throw new ExceptieFilm("Durata filmului a fost introdusa gresit.");
	}

	
	friend ostream& operator<<(ostream& out, Film sursa)
	{
		out << endl;
	
		out << "Filmul " << sursa.nume << " aparut in anul " << sursa.anAparitie << ", cu id " << sursa.id << " si durata de " << sursa.durata << " minute," << endl;
		if (sursa.nr_cinematografe > 0 && sursa.incasari != NULL)
		{
			out << "a fost difuzat in " << sursa.nr_cinematografe << " cinematografe si a inregistrat veniturile: ";
			for (int i = 0; i < sursa.nr_cinematografe; i++)
			{
				out << sursa.incasari[i];
				if (i < sursa.nr_cinematografe - 1) cout << ", ";
			}
		}
		else out << "nu a fost difuzat inca.";

		return out;
	}

	friend istream& operator  >> (istream& in, Film& sursa)
	{
		cout << endl;
		cout << "Numele: ";
		char aux[200];
		in.getline(aux,100);
		if (strlen(aux) > 2)
		{
			delete[] sursa.nume;
			sursa.nume = new char[strlen(aux) + 1];
			strcpy(sursa.nume, aux);

		}
		cout << "Nr cinematografe: ";
		int auxnr;
		in >> auxnr;
		float auxnote[200];
		for (int i = 0; i < auxnr; i++) {
			cout << "Incasari pt cinematogarful " << i + 1 << ": ";
			in >> auxnote[i];
		}

		if (auxnr > 0 && auxnote != NULL)
		{
			sursa.nr_cinematografe = auxnr;
			delete[] sursa.incasari;
			sursa.incasari = new float[auxnr];
			for (int i = 0; i < auxnr; i++) {
				if (auxnote[i] > 0) {
					sursa.incasari[i] = auxnote[i];
				}
				else {
					sursa.incasari[i] = 0;
				}

			}

		}


		int an;
		cout << "An Aparitie: ";
		in >> an;
		if (an >= 1900 && an <= 2022) sursa.anAparitie = an;


		cout << "Durata filmului: ";
		int durata;
		in >> durata;
		if (durata > 60)sursa.durata = durata;

		return in;
	}
	
	friend ofstream& operator << (ofstream& out, Film sursa)
	{
		int lungimeNume = (strlen(sursa.nume) + 1);
		out.write((char*)&lungimeNume, sizeof(int));
		out.write(sursa.nume, lungimeNume);
		out.write((char*)&sursa.durata, sizeof(int));
		out.write((char*)&sursa.anAparitie, sizeof(int));
		out.write((char*)&sursa.nr_cinematografe, sizeof(int));
		for(int i=0;i<sursa.nr_cinematografe;i++)
			out.write((char*)&sursa.incasari[i], sizeof(float));
		return out;
	 }

	friend ifstream& operator>>(ifstream& in, Film& sursa)
	{
		int lungimeNume;
		in.read((char*)&lungimeNume, sizeof(int));
		delete[]sursa.nume;
		sursa.nume = new char[lungimeNume];
		in.read(sursa.nume, lungimeNume);
		in.read((char*)&sursa.durata, sizeof(int));
		in.read((char*)&sursa.anAparitie, sizeof(int));
		in.read((char*)&sursa.nr_cinematografe, sizeof(int));
		delete[]sursa.incasari;
		sursa.incasari = new float[sursa.nr_cinematografe];
		for (int i = 0;i < sursa.nr_cinematografe;i++)
			in.read((char*)&sursa.incasari[i], sizeof(float));
		return in;
	}

	void scriereFisier(ofstream& out)
	{
		out << this->durata << endl;
		out << this->nume << endl;
		out << this->anAparitie << endl;
		out << this->nr_cinematografe << endl;
		for(int i=0;i<this->nr_cinematografe;i++)
			out << this->incasari[i] << endl;
	
	}

	void citireFisier(ifstream& in)
	{
		in >> this->durata;
		delete[] this->nume;
		char buffer[200];
		in.ignore();
		in.getline(buffer, 200);
		this->nume = new char[strlen(buffer) + 1];
		strcpy(this->nume, buffer);
		in >> this->anAparitie;
		in >> this->nr_cinematografe;
		delete[] this->incasari;
		this->incasari = new float[this->nr_cinematografe];
		for (int i = 0;i < this->nr_cinematografe;i++)
			in >> this->incasari[i];

	}


	Film& operator--()
	{
		this->durata -= 30;
		if (this->durata < 0)this->durata = 0;
		return *this;
	}

	Film operator--(int)
	{
		Film copie = *this;
		this->durata -= 30;
		if (this->durata < 0)this->durata = 0;
		return copie;
	}

	
	Film operator-(int scade)
	{
		Film copie = *this;
		copie.durata -= scade;
		if (copie.durata < 0) copie.durata = 0;
		return copie;
	}

	friend Film operator-(int scade, Film copie)
	{
		copie.durata -= scade;
		if (copie.durata < 0) copie.durata = 0;
		return copie;
	}


	Film operator-(Film copie1)
	{
		Film copie2 = *this;
		if (copie1.durata < copie2.durata)
			copie2.durata -= copie1.durata;
		else copie2.durata = 0;
		return copie2;
	}
	float operator[](int index)
	{
		if (index >= 0 && index <= this->nr_cinematografe - 1)
			return this->incasari[index];
		else throw new ExceptieFilm("Input gresit.");
	}

	void operator()(int index)// afiseaza primele "index" elemente din vectorul obiectului pt care a fost apelat
	{
		if (index > 0 && index <= this->nr_cinematografe)
		{
			for (int i = 0; i < index; i++)
				cout << this->incasari[i] << " ";
		}
		else throw new ExceptieFilm("Index gresit.");
	}

	explicit operator float()
	{
		float suma = 0;
		for (int i = 0; i < this->nr_cinematografe; i++)
			suma += this->incasari[i];
		return suma / this->nr_cinematografe;
	}

	bool operator!()
	{
		if (this->nr_cinematografe > 0) return false;
		else return true;
	}


	
	bool operator == (const Film& f) {
		if (this == &f) return true;
		bool dup = strcmp(this->nume, f.nume) == 0 && this->anAparitie == f.anAparitie && this->durata == f.durata && this->nr_cinematografe == f.nr_cinematografe;
		if (dup) {
			for (int i = 0;i < this->nr_cinematografe;i++)
			{
				if (this->incasari[i] != f.incasari[i]) return false;
			}
			return true;
		}
		else return false;
	}

 
	void afisareAtribut()
	{
		cout <<endl<<"Numele este: " << nume;
	}


};
 int Film::nr_filme = 0;

 void duplicate(Film* f, int n)
 {
	 cout << endl;
	 int* v = new int[n] {0};
	 for (int i = 0;i < n;i++)
	 {
		 if (v[i] == 0) {
			 v[i] = i+1;

			 for (int j = i + 1;j < n;j++)

				 if (f[i] == f[j]) v[j] = i+1;

		 }
	 } // dupa finalizarea acestei secvente in vectorul v vom avea urmatoarele valori:{1,2,1,1,2} pentru vectorul de obiecte {f1,f2,f1,f1,f2}
	 int k;
	 for (int i = 0;i < n;i++)
	 {
		 k = 0;
		 for (int j = 0;j < n;j++)
		
			 if (i+1 == v[j]) k++;
		 if (k > 0)
			 cout << "Filmul cu numele :" << f[i].getNume() << " apare in vector de: " << k << " ori." << endl;
	 }
	 delete[]v;
 }


 class genFilm : public Film
 {
 private:
	 string gen;
	 float nota;
 public:
	 genFilm() : Film()
	 {
		this-> gen = "na";
		 this->nota = -1;
	 }
	 genFilm(int idNou, const char* numeNou, float* incasariNoi, int nrCinema, int an, int durata, float notaNoua, const char* genNou) : Film(idNou, numeNou, incasariNoi, nrCinema, an, durata)
	 {
		 if (notaNoua >= 1 && notaNoua <= 10)
			 this->nota = notaNoua;
		 else throw new ExceptieFilm("Nota invalida");
		 if (strlen(genNou) > 2)
			 this->gen = genNou;
		 else throw new ExceptieFilm("Gen invalid");
	 }

	 genFilm(const genFilm& sursa) : Film(sursa)
	 {
		 this->gen = sursa.gen;
		 this->nota = sursa.nota;
	 }


	 genFilm& operator=(const genFilm& sursa)
	 {
		 if (this != &sursa)
		 {
			 Film::operator=(sursa);
			 this->gen = sursa.gen;
			 this->nota = sursa.nota;
		 }
		 return *this;
	 }

	 friend ostream& operator<<(ostream& out, genFilm& sursa)
	 {
		 out << endl;
		 out << (Film)sursa;
		 out << endl << "Genul filmului: " << sursa.gen;
		 out << endl << "Nota: " << sursa.nota;
		 out << endl;
		 return out;
	 }

	 void afisareAtribut()
	 {
		 cout<<endl<<"Nota este: " << nota;
	 }

 };

 class Actori : public Film
 {
 private:
	 int nrActori;
	 char** numeActori; //vector de siruri de caractere alocat dinamic

 public:
	 Actori() : Film()
	 {
		 this->nrActori = 0;
		 this->numeActori = NULL;
	 }

	 Actori(int idNou, const char* numeNou, float* incasariNoi, int nrCinema, int an, int durata, int nrActori,const  char** numeActori) : Film(idNou, numeNou, incasariNoi, nrCinema, an, durata)
	 {
		 if (nrActori >= 0)
			 this->nrActori = nrActori;
		 else throw new ExceptieFilm("Nu pot fi mai putin de 0 actori :)");
		 if (nrActori > 1 && numeActori != NULL)
		 {
			 this->numeActori = new char* [nrActori];
			 for (int i = 0; i < nrActori; i++)
			 {
				 if (strlen(numeActori[i]) > 3)
				 {
					 this->numeActori[i] = new char[strlen(numeActori[i]) + 1];
					 strcpy(this->numeActori[i], numeActori[i]);
				 }
				 else 
				 {
					 throw new ExceptieFilm("Nume incorect.");
					 this->numeActori[i] = new char[strlen("NA") + 1];
					 strcpy(this->numeActori[i], "NA");
				 }
			 }
		 }
		 else throw new ExceptieFilm("Input pentru actori gresit.");
	 }

	 Actori(const Actori& sursa) : Film(sursa)
	 {
		 this->nrActori = sursa.nrActori;
		 this->numeActori = new char* [nrActori];
		 for (int i = 0; i < nrActori; i++)
		 {
			 this->numeActori[i] = new char[strlen(sursa.numeActori[i]) + 1];
			 strcpy(this->numeActori[i], sursa.numeActori[i]);
		 }
	 }
	 Actori& operator=(const Actori& sursa)
	 {
		 if (this != &sursa)
		 {
			 Film::operator=(sursa);
			 for (int i = 0; i < this->nrActori; i++)
			 {
				 delete[] this->numeActori[i];
			 }
			 delete[] this->numeActori;
			 this->nrActori = sursa.nrActori;
			 this->numeActori = new char* [nrActori];
			 for (int i = 0; i < nrActori; i++)
			 {
				 this->numeActori[i] = new char[strlen(sursa.numeActori[i]) + 1];
				 strcpy(this->numeActori[i], sursa.numeActori[i]);
			 }
		 }
		 return *this;
	 }


	 ~Actori()
	 {
		 for (int i = 0; i < nrActori; i++) {
			 delete[] this->numeActori[i];
		 }
		 delete[] this->numeActori;
	 }



	 friend ostream& operator<<(ostream& out, const Actori& sursa) 
	 {
		 out << (Film)sursa;
		 out << endl;
		 out << "Actori: ";
		 for (int i = 0; i < sursa.nrActori; i++) {
			 out << sursa.numeActori[i] << " ";
		 }
		 return out;
	 }

	 void afisareAtribut()
	 {
		 cout<<endl<<"Nr de actori este: " << nrActori;
	 }

 };

 class Cinema
 {
 private:
	 int nrLocuri;
	 int nrFilme;
	 Film* filme;
 public:

	 Cinema()
	 {
		 this->nrLocuri = 0;
		 this->nrFilme = 0;
		 this->filme = NULL;
	 }

	 Cinema(int locuri, int nrFilm, Film* filme)
	 {
		 if (locuri >= 0)
			 this->nrLocuri = locuri;
		 else throw new ExceptieFilm("Prea putine locuri");
		 if (nrFilm >= 0)
			 this->nrFilme = nrFilm;
		 else throw new ExceptieFilm("Prea putine filme");
		 if (nrFilm > 0 && filme != NULL)
		 {
			 this->filme = new Film[nrFilm];
			 for (int i = 0;i < nrFilm;i++)
				 this->filme[i] = filme[i];
		 }
		 else throw new ExceptieFilm("Input invalid pentru filme");
	 }

	 Cinema(const Cinema& sursa)
	 {
		 this->nrLocuri = sursa.nrLocuri;
		 this->nrFilme = sursa.nrFilme;
		 this->filme = new Film[sursa.nrFilme];
		 for (int i = 0;i < sursa.nrFilme;i++)
			 this->filme[i] = sursa.filme[i];
	 }

	 Cinema& operator=(const Cinema& sursa)
	 {
		 if (this != &sursa)
		 {
			 this->nrLocuri = sursa.nrLocuri;
			 this->nrFilme = sursa.nrFilme;
			 delete[]this->filme;
			 this->filme = new Film[sursa.nrFilme];
			 for (int i = 0;i < sursa.nrFilme;i++)
				 this->filme[i] = sursa.filme[i];
		 }
		 return *this;
	 }

	 ~Cinema()
	 {
		 delete[] this->filme;
	 }

	 friend ostream& operator<<(ostream& out, const Cinema& c) 
	 {
		 out << "Cinema: " << endl;
		 out << "Numarul de locuri: " << c.nrLocuri << endl;
		 out << "Numarul de filme: " << c.nrFilme << endl;
		 out << "Filme:" << endl;
		 for (int i = 0; i < c.nrFilme; i++) 
		 {
			 out << "=========" ;
			 out << c.filme[i] << endl;
			 out << "=========" << endl<<endl;
		 }

		 return out;
	 }
	 void afisareAtribut()
	 {
		 cout << endl<<"Nr de locuri este: " << nrLocuri;
	 }

 };

int main()
{
	Film f1;
	float incasari[]{ 300,200,500 };
	Film f2(1003, "Interstellar", incasari, 3, 2014, 16);
	Film f3(incasari, 3);
	Film f4 = f2;
	Film f5;

	Cinema c1(200, 3, new Film[3]{ f1,f2,f3 });
	Cinema c2(c1);
	Cinema c3;
	c3 = c2;
	cout << endl<<"c3: " << c3;

	Actori a1(1003, "Interstellar", incasari, 3, 2014, 169, 3, new const char* [3] {"Matthew McConaughey", "Jessica Chastain", "Timothée Chalamet"});
	Actori a2(a1);
	Actori a3;
	a3 = a1;
	cout << endl <<"a3: " << a3;

	cout << endl;

	//EXCEPTIE
	try
	{
		Film f10(1005, "d", incasari, 3, 2014, 150);

	 }
	catch (ExceptieFilm* e) {
		cout <<endl << e->afisare();
	}

	cout << endl;

	genFilm gf1(1003, "Interstellar", incasari, 3, 2014, 169,7,"sci-fi");
	genFilm gf2(gf1);

	cout << endl;
	//INTERFATA
	cout << "INTERFATA:" << endl;
	f2.afisareAtribut();
	cout << endl;
	gf1.afisareAtribut();
	cout << endl;
	a1.afisareAtribut();
	cout << endl;
	c1.afisareAtribut();
	cout << endl;
	cout << "==========" << endl;

	ofstream fout;
	fout.open("fisierBinar.bin", ofstream::binary);
	if (fout.is_open()) {

		fout << f2;
		fout.close();
	}


	Film f10;
	ifstream fin;
	fin.open("fisierBinar.bin", ifstream::binary);
	if (fin.is_open()) {
		fin >> f10;
		fin.close();
	}
	cout << "FISIER BINAR: " << endl;
	cout << f10;

	ofstream fout1;
	fout1.open("fisiertxt.txt", ofstream::out);
	if (fout1.is_open()) {

		f2.scriereFisier(fout1);
		fout1.close();
	}

	ifstream fin1;
	fin1.open("fisiertxt.txt", ifstream::in);
	if (fin1.is_open()) {
		f10.citireFisier(fin1);
		fin1.close();
	}
	cout << endl << "FISIER TEXT: " << endl;
	cout << f10;
	cout << endl;
	//polimorfismul se realizeaza prin supraincarcare sau prin functii virtuale dintre care ambele au fost folosite.

	return 0;
}