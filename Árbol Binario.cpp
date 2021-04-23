#include <vcclr.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "dirent.h"
#include <sys/stat.h>
#include <locale.h>
#include <algorithm>
#include "Datos Directorio.h"

using namespace std;

template<typename T>
struct NodoArbol {
	gcroot<T^> value;
	NodoArbol<T> *left;
	NodoArbol<T> *right;
};

template<typename T>
class Arbol_Binario {
public:

	Arbol_Binario();

	void insert_left(T ^key);
	void insert_right(T ^key);
	void inorder_print();

	void busqueda_por_letra_inicial()
	{
		string criterio;
		cin >> criterio;

		busqueda_por_letra_inicial(root, criterio);
	}
	void busqueda_por_letra_final()
	{
		string criterio;
		cin >> criterio;

		busqueda_por_letra_final(root, criterio);
	}
	void busqueda_por_letra_contiene()
	{
		string criterio;
		cin >> criterio;

		busqueda_por_letra_contiene(root, criterio);
	}

	void indexar_por_nombre()
	{
		indexar_por_nombre(root);
	}
	void indexar_por_fecha()
	{
		indexar_por_fecha(root);
	}
	void indexar_por_tamaño()
	{
		indexar_por_tamaño(root);
	}
	void indexar_por_extension()
	{
		indexar_por_extension(root);
	}

	void busqueda_mayor_a()
	{
		long range = 0;
		do {
			cout << endl << "Criterio: Búsqueda mayor a: "; cin >> range;
		} while (range <= 0);
		busqueda_mayor_a(root, range);
	}
	void busqueda_menor_a()
	{
		long range = 0;
		do {
			cout << endl << "Criterio: Búsqueda menor a: "; cin >> range;
		} while (range <= 0);
		busqueda_menor_a(root, range);
	}
	void busqueda_igual_a()
	{
		long range = 0;
		do {
			cout << endl << "Criterio: Búsqueda igual a: "; cin >> range;
		} while (range <= 0);
		busqueda_igual_a(root, range);
	}

	void busqueda_mayor_ordenar()
	{
		busqueda_mayor_ordenar(root, 1);
	}
	void busqueda_menor_ordenar()
	{
		busqueda_menor_ordenar(root, 1000);
	}
	void busqueda_por_letra_inicial_ordenar()
	{
		busqueda_por_letra_inicial_ordenar(root, "t");
	}

	void indexar_por_nombre(NodoArbol<T> *leaf)
	{
		if (leaf != nullptr)
		{
			indexar_por_nombre(leaf->left);
			DatosDirectorio nuevo(leaf->value);
			cout << nuevo.name << endl;
			indexar_por_nombre(leaf->right);
		}
	}
	void indexar_por_fecha(NodoArbol<T> *leaf)
	{
		if (leaf != NULL) {
			indexar_por_fecha(leaf->left);
			DatosDirectorio nuevo(leaf->value);
			cout << nuevo.name << endl;
			cout << "\t" << "Año: " << nuevo.fecha.anio << endl;
			cout << "\t" << "Mes : " << nuevo.fecha.mes << endl;
			cout << "\t" << "Dia : " << nuevo.fecha.dia << endl;
			indexar_por_fecha(leaf->right);
		}
	}
	void indexar_por_tamaño(NodoArbol<T> *leaf)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			indexar_por_tamaño(leaf->left);
			cout << msclr::interop::marshal_as<std::string>(leaf->value->Name) << endl;

			cout << "Tamaño: " << nuevo.size_kb << endl;
			indexar_por_tamaño(leaf->right);
		}
	}
	void indexar_por_extension(NodoArbol<T> *leaf)
	{
		if (leaf != nullptr)
		{
			indexar_por_extension(leaf->left);
			for each(auto variable in leaf->value->GetFiles())
			{
				cout << msclr::interop::marshal_as<std::string>(variable->Name) << endl;
			}
			indexar_por_extension(leaf->right);
		}
	}

	void busqueda_mayor_a(NodoArbol<T> *leaf, long size)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_mayor_a(leaf->left, size);

			if (size < nuevo.size_kb)
				nuevo.MostrarDatos();
			
			busqueda_mayor_a(leaf->right, size);
		}
	}
	void busqueda_menor_a(NodoArbol<T> *leaf, long size)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_mayor_a(leaf->left, size);
			
			if (size > nuevo.size_kb)
					cout << nuevo.name << endl;
			
			busqueda_mayor_a(leaf->right, size);
		}
	}
	void busqueda_igual_a(NodoArbol<T> *leaf, long size)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_mayor_a(leaf->left, size);
			
			if (size == nuevo.size_kb)
				cout << nuevo.name << endl;
			
			busqueda_mayor_a(leaf->right, size);
		}
	}

	void busqueda_por_letra_inicial(NodoArbol<T> *leaf, string crit)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_por_letra_inicial(leaf->left, crit);

			if (crit[0] == nuevo.name[0])
			{
				cout << nuevo.name << endl;
			}
			busqueda_por_letra_inicial(leaf->right, crit);
		}
	}
	void busqueda_por_letra_final(NodoArbol<T> *leaf, string crit)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_por_letra_final(leaf->left, crit);

			if (crit[0] == nuevo.name[nuevo.name.length() - 1])
			{
				cout << nuevo.name << endl;
			}
			busqueda_por_letra_final(leaf->right, crit);
		}
	}
	void busqueda_por_letra_contiene(NodoArbol<T> *leaf, string crit)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_por_letra_contiene(leaf->left, crit);
			bool go = false;

			for (int i = 0; i < nuevo.name.length(); i++)
			{
				if (crit[0] == nuevo.name[i])
				{
					go = true;
					break;
				}
			}

			if (go)
			{
				cout << nuevo.name << endl;
			}
			busqueda_por_letra_contiene(leaf->right, crit);

		}
	}

	void busqueda_mayor_ordenar(NodoArbol<T> *leaf, long size)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_mayor_ordenar(leaf->left, size);

			if (size < nuevo.size_kb)
			{
				aux.push_back(nuevo);
			}

			busqueda_mayor_ordenar(leaf->right, size);
		}
	}
	void busqueda_menor_ordenar(NodoArbol<T> *leaf, long size)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_menor_ordenar(leaf->left, size);

			if (size > nuevo.size_kb)
			{
				aux.push_back(nuevo);
			}

			busqueda_menor_ordenar(leaf->right, size);
		}
	}
	void busqueda_por_letra_inicial_ordenar(NodoArbol<T> *leaf, string crit)
	{
		if (leaf != nullptr)
		{
			DatosDirectorio nuevo(leaf->value);
			busqueda_por_letra_inicial_ordenar(leaf->left, crit);

			if (crit[0] == nuevo.name[0])
			{
				aux.push_back(nuevo);
			}
			busqueda_por_letra_inicial_ordenar(leaf->right, crit);
		}
	}


	void ordenar_ascendente()
	{
		sort(aux.begin(), aux.end(), [](DatosDirectorio a, DatosDirectorio b)
		{
			return a.size_kb < b.size_kb;
		});

		for (int i = 0; i < aux.size(); i++)
		{
			aux.at(i).MostrarDatos();
		}

		for (int i = 0; i < aux.size(); i++)
		{
			aux.erase(aux.begin() + i);
		}
	}

	void ordenar_descendente()
	{
		sort(aux.begin(), aux.end(), [](DatosDirectorio a, DatosDirectorio b)
		{
			return a.size_kb > b.size_kb;
		});

		for (int i = 0; i < aux.size(); i++)
		{
			aux.at(i).MostrarDatos();
		}

		for (int i = 0; i < aux.size(); i++)
		{
			aux.erase(aux.begin() + i);
		}
	}

private:

	void insert_right (T ^key, NodoArbol<T> *leaf);
	void insert_left  (T ^key, NodoArbol<T> *leaf);
	void inorder_print(NodoArbol<T> *leaf);

	NodoArbol<T> *root;
	vector<DatosDirectorio> aux;

};

template<typename T>
Arbol_Binario<T>::Arbol_Binario() {
	root = NULL;
}

template<typename T>
void Arbol_Binario<T>::insert_left(T ^key, NodoArbol<T> *leaf) {
	if (leaf->left != NULL)
	{
		insert_left(key, leaf->left);
	}
	else
	{
		leaf->left = new NodoArbol<T>;
		leaf->left->value = key;
		leaf->left->left = NULL;
		leaf->left->right = NULL;
	}
}

template<typename T>
void Arbol_Binario<T>::insert_right(T ^key, NodoArbol<T>*leaf) {
	if (leaf->right != NULL)
	{
		insert_right(key, leaf->right);
	}
	else
	{
		leaf->right = new NodoArbol<T>;
		leaf->right->value = key;
		leaf->right->right = NULL;
		leaf->right->left = NULL;
	}
}

template<typename T>
void Arbol_Binario<T>::insert_left(T ^key) {
	if (root != NULL) {
		insert_left(key, root);
	}
	else {
		root = new NodoArbol<T>;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

template<typename T>
void Arbol_Binario<T>::insert_right(T ^key) {
	if (root != NULL) {
		insert_right(key, root);
	}
	else {
		root = new NodoArbol<T>;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

template<typename T>
void Arbol_Binario<T>::inorder_print() {
	inorder_print(root);
	cout << "\n";
}

template<typename T>
void Arbol_Binario<T>::inorder_print(NodoArbol<T> *leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		cout << msclr::interop::marshal_as<std::string>(leaf->value->Name) << endl;
		cout << "\t" << "Anio: " << int(leaf->value->CreationTime.Year) << endl;
		cout << "\t" << "Mes : " << int(leaf->value->CreationTime.Month) << endl;
		cout << "\t" << "Dia : " << int(leaf->value->CreationTime.Day) << endl;
		inorder_print(leaf->right);
	}
}
