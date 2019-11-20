#include <fstream>
#include <iostream>
#include <stack>
#include "AutomataFinitoNodeterminista.h"


const std::vector<std::vector<std::pair<Simbolo, Estado>>> &
AutomataFinitoNodeterminista::getFuncionTransicion() const {
    return FuncionTransicion_;
}

void AutomataFinitoNodeterminista::setFuncionTransicion(
        const std::vector<std::vector<std::pair<Simbolo, Estado>>> &funcionTransicion) {
    FuncionTransicion_ = funcionTransicion;
}

AutomataFinitoNodeterminista::AutomataFinitoNodeterminista(const std::string& nombreArchivo) {
 std::ifstream readfile(nombreArchivo);
   if (readfile.is_open()){
     int  tamanolfabeto  = std::stoi(this -> getlinea(readfile));
     if (this->getlinea(readfile) != "~"){
         std::cout<<"\nERROR, en definicion de nfa";
         exit(2);
     }
     std::set<Simbolo> alfabeto;
     for (int i = 0; i <tamanolfabeto ; ++i) {
            alfabeto.insert(this-> getlinea(readfile));
     }
     this -> setAlfabelto(alfabeto);
     std::set<Estado> conjuntoEstados;
     int  numeroEstados  = std::stoi(this -> getlinea(readfile));
     for (int j = 0; j < numeroEstados; ++j) {
       conjuntoEstados.insert(this -> getlinea(readfile));
     }
     this -> setConjuntoEstados(conjuntoEstados);
     Estado estadoInicial = this -> getlinea(readfile);
     if ( !this -> AutomataFinitoDeterminista::pertenece(estadoInicial, conjuntoEstados)){
       std::cout << "\nEl estado de aceptacion no pertenece a el conjunto de estados\n";
       exit(3);
     }
     this -> setEstadoInicial(estadoInicial);
     std::set<Estado> estadoFinal;
     int  numeroFinales  = std::stoi(this -> getlinea(readfile));
     for (int k = 0; k < numeroFinales; ++k) {
       estadoFinal.insert(this -> getlinea(readfile));
     }
     if ( !this -> esSubconjunto(estadoFinal, conjuntoEstados)){
       std::cout << "\nEl conjunto de estados finales no pertenesen a el conjunto de estados\n";
       exit(4);
     }
     this -> setEstadosAceptacion(estadoFinal);
     std::vector<std::vector<std::pair<Simbolo,Estado>>> transiciones;
     int  numerotransiciones  = std::stoi(this -> getlinea(readfile));
     for (int l = 0; l <numerotransiciones ; ++l) {
       std::string linea = getlinea(readfile);
       std::string palabra;
       this -> extraerPalabra( linea, palabra);
       if ( !this -> AutomataFinitoDeterminista::pertenece(palabra, conjuntoEstados)){
         std::cout << "\nTransiciones mal definidas\n";
         exit(5);
       }
       transiciones.resize(this -> getConjuntoEstados() . size());
       std::set<Simbolo>::iterator k;
       int i;
       for (i = 0, k = this->getConjuntoEstados().begin();k != getConjuntoEstados().end(); ++i,++k) {
         if (palabra == *k){
           this -> extraerPalabra( linea, palabra);
           if ( !this ->AutomataFinitoDeterminista:: pertenece(palabra, alfabeto)) {
             std::cout << "\nTransiciones mal definidas\n";
             exit(6);
           }
           if ( !this -> AutomataFinitoDeterminista::pertenece(linea, conjuntoEstados)) {
             std::cout << "\nTransiciones mal definidas\n";
             exit(7);
           }
           std::pair<Simbolo,Estado> pareja(palabra,linea);
           transiciones[i].push_back(pareja);
           }
         }
       }
     this -> AutomataFinitoNodeterminista::setFuncionTransicion(transiciones);
     readfile.close();
   } else {
     std::cout<<"\nERROR, en la apertura de archivo .nfa";
     exit(1);
   }
}

std::string AutomataFinitoNodeterminista::getlinea(std::ifstream &readfile){
    std::string const comentario = "//";
    std::string linea;
    do {
        std::getline(readfile, linea);
    }while (linea.substr(0,2) == comentario && !readfile.eof());
    return linea;
}
void AutomataFinitoNodeterminista::extraerPalabra(std::string &linea, std::string &palabra){
  char const ESPACIO =' ';
  int i;
  for (  i= 0; i < linea.length() ; ++i) {
    if (linea[i] == ESPACIO){
      break;
    }
  }
  palabra = linea.substr(0,i);
  linea = linea.substr(i+1,linea.length());
}

void AutomataFinitoNodeterminista::tranformar_dfa(AutomataFinitoDeterminista &dfa) {
  std::set<Estado> conjuntoInicial;
  conjuntoInicial.insert(this -> getEstadoInicial());
  conjuntoInicial = epsilonClausura(conjuntoInicial);
  std::set<std::set<Estado>> Estadosparadfa;
  Estadosparadfa = construcionSubconjuntos(conjuntoInicial);
  dfa.setAlfabelto(this ->getAlfabelto());
  crearEstadosYTransiciones(conjuntoInicial,Estadosparadfa,dfa);

}

std::set<Estado> AutomataFinitoNodeterminista::epsilonClausura(std::set<Estado> conjuntoEstados) {
  Simbolo const  EPSILON = "~";
  std::set<Estado> analizados;
  while(!conjuntoEstados.empty()) {
    std::set<Estado> destino = transita(*conjuntoEstados.begin(), EPSILON);
    analizados.insert(*conjuntoEstados.begin());
    conjuntoEstados.erase(conjuntoEstados.begin());
    if (!destino.empty()) {
      for (auto i = destino.begin(); i != destino.end() ; ++i) {
        if(!this -> AutomataFinitoDeterminista::pertenece(*i, conjuntoEstados)){
          if (!this->AutomataFinitoDeterminista::pertenece(*i, analizados)){
            conjuntoEstados.insert(*i);
          }
        }
      }
    }
  }
  return analizados;
}

std::set<Estado> AutomataFinitoNodeterminista::transita(const Estado &estadoActual, const Simbolo& simbolo) {
  std::set<Estado> estadosTransitados;
  int i;
  auto k = this -> getAlfabelto().begin();
  for (i = 0,k = this -> getAlfabelto().begin(); k != this ->getAlfabelto().end() ; ++i,++k) {
    if (*k == estadoActual){
      for (auto j = 0; j < this -> AutomataFinitoNodeterminista::FuncionTransicion_[i].size(); j++){
        if ( this -> AutomataFinitoNodeterminista::FuncionTransicion_[i][j].first == simbolo) {
           estadosTransitados.insert(this -> AutomataFinitoNodeterminista::FuncionTransicion_[i][j].second);
        }
      }
    }
  }
  return estadosTransitados;
}

std::set<std::set<Estado>> AutomataFinitoNodeterminista::construcionSubconjuntos(const std::set<Estado>& conjuntoInicial) {
  std::set<std::set<Estado>> faltaAnalizar;
  std::set<std::set<Estado>> analizados;
  faltaAnalizar.insert(conjuntoInicial);
  while (!faltaAnalizar.empty()){
    auto analizar =*faltaAnalizar.begin();
    for(auto i = this -> getAlfabelto().begin(); i != getAlfabelto().end(); i++){
      std::set<Estado> transicionconsimbolo;
      for (auto j = analizar.begin(); j != analizar.end() ; ++j) {
        auto transiciondeunestado = transita(*j, *i);
        transicionconsimbolo.insert(transiciondeunestado.begin(), transiciondeunestado.end());
      }
      transicionconsimbolo = epsilonClausura(transicionconsimbolo);
      if (!(pertenece(transicionconsimbolo, faltaAnalizar) ||
        this->pertenece(transicionconsimbolo, analizados))) {
        analizados.insert(transicionconsimbolo);
      }
    }
    analizados.insert(analizar);
    faltaAnalizar.erase(faltaAnalizar.begin());
  }
  return analizados ;
}

bool AutomataFinitoNodeterminista::pertenece(const std::set<Estado>& conjunto, const std::set<std::set<Estado>>& granconjunto){
  for (auto i = granconjunto.begin(); i != granconjunto.end() ; ++i) {
    if(*i == conjunto){
      return true;
    }
  }
  return false;
}

void AutomataFinitoNodeterminista::crearEstadosYTransiciones(std::set<Estado> estadoInicial,
                                                             std::set<std::set<Estado>> conjuntoEstado,
                                                             AutomataFinitoDeterminista &dfa) {
  Estado const ESTADOINICIAL = "q0";
  char const PrimerEstado ='A';
  dfa.setEstadoInicial(ESTADOINICIAL);
  std::set<Estado> conjuntoEstadodfa;
  conjuntoEstado.erase(estadoInicial);
  for (int i = 0; i <conjuntoEstado.size() ; ++i) {
      Estado estado = "A" + i;
    conjuntoEstadodfa.insert(estado);
  }
  dfa.setConjuntoEstados(conjuntoEstadodfa);
  std::set<Estado> final;
  std::vector<std::vector<Estado>> transiciones;
  std::set<Simbolo> alfabeto = dfa.getAlfabelto();
  this ->AutomataFinitoDeterminista::inicializarTransiciones(transiciones,alfabeto,conjuntoEstadodfa);
    auto j = conjuntoEstado.begin();
    auto i = conjuntoEstadodfa.begin();
    for (j = conjuntoEstado.begin(), i = conjuntoEstadodfa.begin(); j != conjuntoEstado.end() ; ++j, ++i) {
        for (auto k = alfabeto.begin(); k !=alfabeto.end() ; ++k) {
            std::set<Estado> simbolo = transita(*j, *k);
            auto l = conjuntoEstado.begin();
            auto m = conjuntoEstadodfa.begin();
            for (l = conjuntoEstado.begin(), m = conjuntoEstadodfa.begin(); j != conjuntoEstado.end() ; ++j, ++i) {
                if((*l)==simbolo){
                    for (int n = 0; n <transiciones.size() ; ++n) {
                        for (int i1 = 0; i1 < transiciones[n].size() ; ++i1) {
                            //TODO
                        }
                    }
                }
            }
        }
        if (esdeaceptacion(*j)){
            final.insert(*i);
        }
    }
  if(esdeaceptacion(estadoInicial)){
      final.insert(ESTADOINICIAL);
  }
  dfa.setFuncionTransicion(transiciones);

}
std::set<Estado> AutomataFinitoNodeterminista::transita(const std::set<Estado>& conjuntoEstados, const Simbolo& simbolo) {
  std::set<Estado> estadosTransitados;
  std::set<Estado> estadosIniciales = epsilonClausura(conjuntoEstados);
  for (auto j = estadosIniciales.begin(); j != estadosIniciales.end() ; ++j) {
    std::set<Estado> parcial = transita((*j),simbolo);
    estadosTransitados.insert(parcial.begin(),parcial.end());
  }
  epsilonClausura(estadosTransitados);
  return estadosTransitados;
}

bool AutomataFinitoNodeterminista::esdeaceptacion(const std::set<Estado>& conjuntoEstados) {
  for (auto i = conjuntoEstados.begin(); i != conjuntoEstados.end() ; ++i) {
    for (auto j = this ->getEstadosAceptacion().begin(); j != getEstadosAceptacion().end() ; ++j) {
      if (*i == *j ){
        return true;
      }
    }
  }
  return false;
}
