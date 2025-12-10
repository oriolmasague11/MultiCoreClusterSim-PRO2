/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() 
{
    mem_max = 0; 
    Proceso p(-1,mem_max,0); //hueco
    mem.insert(make_pair(0,p));
    set<int> p_inis; 
    p_inis.insert(0); 
    huecos.insert(make_pair(mem_max,p_inis));
    mem_libre = 0; 
}

Procesador::Procesador(int m) 
{
    mem_max = m; 
    Proceso p(-1,m,0); //hueco
    mem.insert(make_pair(0,p));
    huecos[m].insert(0);
    mem_libre = m; 
}

void Procesador::anadir_proceso(const Proceso& p, char& error) {    
    map<int,int>::const_iterator it = pos_inis.find(p.consultar_id()); 
    if (it != pos_inis.end()) error = 'b';
    else {

        int mempro = p.consultar_mem(); 
        map<int,set<int>>::iterator ith = huecos.lower_bound(mempro); 
        if (ith != huecos.end()) {
            error = 'x'; 
            set<int>::iterator itc = (ith->second).begin(); 
            int pos = (*itc); 
            (ith->second).erase(itc); 
            if ((ith->second).empty()) huecos.erase(ith); 
            map<int,Proceso>::iterator itm = mem.find(pos); 

            int memhueco = (itm->second).consultar_mem() - mempro; 

            //añadimos el proceso
            itm = mem.erase(itm); 
            itm = mem.insert(itm, make_pair(pos,p));  

            //añadimos el nuevo hueco
            if (memhueco != 0) {
                Proceso hueco(-1,memhueco,0); 
                int poshueco = pos + mempro; 
                itm = mem.insert(itm, make_pair(poshueco,hueco)); 
                anadir_hueco(memhueco,poshueco); 
            }

            //añadimos el proceso al mapa de posiciones iniciales
            int id_proceso = p.consultar_id(); 
            pos_inis.insert(make_pair(id_proceso,pos)); 

            mem_libre -= mempro; 

        } else error = 'c';

    }
}

bool Procesador::cabe_proceso(const Proceso &p, int& tam_hueco) const {
    int mempro = p.consultar_mem(); 
    map<int,set<int>>::const_iterator ith = huecos.lower_bound(mempro); 
    if (ith != huecos.end()) {tam_hueco = (ith->first); return true;}
    return false; 
}

int Procesador::consultar_m_libre() const {
    return mem_libre; 
}

bool Procesador::existe_proceso(int id) const {
    map<int,int>::const_iterator it = pos_inis.find(id); 
    if (it == pos_inis.end()) return false; 
    return true; 
}

bool Procesador::procesos_activos() const {
    if (pos_inis.empty()) return false; 
    return true; 
}


void Procesador::eliminar_proceso(int id, char& error) {

    map<int,int>::const_iterator itp = pos_inis.find(id); 

    if (itp == pos_inis.end()) error = 'b'; 
    else {
        error = 'x';
        int pos = (itp->second); 
        map<int,Proceso>::iterator it = mem.find(pos); 
        terminar_proceso(it);   
        if (it != mem.begin()) mirar_izq(it); 
        if (++it != mem.end()) mirar_izq(it);
    }   
}

void Procesador::avanzar_tiempo(int t) {
    map<int,Proceso>::iterator it = mem.begin(); 
    while (it != mem.end()) {  
        if ((it->second).consultar_id() == -1) ++it; 
        else {
            int tf = (it->second).consultar_t() - t; 
            if (tf > 0) { (it->second).modificar_t(tf); ++it; }
            else {
                terminar_proceso(it);  
                if (it != mem.begin()) mirar_izq(it); 
                if (++it != mem.end()) mirar_izq(it);
            }
        }
    }
}

void Procesador::terminar_proceso(map<int,Proceso>::iterator& it) {
    //Borramos el proceso del mapa identificador - posiciones iniciales
    map<int,int>::iterator itp = pos_inis.find((it->second).consultar_id());
    pos_inis.erase(itp); 

    int memh = (it->second).consultar_mem();
    int pos = (it->first); 

    //lo añadimos al mapa de huecos
    anadir_hueco(memh,pos);

    //lo convertimos en un hueco
    (it->second).modificar_t(0);
    (it->second).modificar_id(-1);

    mem_libre += memh; 

}

void Procesador::borrar_hueco(int mem, int pos) 
    // Borra la posicion del hueco dentro del conjunto de posiciones de una determinada cantidad de memoria
{
    map<int,set<int>>::iterator ith = huecos.find(mem); 
    set<int>::iterator itc = (ith->second).find(pos);
    (ith->second).erase(itc);
    if ((ith->second).empty()) huecos.erase(ith); 
}

void Procesador::anadir_hueco(int memhueco, int poshueco) 
    // Añade un hueco dentro del conjunto de posiciones que ocupan esa memoria
{
    map<int,set<int>>::iterator ith = huecos.find(memhueco); 

    if (ith == huecos.end()) { 
        set<int> conj; 
        conj.insert(poshueco); 
        huecos.insert(make_pair(memhueco,conj)); 
    } else {
        (ith->second).insert(poshueco); 
    }
}

void Procesador::mirar_izq(map<int,Proceso>::iterator& it) {
    map<int,Proceso>::iterator esq = it; 
    --esq; 

    if ((esq->second).consultar_id() == -1 and (it->second).consultar_id() == -1) {
        int mem_esq = (esq->second).consultar_mem(); 
        int pos_esq = (esq->first); 
        int mem_p = (it->second).consultar_mem(); 
        int pos_p = (it->first); 

        borrar_hueco(mem_esq, pos_esq); 
        borrar_hueco(mem_p, pos_p);

        int memf = mem_esq + mem_p;
        //borramos el proceso apuntado por it
        it = mem.erase(it); 
        //augmentamos la memoria del proceso a la izquierda de it (apuntado por esq)
        (esq->second).modificar_mem(memf); 

        anadir_hueco(memf,pos_esq); 
        //recolocamos el iterador en el hueco resultante
        it = esq; 
    }
}


void Procesador::compactar_memoria() {  
    if (mem_libre != 0) {

        map<int,Proceso>::iterator it = mem.begin(); 
        int pos_seg = 0; 
        while (it != mem.end()) {

            if ((it->second).consultar_id() == -1) { it = mem.erase(it); }
            else {
                Proceso p = (it->second); 
                it = mem.erase(it); 
                it = mem.insert(it,make_pair(pos_seg,p)); 

                //lo cambiamos del mapa id - posicion inicial
                map<int,int>::iterator itp = pos_inis.find(p.consultar_id()); 
                (itp->second) = pos_seg; 

                pos_seg += p.consultar_mem();

                ++it;
            } 
        }

        Proceso hueco(-1,mem_libre,0);
        it = mem.insert(it,make_pair(pos_seg,hueco));

        huecos.clear(); 
        anadir_hueco(mem_libre,pos_seg);
    }
}



void Procesador::escribir() const 
{
    map<int, Proceso>::const_iterator it;
    for (it = mem.begin(); it != mem.end(); ++it) {
        if((it->second).consultar_id() != -1) {
        cout << (it->first) << " ";
        (it->second).escribir(); 
        }
    } 
}


