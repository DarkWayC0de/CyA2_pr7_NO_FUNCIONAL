/**
 *@file AutomataFinitoDeterminista.cpp 
 *@version 2.0
 *@date 28/10/2019
 *@author Diego Cruz Rodríguez
 *@title Clase AutomataFinitoDeterminista
 *@brief Universidad de La Laguna
 *@brief Escuela Superior de Ingeniería y Tecnología 
 *@brief Grado en Ingeniería Informática
 *@brief Asignatura: Computabilidad y Algoritmia (CyA)
 *@brief Curso: 2º
 *@brief Prácticas 6 - 7 de CyA 
 *@brief Correo: alu0101105802@ull.edu.es
 *@brief 
 *@brief Este Archivo guarda un DFA
 *
 */
#include <fstream>
#include <iostream>
#include "AutomataFinitoDeterminista.h"


const std::set<std::string> &AutomataFinitoDeterminista::getAlfabelto() const {
  return Alfabelto_;
}
void AutomataFinitoDeterminista::setAlfabelto(const std::set<std::string> &alfabelto) {
  Alfabelto_ = alfabelto;
}
const std::set<std::string> &AutomataFinitoDeterminista::getConjuntoEstados() const {
  return ConjuntoEstados_;
}
void AutomataFinitoDeterminista::setConjuntoEstados(const std::set<std::string> &estados) {
  ConjuntoEstados_ = estados;
}
const std::string &AutomataFinitoDeterminista::getEstadoInicial() const {
  return EstadoInicial_;
}
void AutomataFinitoDeterminista::setEstadoInicial(const std::string &estadoInicial) {
  EstadoInicial_ = estadoInicial;
}
const std::set<std::string> &AutomataFinitoDeterminista::getEstadosAceptacion() const {
  return EstadosAceptacion_;
}
void AutomataFinitoDeterminista::setEstadosAceptacion(const std::set<std::string> &estadosAceptacion) {
  EstadosAceptacion_ = estadosAceptacion;
}
const std::vector<std::vector<std::string>> &AutomataFinitoDeterminista::getFuncionTransicion() const {
  return FuncionTransicion_;
}
void AutomataFinitoDeterminista::setFuncionTransicion(
                    const std::vector<std::vector<std::string>> &funcionTransicion) {
  FuncionTransicion_ = funcionTransicion;
}
void  AutomataFinitoDeterminista::crearArchivoDot(std::string nombreArchivo){
  std::string const CABECERADOT = "/* Universidad de La Laguna\n"
                                  "   Grado en Ingenieria Informatica\n"
                                  "   Computabilidad y Algoritmia\n\n"
                                  "   Fichero DOT de representacion de un DFA\n"
                                  "   Fichero Generado por Programa de la practica numero 6\n"
                                  "   Creado por Diego Cruz Rodríguez\n"
                                  "*/\n"
                                  "digraph DFA {\n"
                                  "  rankdir=LR;\n"
                                  "  size = \"10, 4\";\n"
                                  "  d2tstyleonly = true;\n"
                                  "  node [share = none]; \"\";"
                                  "  node [share = doublecircle];";

  std::ofstream writefile(nombreArchivo);
  if (writefile.is_open()){
    writefile<<CABECERADOT; //Se Introduce la cabecera
    for (auto i = this -> EstadosAceptacion_.begin();
          i != EstadosAceptacion_.end(); i++){
        writefile<<" \""<< *i <<"\"";          //Se añaden los estados finales 
    }
    writefile<<";\n"
               "  node [share = circle];\n"
               "  \"\" -> \"" << this -> EstadoInicial_ << "\";\n"; //Se señala el arranque 
    for (int j = 1; j < FuncionTransicion_.size() ; ++j) {
        for (int i = 1; i < FuncionTransicion_[i].size(); ++i) {
            if( !FuncionTransicion_[j][i].empty()){     //En caso de que la tabla de transicion no sea
                writefile << "  \"" << FuncionTransicion_[j][0] <<"\" -> \""     //vacia, se añade  la
                          << FuncionTransicion_[j][i] << "\" [ label=\""         //Transicion
                          << FuncionTransicion_[0][i] << "\" ];\n";
            }
        }
    }
    writefile<<"}\n";
    writefile.close();
  } else {
    std::cout<<"\nERROR, apertura de archivo de escritura de formato DOT\n";
    exit(6);
  }
}

bool AutomataFinitoDeterminista::pertenece(const std::string& estado, const std::set<std::string>& conjuntoEstados){
    auto i = conjuntoEstados.begin();
    for ( ; i != conjuntoEstados.end(); i++){
        if( *i == estado){
            break;
        }
    }
    return (i != conjuntoEstados.end());
}
bool AutomataFinitoDeterminista::esSubconjunto(const std::set<std::string>& estadosSubconjunto,
                              const std::set<std::string>& estados){
    bool esSubconjunto = true;
    auto i = estadosSubconjunto.begin();
    for (; i != estadosSubconjunto.end(); i++) {
        esSubconjunto &= pertenece(*i, estados);
    }
    return esSubconjunto;
}
void AutomataFinitoDeterminista::inicializarTransiciones(std::vector<std::vector<std::string>>& transiciones,
                                        std::set<std::string> &alfabeto,
                                        std::set<std::string>& estados){
    transiciones.resize(estados.size()+1);
    for (int i = 0; i <=estados.size() ; ++i) {
        transiciones[i].resize(alfabeto.size()+1);
    }
    int contador = 1;
    for (const auto & simbolo : alfabeto) { //añadimos indice simbolos
        transiciones[0] [contador++] = simbolo;
    }
    contador = 1;
    for (const auto & estado : estados) { //añadimos indice estados
        transiciones[contador++] [0] = estado;
    }
}

