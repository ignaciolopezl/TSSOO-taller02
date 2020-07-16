# TSSOO-taller1

##### ignacio lopez - ignacio.lopezl@alumnos.uv.cl

###### Universidad de Valparaíso

---



## 1. Introducción

En el presente documento se detallara el desarrollo del taller 02 de la asignatura taller se sistemas operativos de la universidad de valparaiso, esta consta de realizar el diseño y la implementacion orientando al trabajo con hilos, y evaluar su efeciencia temporal versus a su contraparte secuencial, esta actividad consta de dos modulos, el primer encargado de llenar un arreglo de numeros uint32_t dentro de un rango de numeros aleatorios, el segundo modulo es realiaz la suma de esos numeros dentro de arreglo, para eso fue necesario ciertos parametros de entradas como el largo del arreglo que al ejecutar el codigo se especifica como "-N", el numero de hilos "-t", la cota minima de random "-l", la cota maxima de random "-L" y finalmente la ayuda "-h", la forma de uso se detalla a continuacion.

```
./ sumArray -N numero -t  numero -l  numero -L  numero -h
```

## 2. Diseño
 
El diseño general en el cual se baso para general el codigo consta de ciertos paramemtros de entrada que se detallo en la introduccion mas un arreglo vacio, con estos parametros pasan a traves del modulo 1 dejando como salida al arreglo lleno de numeros randomicos que fueron llenados mediante hilos, este arreglo sirve de entrada para el segundo modulo, el cual hara la suma de los numeros randomicos de la misma manera que el primer modulo con hilos.

### 2.1 Modulo 1

 Como ya se detallo en el diseño general en este modulo se encarga de llenar un arreglo de numero randomicos mediante hilos, para eso e utilizo para eso se utilizo una funcion rellenar, esta se separa en dos casos, el primero el serial y el segundo el paralelo, en esta funcion se llena el arreglo, al pasarle paramentros de inicio y fin de llenado, estos varian dependiendo de cuandos hilo se crean, y posteriormente se crean los hilos con la funcion, y los parametros correctos para que el incio y fin sea correcto.


### 2.2 Modulo 2
 
En este modulo se encarga de la suma paralela de los numeros randomicos llenados anteriormente, para eso se utilizo un funcion llamada suma, que del mismo modo se divide en dos casos, paralelo y secuencial. Y del mismo modo que se hizo en el modulo anterior se se trabajo con parameros de inicio y fin, que se encarga de dividir el arreglo y sumar la cantidad de numeros que le corresponde a cada hilo, esta suma se asigna a un arreglo de sumas parciales, y posteriormente se recorre ese arreglo para obtener la suma total

## 3. Conclusiones 
Una vez habiendo terminado, la ejecucion del codigo y haber obtenido resultados, se puede observar que efectivamente mejora el rendimiento temporal al aplicar paralelismo mediante hilos, pero esto solo se puede aplicar hasta cierto punto por limitaciones de hardware, dado que un core permite una cierta cantidad de hilos, por lo cual limita la mejora, tambien se puede destacar que la paralelizacion depende de la complejidad de lo que se requiera hacer, eso se puede aborado de dos puntos de vista, la primera es que el codigo esta tan sencillo que no mejorar su rendimiento al hacer una paralelizacion mediante hilos, y la segunda es que le codigo sea tan complejo que es dificil encontrar una paralelizacion, pero a diferencia que la primera es factible y mejorar el tiempo, estos son los puntos mas importantes tratos en este taller.
