/**
 *@file NFA2DFA.cpp 
 *@version 1.0
 *@date 29/10/2019
 *@author Diego Cruz Rodríguez
 *@title Archivo Principal
 *@brief Universidad de La Laguna
 *@brief Escuela Superior de Ingeniería y Tecnología 
 *@brief Grado en Ingeniería Informática
 *@brief Asignatura: Computabilidad y Algoritmia (CyA)
 *@brief Curso: 2º
 *@brief Práctica 7 CyA - La construcción de subconjuntos
 *@brief Correo: alu0101105802@ull.edu.es
 *@brief 
 *@brief Este Archivo contiene la funcion principal del programa,
 *@brief en ella se realiza la gestiosn y comprobacion de los
 *@brief argumentos, ejecucion de la clase AutomatafinitoNodeterminista,
 *@brief pide la tranformacion de nfa a dfa y pide al dfa que se escriba 
 *@brief en archivo.
 *
 */

#include <iostream>
#include <string>
#include "AutomataFinitoNodeterminista.h"
#include "AutomataFinitoDeterminista.h"


int main(int argc, char *argv[]){
  std::string const AYUDA = "--help";
  std::string const ARCHIVO_DFA = ".dfa";
  std::string const ARCHIVO_NFA = ".nfa";
  switch (argc) {
    case 3 : {
      std::string nombreArchivoLectura = argv[1];
      std::string nombreArchivoEscritura = argv[2];
      std::string extencion_nfa = nombreArchivoLectura.substr(nombreArchivoLectura.length() - 4, 4);
      std::string extencion_dfa = nombreArchivoEscritura.substr(nombreArchivoEscritura.length() - 4, 4);
     
      if (extencion_nfa == ARCHIVO_NFA) {
        if (extencion_dfa == ARCHIVO_DFA) {
          AutomataFinitoNodeterminista nfa(nombreArchivoLectura);
          AutomataFinitoDeterminista dfa;
          nfa.tranformar_dfa(dfa);
          //dfa.imprimirArchivoDFA(nombreArchivoEscritura);
          break;
        }
      }
    }
    case 2 : {
      std::string comando = argv[1]; 
      if (comando == AYUDA) {
        std::cout<<"\nEste programa tranfora un NFA a un DFA usando el metodo\n"
                 <<"de construcion de conjuntos. Para un correcto funcionamiento\n"
                 <<"se debe introducir un fichero de entrada input.nfa y un\n"
                 <<"fichero de salida output.dfa\n\n"
                 <<"---------------------------------------------------------\n\n"
                 <<"Ejemplo de uso:\n"
                 <<"$ ./NFA2DFA input.nfa output.dfa\n\n";
        break;
      }
    }
    case 1 :
    default :
      std::cout<<"Modo de empleo: ./NFA2DFA input.nfa output.dfa\n"
               <<"Pruebe './NFA2DFA --help' para más información.\n";
  }
  return 0;
}

