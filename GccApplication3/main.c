/*
 * GccApplication3.c
 *
 * Created: 28/01/2025 10:01:39
 * Author : pablo
 */ 

#define F_CPU 16000000
#include "Display/Display.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
/*-----------------------------Variables---------------------------------------------------------*/
uint8_t iniciar = 0;
uint8_t si_contar = 0;
uint8_t contador1 = 0;
uint8_t contador2 = 0;
uint8_t jugador1 = 0;
uint8_t jugador2 = 0;
uint8_t fin1 = 0;
uint8_t fin2 = 0;
volatile uint8_t prev_PC0 = 1;
volatile uint8_t prev_PC1 = 1;
volatile uint8_t prev_PC2 = 1;

/*-----------------------------Inicializar Funciones----------------------------------------------*/
void setup(void);
void Salida1_app(uint8_t contador1);
void Salida2_app(uint8_t contador2);
void multiplexar(void);


/*-----------------------------Main---------------------------------------------------------------*/
int main(void)
{
    setup();
	numeros(0);
	
    while (1) 
    {
		if (iniciar == 1)
		{
			iniciar = 0;
			numeros(5);
			_delay_ms(1000);
			numeros(4);
			_delay_ms(1000);
			numeros(3);
			_delay_ms(1000);
			numeros(2);
			_delay_ms(1000);
			numeros(1);
			_delay_ms(1000);
			numeros(0);
			contador1 = 0;
			contador2 = 0;
			si_contar = 1;
		}
		if (fin1 == 1){
			si_contar = 0;
			contador2 = 0;
			numeros(1);
		}
		else if (fin2 == 1){
			si_contar = 0;
			contador1 = 0;
			numeros(2);
		}
		Salida2_app(contador2);
		Salida1_app(contador1);
		multiplexar();
		_delay_ms(5);
    }
}

/*-----------------------------Setup-------------------------------------------------------------*/
void setup(void) {
	cli();
	si_contar = 0;
	iniciar = 0;
	DDRC &= ~((1<<PC0) | (1<<PC1) | (1<<PC2));
	DDRC |= ((1<<PC3) | (1<<PC4) | (1<<PC5) | (1<<PC6));  
	DDRB |= ((1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3));  
	PORTC |= ((1<<PC0) | (1<<PC1) | (1<<PC2));
	initDisplay();  
	
	// Habilitando interrupciones
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10); 
	sei();
}

/*-----------------------------Interrupciones-----------------------------------------------------*/
ISR(PCINT1_vect) {
	
	uint8_t state = PINC;


	if ((prev_PC1 == 1) && ((state & (1 << PC1)) == 0)) {
		_delay_ms(5);
		if ((PINC & (1 << PC1)) == 0) {
			iniciar = 1;
			contador1 = contador2 = jugador1 = jugador2 = fin1 = fin2 = 0;
		}
	}

	//Boton PC2
	if ((prev_PC2 == 1) && ((state & (1 << PC2)) == 0) && (si_contar == 1)) {
		_delay_ms(5);
		if ((PINC & (1 << PC2)) == 0) {
			contador2++;
		}
	}
	
	
	// Boton PC0
	if ((prev_PC0 == 1) && ((state & (1 << PC0)) == 0) && (si_contar == 1)) {
		_delay_ms(5);
		if ((PINC & (1 << PC0)) == 0) {
			contador1++;
		}
	}



	// Actualizamos los estados previos
	prev_PC0 = ((state & (1 << PC0)) != 0) ? 1 : 0;
	prev_PC1 = ((state & (1 << PC1)) != 0) ? 1 : 0;
	prev_PC2 = ((state & (1 << PC2)) != 0) ? 1 : 0;
}


/*-----------------------------Funciones secundarias-----------------------------------------------------*/
void multiplexar(void){
	_delay_ms(5);
	PORTB = jugador2;
	PORTC |= (1<<PC4);
	PORTC &= ~(1<<PC3);
	_delay_ms(5);
	PORTB = jugador1;
	PORTC |= (1<<PC3);
	PORTC &= ~(1<<PC4);
	
	
}

void Salida1_app(uint8_t contador1){
	switch(contador1){
		case 0:
		jugador1 = 0x00;
		break;
		case 1:
		jugador1 = 0x01;
		break;
		case 2:
		jugador1 = 0x02;
		break;
		case 3:
		jugador1 = 0x04;
		break;
		case 4:
		jugador1 = 0x0F;
		fin1 = 1;
		break;
		default:
		jugador1 = 0x00;
	}
}

void Salida2_app(uint8_t contador2){
	switch(contador2){
		case 0:
		jugador2 = 0x00;
		break;
		case 1:
		jugador2 = 0x01;
		break;
		case 2:
		jugador2 = 0x02;
		break;
		case 3:
		jugador2 = 0x04;
		break;
		case 4:
		jugador2 = 0x0F;
		fin2 = 1;
		break;
		default:
		jugador2 = 0x00;
	}
}

