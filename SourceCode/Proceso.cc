/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() 
{
  // Inicializa una proceso con los atributos a zero
  id = 0; 
  mem = 0;
  t_eje = 0; 
}

Proceso::Proceso(int a, int b, int c) {
    id = a; 
    mem = b; 
    t_eje = c; 
}

int Proceso::consultar_id() const
{
  return id;
}

int Proceso::consultar_mem() const
{
  return mem;
}

int Proceso::consultar_t() const
{
  return t_eje;
}

void Proceso::modificar_id(int x) 
{
    this->id = x; 
}

void Proceso::modificar_mem(int x) 
{
    this->mem = x; 
}

void Proceso::modificar_t(int x) 
{
    this->t_eje = x; 
}

void Proceso::leer()
{
    cin >> id >> mem >> t_eje; 
}

void Proceso::escribir() const
{
   cout << id << " " << mem << " " << t_eje << endl; 
}