/*
 * Display.c
 *
 * Created: 28/01/2025 12:17:59
 *  Author: pablo
 */ 

#include "Display.h"
#include <avr/io.h>
#include <stdint.h>

void initDisplay(void){
	// Puerto D como salida
	DDRD = 0xFF;
	PORTD = 0;
	// Utilizar Rx y Tx
	UCSR0B = 0;
}

void numeros(uint8_t Numero){
	switch (Numero) {
		case 0:
		PORTD = 0x3F;  // 0b00111111 -> a, b, c, d, e, f encendidos.
		break;
		case 1:
		PORTD = 0x06;  // 0b00000110 -> b, c encendidos.
		break;
		case 2:
		PORTD = 0x5B;  // 0b01011011 -> a, b, d, e, g encendidos.
		break;
		case 3:
		PORTD = 0x4F;  // 0b01001111 -> a, b, c, d, g encendidos.
		break;
		case 4:
		PORTD = 0x66;  // 0b01100110 -> b, c, f, g encendidos.
		break;
		case 5:
		PORTD = 0x6D;  // 0b01101101 -> a, c, d, f, g encendidos.
		break;
		case 6:
		PORTD = 0x7D;  // 0b01111101 -> a, c, d, e, f, g encendidos.
		break;
		case 7:
		PORTD = 0x07;  // 0b00000111 -> a, b, c encendidos.
		break;
		case 8:
		PORTD = 0x7F;  // 0b01111111 -> Todos los segmentos encendidos.
		break;
		case 9:
		PORTD = 0x6F;  // 0b01101111 -> a, b, c, d, f, g encendidos.
		break;
		default:
		PORTD = 0x00;  // Apagar todos los segmentos.
		break;
	}
}