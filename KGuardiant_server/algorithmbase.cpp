#include "algorithmbase.h"


/*
 * Constructor vacio da clase AlgorithmBase.
 */
AlgorithmBase::AlgorithmBase() {

}
/*
 * Destructor da clase AlgorithmBase.
 */
AlgorithmBase::~AlgorithmBase() {

}
/*
 * Método Abstracto encargado de encuestrar o usuario para obter datos
 * adicionais para a execución do algoritmo.
 */
void AlgorithmBase::consoleInput() {

}
/*
 * Método encargao de realizar a execución propiamente dita do algoritmo.
 */
void AlgorithmBase::execute() {

}
/*
 * Método Abstracto encargado de xerar un log dos parámetros de saida do
 * algoritmo no caso de que produza algunha saida.
 */
void AlgorithmBase::logOutput() {

}
/*
 * Método Abstracto encargado de xerar un log dos parámetros de entrada do
 * algoritmo no caso de que teña.
 */
void AlgorithmBase::logParams() {

}
/*
 * Método abstracto encagado de definir unha plantilla abstracta para a
 * execución dun algoritmo concreto.
 */
void AlgorithmBase::run() {

    consoleInput();
    logParams();
    execute();
    logOutput();
}
