/** @file Procesador.hh
    @brief Especificacion de la clase Procesador
*/

#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM  
#include <string>
#include <map>
#include <set>
#endif

/** @class Procesador
    @brief Representa un Processador con memoria de procesos

    Ofrece operaciones para introducir procesos en la memoria, asi como quitarlos o compactarla. 

*/

class Procesador
{

    // Descripcion: posee una memoria donde almacena los procesos

private: 

  /** @brief Cantidad de memoria del procesador */
  int mem_max; 
  /** @brief Cantidad de memoria disponible del procesador */
  int mem_libre; 
  /** @brief Memoria del procesador donde contiene los procesos */
  map<int, Proceso> mem;
  /** @brief Memoria de huecos con los tamaños de los huecos y sus posiciones iniciales */
  map<int, set<int>> huecos;
  /** @brief Diccionario con las posiciones iniciales de cada procesador */
  map<int,int> pos_inis; 


public: 

  //Constructoras

  /** @brief Creadora por defecto
      \pre <em>cierto</em>
      \post El resultad0 es un procesador sin procesos
  */
  Procesador(); 

  /** @brief Creadora con identificador
      \pre m>0
      \post El resultado es un Procesador con una memoria de tamaño m y sin procesos en la memoria
  */
  Procesador(int m); 

  //Consultoras

  /** @brief Consultora de la existencia de un proceso
      \pre <em>cierto</em>
      \post El resultado es cierto si el parametro implicito posee un proceso con identificador
      id y falso en caso contrario. 
  */
  bool existe_proceso(int id) const; 

  /** @brief Consultora de procesos activos
      \pre <em>cierto</em>
      \post Devuelve cierto si el parametro implicito tiene procesos en la memoria y falso en caso
      contrario. 
  */
  bool procesos_activos() const;

  /** @brief Consultora de si un proceso cabe en la memoria. 
      \pre <em>cierto</em>
      \post El resultado es cierto si el proceso p cabe en la memoria del parametro implicito y 
      falso en caso contrario. tam_hueco indica el tamaño del hueco mas ajustado donde cabe el 
      proceso p. 
  */
  bool cabe_proceso(const Proceso &p, int& tam_hueco) const;

  /** @brief Consultora de la memoria disponible de procesador
      \pre <em>cierto</em>
      \post El resultado es un entero que representa la cantidad de memoria no ocupada del 
      parametro implicito. 
  */
  int consultar_m_libre() const;


  //Modificadoras

  /** @brief Operacion para añadir un proceso a la memoria del procesador 
      \pre <em>cierto</em>
      \post Error indica si ya existe un proceso con el mismo identificador
      que p o si no cabe p en el parametro implicito. Si no existe error
      se añade el proceso p a la memoria del parametro implicito. 
  */
  void anadir_proceso(const Proceso& p, char& error); 

  /** @brief Modificadora que avanza el tiempo del procesador 
      \pre t>0
      \post El tiempo de ejecucion de los procesos del parametro implicito ha avanzado
      t unidades de tiempo. Aquellos que han finalizado su tiempo de ejecucion han sido
      eliminados de la memoria. 
  */
  void avanzar_tiempo(int t);

  /** @brief Operacion de eliminar un proceso
      \pre <em>cierto</em>
      \post Error indica si el proceso con identificador id no esta en el parametro implicito.
      Si no hay error se elimina el proceso del parametro implicito. 
  */
  void eliminar_proceso(int id, char& error);

  /** @brief Operacion de compactar la memoria
      \pre <em>cierto</em>
      \post Todos los procesos del parametro implicito se han desplazado hacia el principio de la
      memoria, sin dejar huecos, sin solaparse y respetando el orden inicial. 
  */
  void compactar_memoria();

  //Escritura de un processador

  /** @brief Operación de escritura
      \pre <em>cierto</em>
      \post se han escrito por el canal estandard de salida los procesos de la memoria del parametro implicito
      por orden creciente des de la primera posicion de memoria. 
  */
  void escribir() const;

private: 

  /** @brief Añade un hueco al mapa de huecos
      \pre memhueco>0, poshueco>=0
      \post Se ha añadido a la memoria de huecos del parametro implicito un hueco, con 
      memoria memhueco, y su posicion poshueco. 
  */
  void anadir_hueco(int memhueco, int poshueco); 


  /** @brief Borra un hueco del mapa de huecos
      \pre memhueco>0, poshueco>=0
      \post Se ha eliminado del conjunto de posiciones iniciales de la clave mem del mapa de huecos
      la posicion pos. En caso que el conjunto haya quedado vacio tambien se ha eliminado la clave mem. 
  */
  void borrar_hueco(int mem, int pos); 

  /** @brief Operacion de eliminar un proceso 
      \pre <em>cierto</em>
      \post Se ha eliminado el proceso apuntado por it y se ha colocado un hueco.
  */
  void terminar_proceso(map<int,Proceso>::iterator& it);

  /** @brief Mira si el proceso de la izquierda es un hueco
      \pre it != mem.begin() y ++it != mem.end()
      \post Si el proceso situado antes del proceso apuntado por it es un hueco (identificador = -1)
      este se elimina juntamente com el proceso apuntado por it y se substituye por un hueco del 
      tamaño de ambos. En caso contrario, el parametro implicito permanece igual. 
  */
  void mirar_izq(map<int,Proceso>::iterator& it);

}; 

#endif
