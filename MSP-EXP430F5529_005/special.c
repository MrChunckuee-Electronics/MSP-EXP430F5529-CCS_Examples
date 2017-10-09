/*******************************************************************************
 *
 *                  Libreria para funciones especiales
 *
 *******************************************************************************
 * FileName:        special.c
 * Processor:       ---------
 * Complier:        CCS 7.2.0
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Libreria para funciones especiales, o funciones que apliquen
 *                  para varios proyectos
 *******************************************************************************
 * Historial del firmware
 * Rev.     Date        Comment
 *  v1.00   08/10/2017  - Creación de la libreria
 *                      - Se implemento la función ltoa
 *                      - Se implemento la función ftoa
 ******************************************************************************/

/*******************************************************************************
 * Function:        unsigned char SPECIAL_ltoa(long long numero, char* conv)
 * Description:     Esta funcion convierte de long long a cadena.
 * Precondition:    None
 * Parameters:      long long numero = dato a convertir
 *                  char* conv = array donde se guardara la conversión
 * Return Values:   Regresa el numero de digitos convertidos
 * Remarks:         Codigo original de InDevice:
 *                  https://www.youtube.com/channel/UCnyRm08-AenzPuIk3vsqftA
 * *****************************************************************************/
unsigned char SPECIAL_ltoa(long long numero, char* conv){
    char convTemp[21]; //longitud maxima de long 12 digitos con signo
    register char *punteroActual;
    register int num=0;
    register char i=0;
    register long long  numeroReg = numero;//paso el numero a un registro para aumentar rendimiento

    punteroActual = &convTemp[21 - 1]; //empezamos llenando desde la ultima posicion
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion
    if( numeroReg < 0){
        numeroReg*=-1;
    }
    do {
        punteroActual--;//se decrementa la posicion donse guardara el valor
        num=numeroReg % 10; //obtiene el digito de mayor peso
        //num1=abs(num);//un if es mas rapido que una multiplicacion por -1 si es negativo el valor
        *punteroActual = num  + '0'; //convierte el valor en caracter
    }  while((numeroReg /= 10)); //mientras exista un digito sigue el ciclo

    if ( numero < 0)
    {
        punteroActual--;
        *punteroActual = '-';//si el numero es negativo guarda el signo negativo
    }

    numeroReg=convTemp+21-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo burbuja optimizado
    {
        //toma como base para copiar el ultimo digito utilizado
        //ejemplo
       // convTemp="xxxxxxx-156\0"
       // punteroActual = "-156\0"
        //conv="-156\0"
        ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;
}

/*******************************************************************************
 * Function:        unsigned char SPECIAL_ftoa(double numero, int decimales, char* conv)
 * Description:     Esta funcion convierte de double a cadena.
 * Precondition:    None
 * Parameters:      double numero = dato a convertir
 *                  int decimales = numero de decimales que deseamos en el resultado
 *                  char* conv = array donde se guardara la conversión
 * Return Values:   Regresa la cantidad de digitos convertidos.
 * Remarks:         Codigo original de InDevice:
 *                  https://www.youtube.com/channel/UCnyRm08-AenzPuIk3vsqftA
 * *****************************************************************************/
unsigned char SPECIAL_ftoa(double numero, int decimales, char* conv){
    const long long dec[16]= {0,10,100,1000,10000,100000,1000000,10000000,100000000,
                              1000000000,10000000000,100000000000,1000000000000,
                              10000000000000,100000000000000,1000000000000000
    };
    register long long deci=0; //contiene los decimales en version entero
    register double decimal=0;//contiene el valor de decimales en version double
    register unsigned char valores=0;//cuantos digitos se imprimen

    decimal=numero-(long long)numero; //obtiene la parte decimal
    decimal*=dec[decimales];//hace la multiplicacion depende de cuantos decimales necesitemos
    deci=(long long)decimal;//castea la parte decimal a un long long (64 bits)
    if(deci<0)//si el numero es negativo elimina el signo
      deci*=-1;

    valores= SPECIAL_ltoa((long long)numero, conv); //convierte la parte entera del numero
    conv[valores]='.';//agrega un '.' en la posicion del fin de cadena
    valores++;//aumenta a la siguiente posicion
    valores+=SPECIAL_ltoa(deci, &conv[valores]);//convierte la parte decimal despues del punto
    return valores;//regresa la cantidad de digitos convertidos
}


