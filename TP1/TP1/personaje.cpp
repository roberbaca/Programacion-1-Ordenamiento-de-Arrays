#include "personaje.h"

personaje::personaje() // constructor
{
	posicion_x = 160;
	posicion_y = 350;
	velocidad_x = 0;
	velocidad_y = 0;
	velocidad_yMax = 250;
	gravedad = 20;
	altura_salto = 150;
	altura_piso = 350;
	esta_saltando = false;

	evento = new Event;
	
	//sonido para el salto
	if (!buffer.loadFromFile("jump.wav"))
	{
		// Error...
	}
		
	sound.setBuffer(buffer);
	sound.setVolume(50);
	
	cargar_graficos();
}


void personaje::cargar_graficos()
{
	txt_personaje = new Texture;
	txt_personaje->loadFromFile("personaje.png");
	
	spr_personaje = new Sprite(*txt_personaje);
	spr_personaje->setTexture(*txt_personaje);
	spr_personaje->setScale(3,3);
	spr_personaje->setOrigin(8,20); // origen en la parte inferior de la imagen
	spr_personaje->setPosition(posicion_x, posicion_y);
}


void personaje::actualizar_pos(Time *tiempo)
{
	/* Calculamos la Posicion(distancia) = velocidad x tiempo
	   La posicion en x esta limitada a los boundaries de la ventana.
    */

	limite_izquierda = spr_personaje->getGlobalBounds().width;
	limite_derecha = 800 - spr_personaje->getGlobalBounds().width;;

	if ((spr_personaje->getPosition().x <= limite_derecha) && (spr_personaje->getPosition().x >= limite_izquierda))
	{
		posicion_x += velocidad_x * tiempo->asSeconds();
	}

	if (spr_personaje->getPosition().x > limite_derecha)
	{
		posicion_x = limite_derecha;
	}

	if (spr_personaje->getPosition().x < limite_izquierda)
	{
		posicion_x = limite_izquierda;
	}

	posicion_y += velocidad_y * tiempo->asSeconds();
	

	// limito la velocidad de caida para que el personaje no se acelere indefinidamente	
	if (velocidad_y > velocidad_yMax)
	{
		velocidad_y = 250;
	}
		
	// Para detectar si el personaje esta en el aire
	if (spr_personaje->getPosition().y == altura_piso) 
	{
		esta_saltando = false;
	}
	
	//cuando el personaje esta en el aire, aplicamos la gravedad
	if ((spr_personaje->getPosition().y > altura_salto) && (spr_personaje->getPosition().y < altura_piso))
	{
		velocidad_y += gravedad;
	}

	// para evitar que el personaje caiga por debajo de la plataforma. En el futuro cambiar por un checkcollision
	if (spr_personaje->getPosition().y > altura_piso)
	{
		posicion_y = altura_piso;
		velocidad_y = 0;
	}

	//actualizamos la posicion del personaje
	spr_personaje->setPosition(posicion_x, posicion_y);
	
}



void personaje::actualizar_mov(Event& evento)
{
	//Eventos con el teclado
			
	if (evento.type == Event::KeyPressed)
		{
		// evitamos el doble salto
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == altura_piso)
		{
			sound.play();
			esta_saltando = true;
			velocidad_y = -400;
		}

		// movimiento a la derecha
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			velocidad_x = 200;
		}

		// movimiento a la izquierda
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			velocidad_x = -200;
		}
		
		// si presiono izquierda y derecha a la vez, el personaje no se mueve en el eje X
		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Left)))
		{
			velocidad_x = 0;
		}
	}


	else if (evento.type == Event::KeyReleased)
	{
		//Al soltar la tecla de salto, se activa la gravedad afectando la velocidad en el eje y
		if ((evento.key.code == Keyboard::Up) && esta_saltando)
		{
			esta_saltando = false;
			velocidad_y += gravedad;
		}

		//Si dejamos de tocar las teclas de derecha o de izquierda, el personaje no se mueve
		if (evento.key.code == Keyboard::Right)
		{
			velocidad_x = 0;
		}

		if (evento.key.code == Keyboard::Left)
		{
			velocidad_x = 0;
		}
	}
	
}


Sprite personaje::get_sprite()
{
	return *spr_personaje;
}