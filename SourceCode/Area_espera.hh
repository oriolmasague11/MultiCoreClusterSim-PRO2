/** @file Area_espera.hh
    @brief Especificació de la clase Area_espera
*/

#ifndef _AREA_ESPERA_
#define _AREA_ESPERA_

#include "Cluster.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM  
#include <list>
#endif

struct Prioridad {
  int colocados; 
  int rechazados; 
  list<Proceso> l; 
};

/** @class Area_espera
    @brief Representa el area de espera con las prioridades de los procesos pendientes.

*/

class Area_espera
{

    // Descripcion: contiene las prioridades con sus respectivos procesos pendientes
    // y las operaciones necesarias para gestionarlas. 

private: 

  /** @brief Contenedor de memoria con las prioridades i los procesos pendientes */
  map<string,Prioridad> prioridades;

public: 

  //Constructora

  /** @brief Creadora por defecto.
      \pre <em>cierto</em>
      \post El resultado es una area de espera sin prioridades
  */
  Area_espera();

  //Modificadoras

  /** @brief Operacion para añadir una prioridad
      \pre <em>cierto</em>
      \post Error indica si ya existe en el parametro implicito una prioridad con identificador
      id. En caso contrario se añade una prioridad con 
      identificador id al parametro implicito. 
  */
  void anadir_prioridad(string id, bool& error);

  /** @brief Operacion para eliminar una prioridad
      \pre <em>cierto</em>
      \post Error indica si no existe en el parametro implicito una prioridad con identificador
      id o si esta tiene procesos pendientes. En caso que no haya error se elimina del parametro implicito la prioridad con identificador id. 
  */
  void eliminar_prioridad(string id, char& error); 

  /** @brief Operacion para añadir un proceso
      \pre <em>cierto</em>
      \post Si no existe la prioridad en el parametro implicito o si ya habia un
      proceso con ese identificador y esa prioridad se devulve el tipo de 
      error. En caso que no haya error se añade al parametro implicito proceso p a la prioridad con id
      "prioridad".
  */
  void anadir_proceso(Proceso p, string prioridad, char& error);

  /** @brief Operacion de enviar procesos pendientes al cluster
      \pre n es un entero no negativo
      \post Se intentan colocar n procesos del parametro implicito en el cluster c
      por orden de prioridad. Dentro de la misma prioridad se envian primero los
      mas antiguos. Se intentaran colocar hasta n procesos sin repetir, o hasta
      que no queden mas procesos por enviar en el parametro implicito. 
  */
  void enviar_procesos_cluster(int n, Cluster& c);

  //Consultores

  /** @brief Consultora de existencia de prioridad
      \pre <em>cierto</em>
      \post Devuelve cierto si existe una prioridad con identificador "identificador"
      en el parametro implicito y falso en caso contrario.
  */
  bool existe_prioridad(string prioridad) const; 

  //Escritura y lectura

  /** @brief Operación de lectura
      \pre N>0
      \post El parametro implicito posee N prioridades procedentes del canal estandard de entrada.
  */
  void leer(int N); 

  /** @brief Operacion de escritura
      \pre <em>cierto</em>
      \post Se ha escrito por el canal de salida estandard los procesos pendientes del parametro implicito
      por orden creciente de prioridad. Para cada prioridad se escriben los procesos pendientes por 
      orden creciente de antiguedad. 
  */
  void imprimir() const;

  /** @brief Operacion de escritura de prioridad
      \pre Existe una prioridad con identificador idp
      \post Se han escrito por el canal de salida estandard los procesos pendientes de la prioridad
      con identificador idp por oden creciente de antiguedad.
  */
  void imprimir_prioridad(string idp) const;

}; 

#endif