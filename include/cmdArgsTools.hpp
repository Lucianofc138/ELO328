#ifndef COMMAND_LINE_ARGUMENTS_TOOLS_HPP_
#define COMMAND_LINE_ARGUMENTS_TOOLS_HPP_

#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <sstream>
/**
 * Obtiene la posicion del argumento @param arg, en el arreglo @param argv de 
 * tamanio @param argc.
 * 
 * @param arg       :   String que se busca en el arreglo
 * @param argv      :   Arreglo de entrada de ejecucion
 * @param argc      :   Tamanio del arreglo de entrada de ejecución
 */
int getArgPosition(std::string arg, char** argv, int argc);

/**
 * Verifica la existencia del archivo ingresado.
 *
 * @param path      :   Ruta del archivo ingresado
 */
bool isAValidPath(char* path);

double getGammaFromArgs(bool workingWithImg, int tokenPos, char** argv, int argc);

/**  
 * Obtiene el tamanio del frame al cual se le ejecutara la correccion gamma, a 
 * partir de los valores ingresados en la ejecucion, obtenidos en @param argv 
 * de tamanio @param argc y guarda los valores obtenidos en el arreglo @param
 * border.
 * 
 * 
 * @param border    :   Arreglo de enteros con los valores de posicion, ancho
 *                      y alto (x, y, w, h respectivamente)
 * @param argv      :   Arreglo de entrada de ejecucion
 * @param argc      :   Tamanio de arreglo de entrada
 */
int setBorderFromArgs(int border[], int imageWidth, int imageHeigth, char** argv, int argc);

/**  
 * Obtiene los colores correspondientes al borde que se 
 * 
 * @param frameColorRGB :   Arreglo de colores del borde
 * @param argv          :   Arreglo de entrada de  ejecucion
 * @param argc          :   Tamanio de arreglo de entrada
 */
int setBorderColorFromArgs(int frameColorBGR[], char** argv, int argc);

/**  
 * Obtiene los colores correspondientes al borde que se 
 * 
 * @param argv          :   Arreglo de entrada de  ejecucion
 * @param argc          :   Tamanio de arreglo de entrada
 */
int getModeFromArgs(char** argv, int argc);

#endif