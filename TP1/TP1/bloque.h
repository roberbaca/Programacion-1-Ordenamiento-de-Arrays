#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;

class bloque
{

public:

	bloque();
	void cargar_graficos();
	Sprite get_sprite(); // devuelve el sprite
	Text get_text(); // devuelte el texto
	void set_position(float x, float y); // para setear posicion de los bloques
	void set_valor(int num_rnd); // para setear valor a mostrar dentro de los bloques
	void set_textColor(Color colorTexto); // para setear el color del texto dentro de los bloques
	
private:

	float posicion_x, posicion_y;
	Color colorTexto;

	int valor; // variable en la que voy a almacenar uno de los numeros random del array

	Sprite* spr_bloque;
	Texture* txt_bloque;
	Text texto;
	Font fuente;

};