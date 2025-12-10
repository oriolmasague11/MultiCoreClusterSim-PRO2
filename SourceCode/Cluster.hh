/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_
#define _CLUSTER_

#include "Procesador.hh"

#ifndef NO_DIAGRAM  
#include "BinTree.hh"
#endif

/** @class Cluster
    @brief Representa un Cluster con procesadores.

*/

struct Res {
    bool posible; 
    int tam_hueco; 
    int m_libre; 
    int profundidad; 
    string id; 
};

class Cluster 
{
    // Descripción: estructura de procesadores con sus respectivos procesos

private: 

  /* Un cluster esta compuesto por distintos procesadores, que a su vez pueden
     tener procesadores auxiliares, por tanto, tendrá forma arborescente. 
     El cluster posee un arbol con los identificadores de los procesadores y 
     un diccionario con el id del procesador (clave) i el procesador en 
     cuestion (informacion). */

  /** @brief Estructura de procesadores del cluster */
  BinTree<string> arbol_procesadores; // 
  /** @brief Diccionario con los identificadores de los procesadores y sus 
  respectivos procesadores */
  map<string,Procesador> procesadores; 

public: 

  //Constructoras

  /** @brief Creadora por defecto.
      \pre <em>cierto</em>
      \post El resultado es un cluster sin procesadores
  */
  Cluster(); 

  //Modificadoras
  
  /** @brief Avanza el tiempo
      \pre t es un entero positivo
      \post el tiempo de los procesos de todos los procesadores del parametro implicito
      ha progresado t unidades y han sido finalizados aquellos procesos cuyo tiempo 
      de ejecucion ha terminado. 
  */
  void avanzar_t(int t);

  /** @brief Operacion para añadir un proceso a un procesador 
      \pre <em>cierto</em>
      \post Error indica si no existe un procesador con identificador id en el cluster
      o este ya contiene un proceso con el mismo identificador que p o 
      el procesador esta lleno. En caso que no haya error se añade el proceso p al procesador con identificador
      id del parametro implicito. 
    */
  void anadir_proceso_procesador(string id, Proceso p, char& error);

  /** @brief Operacion para eliminar un proceso de un procesador 
      \pre <em>cierto</em>
      \post Error indica si no existe un procesador con identificador id en el cluster
      o el proceso p no esta en el procesador. En caso que no haya error, se elimina el proceso de la memoria del
      procesador con identificador id del parametro implicito. 
  */
  void eliminar_proceso_procesador(string id, int idp, char& error);

  /** @brief Modificadora de la estructura del cluster
      \pre <em>cierto</em>
      \post Error indica si no existe un procesador con identificador id, o este 
      tiene procesos en ejecución, o tiene procesadores auxiliares.
      En caso que no haya error se añade el cluster clu 
      al parametro implicito, situandolo en la posicion del procesador 
      con identificador id.
  */
  void modificar_cluster(string id, const Cluster& clu, char& error);

  /** @brief Operacion para compactar la memoria de un procesador del Cluster. 
      \pre <em>cierto</em>
      \post Error indica si no existe un procesador con identificador id en el parametro implicito. En caso que no haya error
      se desplaza todos los procesos al principio de la memoria del procesador, sin dejar huecos, 
      ni solaparse y respetando el orden inicial. 
  */
  void compactar_memoria_procesador(string id, char& error);
  
  /** @brief Operacion para compactar la memoria de los procesadores del Cluster
      \pre <em>cierto</em>
      \post En todos los procesadores del parametro implicito se desplazan los procesos al 
      principio de la memoria, sin dejar huecos, sin solaparse y respetando el 
      orden inicial. 
  */
  void compactar_memoria_cluster();


  //Consultoras

  /** @brief Consultora del mejor procesador para colocar un proceso p
      \pre <em>cierto</em>
      \post El resultado es el procesador mas adiente del parametro implicito para colocar el 
      proceso p, en funcion de el procesador con el hueco mas ajustado, 
      el que mayor memoria libre poseea, el mas cercano a la raiz o el 
      que este situado mas a la izquierda en la estructura del cluster. 
      Las condiciones son evaluadas en ese orden. Aceptado indica si el proceso
      se puede colocar en algun procesador del parametro implicito o no. 
  */
  string elegir_mejor_procesador(Proceso p, bool& aceptado); 

  //Lectura y escritura

  /** @brief Operació de lectura
      \pre estan preparados en el canal estandar de entrada un entero no negativo, que 
      representa el numero de procesadores a leer, y los datos de tal numero de procesadores.
      \post El parametro implicito contien los procesadores leidos del canal estandar de entrada.
  */
  void configurar(); 

  /** @brief Operación de escritura
      \pre <em>cierto</em>
      \post Se han escrito por el canal estandar de salida los procesadores del parametro
       implicito en orden creciente de identificador.
  */
  void escriure() const;

  /** @brief Operación de escritura de la estructura
      \pre <em>cierto</em>
      \post Se ha escrito la estructura de los procesadores del parametro implicito por el canal 
      estandard de salida. 
  */
  void escriure_estructura() const; 

  /** @brief Operacion de escritura de un procesador del cluster
      \pre <em>cierto</em>
      \post Error indica si no existe un procesador con identificador id en el parametro implicito se devuelve
      un error. En caso que no haya error se escribe por el canal estandar de salida los datos 
      de los procesos (identificador, memoria y tiempo de ejecución) del procesador con identificador id.  
  */
  void escribir_procesador(string id, char& error) const;

private:

  /** @brief Busqueda recursiva para modificar el arbol de procesadores
      \pre <em>cierto</em>
      \post El resultado es cierto en caso que se haya encontrado el procesador en question
      y es falso en caso contrario. Error indica si el procesador tiene
      procesos activos o procesadores auxiliares. En caso que no haya error se añade al nodo del 
      procesador el nuevo arbol del cluster. 
  */   
  bool modificar_rec(BinTree<string> &a, string id, const BinTree<string>& suba, char& error); //privada

  /** @brief Recorrido recursivo para encontrar el mejor procesador
      \pre <em>cierto</em>
      \post El resultado es un struc Res con la informacion del mejor procesador
      para colocar el proceso p, de acuerdo con los criterios mencionados previamente
      (si cabe el proceso, el hueco mas ajustado, el de mayor memoria disponible, 
      el de menor profundidad, o el que este mas a la izquierda).
  */     
  Res mejor_procesador(const BinTree<string>& a, Proceso p, int prof); //privada

  /** @brief Operacion de comparacion de dos procesadores
      \pre <em>cierto</em>
      \post El resultado sera cierto en caso que la respuesta r1 sea mejor que 
      la respuesta r2 (en base a los criterios mencionados previamente) y falso
      en caso contrario. 
  */   
  bool mejor(const Res& r1, const Res& r2); //privada

  /** @brief Creadora de respuestas para procesadores
      \pre <em>cierto</em>
      \post El resultado es un struct Res con los datos del procesador
      con identificador id_pro con respecto al proceso p. 
  */   
  Res crear_respuesta(string id_pro, const Proceso& p, int prof); //privada

  /** @brief Operación de lectura de un árbol de procesadores
      \pre  cierto
      \post a contiene el árbol con los identificadores de los procesadores leído de la entrada
  */   
 void leer_arbol_procesadores(BinTree<string>& a);

  /** @brief Operación de escritura de la estructura de un árbol de procesadores
      \pre  cierto
      \post Se ha escrito a por el canal de salida estándard la estructura del árbol
  */   
  static void escribir_estructura_arbol_procesadores(const BinTree<string>& a);

};

#endif
