#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ctype.h>

#include <windowsx.h>
#include <cstddef>
#include <Windows.h>
using namespace std;
int opord;
int i = 1;
int j = 1;
char numfactura[20];
char nomcliente[100];
char direccion[20];
char rfc[20];
char fecha[20];
char dias[20];
char tipopago[20];
double subtotal;
double iva;
double descuento;
int total;
bool encontrado;
char aux[1000];
int num;
int numm = 0;
int nummm = 0;
string auxx;

string obtenerDireccion(string filename) {
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	char ch[260];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 260, &DefChar, NULL);
	string str(ch);
	size_t found = str.find_last_of("/\\");
	string pathoriginal = str.substr(0, found);
	string fileexecutable = str.substr(found + 1);
	string pathfile = pathoriginal + "\\" + filename;
	return pathfile;
}

void leer(){
	system("cls");
	ifstream salida;
	salida.open(obtenerDireccion("Factura.txt"), ios::in);
	if (salida.fail()){
		cout << "Hubo un problema con el archivo";
		exit(1);
	}
	else{
		salida >> numfactura;
		while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
			salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
			cout << "Numero de factura: " << numfactura << "\n" << "Nombre del Cliente: " << nomcliente << "\n" << "Direccion: " << direccion << "\n" << "RFC: " << rfc << "\n" << "Fecha: " << fecha << "\n" << "Dias: " << dias << "\n" << "Tipo de Pago: " << tipopago << "\n" << "Subtotal: " << subtotal << "\n" << "IVA: " << iva << "\n" << "Descuento: " << descuento << "\n" << "Total: " << total << endl << endl;
			salida >> numfactura;
		}
		salida.close();
	} getch();
}



void main()
{
	SetConsoleTitle(("Facturas C++ Win32"));
	bool repeticion = true;
	do{
		int opmenusel;
		cout << " Asociacion de contadores Unidos S.A de C.V" << endl;
		cout << " Registro de Facturaciones " << endl;
		cout << " Digite las opcion que desee, tecleando el numero correspondiente" << endl;
		cout << "\t 1 .- Agregar un registro " << endl;
		cout << "\t 2 .- Eliminar un registro" << endl;
		cout << "\t 3 .- Modificar registros " << endl;
		cout << "\t 4 .- Realizar una consulta ordenada" << endl;
		cout << "\t 5 .- Buscar una Factura" << endl;
		cout << "\t 6 .- Salir del programa" << endl;
		cout << " Opcion elegida: ";
		cin >> opmenusel;
		if (opmenusel == 1){
			system("cls");
			int numfactura = 1;
			FILE *archivo;
			archivo = fopen(obtenerDireccion("Factura.txt").c_str(), "a+");
			if (archivo != NULL)
			{
				cout << "Si desea dejar de capturar coloque en el No. de Factura el #0" << endl;
				do
				{
					printf("No. de Factura: ");
					scanf("%d", &numfactura);
					if (numfactura > 0)
					{
						printf("Nombre del Cliente: ");
						scanf("%s", nomcliente); //declarar valor que se pide (%s pide letras y numeros)
						printf("Dirección del cliente: ");
						scanf("%s", direccion);
						printf("RFC: ");
						scanf("%s", rfc);
						printf("Fecha de factura: ");
						scanf("%s", fecha);
						printf("Dias de Credito: ");
						scanf("%s", dias);
						printf("Tipo de pago: ");
						scanf("%s", tipopago);
						printf("Subtotal: ");
						scanf("%lf", &subtotal); // %lf significa valores flotantes, dobles o booleanos
						printf("IVA: ");
						scanf("%lf", &iva);
						printf("Descuento: ");
						scanf("%lf", &descuento);
						total = (subtotal + (subtotal*(iva / 100))) - (subtotal*(descuento / 100));
						cout << "Total a pagar: " << total << endl;
						cout << "Registro guardado" << endl;
						fprintf(archivo, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%lf\t%lf\t%lf\t%d\n", numfactura, nomcliente, direccion, rfc, fecha, dias, tipopago, subtotal, iva, descuento, total); //mete los valores en el archivo %d es el no de inventario, y lo demas pues ya sabes
					}
				} while (numfactura > 0);
				fclose(archivo);
			}
			else{
				cout << "No se puede encontrar el archivo";
				exit(1);
			}
		}
		if (opmenusel == 2){
			system("cls");
			ifstream salida;
			salida.open(obtenerDireccion("Factura.txt"), ios::in);
			ofstream entrada;
			entrada.open(obtenerDireccion("temporal.txt"), ios::out);
			if (salida.fail()){
				cout << "Hubo un problema con el archivo";
				exit(1);
			}
			else{
				char aux[20];
				cout << "Introduzca el Numero de Cliente a eliminar: ";
				cin >> aux;
				salida >> numfactura;
				while (!salida.eof()){
					salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
					if (strcmp(aux, numfactura) == 0){
						cout << "Se ha eliminado correctamente" << endl;
					}
					else{
						entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
					}
					salida >> numfactura;
				}
				entrada.close();
				salida.close();
				remove(obtenerDireccion("Factura.txt").c_str());
				rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
			}
		}
		if (opmenusel == 3){
			system("cls");
			bool encontrado;
			encontrado = false;
			ifstream salida;
			salida.open(obtenerDireccion("Factura.txt"), ios::in);
			ofstream entrada;
			entrada.open(obtenerDireccion("temporal.txt"), ios::out);
			if (salida.fail()){
				cout << "Hubo un problema con el archivo";
				exit(1);
			}
			else{
				cout << "Introduzca el Numero de Cliente a modificar: ";
				cin >> aux;
				salida >> numfactura;
				while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada
					salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
					if (strcmp(aux, numfactura) == 0){
						encontrado = true;
						cout << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total;
						cout << endl;
						cout << "ingresa el nuevo nombre del cliente: ";
						cin >> nomcliente;
						cout << endl;
						cout << "ingresa la nueva direccion: ";
						cin >> direccion;
						cout << endl;
						cout << "ingresa el nuevo RFC: ";
						cin >> rfc;
						cout << endl;
						cout << "ingresa la nueva fecha: ";
						cin >> fecha;
						cout << endl;
						cout << "ingresa los nuevos dias de credito: ";
						cin >> dias;
						cout << endl;
						cout << "ingresa el nuevo tipo de pago: ";
						cin >> tipopago;
						cout << endl;
						cout << "ingresa el nuevo subtotal($): ";
						cin >> subtotal;
						cout << endl;
						cout << "ingresa el nuevo IVA(%): ";
						cin >> iva;
						cout << endl;
						cout << "ingresa el nuevo descuento(%): ";
						cin >> descuento;
						cout << endl;
						total = (subtotal + (subtotal*(iva / 100))) - (subtotal*(descuento / 100));
						cout << "Total a pagar: " << total << endl;
						entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
						cout << "Registro modificado satisfactoriamente";

					}
					else{
						entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
					}
					salida >> numfactura;
				}
				entrada.close();
				salida.close();
				remove(obtenerDireccion("Factura.txt").c_str());
				rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
			}
		}
		//Para ordenar
		if (opmenusel == 4){
			bool rep = true;
			do{
				system("cls");
				cout << "Asociacion de contadores Unidos S.A de C.V" << endl;
				cout << "Consulta de facturas" << endl;
				cout << "Digite las opcion que desee, tecleando el numero correspondiente" << endl;
				cout << " 1 .- Consultar por Numero de cliente " << endl;
				cout << " 2 .- Consulta por Nombre del cliente" << endl;
				cout << " 3 .- Consulta por Fecha de factura " << endl;
				cout << " 4 .- Consulta por Dirección del cliente " << endl;
				cout << " 5 .- Consulta por fecha de vencimiento" << endl;
				cout << " 6 .- Consulta por totales a pagar" << endl;
				cout << " 7 .- Regresar al menú" << endl;
				cout << "Opcion elegida: ";
				cin >> opord;

				//Ordenar por numeros de FACTURA
				if (opord == 1){
					system("cls");

					for (num = 1; num < 100; num++){
						ifstream salida;
						salida.open(obtenerDireccion("Factura.txt"), ios::in);
						ofstream entrada;
						entrada.open(obtenerDireccion("temporal.txt"), ios::app);
						if (salida.fail()){
							cout << "Hubo un problema con el archivo";
							exit(1);
						}
						else{
							sprintf(aux, "%d", num);
							salida >> numfactura;
							while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
								salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
								/*cout<<"num"<<num<<endl;
								cout<<"aux"<<aux<<endl;*/
								if (strcmp(aux, numfactura) == 0){
									entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
								}
								else{}// Aqui termina el if
								salida >> numfactura;
							}// Termina el ciclo de leer hasta al final del archivo
							entrada.close();
							salida.close();
						}
					}
					remove(obtenerDireccion("Factura.txt").c_str());
					rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
					leer();
				}

				//NOMBRE DE CLIENTE
				if (opord == 2){
					system("cls");
					for (num = 65; num < 123; num++){
						ifstream salida;
						salida.open(obtenerDireccion("Factura.txt"), ios::in);
						ofstream entrada;
						entrada.open(obtenerDireccion("temporal.txt"), ios::app);
						if (salida.fail()){
							cout << "Hubo un problema con el archivo";
							exit(1);
						}
						else{
							auxx = toascii(num);
							salida >> numfactura;
							while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
								salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
								/*cout<<"num"<<num<<endl;
								cout<<"aux"<<aux<<endl;*/
								strncpy(aux, nomcliente, 1);
								if (strcmp(aux, auxx.c_str()) == 0){
									entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
								}
								else{}// Aqui termina el if
								salida >> numfactura;
							}// Termina el ciclo de leer hasta al final del archivo
							entrada.close();
							salida.close();
						}
					}
					remove(obtenerDireccion("Factura.txt").c_str());
					rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
					leer();
				}

				//FECHA
				if (opord == 3){
					system("cls");

					for (num = 1; num < 100; num++){
						ifstream salida;
						salida.open(obtenerDireccion("Factura.txt"), ios::in);
						ofstream entrada;
						entrada.open(obtenerDireccion("temporal.txt"), ios::app);
						if (salida.fail()){
							cout << "Hubo un problema con el archivo";
							exit(1);
						}
						else{
							if (num == 32){
								num = 0;
								numm++;
							}
							if (numm == 13){
								numm = 0;
								nummm++;
							}
							if (nummm == 30){
								num = 33;
								nummm = 0;
							}
							sprintf(aux, "%d%s%d%s%d", num, "/", numm, "/", nummm);
							salida >> numfactura;
							while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
								salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
								if (strcmp(aux, fecha) == 0){
									entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
								}
								else{}// Aqui termina el if
								salida >> numfactura;
							}// Termina el ciclo de leer hasta al final del archivo
							entrada.close();
							salida.close();
						}
					}
					remove(obtenerDireccion("Factura.txt").c_str());
					rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
					leer();

				}

				//DIRECCION
				if (opord == 4){
					system("cls");
					for (num = 65; num < 123; num++){
						ifstream salida;
						salida.open(obtenerDireccion("Factura.txt"), ios::in);
						ofstream entrada;
						entrada.open(obtenerDireccion("temporal.txt").c_str(), ios::app);
						if (salida.fail()){
							cout << "Hubo un problema con el archivo";
							exit(1);
						}
						else{
							auxx = toascii(num);
							salida >> numfactura;
							while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
								salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
								/*cout<<"num"<<num<<endl;
								cout<<"aux"<<aux<<endl;*/
								strncpy(aux, direccion, 1);
								if (strcmp(aux, auxx.c_str()) == 0){
									entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
								}
								else{}// Aqui termina el if
								salida >> numfactura;
							}// Termina el ciclo de leer hasta al final del archivo
							entrada.close();
							salida.close();
						}
					}
					remove(obtenerDireccion("Factura.txt").c_str());
					rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
					leer();

				}

				//VENCIMIENTO
				if (opord == 5){
					system("cls");

					for (num = 1; num < 100; num++){
						ifstream salida;
						salida.open(obtenerDireccion("Factura.txt"), ios::in);
						ofstream entrada;
						entrada.open(obtenerDireccion("temporal.txt"), ios::app);
						if (salida.fail()){
							cout << "Hubo un problema con el archivo";
							exit(1);
						}
						else{
							sprintf(aux, "%d", num);
							salida >> numfactura;
							while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
								salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
								/*cout<<"num"<<num<<endl;
								cout<<"aux"<<aux<<endl;*/
								if (strcmp(aux, dias) == 0){
									entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
								}
								else{}// Aqui termina el if
								salida >> numfactura;
							}// Termina el ciclo de leer hasta al final del archivo
							entrada.close();
							salida.close();
						}
					}
					remove(obtenerDireccion("Factura.txt").c_str());
					rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
					leer();

				}

				//TOTAL A PAGAR
				if (opord == 6){
					system("cls");

					for (num = 0; num < 1000; num++){
						ifstream salida;
						salida.open(obtenerDireccion("Factura.txt"), ios::in);
						ofstream entrada;
						entrada.open(obtenerDireccion("temporal.txt"), ios::app);
						if (salida.fail()){
							cout << "Hubo un problema con el archivo";
							exit(1);
						}
						else{
							sprintf(aux, "%d", num);
							salida >> numfactura;
							while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
								salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
								/*cout<<"num"<<num<<endl;
								cout<<"aux"<<aux<<endl;*/
								if (num == total){
									entrada << numfactura << " " << nomcliente << " " << direccion << " " << rfc << " " << fecha << " " << dias << " " << tipopago << " " << subtotal << " " << iva << " " << descuento << " " << total << endl;
								}
								else{}// Aqui termina el if
								salida >> numfactura;
							}// Termina el ciclo de leer hasta al final del archivo
							entrada.close();
							salida.close();
						}
					}
					remove(obtenerDireccion("Factura.txt").c_str());
					rename(obtenerDireccion("temporal.txt").c_str(), obtenerDireccion("Factura.txt").c_str());
					leer();
				}

				//SALIR AL MENU
				if (opord == 7){
					rep = false;
				}

			} while (rep == true);

		}//cierre del if opcion

		if (opmenusel == 5){
			system("cls");
			ifstream salida;
			salida.open(obtenerDireccion("Factura.txt"), ios::in);
			if (salida.fail()){
				cout << "Hubo un problema con el archivo";
				exit(1);
			}
			else{
				cout << "Introduzca el Numero de Cliente a buscar: ";
				cin >> aux;
				salida >> numfactura;
				while (!salida.eof()){ //lectura es salida y auxClave es como mi aux y, aux es entrada, mientras no sea final del archivo
					salida >> nomcliente >> direccion >> rfc >> fecha >> dias >> tipopago >> subtotal >> iva >> descuento >> total;
					if (strcmp(aux, numfactura) == 0){
						cout << "Numero de factura: " << numfactura << "\n" << "Nombre del Cliente: " << nomcliente << "\n" << "Direccion: " << direccion << "\n" << "RFC: " << rfc << "\n" << "Fecha: " << fecha << "\n" << "Dias: " << dias << "\n" << "Tipo de Pago: " << tipopago << "\n" << "Subtotal: " << subtotal << "\n" << "IVA: " << iva << "\n" << "Descuento: " << descuento << "\n" << "Total: " << total << endl << endl;;
					}
					else{}// Aqui termina el if
					salida >> numfactura;
				}// Termina el ciclo de leer hasta al final del archivo
				salida.close();
			} getch();
		}

		if (opmenusel == 6){
			exit(1);
		}
		if (opmenusel>6){
			system("cls");
			cout << "Ha seleccionado una opción que no existe" << endl;
			getch();
		}

		system("cls");
	} while (repeticion == true);
}