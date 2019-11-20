/**
 * @file AutomataFinitoDeterminista.h 
 * @version 2.0
 * @date 28/10/2019
 * @author Diego Cruz Rodríguez
 * @title Clase AutomataFinitoDeterminista
 * @brief Universidad de La Laguna
 * @brief Escuela Superior de Ingeniería y Tecnología 
 * @brief Grado en Ingeniería Informática
 * @brief Asignatura: Computabilidad y Algoritmia (CyA)
 * @brief Curso: 2º
 * @brief Prácticas 6 - 7 de CyA
 * @brief Correo: alu0101105802@ull.edu.es
 * @brief 
 * @brief Este Archivo guarda un DFA y defino los tipos de datos 
 * @brief Estado y Simbolo
 *
 */
#ifndef AUTOMATAFINITODETERMINISTA_H
#define AUTOMATAFINITODETERMINISTA_H
#include <string>
#include <set>
#include <vector>

typedef std::string Simbolo;
typedef std::string Estado;



class AutomataFinitoDeterminista{
  public:
    /**
     * @brief Constructor de la clase
     */ 
    AutomataFinitoDeterminista() = default;
    virtual ~AutomataFinitoDeterminista() = default;
    const std::set<Simbolo> &getAlfabelto() const;
    void setAlfabelto(const std::set<Simbolo> &alfabelto);
    const std::set<Estado> &getConjuntoEstados() const;
    void setConjuntoEstados(const std::set<Estado> &estados);
    const Estado &getEstadoInicial() const;
    void setEstadoInicial(const Estado &estadoInicial);
    const std::set<Estado> &getEstadosAceptacion() const;
    void setEstadosAceptacion(const std::set<Estado> &estadosAceptacion);
    const std::vector<std::vector<Estado>> &getFuncionTransicion() const;
    void setFuncionTransicion(const std::vector<std::vector<Estado>> &funcionTransicion);
    /**
     * @brief Apartir de los datos de la clase crea un archivo tipo DOT
     * @param nombreArchivo string con el nombre del archivo a crear 
     */
    void  crearArchivoDot(std::string nombreArchivo);
protected:
    bool pertenece(const std::string &estado, const std::set<std::string> &conjuntoEstados);
    bool esSubconjunto(const std::set<std::string> &estadosSubconjunto, const std::set<std::string> &estados);
    void inicializarTransiciones(std::vector<std::vector<std::string>> &transiciones, std::set<std::string> &alfabeto,
                                 std::set<std::string> &estados);
private:
    std::set<Simbolo> Alfabelto_;
    std::set<Estado> ConjuntoEstados_;
    Estado EstadoInicial_;
    std::set<Estado> EstadosAceptacion_;
    std::vector<std::vector<Simbolo>> FuncionTransicion_;


};

#endif //AUTOMATAFINITODETERMINISTA_H
