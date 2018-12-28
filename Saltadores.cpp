/* Practica evaluable 2018/2019

Nombre y apellidos: Sergio Jim�nez Salmer�n
DNI: 15428591F
Grado: Sistemas Electr�nicos
Grupo: B

*/
#include <iostream>
#include <string>
#include <array>

using namespace std;

// -- Constantes -------
const int MAX_DEPORTISTAS = 100;
const int OK = 0;
const int LISTA_LLENA = 1;
const int LISTA_VACIA = 2;
const int YA_EXISTE = 3;
const int NO_EXISTE = 4;
const int NO_DEPOR_NACION = 5;


// -- Tipos ------------
typedef struct{
    string nombre;
    string nacion;
    float try1, try2, try3;
    float mejorMarca;
} TInfoDepor;

typedef array <TInfoDepor, MAX_DEPORTISTAS> TListDepor;

typedef struct{
    unsigned nDepor;
    TListDepor depor;
} TCompeticion;

// -- Subalgoritmos ----
void Vaciar(TCompeticion &c);
void MostrarDep(const TInfoDepor &d);
void Mostrar(const TCompeticion &c, unsigned &ok);
void Inscribir(const TInfoDepor &d, TCompeticion &c, unsigned &ok);
void Prueba(const string &nombre, const float &salto1, const float &salto2, const float &salto3, TCompeticion &c, unsigned &ok);
void Descalificar(const TInfoDepor &d, TCompeticion &c, unsigned &ok);
void Ganador(TCompeticion &c, int &x, unsigned &ok);
void Nacionalidad(const string &pais, const TCompeticion &c, unsigned &ok);
//void Ordenar(TCompeticion &c);
//int ordenar_puntuacion(TCompeticion &c, int pos);
//unsigned buscar_ganador(const TCompeticion &c);
unsigned buscar_deport(const string &nombre, const TCompeticion &c);
float calc_mejormarca(const float &salto1, const float &salto2, const float &salto3);
unsigned Menu();
void cod_error(unsigned cod);

// -- Principal --------
int main() {
    TCompeticion c;
    TInfoDepor d;
    int gana = 0;
    string nombre, pais;
    float salto1, salto2, salto3;
    unsigned ok;
    unsigned opcion;
    Vaciar(c);
    do {
        opcion = Menu();
        switch (opcion) {
        case 1:   // Mostrar toda la estructura
            cout << "LISTA DE PARTICIPANTES: " << endl;
            Mostrar(c,ok);
            cod_error(ok);
            break;
        case 2:    // Inscribir deportista
            cout << "Introduzca datos de el/la participante" << endl;
            cout << "Introduzca nombre: ";
            cin >> d.nombre;
            cout << "Introduzca nacionalidad: ";
            cin >> d.nacion;
            Inscribir(d,c,ok);
            cod_error(ok);
            break;
        case 3:   // Realizar la prueba
            cout << "Introduzca el nombre de el/la participante: ";
            cin >> nombre;
            cout << "Introduzca las puntuaciones: " << endl;
            cout << "Salto 1: ";
            cin >> salto1;
            cout << "Salto 2: ";
            cin >> salto2;
            cout << "Salto 3: ";
            cin >> salto3;
            Prueba(nombre,salto1,salto2,salto3,c,ok);
            cod_error(ok);
            break;
        case 4:  // Ganador
            Ganador(c,gana,ok);
            cout << "El ganador de la prueba es ";
            cout << c.depor[gana].nombre;
            cout << ", de ";
            cout << c.depor[gana].nacion;
            cout << ". Con una puntuacion de ";
            cout << c.depor[gana].mejorMarca;
            cout << "." << endl;
            cod_error(ok);
            break;
        case 5:   // Nacionalidad
            cout << "Introduzca nacionalidad: ";
            cin >> pais;
            Nacionalidad(pais,c,ok);
            cod_error(ok);
            break;
        case 6:   // Descalificar
            cout << "Introduzca el nombre de el/la participante: ";
            cin >> d.nombre;
            Descalificar(d,c,ok);
            cod_error(ok);
        }
    } while (opcion != 0 );
}

// -- Subalgoritmos ----
void Vaciar(TCompeticion &c)
{
    c.nDepor = 0;
}

void MostrarDep(const TInfoDepor &d)
{
    cout << "Nombre: " << d.nombre << endl;
    cout << "Nacionalidad: " << d.nacion << endl;
    cout << "Puntuaciones: " << endl;
    cout << "Salto 1: " << d.try1 << "|";
    cout << "Salto 2: " << d.try2 << "|";
    cout << "Salto 3: " << d.try3 << endl;
    cout << "Mejor salto: " << d.mejorMarca << endl;
    cout << "-----------------" << endl;
}

void Mostrar(const TCompeticion &c, unsigned &ok)
{
    if (c.nDepor > 0){
        for(int i=0; i< c.nDepor; i++) {
            MostrarDep(c.depor[i]); // Muestra un deportista
        }
        ok = OK;
    } else {
        ok = LISTA_VACIA;
    }
}

void Inscribir(const TInfoDepor &d, TCompeticion &c, unsigned &ok)
{
    int i = buscar_deport(d.nombre, c);
    if(i < c.nDepor)
    {
        ok = YA_EXISTE;
    } else if (c.nDepor>=c.depor.size()) {
        ok = LISTA_LLENA;
    } else {
        ok = OK;
        c.depor[c.nDepor] = d;
        c.nDepor++;
    }
}

void Prueba(const string &nombre, const float &salto1, const float &salto2, const float &salto3, TCompeticion &c, unsigned &ok)
{
    unsigned i = buscar_deport(nombre, c);
    if(i >= c.nDepor)
    {
        ok = NO_EXISTE;
    } else {
        ok = OK;
        c.depor[i].try1=salto1;
        c.depor[i].try2=salto2;
        c.depor[i].try3=salto3;
        c.depor[i].mejorMarca = calc_mejormarca(salto1,salto2,salto3);
    }
}

void Descalificar(const TInfoDepor &d, TCompeticion &c, unsigned &ok)
{
    unsigned i = buscar_deport(d.nombre, c);
    if(i >= c.nDepor)
    {
        ok = NO_EXISTE;
    } else {
        ok = OK;
        if(i < c.nDepor-1)
        {
            c.depor[i] = c.depor[c.nDepor-1];
        }
        c.nDepor--;
    }
}

void Ganador(TCompeticion &c, int &gana, unsigned &ok)
{
    if(c.nDepor>0)
    {
        ok = OK;
        //gana = 0;
        for(int i = 0; i<c.nDepor;i++)
        {
            if(c.depor[i].mejorMarca>c.depor[gana].mejorMarca)
            {
                gana = i;
            }
        }
    } else {
        ok = LISTA_VACIA;
    }
}

void Nacionalidad(const string &pais, const TCompeticion &c, unsigned &ok)
{
    bool hay_pais = false;
    if(c.nDepor>0){
        for(int x=0; x<c.nDepor; x++)
        {
            if(pais==c.depor[x].nacion)
            {
                ok = OK;
                hay_pais = true;
                MostrarDep(c.depor[x]);

                //if()
            }
        }
        if(!hay_pais)
        {
            ok = NO_DEPOR_NACION;
        } else {
            ok = OK;
        }
    } else {
        ok = LISTA_VACIA;
    }
}

/*
void Ordenar(TCompeticion &c)
{
    for(int i=0;i<c.depor.size();i++){
        if(c.depor[i].mejorMarca>c.depor[i+1].mejorMarca)
        {
            TInfoDepor aux = c.depor[i];
            c.depor[i]=c.depor[i+1];
            c.depor[i+1]=aux;
        }
    }
}

/*
int ordenar_puntuacion(TCompeticion &c, int pos)
{
    int mejor_puntuacion = pos;
    for(int i=mejor_puntuacion+1; i<c.depor.size(); i++)
    {
        if(c.depor[i].mejorMarca>c.depor[mejor_puntuacion].mejorMarca)
        {
            mejor_puntuacion=i;
        }
    }
    return mejor_puntuacion;
}
*/




unsigned buscar_deport(const string &nombre, const TCompeticion &c)
{
    unsigned i = 0;
    while((i < c.nDepor)&&(nombre != c.depor[i].nombre)){
        i++;
    }
    return i;
}

float calc_mejormarca(const float &salto1, const float &salto2, const float &salto3)
{
    float mejorMarca = salto1;
    if(salto2>mejorMarca)
    {
        mejorMarca = salto2;
    }
    if(salto3>mejorMarca)
    {
        mejorMarca = salto3;
    }
    return mejorMarca;
}

unsigned Menu()
{
    unsigned opcion;
    cout << "-------------------------" << endl;
    cout << "     MENU PRINCIPAL      " << endl;
    cout << "-------------------------" << endl;
    cout << "1. - Mostrar todo" << endl;
    cout << "2. - Inscribir deportista" << endl;
    cout << "3. - Realizar la prueba" << endl;
    cout << "4. - Ganador" << endl;
    cout << "5. - Nacionalidad" << endl;
    cout << "6. - Descalificar" << endl;
    cout << endl;
    cout << "0. - Salir" << endl;
    do {
        cout << "Introduzca Opcion: ";
        cin >> opcion;
    } while ( ! ((opcion >= 0) && (opcion <= 5)) );
    return opcion;
}

void cod_error(unsigned cod)
{
    switch(cod)
    {
    case OK:
        cout << "Operacion realizada con exito" << endl;
        break;
    case LISTA_LLENA:
        cout << "Lista de deportistas llena" << endl;
        break;
    case LISTA_VACIA:
        cout << "Lista de deportistas vacia" << endl;
        break;
    case YA_EXISTE:
        cout << "El deportista ya se encuentra inscrito" << endl;
        break;
    case NO_EXISTE:
        cout << "El deportista no se encuentra inscrito" << endl;
        break;
    case NO_DEPOR_NACION:
        cout << "No hay deportistas de esa nacion" << endl;
        break;
    }
}