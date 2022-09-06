#include <iostream>
#include <fstream>

using namespace std;

void ordenardoble (int vec[], int dimv, float mat[][5],int cliente, float aux[]){

    for (int j = 0; j < dimv; j++)
    {
        aux[j] = mat[cliente][j];
    };
    

    int i,pos,imax;

    for (pos = 0; pos < dimv-1; pos++)
    {
        imax = pos;
        for (i = pos + 1; i < dimv; i++)
        {
            if (aux[i] < aux[imax])
            {
                imax = i ;
            };
        };
        swap(aux[imax],aux[pos]);
        swap(vec[imax],vec[pos]);
    };

};

void mostrarmat(float m[][5], int dfil)
{
	const int dcol {5}; // solo por prolijidad

	for (int i = 0; i < dfil; ++i) {
		for (int j = 0; j < dcol; ++j)
			cout << m[i][j] << "\t";
		cout << endl;
	};
};

void mostrarvector (string vec[], int dimv){

    for (int i = 0; i < dimv; i++)
       {
         cout << vec[i] << endl;
       };

};

void lista_peso (string clientes[], string productos[], int dclientes, int dproductos, float peso[][5], int prod_clientes []){

    string clave;

    for (int i = 0; i < dclientes; i++){
      
        for (int j = 0; j < dproductos; j++){

            if ( peso[i][j] > 13000)
            {
                clave += (productos[j] + " ");
                prod_clientes[i]++;
            };
        };      

        cout << "\n" << clientes[i] << ": " << clave << endl;
        clave = "";

    };
};

void lista_kg (string clientes[], string productos[], int dclientes, int dproductos, float kg[][5], int cliente, float aux[]){

    int vector_orden []{0,1,2,3,4};

    ordenardoble(vector_orden,dproductos,kg,cliente,aux);

    cout << endl << clientes[cliente] << ": " << endl;

    for (int j = 0; j < dproductos; j++){

        cout << "          "<< productos[vector_orden[j]] << ": " << aux[j] << endl;
        
    };     

    cout << endl;
    
};

int mayvector (int prod_clientes[], int dclientes){

    int pos = 0;
    int may = prod_clientes[pos];


    for (int i = 0; i < dclientes; i++)
    {
        if ( prod_clientes[i] > may)
        {
            may = prod_clientes[i];
            pos = i;
        };
        
    };

    return pos;
    
};

int main (){

    const int dclientes = 8;
    const int dproductos = 5;
    bool debug {false};

    string clientes [dclientes]{};
    string productos [dproductos]{};
    float peso_prod_clientes [dclientes][dproductos]{};
    float kg_prod_clientes [dclientes][dproductos]{};
    int producto_clientes [dclientes]{};
    int cant_entregas[dclientes][dproductos]{};
    float aux_mat_cliente[dproductos]{0,1,2,3,4};

    ifstream archilec;
    archilec.open("Nombres.txt");
    if (!archilec)
    {
        cout << "Error al abrir el archivo de nombres! " << endl;
        return 1;
    };

    for (int i = 0 ; i < dclientes && archilec >> clientes[i] ; i++);
    for (int i = 0 ; i < dproductos && archilec >> productos[i] ; i++);

    archilec.close();

    if (debug)
    {

        cout << "====================clientes======================" << endl;

        mostrarvector(clientes,dclientes);

        cout << "\n====================productos======================" << endl;

        mostrarvector(productos,dproductos);
       
    };
     
    ifstream archilec2;
    archilec2.open("datos.txt");
    if (!archilec2)
    {
        cout << "Error al abrir el archivo de datos! " << endl;
        return 1;
    };

    int codcliente,codproducto;
    float peso,km;

    while (archilec2>>codcliente>>codproducto>>peso>>km)
    {
        peso_prod_clientes[codcliente][codproducto] += peso;
        kg_prod_clientes[codcliente][codproducto] += km;
        cant_entregas[codcliente][codproducto]++;
    }

    if (debug)
    {

        cout << "\n====================peso======================" << endl;

        mostrarmat(peso_prod_clientes,dclientes);

        cout << "\n====================distancia======================" << endl;

        mostrarmat(kg_prod_clientes,dclientes);
       
    };


    cout << "\n\n================================================" << endl << endl;

    //PUNTO 1

    cout << "Listado de clientes y sus productos que superaron los 13000 kg transportados: " << endl;
    lista_peso(clientes,productos,dclientes,dproductos,peso_prod_clientes,producto_clientes);

    //PUNTO 2

    cout << "\n\n================================================" << endl << endl;

    cout << "\nCliente con mayores productos entregados: " << endl;

    int mayclient = mayvector(producto_clientes, dclientes);

    lista_kg(clientes,productos,dclientes,dproductos,kg_prod_clientes,mayclient,aux_mat_cliente);

    //PUNTO 3

    cout << "\n\n================================================" << endl << endl;

    int productosclientex[dproductos]{};

    for (int j = 0; j < dproductos ; j++){
        productosclientex[j] = kg_prod_clientes[mayclient][j];
    };

    int mayprodkm = mayvector(productosclientex,dproductos);
    int suma = 0;

    for (int i = 0; i < dclientes; i++)
    {
        suma += cant_entregas[i][mayprodkm];
    }
    

    cout << "Es el producto " << productos[mayprodkm] << " con una cantidad de " << productosclientex[mayprodkm] << " kilometros y unas " << suma << " entregas!" << endl << endl << endl;

    return 0;
};