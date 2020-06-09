#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//variables globales
    
    struct Nodo{
        int info;
        struct Nodo *sig;
        struct Nodo *ant;
    };//Struct del Nodo Lista dolemente enlazada
    typedef struct Nodo tNodo;// tNodo nombre del tipo de dato
    int Fin=0;//Sera la cantidad de celdas que estan siendo usadas en el arreglo
    int array[100000];//Cantidad estatica de el arreglo
    long AccesoLista=0;//Cantidad de accesos en la lista
    long AccesoArreglo=0;// Cantidad de accesos en el arreglo
    
//----------------------------------------------------------------------------------------------------

    //Firmas
    
    tNodo * Toma_comando(char aux, FILE *,tNodo *);//Realiza el programa segun el ingreso del usuario
    tNodo * Procesar_Archivo_I(FILE *,tNodo *);//Hace casi todo lo correspondiente a el comando I
    tNodo * Procesar_Archivo_E(FILE *,tNodo *);//Hace casi todo lo correspondiente a el comando I
    tNodo * Crea_Nodo(int ,tNodo *);//Crea un nodo nuevo para la lista
    tNodo * Insertar_Ordenada_Lista(tNodo * ,int );//Toma el dato del archivo y lo inserta en la lista
    tNodo * Buscar_Eliminar_Lista(tNodo * , int );//Busca un numero del archivo y lo elimina en la lista
    void Insertar_Ordenado_Arreglo(int );//Toma el dato del archivo y lo inserta en el arreglo
    void Buscar_Eliminar_Arreglo(int );//Busca un numero del archivo y lo elimina en el arreglo
    void Mostrar(tNodo *);//Muestra por pantalla los datos de las listas
    void Imprime_Bytes();//Muestra por pantalla los Bytes de las listas
    FILE * Abre_arch(char * entrada);//Abre el archivo ingresado
//-------------------------------------------------------------------------------------------------------
    
    //Funciones
//Parametros de Toma_comando: El comando, el archivo y la lista
tNodo * Toma_comando(char aux,FILE * Arch, tNodo * Lista)
{
    AccesoLista=0;
    AccesoArreglo=0;
    switch (aux)
    {
        case 'I': //Opcion I
            Lista=Procesar_Archivo_I(Arch,Lista);//Llamada de la funcion la cual retornará el inicio de la lista
            Imprime_Bytes();//Imprimirá la cantidad de Bytes utilizados en ese momento por la lista doblemente enlazada y el arreglo
            printf("Cantidad de accesos a memoria\n");
            printf("\tEn lista doblemente enlazada: %ld\n",AccesoLista);
            printf("\tEn arreglo: %ld\n\n",AccesoArreglo);
            fclose(Arch);//Cierra el archivo
            break;
        case 'E'://Opcion E
            Lista=Procesar_Archivo_E(Arch, Lista);//Llamada de la funcion la cual retornará el inicio de la lista
            Imprime_Bytes();//Imprimirá la cantidad de Bytes utilizados en ese momento por la lista doblemente enlazada y el arreglo
            printf("Cantidad de accesos a memoria\n");
            printf("\tEn lista doblemente enlazada: %ld\n",AccesoLista);
            printf("\tEn arreglo: %ld\n\n",AccesoArreglo);
            fclose(Arch);//Cierra el archivo
            break;
        case 'L'://Opcion L
            Mostrar(Lista);//Muestra los datos contenidos en ambas listas
            break;
        case 'T'://Opcion T
            Imprime_Bytes();//Imprimirá la cantidad de Bytes utilizados en ese momento por la lista doblemente enlazada y el arreglo
            break;
        case 'F'://Opcion F
            printf("Finalizado.\n");//Simplemente con este comando se termina el programa
            break;
        default://Situacion en la cual el usuario ingresó mal el comando
            printf("Ingrese comando correcto.\n\n");            
            break;
    }
    return Lista;
}
//Parametros de Procesar_Archivo_I: El archivo y la lista
tNodo * Procesar_Archivo_I(FILE * Archivo, tNodo * L)
{
    clock_t start = clock();
	int valaux=0;//Variable tendrá el valor de el numero sacado del archivo ins
	char saux[100];//Variable para sacar el dato del archivo ins
	while(feof(Archivo)==0){//Ciclo para recorrer el archivo hasta que termine
        fgets(saux,100,Archivo);//Toma de dato del archivo ins
        if(feof(Archivo)==0){//If para controlar que el fgets no tome el salto de la ultima linea del archivo ins
            saux[strlen(saux)-1]=0;//Se le quita el salto de linea a la cadena y se le asigna 0 que es final de cadena
            valaux=atoi(saux);//Transformación de la cadena a entero
	        L=Insertar_Ordenada_Lista(L,valaux);//L se le asigna el inicio de la lista
	        AccesoLista=AccesoLista+1;
 //Se le suma 1 al acceso de memoria de la lista doblemente enlazada por la asignacion a L
        }
	}
	printf("Tiempo transcurrido: %f\n", (((double)clock() - start) / CLOCKS_PER_SEC)/60);
	fseek(Archivo,0, SEEK_SET );
	start = clock();
	while(feof(Archivo)==0){//Ciclo para recorrer el archivo hasta que termine
        fgets(saux,100,Archivo);//Toma de dato del archivo ins
        if(feof(Archivo)==0){//If para controlar que el fgets no tome el salto de la ultima linea del archivo ins
            saux[strlen(saux)-1]=0;//Se le quita el salto de linea a la cadena y se le asigna 0 que es final de cadena
            valaux=atoi(saux);//Transformación de la cadena a entero
	        Insertar_Ordenado_Arreglo(valaux);
        }
	}
    printf("Tiempo transcurrido: %f\n", (((double)clock() - start) / CLOCKS_PER_SEC)/60);
	return L;//Retorna la lista
}
//Parametros de Procesar_Archivo_E: El archivo y la lista
tNodo * Procesar_Archivo_E(FILE * Archivo, tNodo * L)
{
    clock_t start = clock();
    int valaux=0;//Variable tendrá el valor de el numero sacado del archivo eli
	char saux[100];//Variable para sacar el dato del archivo eli
    while(feof(Archivo)==0){//Ciclo para recorrer el archivo hasta que termine
        if(L!=NULL){//If para ver si hay algo ingresado en las listas, para que haya algo que se pueda eliminar
            fgets(saux,100,Archivo);//Toma de dato del archivo eli
            if(feof(Archivo)==0){//If para controlar que el fgets no tome el salto de la ultima linea del archivo eli
                saux[strlen(saux)-1]=0;//Se le quita el salto de linea a la cadena y se le asigna 0 que es final de cadena
                valaux=atoi(saux);//Transformación de la cadena a entero
                L=Buscar_Eliminar_Lista(L,valaux);//L se le asigna el inicio de la lista
                AccesoLista=AccesoLista+1;
 //Se le suma 1 al acceso de memoria de la lista doblemente enlazada por la asignacion a L
            }
        }
        else{//Caso en que no hayan datos en las listas
            printf("No hay nada en las listas en este momento.\n\n");
            break;
        }
    }
    printf("Tiempo transcurrido: %f\n", (((double)clock() - start) / CLOCKS_PER_SEC)/60);
    fseek(Archivo,0, SEEK_SET );
    start = clock();
    while(feof(Archivo)==0){//Ciclo para recorrer el archivo hasta que termine
        if(L!=NULL){//If para ver si hay algo ingresado en las listas, para que haya algo que se pueda eliminar
            fgets(saux,100,Archivo);//Toma de dato del archivo eli
            if(feof(Archivo)==0){//If para controlar que el fgets no tome el salto de la ultima linea del archivo eli
                saux[strlen(saux)-1]=0;//Se le quita el salto de linea a la cadena y se le asigna 0 que es final de cadena
                valaux=atoi(saux);//Transformación de la cadena a entero
                Buscar_Eliminar_Arreglo(valaux);
            }
        }
        else{//Caso en que no hayan datos en las listas
            printf("No hay nada en las listas en este momento.\n\n");
            break;
        }
    }
    printf("Tiempo transcurrido: %f\n", (((double)clock() - start) / CLOCKS_PER_SEC)/60);
    return L;
}
//Parametros de Crea_Nodo: El valor sacado de el archivo ins y la lista
tNodo * Crea_Nodo(int valor, tNodo * L)
{ 
        L = (tNodo *)malloc(sizeof(tNodo));//Se reserva espacio en la memoria para otro nodo
        AccesoLista=AccesoLista+2;//Se le summa 2 a los accesos de memoria a la lista doblemente enlazada por la comparacion en el if y por la asignacion a L
        if (L != NULL)//Caso en que se pudo crear el nodo y la lista contenga ya algo
        {
            L->info = valor;//Se le asigna el valor del archivo ins
            L->sig = NULL;
            L->ant = NULL;
            AccesoLista=AccesoLista+3;//Se le suma 3 a los accesos de memoria a la lista doblemente enlazada las asignaciones a L
        }
        else
        {
            printf("\n\tERROR: No hay memoria suficiente para generar un nuevo Nodo.");
            printf("\n\tEste programa se cerrar%c.", 160);
            return 0;
        }
    return L;//Retorna la lista
}
//Parametros de Insertar_Ordenada_Lista: La lista y el valor sacado de el archivo ins
tNodo * Insertar_Ordenada_Lista(tNodo * L, int Valor) 
{
	tNodo *pNodo, *aux1, *aux2;//Se crean punteros para formar los enlances en la lista doblemente enlazada
    pNodo = Crea_Nodo(Valor,L);//Se le asigna el nuevo nodo al puntero
    AccesoLista=AccesoLista+2;
 //Se le suman 2 a los accesos de memoria de las listas doblemente enlazadas por la comparacion del if y la asignacion a pNodo 
    if(L == NULL){//Si la Lista no es nula
        L = pNodo;//Se le asigna el primer nodo a L que es el que siempre tendrá el inicio de la lista
        AccesoLista=AccesoLista+1;
 //Se le suma un accesos de memoria a la lista doblemente enlazada por la asignacion a L
    }    
    else//Si L ya tiene un comienzo solo seguira con los siguientes pasos
    {
        AccesoLista=AccesoLista+1;
 //Se le suma un accesos de memoria a la lista doblemente enlazada por la comparacion del if
        if(Valor < L->info)//Compara si el valor del archivo ins es menor a la info de L
        {
            pNodo->sig = L;//Se unen los punteros
            L->ant = pNodo;//Se unen los punteros
            L=pNodo;//Se le asigna nuevamente pNodo a L para que quede como el primero de la lista
            AccesoLista=AccesoLista+3;
 //Se le suman 3 a los accesos a memoria de las listas doblemente enlazadas por las asignaciones a pNodo y a L
        }
        else//Si el valor del archivo ins es mayor o igual entones sigue con los siguientes pasos
        {
            aux1 = L;//aux1 tendra el puntero a L, para que este sea utilizado para movernos en la lista
            AccesoLista=AccesoLista+1;
 //Se le suma un acceso de memeoria a la lista doblemente enlazada por la asignacion a aux1 
            while(aux1!=NULL)//Mientras el puntero auxiliar no llegue a nulo hará lo siguiente
            {
                AccesoLista=AccesoLista+2;
 //Se le suman 2 a los accesos de memoria de la lista doblemente enlazada por la comparacion del while y la comparacion del if
                if(aux1->info <= Valor)//Se compara si el valor del puntero que se va moviendo es menor o igual al valor del archivo ins
                {
                	aux2=aux1;//Se guarda el puntero en otro auxiliar para no perderlo
            	    aux1 = aux1->sig;//El aux1 avanza al siguiente nodo
            	    AccesoLista=AccesoLista+2;
 //Se le suman 2 a los accesos de memoria de la lista por las asignaciones a aux2 y aux1
                }
                else//Si el valor de el archivo ins es menor entonces
                    break;        //Sale del ciclo
            }
            AccesoLista=AccesoLista+1;
 //Se le suma un accesos de memoria a la lista doblemente enlazada por la compraracion en el if
            if(aux1!=NULL){//Si aux1 es diferente de nulo
        	    pNodo->sig = aux1;//Se le asigna a aux1 la posicion siguiente de pNodo
        	    pNodo->ant=aux1->ant;//Se le asgina al anterior de aux1 a anterior de pNodo
         	    aux1->ant=pNodo;//Se le asigna al anterior de aux1 el pNodo
         	    aux2= pNodo->ant;//Se le asigna a aux2 el anterior de pNodo
         	    aux2->sig=pNodo;//Se le asigna a siguiente de aux2 el pNodo
         	    AccesoLista=AccesoLista+5;
 //Se le suman 5 a acceoso de memoria de la lista doblemente enlazada por las asignaciones anterirores
            }
            else{//Si aux1 es nulo
            aux2->sig=pNodo;//Se le asigna al siguiente de aux2 el pNodo
        	pNodo->ant=aux2;//Se le asigna al anterior de pNodo el aux2
        	AccesoLista=AccesoLista+2;
 //Se le suman 2 a accesos de memoria de la lista doblemente enlazada por las asignaciones anteriores
            }
        aux1=NULL;//Se dejan en nulo las variables que servian de auxiliar
        aux2=NULL;
        AccesoLista=AccesoLista+2;
 //Se le suman 2 a accesos de memoria de la lista doblemente enlazada por las asignaciones anteriores
        }
    }
    pNodo = NULL;
    AccesoLista=AccesoLista+1;
 //Se le suman un accesos de memoria de la lista doblemente enlazada por la asignacion anterior
    return L;//Retorna el puntero a la lista
}
//Parametros de Buscar_Eliminar_Lista: La lista y el valor sacado de el archivo eli, el cual será eliminado
tNodo * Buscar_Eliminar_Lista(tNodo * L, int ValorAEli)
{
    tNodo * aux, * aux2;//Se crean punteros para formar los enlances en la lista doblemente enlazada
    aux=L;//Se le asigna la lista a aux
    AccesoLista=AccesoLista+1;
 //Se le suma un accesos a la lista doblemente enlazada por la asignacion a aux
    while(aux!=NULL){//Mientras el puntero auxiliar no llegue a nulo hará lo siguiente
        AccesoLista=AccesoLista+2;
 //Se le suman 2 a los accesos de memoria de la lista enlazada por la comparacion del while y la comparacion del if
        if(ValorAEli==aux->info){//Si el valor del archivo eli es igual al del auxiliar entonces
            AccesoLista=AccesoLista+1;
 //Se le suma un accesos a la memoria de la lista doblemente enlazada por la comparacion del if
            if(aux!=L){//Si aux es distinto de L
                aux2=aux->ant;//Se le asigna a aux2 el anterior de aux
                aux2->sig=aux->sig;//Se le asigna al siguiente de aux2 el siguiente de aux
                free(aux);//Se libera la memoria de aux que es el que contiene el valor a eliminar
                AccesoLista=AccesoLista+4;
 //Se le suman 4 a los accesos de memoria de la lista doblemente enlazada por las asignaciones anteriores y por la comparacion del if
                if(aux2->sig!=NULL){//Si el siguiente del aux2 es distinto de nulo entonces
                    aux=aux2->sig;//Se le asigna a aux el siguiente de aux2
                    aux->ant=aux2;//Se le asigna al anterior de aux el aux2
                    AccesoLista=AccesoLista+2;
 //Se le suman 2 a los accesos de memoria de la lista doblemente enlazada por las asignaciones anteriores
                }
                else{//Si el siguiente del aux2 es nulo
                    aux=aux2;//Se le asigna a aux el aux2
                    AccesoLista=AccesoLista+1;
 //Se le suma un acceso a memoria a la lista doblemente enlazada por la asignacion a aux
                }
            }
            else{//Si aux es igual a L
                AccesoLista=AccesoLista+1;
 //Se le suma un acceso a memoria a la lista doblemente enlazada por la comparacion del if siguiente
                if(ValorAEli<=aux->info){//Si el valor de el archivo eli es menor o igual al de aux
                    L=L->sig;//Se le asigna el siguiente de L a L
                    free(aux);//Se libera la memoria de aux
                    aux=L;//Se le asigna a aux el puntero a L
                    AccesoLista=AccesoLista+4;
 //Se le suman 4 accesos a la memoria a la lista doblemente enlazada por las asignaciones anteriores y por la comparacion del if siguente
                    if(L!=NULL){//Si L es distinto de nulo
                        L->ant=NULL;//Se le asigna al anterior de L un nulo
                        AccesoLista=AccesoLista+1;
 //Se le suma un acceso de memoria a la lista doblemente enlazada por la asignacion a L
                    }
                }
                else//Si el valor de el archivo eli es mayor entonces
                   break;//Se sale del ciclo 
            }
        }
        else{//Si el valor del archivo eli es diferente del info de aux entonces
            aux=aux->sig;//Se le asigna a aux el siguiente de aux, avanzando al otro nodo 
            AccesoLista=AccesoLista+1;
 //Se le suma un acceso de memoria a la lista doblemente enlazada por la asignacion a aux
        }
    }
    return L;//Retorna el inicio de la lista
}
//Parametros de Insertar_Ordenado_Arreglo: El valor sacado de el archivo ins
void Insertar_Ordenado_Arreglo(int Valor) 
{
    int i,j;//Se inicializan iteradores para los for siguientes

    if(Fin == 0) //Si Fin que es la cantidad de celdas utilizadas por el arreglo es igual a 0, entonces
    {
        array[0] = Valor;//Se le asigna el valor del archivo ins a la primera celda de el arreglo
        AccesoArreglo=AccesoArreglo+1;
 //Se le suma un acceso de memoria al arreglo por la asignacion al array en su primera celda
    }   
    else{//Si Fin es distinto de 0, entonces
        for(i=0;i<Fin;i++)//Para el iterador i=0 que va desde 0 hasta Fin que avanza en 1, hará
        {
            AccesoArreglo=AccesoArreglo+1;
 //Se le suma un acceso de memoria al arreglo por la comparacion en el proximo if
            if(Valor<=array[i])//Si el valor del archivo ins es menor o igual al valor del arreglo en la posicion i, entonces
            {
                break;//Se sale del ciclo
            }
        }
 //El for anterior es solo para encontrar la posicion en donde insertar el numero
        if(i!=Fin){//Si i es distinto de Fin entonces
            for(j=Fin;j>i;j--)//Para j=Fin desde j hasta uno mayor que i con paso j--, entonces
            {
                array[j]=array[j-1];//Se le asigna al arreglo en la posicion j el valor del arreglo en la posicion j-1
                AccesoArreglo=AccesoArreglo+1;
 //Se le suma un acceso de memoria al arreglo por la asignacion al arreglo en la posicion j
            }
        }
        array[i]=Valor;//Se le asigna al arreglo en la posicion i el valor del archivo ins
        AccesoArreglo=AccesoArreglo+1;
        //Se le suma un acceso de memoria al arreglo por la asignacion al arreglo en la posicion i
    }
    Fin++;//Suma en uno el contador Fin, porque se llenó una celda con el valor del archivo ins
}
 //Parametros de Buscar_Eliminar_Arreglo: El valor sacado de el archivo eli
void Buscar_Eliminar_Arreglo(int ValorAEli)
{
    int i,j;//Se inicializan los iteradores para los siguientes for
    if(Fin!=0){//Si Fin es distinto de 0 
        for(i=0;i<Fin;i++){//Para i=0 desde i hasta Fin con i++, hacer
            AccesoArreglo=AccesoArreglo+1;
 //Se le suma un acceso a la memoria al arreglo por la comparacion en el if siguiente
            if(ValorAEli==array[i]){//Si el valor del archivo eli es igual al valor del arreglo en la posicion i
                for(j=i;j<Fin;j++)//Para j=i desde j hasta Fin con paso j+, hacer
                {
                    array[j]=array[j+1];//Se le asigna al arreglo en la posicion j el valor del arreglo en la posicion j+1
                    AccesoArreglo=AccesoArreglo+1;
 //Se le suma un acceso a la memoria al arreglo por la asignacion al arreglo en la posicion j
                }   
                array[Fin]=0;//Se le asigna a la posicion Fin del arreglo el 0 para restarle 1 al total
                AccesoArreglo=AccesoArreglo+1;
 //Se le suma un acceso a la memoria al arreglo por la asignacion al arreglo en la pocision Fin
                Fin--;//Fin disminuye en 1
                i--;//I disminuye en 1
            }
            else{//Si el valor del archivo eli es diferente al valor del arreglo en la posicion i 
                AccesoArreglo=AccesoArreglo+1;
 //Se le suma un acceso a la memoria al arreglo por la comparacion en el if siguiente
                if(ValorAEli<array[i]){//Si el valor del archivo eli es menor al valor del arreglo en la posicion i, entonces
                    break;//Termina el ciclo
                }    
            }
        }
    }
}
//Parametros de Mostrar: La lista
void Mostrar(tNodo *L)
{
    int j; //Se inicializa un iterador para usarse en el for
    if(L!=NULL) //Si la lista es distinta a nulo
    {
        tNodo * aux; //Se inicializa una lista auxiliar
        int i=1; 
        aux=L; // se iguala la lista con la auxiliar
        while(aux!=NULL) //Mientra la lista auxiliar sea distinta de nulo imprime cada nodo
        {
            printf("Nodo[%d]= %d\n",i,aux->info);
            aux=aux->sig; //El auxiliar avanza al nodo siguiente
            i++;
        }
        for(j=0;j<Fin;j++) //Recorre el array y lo va imprimiedo
        {
            printf("Arreglo[%d]=%d\n",j,array[j]);
        }
    }
    else //Si la lista es nula entonces
    {
        printf("No existen elemento en las listas en este momento.\n\n"); 
    }
}
//Parametros de Imprime_Bytes:Sin parametros necesarios
void Imprime_Bytes()
{
    int aux=sizeof(tNodo)*Fin; //Inicialización de un aux del tamaño de tNodo * Fin
    int aux2=sizeof(int)*Fin; //Inicialización de un aux2 del tamaño de tNodo * Fin
    printf("\t La Lista doblemente enlazada utiliza %d Bytes\n",aux);
    printf("\t El arreglo utiliza %d Bytes\n\n",aux2);
}
//Parametros de Abre_arch: Cadena la cual contiene todo lo ingresado por el usuario al iniciar el programa
FILE * Abre_arch(char * entrada)
{
    FILE * Arch;//Iniciaización variable tipo archivo
    Arch=fopen((entrada+2),"r"); //Se abre el archivo en forma de lectura
    if(Arch==NULL) // si el archivo está vacío
    {
        printf("No se encontró el archivo.\n\n");
        return 0;
    }
    printf("Se abrió correctamente el archivo.\n");
    return Arch;// retorna el archivo
}

//--------------------------------------------------------------------------------------------------------

int main() 
{
    int Flag= 0;//Utilizada para controlar si hubo un error en el ingreso de comando
    char entrada[1000];//Variable para tomar toda la linea ingresada por el usuario
    char comando;//Variable para tomar el comando ingresado
    tNodo * Lista=NULL;//Puntero que apuntara al primer numero de la lista 
    FILE * Auxarch=NULL;//Variable para el archivo que se abrirá

    printf("Laboratorio_1:\n\n");
    do  //Ciclo que se asegura de que el programa no termine hastá que se ingrese el comando necesario
    {
        Flag=0;
        printf("\t Ingrese comando: ");
        gets(entrada);//Toma la linea ingresada por el usuario
        Auxarch=NULL;
        if(strlen(entrada)>=1)//Revisa si cumple con la cantidad necesaria para realizar un comando
        {
            comando=entrada[0];//Asigna la primera posicion de la cadena, en donde se encuentra el comando
            if(comando=='I'||comando=='E')//Caso de que se ingrese I o E 
            {
                if(strlen(entrada)>=3)//Revisa si tiene la cantidad para un comando y el archivo necesario 
                {
                	Auxarch=Abre_arch(entrada);//Se le asigna el archivo a la variable
                    if(Auxarch==NULL)//Revisa si se ingresó bien el archivo
                    {
                        Flag=1;
                    }
                }
                else
                {
                    printf("Falta el archivo para este comando.\n\n");
                    Flag=1;
                }
            }
            if(Flag==0){
                Lista=Toma_comando(comando,Auxarch,Lista);//Lista siempre tendra el inicio de la lista   
            }
        }
        else
        {
        printf("Se ingresó mal el comando, ejecute nuevamente.\n");
        Flag=1;
        }
    }while(comando!='F');
    return (0);
}