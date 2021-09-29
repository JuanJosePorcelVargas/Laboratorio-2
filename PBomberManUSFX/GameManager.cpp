#include "GameManager.h"


GameManager::GameManager() {
	gWindow = nullptr;
	gRenderer = nullptr;
	texturaBomber1 = nullptr;
	texturaBomber2 = nullptr;
	texturaEnemigo1 = nullptr;
	texturaEnemigo2 = nullptr;
	texturaEnemigo3 = nullptr;
	texturaEnemigo4 = nullptr;
	texturaEnemigo5 = nullptr;
	texturaExplosion1 = nullptr;
	texturaExplosion2 = nullptr;
	texturaExplosion3 = nullptr;
	texturaExplosion4 = nullptr;
	texturaExplosion5 = nullptr;
}

bool GameManager::onInit() {

	//Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Bomber Man USFX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{

			////Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
};

bool GameManager::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture("texture.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}


void GameManager::close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int GameManager::onExecute() {
	if (!onInit()) {
		cout << "Failed to initialize!" << endl;
		return -1;
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event event;

		texturaBomber1 = new Texture(gRenderer);
		texturaBomber1->loadFromImage("resources/bomber.bmp");
		texturaBomber2 = new Texture(gRenderer);
		texturaBomber2->loadFromImage("resources/textures.bmp");
		//Enemigos
		texturaEnemigo1 = new Texture(gRenderer);
		texturaEnemigo1->loadFromImage("resources/textures.bmp");
		texturaEnemigo2 = new Texture(gRenderer);
		texturaEnemigo2->loadFromImage("resources/textures.bmp");
		texturaEnemigo3 = new Texture(gRenderer);
		texturaEnemigo3->loadFromImage("resources/textures.bmp") ;
		texturaEnemigo4 = new Texture(gRenderer);
		texturaEnemigo4->loadFromImage("resources/textures.bmp");
		texturaEnemigo5 = new Texture(gRenderer);
		texturaEnemigo5->loadFromImage("resources/textures.bmp");
		//Explosion
		texturaExplosion1 = new Texture(gRenderer);
		texturaExplosion1->loadFromImage("resources/textures.bmp");
		texturaExplosion2 = new Texture(gRenderer);
		texturaExplosion2->loadFromImage("resources/textures.bmp");
		texturaExplosion3 = new Texture(gRenderer);
		texturaExplosion3->loadFromImage("resources/textures.bmp");
		texturaExplosion4 = new Texture(gRenderer);
		texturaExplosion4->loadFromImage("resources/textures.bmp");
		texturaExplosion5 = new Texture(gRenderer);
		texturaExplosion5->loadFromImage("resources/textures.bmp");

		Bomber* b1 = new Bomber(texturaBomber1);
		Bomber* b2 = new Bomber(texturaBomber2);
		Enemigo*e1 = new Enemigo(texturaEnemigo1);
		Enemigo* e2 = new Enemigo(texturaEnemigo2);
		Enemigo* e3 = new Enemigo(texturaEnemigo3);
		Enemigo* e4 = new Enemigo(texturaEnemigo4);
		Enemigo* e5 = new  Enemigo(texturaEnemigo5);
		Explosion* ex1 = new Explosion(texturaExplosion1);
		Explosion* ex2 = new Explosion(texturaExplosion2);
		Explosion* ex3 = new Explosion(texturaExplosion3);
		Explosion* ex4 = new Explosion(texturaExplosion4);
		Explosion* ex5 = new Explosion(texturaExplosion5);
		
		b1->setImagenX(3);
		b1->setImagenY(3);
		b1->setAncho(20);
		b1->setAlto(30);

		b2->setImagenX(570);
		b2->setImagenY(3);
		b2->setAncho(30);
		b2->setAlto(35);

		//Enemigo
		e1->setImagenX(3);
		e1->setImagenY(160);
		e1->setAncho(19);
		e1->setAlto(25);

		e2->setImagenX(3);
		e2->setImagenY(183);
		e2->setAncho(19);
		e2->setAlto(25);

		e3->setImagenX(3);
		e3->setImagenY(208);
		e3->setAncho(19);
		e3->setAlto(25);

		e4->setImagenX(3);
		e4->setImagenY(233);
		e4->setAncho(20);
		e4->setAlto(25);

		e5->setImagenX(3);
		e5->setImagenY(256);
		e5->setAncho(20);
		e5->setAlto(25);

		//Explosion

		ex1->setImagenX(304);
		ex1->setImagenY(20);
		ex1->setAncho(30);
		ex1->setAlto(30);

		ex2->setImagenX(304);
		ex2->setImagenY(50);
		ex2->setAncho(30);
		ex2->setAlto(30);

		ex3->setImagenX(304);
		ex3->setImagenY(70);
		ex3->setAncho(30);
		ex3->setAlto(30);

		ex4->setImagenX(304);
		ex4->setImagenY(90);
		ex4->setAncho(30);
		ex4->setAlto(30);

		ex5->setImagenX(23);
		ex5->setImagenY(915);
		ex5->setAncho(50);
		ex5->setAlto(50);




			

		actoresJuego.push_back(b1);
		actoresJuego.push_back(b2);
		actoresJuego.push_back(e1);
		actoresJuego.push_back(e2);
		actoresJuego.push_back(e3);
		actoresJuego.push_back(e4);
		actoresJuego.push_back(e5);
		actoresJuego.push_back(ex1);
		actoresJuego.push_back(ex2);
		actoresJuego.push_back(ex3);
		actoresJuego.push_back(ex4);
		actoresJuego.push_back(ex5);




		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&event) != 0)
			{
				//User requests quit
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			//Clear screen
			//SDL_RenderClear(gRenderer);

			//Render texture to screen
			//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
			
				
			////Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Update screen

			/*onLoop();
			onRender();*/
			
			for (int i = 0; i < actoresJuego.size(); i++) {
				((GameActor*)actoresJuego[i])->setPosicionX(rand() % SCREEN_WIDTH);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);

				actoresJuego[i]->render();
			}

			SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;

}

SDL_Texture* GameManager::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}