/********************************************************************************

Laboratorio 4.
Nombre: Diego Alexander Hernández Silvestre | Carné 21270
Parte1.cpp
Catedrático: Roger Díaz
Descripción: Programa encargado de realizar los cálculos de productos procedentes
del mes de julio y agosto de &Cafe.
Fecha: 04/09/2022

*********************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <iostream>

using namespace std;

struct InfoTotal {
    double montoTotal;
    double costoVariable;
    double utilidadAlMes;
};

struct InfoProducto {
    string producto;
    double precioUnitario;
    double costoFijo;
    double unidadVendida;
    double ventasPorProducto;
    double utilidadPorProducto;

};

//Subrutina encargada de realizar los cálculos de los productos.
void *rubro(void *n){
    InfoProducto * i ;
    i = (InfoProducto*)n;
    i->ventasPorProducto = (i->unidadVendida) * (i->precioUnitario);
    i->utilidadPorProducto = (i->ventasPorProducto)-(i->unidadVendida*i->costoFijo);
    pthread_exit(NULL);
}

int main () {
    fflush(NULL);
    InfoProducto info[16];

    //Ingresamos los valores proprocionados.
    info[0] = {"White mocha", 32.00,19.20,300};
    info[1] = {"Porcion de pastel de chocolate", 60.00,20.00,400};
    info[2] = {"Cafe americano 8onz", 22.00,13.20,1590};
    info[3] = {"Latte 8onz", 24.00,17.20,200};
    info[4] = {"Toffee coffe", 28.00,20.10,390};
    info[5] = {"Cappuccino 8onz", 24.00,17.20,1455};
    info[6] = {"S'mores Latte", 32.00,23.00,800};
    info[7] = {"Cafe tostado molido", 60.00,20.00,60};
    info[8] = {"White mocha", 32.00,19.20,380};
    info[9] = {"Porcion de pastel de chocolate", 60.00,20.00,250};
    info[10] = {"Cafe americano 8onz", 22.00,13.20,800};
    info[11] = {"Latte 8onz", 24.00,17.20,250};
    info[12] = {"Toffee coffe", 28.00,20.10,600};
    info[13] = {"Cappuccino 8onz", 24.00,17.20,1200};
    info[14] = {"S'mores Latte", 32.00,23.00,1540};
    info[15] = {"Cafe tostado molido", 60.060,20.00,15};
    InfoTotal infoTotal[2];
    infoTotal[0].costoVariable = 45640.00;
    infoTotal[1].costoVariable = 40590.00;

    //Bienvenida al usuario
    cout<<"LABORATORIO 4 - TIENDA &CAFE"<<endl<<"Bienvenido, vamos a realizar el registro de ventas del mes de julio y agosto."<<endl<<"Espere mientras se imprimen los calculos..."<<endl;
    pthread_t t;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (int i= 0; i<16; i++){//Creación de hilos.
        pthread_create(&t, &attr, rubro, (void *)&info[i]);
    }
    for (int i= 0; i<16; i++){//Asegurar que se ejecuten de manera paralela.
        pthread_join(t, NULL);
    }
    cout<<"\nReporte del mes Julio"<<endl;
    cout<<"Ventas por producto"<<endl;
    for (int i=0;i<8;i++) {//Resultados de ventas julio
        cout<<info[i].producto<<": Q"<<info[i].ventasPorProducto<<endl;
    }
    cout<<""<<endl;
    for (int i=0;i<8;i++) {//Calculo de monto total julio
        infoTotal[0].montoTotal += info[i].ventasPorProducto;
    }

    //Impresión de resultados julio
    infoTotal[0].utilidadAlMes = infoTotal[0].montoTotal - infoTotal[0].costoVariable;
    cout<<"Total ventas: Q"<<infoTotal[0].montoTotal<<endl;
    cout<<"Costos variables: Q"<<infoTotal[0].costoVariable<<endl;
    cout<<"Utilidad del mes: Q"<<infoTotal[0].utilidadAlMes<<endl;

    cout<<"\nReporte del mes Agosto"<<endl;
    cout<<"Ventas por producto"<<endl;
    for (int i=8;i<16;i++) {//Resultados de ventas agosto
        cout<<info[i].producto<<": Q"<<info[i].ventasPorProducto<<endl;
    }
    cout<<""<<endl;
    for (int i=8;i<16;i++) {//Calculo de monto total agosto
        infoTotal[1].montoTotal += info[i].ventasPorProducto;
    }

    //Impresión de resultados agosto
    infoTotal[1].utilidadAlMes = infoTotal[1].montoTotal - infoTotal[1].costoVariable;
    cout<<"Total ventas: Q"<<infoTotal[1].montoTotal<<endl;
    cout<<"Costos variables: Q"<<infoTotal[1].costoVariable<<endl;
    cout<<"Utilidad del mes: Q"<<infoTotal[1].utilidadAlMes<<endl;

    pthread_exit(NULL);//Finalización de hilos
    return 0;
}