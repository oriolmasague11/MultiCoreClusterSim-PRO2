/** @file Area_espera.cc
    @brief Código de la clase Area_espera 
*/

#include "Area_espera.hh"

Area_espera::Area_espera() 
{
  
}

void Area_espera::leer(int N) {
    for (int i = 0; i < N; ++i) {
        string id; 
        cin >> id; 
        Prioridad prio; 
        prio.colocados = prio.rechazados = 0; 
        prioridades.insert(make_pair(id,prio));
    }
}

void Area_espera::anadir_prioridad(string id, bool& error) {
    error = existe_prioridad(id); 
    if (not error) {
        Prioridad prio;
        prio.colocados = prio.rechazados = 0;  
        prioridades.insert(make_pair(id,prio)); 
    }
}

bool Area_espera::existe_prioridad(string prioridad) const 
{ 
    map<string,Prioridad>::const_iterator it = prioridades.find(prioridad); 
    if (it == prioridades.end()) return false; 
    return true; 
}

void Area_espera::eliminar_prioridad(string id, char& error) {
    map<string,Prioridad>::iterator it = prioridades.find(id); 
    if (it == prioridades.end()) error = 'a';
    else if (not (it->second).l.empty()) error = 'b'; 
    else {
        error = 'x'; 
        prioridades.erase(it); 
    }
}

bool existeix_proceso(int id,const list<Proceso>& l) {
    // El resultado es cierto si existe un proceso con identificador id
    // en esa prioridad y falso en caso contrario. 

    list<Proceso>::const_iterator it = l.begin();
    while (it != l.end()) {
        if((*it).consultar_id() == id) return true; 
        else ++it; 
    }
    return false; 
}

void Area_espera::anadir_proceso(Proceso p, string prioridad, char& error) {   
    map<string,Prioridad>::iterator it = prioridades.find(prioridad);
    if (it == prioridades.end()) error = 'a';
    else if (existeix_proceso(p.consultar_id(),(it->second).l)) error = 'b';
    else {
        error = 'x'; 
        list<Proceso>::iterator it2 = (it->second).l.end(); 
        (it->second).l.insert(it2,p); 
    }
}

void Area_espera::enviar_procesos_cluster(int n, Cluster& c) {
    int coloc = 0; 
    map<string,Prioridad>::iterator it;
    for (it = prioridades.begin(); (coloc != n) and (it != prioridades.end()); ++it) {

        list<Proceso>::iterator itl = (it->second).l.begin();
        int cont = (it->second).l.size();
        while ((coloc != n) and cont != 0) {
            bool aceptado; 
            Proceso p = (*itl);
            string id_pr = c.elegir_mejor_procesador(p,aceptado); 
            char e; 
            if (aceptado) { c.anadir_proceso_procesador(id_pr,p,e);
            (it->second).colocados += 1; ++coloc; }
            else {
                (it->second).rechazados += 1; 
                list<Proceso>::iterator itl2 = (it->second).l.end(); 
                (it->second).l.insert(itl2,(*itl));
            }

            itl = (it->second).l.erase(itl);
            --cont; 
        }

    }
}

void Area_espera::imprimir() const
{
        map<string,Prioridad>::const_iterator it; 
        for (it = prioridades.begin(); it != prioridades.end(); ++it) {
            cout << (it->first) << endl; 
            list<Proceso>::const_iterator it2; 
            for (it2 = (it->second).l.begin(); it2 != (it->second).l.end(); ++it2) {
                int id = (*it2).consultar_id(); 
                cout << id << " " << (*it2).consultar_mem() << " " << (*it2).consultar_t() << endl; 
            } 
            cout << (it->second).colocados << " " << (it->second).rechazados << endl; 
        }
}

void Area_espera::imprimir_prioridad(string idp) const 
{
    map<string,Prioridad>::const_iterator it = prioridades.find(idp);
    list<Proceso>::const_iterator it2; 
    for (it2 = (it->second).l.begin(); it2 != (it->second).l.end(); ++it2) {
        int id = (*it2).consultar_id(); 
        cout << id << " " << (*it2).consultar_mem() << " " << (*it2).consultar_t() << endl; 
    } 
    cout << (it->second).colocados << " " << (it->second).rechazados << endl; 
}