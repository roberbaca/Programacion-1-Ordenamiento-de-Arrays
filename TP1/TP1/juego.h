#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "personaje.h"
#include "bloque.h"

using namespace std;
using namespace sf;

class juego
{

public:

	juego(Vector2i resolucion, string titulo); // constructor

	void cargar_imagenes();
	void procesar_eventos();
	void game_loop(); // loop principal del juego
	void dibujar(int arr[10]); //para dibujar. Le indico por parametro el array que se debe mostrar en pantalla dentro de los bloques
	void ordenar_arreglo(); // este metodo ordena el arreglo (burbuja)
	void actualizarContador(); // cronometro en reversa
	void chequear_colisiones(); // para chequear si el personaje colisionó con el bloque
	void fin_juego(); // para chequear si se cumplen las condiciones de fin de juego
	void descontar_seg(); // para descontar 10 segundos si se elige un bloque incorrecto

private:

	RenderWindow *ventana1;
	View *camara1;
	Event *evento1;

	int arreglo[10]; // arreglo de 10 numeros random
	int arr_ordenado[10]; // array ordenado para comparar con el desordenado
	bool verificador[10]; // array para verificar cuales bloques se seleccionaron en orden
	int cont_aciertos; // contador auxiliar para avanzar en los indices del array verificador. Cuenta los aciertos
	
	bool flag; // bandera auxiliar para ejectura la funcion de desonctar_seg 1 sola vez
		
	//variables para controlar el tiempo y los fps
	float fps, tiempoFrame, tiempo2;
	Time* tiempo1;
	Time *dt;
	Clock* reloj1;
	Clock* reloj2;
	Clock relojContador;

	//variables para controlar el cronometro en reversa
	int tiempo_juego;
	float tiempoInicio;
	float tiempoFin;
	int seconds;

	//texto y fuentes
	Text textoContador;
	Font fuenteContador;

	//sonidos
	Sound sonido_alarm;
	Sound sonido_gameOver;
	Sound sonido_victory;
	Sound sonido_bloque;
	SoundBuffer buffer_alarm;
	SoundBuffer buffer_gameOver;
	SoundBuffer buffer_victory;
	SoundBuffer buffer_bloque;

	//musica del juego
	Music musica;

	//bandera para ver si se cunmple las condiciones de fin de juego
	bool game_over;

	// sprite y textura del background
	Sprite* spr_fondo;
	Texture* txt_fondo;

	// creo una instancia del personaje
	personaje *player1; 

	// creo un array de 10 bloques
	bloque* blocky[10];

};




