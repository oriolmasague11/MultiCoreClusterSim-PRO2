/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef _PROCESO_
#define _PROCESO_

using namespace std; 

#ifndef NO_DIAGRAM  
#include <iostream> 
#endif

/** @class Proceso
    @brief Representa un proceso con sus caracteristicas

*/

class Proceso
{

private: 
  /** @brief Identificador del proceso */
  int id; 
  /** @brief Cantidad de memoria necesaria del proceso */
  int mem; 
  /** @brief Tiempo de ejecucion del porceso */
  int t_eje; 

public: 

  //Constructoras

  /** @brief Creadora por defecto
      \pre <em>cierto</em>
      \post El resultat es un proceso sin identificador y con memoria y tiempo de 
      ejecucion iguales a cero. 
  */
  Proceso();

  /** @brief Creadora con valores concretos
      \pre <em>cierto</em>
      \post El resultado es un proceso con identificador "a", memoria "b"
      y tiempo de ejecucion "c".
  */
  Proceso(int a, int b, int c);

  //Consultoras

  /** @brief Consultora del identificador
      \pre <em>cierto</em>
      \post El resultado es el identificador del parametre parametro implicito
  */
  int consultar_id() const;

  /** @brief Consultora de la memoria que ocupa el proceso
      \pre <em>cierto</em>
      \post El resultado es la memoria del parametro implicito
  */
  int consultar_mem() const;

  /** @brief Consultora del tiempo de ejecucion
      \pre <em>cierto</em>
      \post El resultado es el tiempo de ejecucion del parametro implicito
  */
  int consultar_t() const;

  //Modificadores

  /** @brief Modificadora del identificador 
      \pre x es un entero mayor o igual que zero
      \post El id del parametro implicito pasa a ser "x".
  */
  void modificar_id(int x); 

  /** @brief Modificadora de la memoria 
      \pre x es un entero mayor o igual que zero
      \post La memoria del parametro implicito pasa a ser "x".
  */
  void modificar_mem(int x); 

  /** @brief Modificadora del tiempo de ejecucion del proceso 
      \pre x es un entero mayor o igual que zero
      \post El tiempo de ejecucion del parametro implicito pasa a ser "x"
  */
  void modificar_t(int x); 

  //Lectura y escritura

  /** @brief Operacion de lectura
      \pre estan preparados al canal estandar de entrad un string y dos enteros no negativos
      \post El parametro implicito pasa a tener los atributos leidos por el canal estandar de entrada. 
  */
  void leer(); 

  /** @brief 
      \pre <em>cierto</em>
      \post Se han escrito los atributos del parametro implicito en el canal estandar de salida. 
  */
  void escribir() const; 

}; 

#endif