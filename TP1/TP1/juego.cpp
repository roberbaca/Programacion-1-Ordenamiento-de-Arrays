#include "juego.h"


juego::juego(Vector2i resolucion, string titulo) // constructor
{
	cont_aciertos = 0; // para llevar un conteo de la cantidad de aciertos
	
	fps = 60.f; // para que corra a 60 frames por segundo
	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);
	
	game_over = false; // para verificar condicion de fin de juego

	cargar_imagenes();

	evento1 = new Event;

	// incializamos los relojes:
	reloj1 = new Clock;
	reloj2 = new Clock;
	tiempo1 = new Time;
	dt = new Time;

	//cronometro
	tiempoInicio = 0.f;
	tiempoFin = 0.f;
	tiempo_juego = 60; // duracion de la partida
	seconds = 0;
	
	flag = false; // bandera que uso para descontar los segundos
	
	// incializamos el personaje
	player1 = new personaje();

	// incializamos los bloques. El array verificador se genera con todos los elementos igual a false
	for (int i = 0; i < 10; i++)
	{
		blocky[i] = new bloque();
		verificador[i] = false;
	}
		
	 // musica

	if (!musica.openFromFile("musica1.wav"))
	{
		//Error		
	}

	musica.setLoop(true);
	musica.play();


	// sonido alarma
	if (!buffer_alarm.loadFromFile("alarm.ogg"))
	{
		// Error...
	}

	sonido_alarm.setBuffer(buffer_alarm);
	sonido_alarm.setVolume(100);
	

	// sonido bloque
	if (!buffer_bloque.loadFromFile("\coin.wav"))
	{
		// Error...
	}

	sonido_bloque.setBuffer(buffer_bloque);
	sonido_bloque.setVolume(50);

	// sonido Game Over
	if (!buffer_gameOver.loadFromFile("GameOver.wav"))
	{
		// Error...
	}

	sonido_gameOver.setBuffer(buffer_gameOver);
	sonido_gameOver.setVolume(100);
		

	// sonido Victoria
	if (!buffer_victory.loadFromFile("victory.ogg"))
	{
		// Error...
	}

	sonido_victory.setBuffer(buffer_victory);
	sonido_victory.setVolume(100);

			
	// creo el arreglo de 10 numeros random y lo muestro por consola para debug
	cout << "Valores desordenados: " << endl;

	for (int i = 0; i < 10; i++)
	{
		arreglo[i] = rand() % 999 + 1;
		cout << arreglo[i] << endl;
	}
	
	ordenar_arreglo(); // ordeno los elementos del arreglo de menor a mayor

	game_loop(); // loop principal del juego

}


void juego::cargar_imagenes()
{
	ventana1->setMouseCursorVisible(false); // oculatmos el cursor del mouse

	//cargamos las texturas del background
	txt_fondo = new Texture;
	txt_fondo->loadFromFile("fondo.png");
	spr_fondo = new Sprite(*txt_fondo);
		
	// fuente para el contador en reversa
	if (!fuenteContador.loadFromFile("Square.ttf"))
	{
		//error
	}

	textoContador.setFont(fuenteContador);
	textoContador.setCharacterSize(48);
}



void juego::procesar_eventos()
{
	while (ventana1->pollEvent(*evento1))
	{
		switch (evento1->type)
		{
		case Event::Closed:
			exit(1);
			break;
		}

	}
	
}


void juego::dibujar(int arr[10])
{
	// dibujamos el background, personaje del jugador, bloques, numeros en los bloques y cronometro
	ventana1->draw(*spr_fondo); 
	ventana1->draw(player1->get_sprite());

	for (int i = 0; i < 10; i++)
	{
		ventana1->draw(blocky[i]->get_sprite());
		blocky[i]->set_position(75 * i + 65,200);
		blocky[i]->set_valor(arr[i]); // le asignamos a cada bloque un numero del arreglo
		ventana1->draw(blocky[i]->get_text());
	}
	
	ventana1->draw(textoContador);
}



void juego::game_loop()
{
	//Asignar a tiempoInicio una unica vez, el tiempo actual + el tiempo de juego en segundos.
	tiempoInicio = relojContador.getElapsedTime().asSeconds() + tiempo_juego;

	//bucle ppal del juego
	while (ventana1->isOpen())
	{
		*tiempo1 = reloj1->getElapsedTime();
			
		if (tiempo2 + tiempoFrame < tiempo1->asSeconds()) // para que transcurra 1 fps entre ciclos
		{
			tiempo2 = tiempo1->asSeconds();

			*dt = reloj2->restart(); // el tiempo dt lo uso para las formulas de MRU del personaje

			actualizarContador(); // cronometro en reversa

			ventana1->clear(); // limpiar la ventana

			procesar_eventos();
			
			player1->actualizar_pos(dt); // posicion del jugador

			if (!game_over) // movimientos del juegador. Evito que el jugador se mueva al finalizar el juego
			{
				player1->actualizar_mov(*evento1);
			}

			chequear_colisiones(); //chequeo si el personaje colisiona con los bloques

			fin_juego(); // chequeo condicion de victoria o derrota

			/*	Si empieza el juego (game_over = false), entonces dibujo los numeros random (arreglo).
				Sino (game_over = true), dibujo los numeros ordenados de menor a mayor (arr_ordenado)
			*/
						
			if (!game_over)
			{
				dibujar(arreglo);
			}

			else
			{
				dibujar(arr_ordenado);

				for (int i = 0; i < 10; i++)
				{
					blocky[i]->set_textColor(Color::Yellow);
				}

				for (int i = 0; i < cont_aciertos; i++) // Muesto los bloques correctos en verde
				{
					blocky[i]->set_textColor(Color::Green);
				}
			}
					
			ventana1->display(); // mostrar la ventana 
		}
	}
}




void juego::ordenar_arreglo()
{
	// copio elemento a elemento del arreglo original a un nuevo arreglo que voy a ordener.
	for (int i = 0; i < 10; i++)
	{
		arr_ordenado[i] = arreglo[i];
	}

	// aplico algoritmo de ordenamiento BURBUJA.

	int auxiliar;

	/*	Necesito un doble FOR para recorrer y manipular el vector. La diferencia es que en el primero
		nuestro límite es 10 (por la cantidad de elementos) y en el segundo el límite es 9 (para no salirnos del vector)
	*/
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr_ordenado[j] > arr_ordenado[j + 1])
			{
				auxiliar = arr_ordenado[j];
				arr_ordenado[j] = arr_ordenado[j + 1];
				arr_ordenado[j + 1] = auxiliar;
			}
		}
	}

	//para debug, veo si funciona correctamente mostrandolo en consola
	cout << endl;
	cout << "Valores ordenados: " << endl;
	for (int i = 0; i < 10; i++) 
	{
		cout << arr_ordenado[i] << endl;
	}

}



void juego::actualizarContador() 
{
	if (!game_over)
	{
		tiempoFin = relojContador.getElapsedTime().asSeconds(); //Asignar a tiempoFin, el tiempo actual en cada framerate

		seconds = (int)(tiempoInicio - tiempoFin);

		if (seconds >= 0)
		{
			char buffer[20];
			sprintf_s(buffer, "Tiempo: %i", seconds);
			textoContador.setString(buffer);
		}
		else
		{
			textoContador.setString("GAME OVER !");
			game_over = true;
		}

		// Cuando quedan menos de 10 segundos, el cronometro se pone rojo
		// Suena una alarma avisando que quedan pocos segundos

		if (seconds <= 10)
		{
			textoContador.setFillColor(Color::Red);
		}

		
		if (seconds == 11)
		{
			sonido_alarm.play();
			sonido_alarm.setLoop(true);
		}
				
	}
}


void juego::chequear_colisiones()
{
	//Al colisionar con un bloque CORRECTO , cambio de color el numero a verde
	for (int i = 0; i < 10; i++)
	{
		if ( blocky[i]->get_sprite().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds() ))
		{
			if ( (arreglo[i] == arr_ordenado[cont_aciertos]) && !verificador[i])
			{
				blocky[i]->set_textColor(Color::Green); // cambiamos de color el texto del bloque a verde
				sonido_bloque.play();
				cont_aciertos++; // sumo 1 al contado de aciertos
				verificador[i] = true; // el boque lo marco como correcto
			}
		}
	}

	// Al colisionar con un bloque INCORRECTO, cambio de color el numero a rojo (para debug) y descuento 10 segundos del cronometro
	for (int i = 0; i < 10; i++)
	{
		if (blocky[i]->get_sprite().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds()))
		{
			if ((arreglo[i] != arr_ordenado[cont_aciertos]) && !verificador[i])
			{	
				//blocky[i]->set_textColor(Color::Red); //cambiamos de color el texto del bloque a rojo para debug
				descontar_seg();
				
			}
		}
	}

	//verifico si el jugador toco el piso para resetear el flag (lo uso para activad la funcion descontar_seg solo una vez por colision incorrecta)
	if (player1->get_sprite().getPosition().y == 350)
	{
		flag = false;
	}


}

void juego::descontar_seg()
{
	// descuento 10 segundo. Uso un flag para correr esta funcion solo 1 vez.
	if (!flag)
	{
		tiempoInicio -= 10;
	}

	flag = true; // reseteo flag
}



void juego::fin_juego()
{
	/*	Chequeo condición de fin de juego, que se da si se cumple una de estas condiciones
		- se seleccionaron correctamente los 10 bloques.
		- se acabó el tiempo. 
		Cualquiera sea el caso, muestro los numeros ordenados y marco en verde los que
		se seleccionaron correctamente (ver dentro de GameLoop).	
	*/

	if (!game_over)
	{
		if (cont_aciertos == 10) // condicion de VICTORIA. Se seleccionaron correctamente los 10 numeros
		{
			sonido_victory.play(); // sonido de victoria. Objetivo cumplido. Ganaste el juego.
			textoContador.setFillColor(Color::Green);
			textoContador.setString("GANASTE !!!"); // mostramos en pantalla "Ganaste" en lugar del contador
			game_over = true; // se cumple la condicion de fin de juego

		}

		if (seconds <= 0)  // condicion de DERROTA. Se acabo el tiempo
		{
			sonido_gameOver.play(); // sonido de derrota. Perdiste.
			textoContador.setFillColor(Color::Red);
			textoContador.setString("GAME OVER"); // mostramos en pantalla el msj "Game Over" en lugar del contador
			game_over = true; // se cumple la condicion de fin de juego
		}
	}

	if (game_over)
	{
		musica.stop(); // detengo la musica y la alarma
		sonido_alarm.stop();
		sonido_alarm.setLoop(false);
	}
}

