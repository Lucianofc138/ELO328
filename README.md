# ELO328 Tarea 1
## Participantes
En esta tarea participaron: Luciano Flores
                            Tomás Muñoz
                            Francisco Romero
                            Agustín Acevedo
                            Martín Miranda

## Descripcion

El objetivo del programa es realizar correción gamma en una imagen fija de la carpeta samples o de la webcam
en tiempo real. Además, esto se puede hacer calculando pixel a pixel o con una tabla precalculada. Por último
el programa es capaz de agregar un marco a la imagen o video de un color definido segun sus parametros RGB

## Enunciado

Escriba un programa que cumpla con la siguiente descripcion:
    ./GAMMA [-m1 | -m2] -v gamma [-f x y w h] [-c r g b]
    ./GAMMA [-m1 | -m2] -i imagen gamma [-f x y w h] [-c r g b]
    -v:    usar webcam.
    -i:    usar imagen.
    image: Ruta de imagen a procesar.
    gamma: Nivel de Gamma. Debe ser un valor real, mayor que 0.
    -f:    (Optional) Define  ́area a la que aplica gamma. Resto es borde.Se define rectángulo posicion (x,y) y tamaño w X h.
            Si no se define, se usa imagen completa.
    -c:    (Optional) Color (r,g,b) del borde. Si no se define,se usa negro.

## Instrucciones

Para compilar desde el terminal, utilizando simbolos para debugger, en el directorio raiz del proyecto
ejecutar:
```
    $ cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build && cmake --build build
```

Para compilar de manera normal, desde el directorio raiz ejecutar:
```
    $ cmake -S . -B build && cmake --build build
```

> Nota: Si alguno de los comandos anteriores resulta en un error, se debe actualizar
> la version de cmake a una version mas reciente.

Para correr en modo imagen:  
```
    $ ./bin/GAMMA [-m1|-m2] -i ./samples/sample0.jpg gamma
```

Para correr en modo webcam:
```
    $ ./bin/GAMMA [-m1|-m2] -v gamma
```

gamma es un valor numerico mayor a 0, ej: 0.5
ES IMPORTANTE EJECUTAR DESDE EL DIRECTORIO RAIZ POR LA DIRECCION RELATIVA DE LAS IMAGENES

Adicionalmente en cualquier modo se puede agregar un marco:
    dimensiones: -f x y w h 
    color:       -c r g b

Dos ejemplos serían:
```
   $ ./bin/GAMMA -m2 -i ./samples/sample0.jpg, 0.8 -f 200 100 880 687
   $ ./bin/GAMMA -m1 -v 1.2 -f 200 100 880 687 -c 100 200 50
```


Para correr el programa que mide los tiempos de ejecucion y compara resultados, escribir:
```
    $ ./bin/TEST_TIME
```

# Resultados

Los últimos resultados obtenidos con TEST_TIME fueron:

```
Tiempo tabla / tiempo pixel a pixel
0.0376707 / 0.0773588 [s]

0.0236043 / 0.0514698 [s]

0.0741616 / 0.160977 [s]

0.0265303 / 0.0554654 [s]

0.0292863 / 0.0633005 [s]

0.0975494 / 0.207634 [s]

0.00198157 / 0.0038832 [s]

0.00186976 / 0.00368859 [s]

0.0303563 / 0.0655164 [s]

0.0419704 / 0.0913595 [s]

Tiempo promedio tabla: 0.0364981
Tiempo promedio pixel a pixel: 0.0780653
```

Donde se puede ver que en general tarde el doble de tiempo en hacer el proceso pixel a pixel