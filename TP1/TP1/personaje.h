#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;

class personaje
{

public:

	personaje();
	void actualizar_pos(Time *tiempo); // calculo de la posicion del personaje
	void actualizar_mov(Event& evento); // eventos con el teclado para mover el personaje
	void cargar_graficos();
	Sprite get_sprite();

private:

	float posicion_x, posicion_y; //posiciones en x e y
	float velocidad_y; // velocidad en eje y
	float velocidad_x; // velocidad en eje x
	float velocidad_yMax; // velocidad maxima en eje y (para limitar el efecto de la aceleracion de la gravedad)
	float gravedad; // gravedad en eje y
	float altura_salto; // altura maxima que puede alcanzar nuestro personaje
	float altura_piso; // posicion en y del personaje cuando toca el piso
	bool esta_saltando; //bandera para verificar si el personaje esta en el aire

	float limite_derecha, limite_izquierda; // boundaries

	Sprite *spr_personaje;
	Texture *txt_personaje;
	
	Event* evento;

	Sound sound;
	SoundBuffer buffer;
};
