/** @mainpage

    Programa para simular el funcionamiento de una arquitectura multiprocesador compuesta
    por un cluster que ha su vez posee distintos procesadores los cuales poseen procesos
    ejecutadonse en sus respectivas memorias. Ademas cuenta con un area de espera para
    aquellos procesos pendientes de ejecutar. 

*/

/** @file program.cc

    @brief Programa principal

    Programa para simular el funcionamiento de una arquitectura multiprocesador. 

*/

#include "Cluster.hh"
#include "Area_espera.hh"
using namespace std; 

int main() {
    Cluster c; 
    c.configurar();
    Area_espera area; 
    int N; 
    cin >> N; 
    area.leer(N);  
    string comando; 
    cin >> comando;
    while (comando != "fin") {

        if (comando == "cc" or comando == "configurar_cluster") {
            cout << "#" << comando << endl; 
            c.configurar(); 

        } else if (comando == "mc" or comando == "modificar_cluster") {
            string id; 
            cin >> id; 
            Cluster clu; 
            clu.configurar(); 
            char error; 
            cout << "#" << comando << " " << id << endl; 
            c.modificar_cluster(id,clu,error); 
            if (error == 'a') cout << "error: no existe procesador" << endl; 
            else if (error == 'b') cout << "error: procesador con procesos" << endl; 
            else if (error == 'c') cout << "error: procesador con auxiliares" << endl; 

        } else if (comando == "app" or comando == "alta_proceso_procesador") {
            string id; 
            cin >> id; 
            Proceso p; 
            p.leer(); 
            char error; 
            cout << "#" << comando << " " << id << " " << p.consultar_id() << endl; 
            c.anadir_proceso_procesador(id,p,error); 
            if (error == 'a') cout << "error: no existe procesador" << endl; 
            else if (error == 'b') cout << "error: ya existe proceso" << endl; 
            else if (error == 'c') cout << "error: no cabe proceso" << endl; 

        } else if (comando == "bpp" or comando == "baja_proceso_procesador") {
            string id; 
            int idp; 
            cin >> id >> idp; 
            char error; 
            cout << "#" << comando << " " << id << " " << idp << endl; 
            c.eliminar_proceso_procesador(id,idp,error); 
            if (error == 'a') cout << "error: no existe procesador" << endl; 
            else if (error == 'b') cout << "error: no existe proceso" << endl; 

        } else if (comando == "at" or comando == "avanzar_tiempo") {
            int t; 
            cin >> t; 
            cout << "#" << comando << " " << t << endl; 
            c.avanzar_t(t);

        } else if (comando == "ipro" or comando == "imprimir_procesador") {
            string id; 
            cin >> id; 
            cout << "#" << comando << " " << id << endl; 
            char error; 
            c.escribir_procesador(id,error); 
            if(error == 'a') cout << "error: no existe procesador" << endl; 

        } else if (comando == "ipc" or comando == "imprimir_procesadores_cluster") {
            cout << "#" << comando << endl; 
            c.escriure(); 

        } else if (comando == "iec" or comando == "imprimir_estructura_cluster" ) {
            cout << "#" << comando << endl; 
            c.escriure_estructura(); 
        
        } else if (comando == "cmp" or comando == "compactar_memoria_procesador") {
            string id; 
            cin >> id; 
            char error; 
            cout << "#" << comando << " " << id << endl; 
            c.compactar_memoria_procesador(id,error);
            if (error == 'a') cout << "error: no existe procesador" << endl; 

        } else if (comando == "cmc" or comando == "compactar_memoria_cluster") {
            cout << "#" << comando << endl; 
            c.compactar_memoria_cluster(); 

        } else if (comando == "ap" or comando == "alta_prioridad") {
            string prioridad; 
            cin >> prioridad; 
            cout << "#" << comando << " " << prioridad << endl; 
            bool error; 
            area.anadir_prioridad(prioridad,error); 
            if (error) cout << "error: ya existe prioridad" << endl; 

        } else if (comando == "bp" or comando == "baja_prioridad") {
            string prioridad; 
            cin >> prioridad;
            cout << "#" << comando << " " << prioridad << endl; 
            char error; 
            area.eliminar_prioridad(prioridad,error);
            if (error == 'a') cout << "error: no existe prioridad" << endl; 
            else if (error == 'b') cout << "error: prioridad con procesos" << endl; 

        } else if (comando == "ape" or comando == "alta_proceso_espera") {
            string prioridad; 
            cin >> prioridad; 
            int id,m,t; 
            cin >> id >> m >> t;
            Proceso p(id,m,t);
            cout << "#" << comando << " " << prioridad << " " << id << endl; 
            char error; 
            area.anadir_proceso(p,prioridad,error);
            if (error == 'a') cout << "error: no existe prioridad" << endl; 
            else if (error == 'b') cout << "error: ya existe proceso" << endl; 

        } else if (comando == "ipri" or comando == "imprimir_prioridad") {
            string id; 
            cin >> id; 
            cout << "#" << comando << " " << id << endl; 
            if (not area.existe_prioridad(id)) cout << "error: no existe prioridad" << endl; 
            else area.imprimir_prioridad(id);

        } else if (comando == "iae" or comando == "imprimir_area_espera") {
            cout << "#" << comando << endl; 
            area.imprimir(); 
            
        } else if (comando == "epc" or comando == "enviar_procesos_cluster") {
            int n; 
            cin >> n; 
            cout << "#" << comando << " " << n << endl; 
            area.enviar_procesos_cluster(n,c);
        }

        cin >> comando; 
    } 
}