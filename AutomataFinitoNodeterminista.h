/**
 * @file AutomataFinitoNodeterminista.h
 * @version 1.0
 * @date 4/11/2019
 * @author Diego Cruz Rodríguez
 * @title Clase AutomataFinitoNodeterminista
 * @brief Universidad de La Laguna
 * @brief Escuela Superior de Ingeniería y Tecnología
 * @brief Grado en Ingeniería Informática
 * @brief Asignatura: Computabilidad y Algoritmia (CyA)
 * @brief Curso: 2º
 * @brief Prácticas 7 de CyA
 * @brief Correo: alu0101105802@ull.edu.es
 * @brief
 * @brief Este Archivo guarda un NFA
 *
 */

#ifndef AUTOMATAFINITONODETERMINISTA_H
#define AUTOMATAFINITONODETERMINISTA_H
#include "AutomataFinitoDeterminista.h"

class AutomataFinitoNodeterminista : public AutomataFinitoDeterminista{
  public:
    AutomataFinitoNodeterminista(const std::string& nombreArchivo);
    virtual ~AutomataFinitoNodeterminista() = default ;
    const std::vector<std::vector<std::pair<Simbolo, Estado>>> &getFuncionTransicion() const;
    void setFuncionTransicion(const std::vector<std::vector<std::pair<Simbolo, Estado>>> &funcionTransicion);
    void tranformar_dfa(AutomataFinitoDeterminista &dfa);

private:
    std::vector<std::vector<std::pair<Simbolo,Estado>>> FuncionTransicion_;
    std::string getlinea(std::ifstream &readfile);
    void extraerPalabra(std::string &linea, std::string &palabra);
    std::set<Estado> epsilonClausura(std::set<Estado> conjuntoEstados);
    std::set<Estado> transita(const std::basic_string<char> &estadoActual, const Simbolo& simbolo);
    std::set<std::set<Estado>> construcionSubconjuntos(const std::set<Estado>& conjuntoInicial);
    bool pertenece(const std::set<Estado>& conjunto, const std::set<std::set<Estado>>& granconjunto);
    void crearEstadosYTransiciones(std::set<Estado> estadoInicial, std::set<std::set<Estado>> conjuntoEstado,
                                   AutomataFinitoDeterminista &dfa);

    bool esdeaceptacion(const std::set<Estado>& conjuntoEstados);

    std::set<Estado> transita(const std::set<Estado> &estadoActual, const Simbolo &simbolo);
};

#endif //AUTOMATAFINITONODETERMINISTA_H

