/** @file Cluster.cc
    @brief Código de la clase Cluster 
*/

#include "Cluster.hh"


Cluster::Cluster() 
{

}

void Cluster::configurar() 
{
  // Esta operación simplemente llama a a otra que lee la estructura
  // de procesadores del cluster. 

  procesadores.clear(); 
  leer_arbol_procesadores(arbol_procesadores);
}

void Cluster::leer_arbol_procesadores(BinTree<string>& a) 
{
  BinTree<string> a1, a2;
  string p;  
  cin >> p;
  if (p != "*") {
    int m;
    cin >> m; 
    leer_arbol_procesadores(a1);
    leer_arbol_procesadores(a2);
    a = BinTree<string>(p, a1, a2);
    Procesador pro(m); 
    procesadores.insert(make_pair(p,pro)); 
  }
}

void Cluster::escribir_procesador(string id, char& error) const
{
    map<string,Procesador>::const_iterator it = procesadores.find(id);
    if (it == procesadores.end()) error = 'a';
    else {
      error = 'x';
      (it->second).escribir(); 
    }
}

void Cluster::anadir_proceso_procesador(string id, Proceso p, char& error) 
{
  map<string,Procesador>::iterator it = procesadores.find(id); 
  if (it == procesadores.end()) error = 'a';
  else (it->second).anadir_proceso(p,error);
}

void Cluster::eliminar_proceso_procesador(string id, int idp, char& error) {
  map<string,Procesador>::iterator it = procesadores.find(id); 
  if (it == procesadores.end()) error = 'a';
  else (it->second).eliminar_proceso(idp,error);
}

void Cluster::avanzar_t(int t) {
  map<string,Procesador>::iterator it; 
  for(it = procesadores.begin(); it != procesadores.end(); ++it) {
    (it->second).avanzar_tiempo(t); 
  }
}

void Cluster::compactar_memoria_procesador(string id, char& error) {
  map<string,Procesador>::iterator it = procesadores.find(id); 
  if (it == procesadores.end()) error = 'a';
  else {
    error = 'x';
    (it->second).compactar_memoria(); 
  }
}

void Cluster::compactar_memoria_cluster() {
  map<string,Procesador>::iterator it; 
  for(it = procesadores.begin(); it != procesadores.end(); ++it) {
    (it->second).compactar_memoria(); 
  }
}

void Cluster::modificar_cluster(string id, const Cluster& clu, char& error) {
  if(not modificar_rec(arbol_procesadores,id,clu.arbol_procesadores,error)) {
    if(error != 'b' and error != 'c') error = 'a'; 
  } else {
    map<string,Procesador>::iterator it1 = procesadores.find(id); 
    procesadores.erase(it1);

    map<string,Procesador>::const_iterator it; 
    for (it = clu.procesadores.begin(); it != clu.procesadores.end(); ++it) procesadores.insert((*it));
  }
}

bool Cluster::modificar_rec(BinTree<string> &a, string id, const BinTree<string>& suba, char& error) {
    if (a.empty()) { return false; }
    else if(a.value() == id) { 
        map<string,Procesador>::const_iterator it = procesadores.find(id); 
        if ((it->second).procesos_activos()) { error = 'b'; return false; }
        else if(a.left().empty() and a.right().empty())
        { a = suba; error = 'x'; return true; }
        else { error = 'c'; return false; }   
    }
    else {
        BinTree<string> a1 = a.left(), a2 = a.right();
        bool b = modificar_rec(a1, id, suba, error); 
        if (not b) b = modificar_rec(a2, id, suba, error); 
        a = BinTree<string> (a.value(), a1, a2); 
        return b;
    } 
}

string Cluster::elegir_mejor_procesador(Proceso p, bool& aceptado) 
{
    Res  r = mejor_procesador(arbol_procesadores, p, 0);
    if(not r.posible) aceptado = false; 
    else aceptado = true; 
    return r.id; 
} 


Res Cluster::mejor_procesador(const BinTree<string>& a, Proceso p, int prof) {
    ++prof; 
    Res r; 
    if (a.empty()) { r.posible = false; } 
    else {

        Res rizq = mejor_procesador(a.left(),p,prof);
        Res rdcha = mejor_procesador(a.right(),p,prof);

        r = crear_respuesta(a.value(),p,prof);
        if (rizq.posible and (not r.posible or mejor(rizq,r))) r = rizq;
        if (rdcha.posible and (not r.posible or not mejor(r,rdcha))) r = rdcha; 

    }
    return r; 
} 

bool Cluster::mejor(const Res& r1, const Res& r2) { 
    if (r1.posible != r2.posible) return r1.posible; 
    else if (r1.tam_hueco != r2.tam_hueco) return (r1.tam_hueco < r2.tam_hueco);    
    else if (r1.m_libre != r2.m_libre) return (r1.m_libre > r2.m_libre);
    else if (r1.profundidad != r2.profundidad) return (r1.profundidad < r2.profundidad);
    return true;    
}

Res Cluster::crear_respuesta(string id_pro, const Proceso& p, int prof) {
    Res r;
    map<string,Procesador>::const_iterator it = procesadores.find(id_pro); 
    int hueco; 
    r.posible = (it->second).cabe_proceso(p,hueco) and not (it->second).existe_proceso(p.consultar_id()); //aixo u fa menos eficient
    r.tam_hueco = hueco;
    r.m_libre = (it->second).consultar_m_libre(); 
    r.profundidad = prof; 
    r.id = id_pro;

    return r; 
} 

void Cluster::escriure_estructura() const
{
  // Esta operacion simplemente llama a una funcion recursiva
  // que escribe la estructura del arbol de procesadores. 
  escribir_estructura_arbol_procesadores(arbol_procesadores);
  cout << endl;
}

void Cluster::escribir_estructura_arbol_procesadores(const BinTree<string>& a)
{
  if (not a.empty()) {
    cout << "(";
    cout << a.value(); 
    escribir_estructura_arbol_procesadores(a.left());
    escribir_estructura_arbol_procesadores(a.right());
    cout << ")"; 
  } else cout << " ";
}

void Cluster::escriure() const
{
  // Escribimos el árbol de procesadores en inorden.
  for (map<string, Procesador>::const_iterator it = procesadores.begin(); it != procesadores.end(); ++it) {
    cout << it->first << endl;
    it->second.escribir();
  }
}
