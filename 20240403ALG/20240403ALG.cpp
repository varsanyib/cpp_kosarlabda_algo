//Algoritmusok �s adatstrukt�r�k - laborgyakorlat 2024.04.03.

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Jatekos
{
	string vezeteknev, csapat;
	int mezszam = 0, magassag = 0, pont = 0;
};
int main()
{
	setlocale(LC_ALL, "hu_HU");
	srand((unsigned int)time(NULL));

	Jatekos* jatekosok = new Jatekos[18];
	string csapatNev1, csapatNev2;
	int db = 0, i = 0, j = 0, db1 = 0, db2 = 0, sum1 = 0, sum2 = 0;

	do
	{
		cout << "K�rem az els� csapat nev�t: ";
		getline(cin, csapatNev1);

		cout << "K�rem a m�sodik csapat nev�t: ";
		getline(cin, csapatNev2);

		if (csapatNev1 == csapatNev2)
		{
			cerr << "\nHiba! A k�t csapatn�v nem egyezhet meg!" << endl;
		}
	} while (csapatNev1 == csapatNev2);
	//Beolvas�s 1. csapat
	ifstream file1("csapat1.txt");
	if (file1.fail())
	{
		cerr << "\nHiba t�rt�nt az els� csapat adainak beolvas�sa k�zben! " << endl;
		exit(1);
	}

	while (i < 18 && !file1.eof())
	{
		jatekosok[i].csapat = csapatNev1;
		file1 >> jatekosok[i].vezeteknev;
		file1 >> jatekosok[i].mezszam;
		jatekosok[i].magassag = (rand() % 46) + 180;
		jatekosok[i].pont = (rand() % 36);
		sum1 += jatekosok[i].pont;
		i++;
	}
	db1 = i;
	file1.close();
	//Beolvas�s 2. csapat
	ifstream file2("csapat2.txt");
	if (file2.fail())
	{
		cerr << "\nHiba t�rt�nt a m�sodik csapat adainak beolvas�sa k�zben! " << endl;
		exit(2);
	}

	while (i < 20 && !file2.eof())
	{
		jatekosok[i].csapat = csapatNev2;
		file2 >> jatekosok[i].vezeteknev;
		file2 >> jatekosok[i].mezszam;
		jatekosok[i].magassag = (rand() % 46) + 180;
		jatekosok[i].pont = (rand() % 36);
		sum2 += jatekosok[i].pont;
		i++;
	}
	db2 = i - db1;
	file2.close();

	db = i;
	
	//Kiirat�s
	cout.setf(ios::left);
	cout << csapatNev1 <<  setw(5) << "\t" << sum1  <<  setw(5) << "\t" << csapatNev2  << "\t" << sum2 << endl;
	cout << "\nn�v" << setw(7) << "\tpont"  << "\tn�v" << setw(7) << "\tpont" << endl;
	for (i = 0; i < db1; i++)
	{
		cout << jatekosok[i].vezeteknev << setw(5) << "\t" << jatekosok[i].pont  << "\t" << jatekosok[db2+i].vezeteknev << setw(5) << "\t" << jatekosok[db2+i].pont << endl;
	}

	//Legalacsonyabb j�t�kos
	Jatekos min = jatekosok[0];
	for (i = 0; i < db; i++)
	{
		if (jatekosok[i].magassag < min.magassag)
		{
			min = jatekosok[i];
		}
	}
	cout << "\nLegalacsonyabb j�t�kos: " << min.vezeteknev << " (mezsz�m: " << min.mezszam << ")" << endl;

	//Nem dobott pontot j�t�kos
	i = 0;
	while (i < db && jatekosok[i].pont != 0)
	{
		i++;
	}
	if (i < db) cout << "\nVolt olyan j�t�kos, aki nem dobott pontot." << endl;
	else cout << "\nNem volt olyan j�t�kos, aki nem dobott pontot!" << endl;

	//Legt�bb pont, csapatonk�nt
	Jatekos max = jatekosok[0];
	for (i = 0; i < db; i++)
	{
		if (jatekosok[i].pont > max.pont) max = jatekosok[i];
	}
	cout << "\nLegt�bb pontot dob� j�t�kos: " << max.vezeteknev << " (csapat: " << max.csapat << ")" << endl;

	//M�rk�z�s �s csoport�tlag
	cout << "\n�sszes �tlag: " << (double)((sum1 + sum2) / db) << endl;
	cout << csapatNev1 << "csapat �tlaga: " << (double)(sum1 / db1) << endl;
	cout << csapatNev2 << "csapat �tlaga: " << (double)(sum2 / db2) << endl;

	//Sz�ls�s�gvizsg�lat
	Jatekos max1 = jatekosok[0], max2 = jatekosok[0], min1 = jatekosok[0], min2 = jatekosok[0];
	for (int i = 0; i < db; i++)
	{
		if (jatekosok[i].csapat == csapatNev1)
		{
			//Csapat 1.
			if (max1.pont > jatekosok[i].pont) max1 = jatekosok[i];
			if (min1.pont < jatekosok[i].pont) min1 = jatekosok[i];
		}
		else {
			//Csapat 2.
			if (max2.pont > jatekosok[i].pont) max2 = jatekosok[i];
			if (min2.pont < jatekosok[i].pont) min2 = jatekosok[i];
		}
	}
	if ((max1.pont - min1.pont) == (max2.pont - min2.pont)) cout << "\nSz�ls�s�gvizsg�latban d�ntetlen lett az eredm�ny!" << endl;
	else if ((max1.pont - min1.pont) > (max2.pont - min2.pont)) cout << "\nA(z) " << min1.csapat << " dobott sz�ls�s�gesen!" << endl;
	else cout << "\nA(z) " << min2.csapat << " dobott sz�ls�s�gesen!" << endl;

	//rendez�s magass�g szerint
	Jatekos temp;
	for (i = 0; i < db - 1; i++)
	{
		for (j = i + 1; j < db; j++)
		{
			if (jatekosok[i].magassag > jatekosok[j].magassag)
			{
				temp = jatekosok[i];
				jatekosok[i] = jatekosok[j];
				jatekosok[j] = temp;
			}
		}
	}

	//ki�rat�s magass�g szerint
	cout << "\nMagass�g szerinti rendez�s: " << endl;
	for (i = 0; i < db; i++)
	{
		cout << jatekosok[i].vezeteknev << "\t" << jatekosok[i].magassag << " cm\t" << jatekosok[i].pont << endl;
	}

	//ki�r�s fileba
	cout << "\nTop 3 ki�rat�s f�jlba... ";
	ofstream fileOut("legjobbak.txt");
	if (fileOut.fail())
	{
		cerr << "\nHiba t�rt�nt a legjobbak f�jlba �r�sa k�zben!" << endl;
		exit(3);
	}
	
	//rendez�s pontsz�mok szerint
	for (i = 0; i < db - 1; i++)
	{
		for (j = i + 1; j < db; j++)
		{
			if (jatekosok[i].pont > jatekosok[j].pont)
			{
				temp = jatekosok[i];
				jatekosok[i] = jatekosok[j];
				jatekosok[j] = temp;
			}
		}
	}

	for (i = (db - 1); i >= (db - 3); i--)
	{
		fileOut << jatekosok[i].vezeteknev << "\t" << jatekosok[i].pont << endl;
	}

	fileOut.close();

	cout << "k�sz" << endl;

	system("PAUSE");
	return 0;
}
