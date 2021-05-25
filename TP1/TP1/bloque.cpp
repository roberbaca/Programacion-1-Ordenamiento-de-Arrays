#include "bloque.h"

bloque::bloque() // constructor
{
	//cargamos la fuente de texto
	if (!fuente.loadFromFile("Square.ttf"))
	{
		// error...
	}

	texto.setFont(fuente);	// seleccion la fuente
	texto.setCharacterSize(22); // tamaño de letra en pixeles
	texto.setFillColor(Color::Yellow);
	
	cargar_graficos();
}


void bloque::cargar_graficos()
{
	txt_bloque = new Texture;
	txt_bloque->loadFromFile("box.png");

	spr_bloque = new Sprite(*txt_bloque);
	spr_bloque->setTexture(*txt_bloque);
	spr_bloque->setScale(3.2, 3.2);
	spr_bloque->setOrigin(10, 10); // origen en el medio
	
}

Sprite bloque::get_sprite()
{
	return *spr_bloque;
}

Text bloque::get_text()
{
	texto.setString(to_string(valor)); 
	texto.setOrigin(texto.getGlobalBounds().width / 2.f, texto.getGlobalBounds().height / 2.f);
	texto.setPosition(spr_bloque->getPosition().x, spr_bloque->getPosition().y - 5);

	return texto;
}


void bloque::set_position(float x, float y)
{
	spr_bloque->setPosition(x, y);
}

void bloque::set_valor(int num_rnd) //asignamos un numero al bloque
{
	valor = num_rnd;
}

void bloque::set_textColor(Color colorTexto)  // le paso por parametro el color
{
	texto.setFillColor(colorTexto);
}


