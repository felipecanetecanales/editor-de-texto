#include <stdio.h>
#include <stdio.h>
#include "display.h"
#include "keyboard.h"
/***************************************************
* Nombre del modulo: keyboard.c
*
* Modulo creado para la asignatura Elo312
* Laboratorio de Estructura de Computadores
* del departamento de Electrónica de la Universidad
* Técnica Federico Santa María. El uso o copia
* está permitido y se agracede mantener el nombre 
* de los creadores.
*
* Escrito inicialmente el 01/01/2004 Por Michael Kusch & Wolfgang Freund
* Modificado el 24/09/2014           Por Mauricio Solís & Andrés Llico.
*
* Descripción del módulo:
* Modulo driver teclado matricial
* Contiene las funciones que permiten manejar el
* teclado matricial.
***************************************************/

/*  Include section
*
***************************************************/
#include "keyboard.h"
int p_anterior;
int modo = 1;
/*  Defines section
*
***************************************************/
typedef unsigned char uchar;

/*  Local Function Prototype Section
*
***************************************************/
void keyboard_button_action(char);


/*  Global Variables Section
*
***************************************************/
uchar BUTMAT_CLK = 0;           // cuántas interrupciones se lleva presionado el botón
uchar BUTMAT_PREV = 0xFF;       // tecla de la lectura anterior, FF => ninguna.


////////////////////////////////////////
//       RUTINAS IMPLEMENTADAS        //
//                                    //

/**************************************************
* Nombre    		: void keyboard_init(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Inicializa los puertos del 
* driver del teclado.
**************************************************/
void keyboard_init(void)
{
    PTOUT = 0x00;
    PTDIR = 0x00;
}

/**************************************************
* Nombre    		: void keyboard_tec_matrix(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Lee la matriz de botones y 
* llama a la función keyboard_button_action() cuando
* detecta que se ha presionado una tecla (o se ha mantenido
* presionada una tecla).
* Esta función debe ser llamada cada cierta cantidad de tiempo.
**************************************************/
void keyboard_tec_matrix(void)
{
    uchar BUTMAT = 0xFF;        // tecla de 0 a 15
    uchar k, i, temp;

    temp = 0x00;
    for(PTDIR = 0x10; PTDIR > 0; PTDIR <<= 1) {
        asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP");
        asm("NOP");
        k = (((~PTIN) & 0x0F) | PTDIR);
        if ( (k & 0x0F) )	           // si hay algún bit de columna en 0, entonces if es verdadero
            temp = k;	               // y se guarda el valor de la columna y filas activas
    }

    if (temp) {	                       // hubo tecla presionada?
        switch	(temp & 0xF0) {
        case BIT4:
            BUTMAT = 0;	 // fila 1
            break;
        case BIT5:
            BUTMAT = 4;	 // fila 2
            break;
        case BIT6:
            BUTMAT = 8;	 // fila 3
            break;
        case BIT7:
            BUTMAT = 12; // fila 4
            break;
        }

        switch	(temp & 0x0F) {
        case BIT0:
            asm("NOP");
            BUTMAT += 0; // col 1
            break;
        case BIT1:
            BUTMAT += 1; // col 2
            break;
        case BIT2:
            BUTMAT += 2; // col 3
            break;
        case BIT3:
            BUTMAT += 3; // col 4
            break;
        }

        if (BUTMAT != BUTMAT_PREV) {              // botón presionado es distinto al anterior?
            BUTMAT_PREV = BUTMAT;
            BUTMAT_CLK = 0;
            keyboard_button_action(BUTMAT);
        }
        else {
            if (++BUTMAT_CLK == 100) {            // presionada por más de 100*10[ms] (1 [s])?
                keyboard_button_action(BUTMAT);   // actuar como si se volvió a presionar el botón
                BUTMAT_CLK -= 33;                 // por cada 0.5 [s] que siga presionado el botón
            }
        }
    }
    else
        BUTMAT_PREV = 0xFF;                       // ningún botón presionado
}
//                                    //
////////////////////////////////////////


////////////////////////////////////////
//     RUTINAS NO IMPLEMENTADAS       //
//                                    //

/**************************************************
* Nombre    		: void keyboard_button_action(char arg1)
* returns			: void
* arg1				: Tecla presionada
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Realiza una accion segun la
tecla que ha sido presionada.
**************************************************/
void keyboard_button_action(char tecla)
{
  //////EDITOR 1 ///////
switch (tecla){
  case 3:
    if(p_anterior != tecla){
      modo = 1;
      break;
    }
  case 7:
    if(p_anterior != tecla){
      modo = 2;
      break;
    }
  case 11:
    if(p_anterior != tecla){
      modo = 3;
      break;
    }
  case 15:
    if(p_anterior != tecla){
      modo = 4;
      break;
    }
  default:
    break;
  }
  if (modo == 1){
    switch(tecla){
    case 0:
      printf("A");
      break;
    case 1:
      printf("B");
      break;
    case 2:
      printf("C");
      break;     
    case 4:
      printf("D");
      break;  
    case 5:
      printf("E");
      break;
    case 6:
      printf("F");
      break;
    case 8:
      printf("G");
      break;
    case 9         :
      printf("H");
      break;    
    case 10:
      printf("I");
      break;
    case 12:
      printf("\b");
      break;
    case 14:
      printf("\n");
      break;
    default:
      break;
    }
  }
  else if (modo == 2){
    switch(tecla){
    case 0:
      printf("J");
      break;
    case 1:
      printf("K");
      break;
    case 2:
      printf("L");
      break;     
    case 4:
      printf("M");
      break;  
    case 5:
      printf("N");
      break;
    case 6:
      printf("O");
      break;
    case 8:
      printf("P");
      break;
    case 9         :
      printf("Q");
      break;    
    case 10:
      printf("R");
      break;
    case 12:
      printf("\b");
      break;
    case 14:
      printf("\n");
      break;
    default:
      break;
    }
  }
  else if (modo == 3){
    switch(tecla){
    case 0:
      printf("S");
      break;
    case 1:
      printf("T");
      break;
    case 2:
      printf("U");
      break;     
    case 4:
      printf("V");
      break;  
    case 5:
      printf("W");
      break;
    case 6:
      printf("X");
      break;
    case 8:
      printf("Y");
      break;
    case 9         :
      printf("Z");
      break;    
    case 12:
      printf("\b");
      break;
    case 14:
      printf("\n");
      break;
    default:
      break;
    }
  }
  else {
    switch(tecla){
    case 12:
      printf("\b");
      break;
    case 13:
      printf("0");
      break;
    case 14:
      printf("\n");
      break;
    case 15:
      break;
    default:
      printf("%d",tecla);
    }
  }
  p_anterior = tecla;
  
}

 /* //////EDITOR 2 ///////
  if ((int)tecla == 0){printf("0");}
  if ((int)tecla == 1){printf("1");}
  if ((int)tecla == 2){printf("2");}
  if ((int)tecla == 3){printf("3");}
  if ((int)tecla == 4){printf("4");}
  if ((int)tecla == 5){printf("5");}
  if ((int)tecla == 6){printf("6");}
  if ((int)tecla == 7){printf("7");}
  if ((int)tecla == 8){printf("8");}
  if ((int)tecla == 9){printf("9");}
  if ((int)tecla == 10){printf("10");}
  if ((int)tecla == 11){printf("11");}
  if ((int)tecla == 12){printf("12");}
  if ((int)tecla == 13){printf("13");}
  if ((int)tecla == 14){printf("14");}
  if ((int)tecla == 15){printf("15");}
}
 */
   
 /*/////EDITOR 3 ///////
 switch (tecla){
  case 3:
    if(p_anterior != tecla){
      printf("A");
      break;
    }
    else
      break;
    
  case 7: 
    if(p_anterior != tecla){
      printf("B");
      break;
    }
    else
      break;
    
  case 11:
    if (p_anterior != tecla){
      printf("C");
      break;
    }
    else
      break;
  case 15:
    if (p_anterior != tecla){
      printf("D");
      break;
    }
    else
      break;
  default:{
    printf("%d",tecla);
    break;
  }
  }
  p_anterior = tecla;
  
}*/
