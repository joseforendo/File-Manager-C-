#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include "Arbol_Binario.h"
#include <string>
#include <msclr/marshal_cppstd.h>
#include "dirent.h"
#include <sys/stat.h>
#include <locale.h>

#define ESPACIO 32

using namespace std;
using namespace System;
using namespace System::IO;

Arbol_Binario<DirectoryInfo> *tree = new Arbol_Binario<DirectoryInfo>();

//Convertir system String to String
string ms_toString(String ^text)
{
	msclr::interop::marshal_context context;
	string normal = context.marshal_as<string>(text);
	return normal;
}

//Saber si una carpeta es directorio
bool IsDir(String ^text)
{
	DIR *directorio;
	string nuevo = ms_toString(text);

	if (directorio = opendir(nuevo.c_str()))
	{
		closedir(directorio);
		return true;
	}
	else
	{
		return false;
	}
}

void SubDirectorios(String ^carpeta)

{
	try {
		DirectoryInfo ^ubicacion = gcnew DirectoryInfo(carpeta);
		tree->insert_left(ubicacion);
		for each  (auto variable in ubicacion->GetDirectories())
		{
			tree->insert_right(variable);
			if (IsDir(variable->ToString()))
			{
				SubDirectorios(variable->ToString());
			}
		}
	}
	catch (Exception ^ex)
	{
		
	}
}

void MostrarInformacionArchivo(DirectoryInfo ^ubicacion)
{
	try 
	{
		for each(auto variable in ubicacion->GetFiles())
		{
			cout << "\t" << msclr::interop::marshal_as<std::string>(variable->Name) << endl;
		}
	}
	catch (Exception ^ex)
	{
		
	}
}

void BuscarPorRuta()
{
	int seguir = 0;
	string aux;
	cout << "Ingrese la ruta: " << endl;
	cin >> aux;

	String ^carpeta = gcnew String(aux.c_str());
	DirectoryInfo ^ubicacion = gcnew DirectoryInfo(carpeta);

	if (IsDir(ubicacion->ToString()))
	{
		for each  (auto variable in ubicacion->GetDirectories())
		{			
			cout << msclr::interop::marshal_as<std::string>(variable->Name) << endl;
			MostrarInformacionArchivo(variable);
		}
	}

	cout << endl << "¿Seguir Buscando? 0: Sí ... 1: No" << endl;
	cin >> seguir;

	if (seguir == 0)
	{
		BuscarPorRuta();
	}
	else
	{
		return;
	}
}

int menu()
{
	int op;
	Console::ForegroundColor = ConsoleColor::Cyan;
	cout << "  _______  _   _    _____     " << endl;
	cout << "  | ____| | | | |   | ___|    " << endl;
	cout << "  | |__   | | | |   | |_      " << endl;
	cout << "  | __|   | | | |   | __|     " << endl;
	cout << "  | |     | | | |_  | |__     " << endl;
	cout << "  |_|     |_| |___| |____|    " << endl;
	cout << endl;
	cout << "1. Serialización " << endl;
	cout << "2. Indexado " << endl;
	cout << "3. Búsqueda de archivos " << endl;
	cout << "4. Ordenar " << endl;
	cout << "0. Salir " << endl;
	do {
		cin >> op;
	} while (op < 0 || op>4);
	return op;
}

int menuIndexado()
{
	int op;
	cout << "Indexar por : " << endl;
	cout << "1. Nombre " << endl;
	cout << "2. Extensión " << endl;
	cout << "3. Tamaño " << endl;
	cout << "4. Fecha de creación " << endl;
	do {
		cin >> op;
	} while (op < 1 || op>4);
	return op;
}

int menuBusqueda()
{
	int operacion;
	cout << "Elija el criterio abuscar : " << endl;
	cout << "1. Por Nombre " << endl;
	cout << "2. Por Tamaño " << endl;
	do {
		cin >> operacion;
	} while (operacion < 1 || operacion>2);
	return operacion;
}

int menuBusquedaNombre()
{
	int ope;
	cout << "1. Empieza con " << endl;
	cout << "2. Finaliza con " << endl;
	cout << "3. Contiene " << endl;
	do {
		cin >> ope;
	} while (ope < 1 || ope>3);
	return ope;
}

int menuBusquedaTamaño()
{
	int operacion;
	cout << "Elija: " << endl;
	cout << "1. Mayor a " << endl;
	cout << "2. Menor a " << endl;
	cout << "3. Igual a " << endl;
	do {
		cin >> operacion;
	} while (operacion < 1 || operacion>3);
	return operacion;
}

int menuOrdenar()
{
	int opcion = 0;

	cout << "Elija los datos a ordenar: " << endl;
	cout << "1. Tamaño " << endl;
	cout << "2. Nombre " << endl;
	do {
		cin >> opcion;
	} while (opcion < 1 || opcion>2);

	return opcion;
}

int menuOrdenarTamaño()

{
	int opcion = 0;
	cout << "1. Ascendente " << endl;
	cout << "2. Descendente " << endl;
	do {
		cin >> opcion;
	} while (opcion < 1 || opcion>2);
	return opcion;
}

int menuAscendenteDescendente()
{
	int opcion = 0;
	cout << "1. Ascendente " << endl;
	cout << "2. Descendente " << endl;
	do {
		cin >> opcion;
	} while (opcion < 0 || opcion>2);
	return opcion;
}

void menuPrincipal()
{
	int opcion_menu = 0;
	int opcion_indexado = 0;
	int opcion_busqueda = 0;
	int opcion_busqueda_nombre = 0;
	int opcion_busqueda_tamaño = 0;
	int opcion_ordenar = 0;
	int opcion_ordenar_tamaño = 0;
	int opcion_ordenar_letra = 0;
	opcion_menu = menu();

	switch (opcion_menu)
	{
	case 1:
		BuscarPorRuta(); break;
	case 2:
		opcion_indexado = menuIndexado();
		switch (opcion_indexado)
		{
		case 1:
			tree->indexar_por_nombre(); break;
		case 2:
			tree->indexar_por_extension(); break;
		case 3:
			tree->indexar_por_tamaño(); break;
		case 4:
			tree->indexar_por_fecha(); break;
		}
		break;
	case 3:
		opcion_busqueda = menuBusqueda();
		switch (opcion_busqueda)
		{
		case 1:
			opcion_busqueda_nombre = menuBusquedaNombre();
			switch (opcion_busqueda_nombre)
			{
			case 1:
				tree->busqueda_por_letra_inicial(); break;
			case 2:
				tree->busqueda_por_letra_final(); break;
			case 3:
				tree->busqueda_por_letra_contiene(); break;
			}
			break;
		case 2:
			opcion_busqueda_tamaño = menuBusquedaTamaño();
			switch (opcion_busqueda_tamaño)
			{
			case 1:
				tree->busqueda_mayor_a(); break;
			case 2:
				tree->busqueda_menor_a(); break;
			case 3:
				tree->busqueda_igual_a(); break;
			}
			break;
		}
		break;
	case 4:
		opcion_ordenar = menuOrdenar();
		switch (opcion_ordenar)
		{
		case 1:
			tree->busqueda_mayor_ordenar();
			opcion_ordenar_tamaño = menuAscendenteDescendente();
			switch (opcion_ordenar_tamaño)
			{
			case 1:
				tree->ordenar_ascendente();
				break;
			case 2:
				tree->ordenar_descendente();
				break;
			}
			break;
		case 2:
			tree->busqueda_menor_ordenar();
			opcion_ordenar_letra = menuAscendenteDescendente();
			switch (opcion_ordenar_letra)
			{
			case 1:
				tree->ordenar_ascendente();
				break;
			case 2:
				tree->ordenar_descendente();
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 0:

		exit(0);
		break;

	default:
		break;
	}
	_getch();
	system("cls");
	menuPrincipal();
}

int main()
{
	setlocale(LC_ALL, "Spanish");
	SubDirectorios("C:/");

	menuPrincipal();
	_getch();
}
