#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<fstream>
#include<filesystem>
#include<vector>
#include<cstdlib>
#include<math.h>

using namespace sf;

void startsGameUniverse(RenderWindow& window);

void ShootBallGame(RenderWindow& window);
void SikhAttacks(RenderWindow& window);
void SpaceWar(RenderWindow& window);
void FlappyBird(RenderWindow& window);

int main() {
	
	RenderWindow window(VideoMode(1400.f, 800.f), "Game Universe", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	/* Start Animation */
	startsGameUniverse(window);

	/* Background Screen */
	Texture bgtex;
	Sprite background;
	if (!bgtex.loadFromFile("Textures/bg.png"))
		throw "No background image load";

	background.setTexture(bgtex);
	background.setScale(1.1f, 1.12f);

	/* Buttons :*/
	Vector2i mousePos;

	CircleShape b1;
	b1.setRadius(132.f);
	b1.setFillColor(Color::Transparent);
	b1.setPosition(333.f, 90.f);
	bool hoverButton1= false;

	CircleShape b2;
	b2.setRadius(132.f);
	b2.setFillColor(Color::Transparent);
	b2.setPosition(826.f, 90.f);
	bool hoverButton2= false;
	
	CircleShape b3;
	b3.setRadius(132.f);
	b3.setFillColor(Color::Transparent);
	b3.setPosition(333.f, 435.f);
	bool hoverButton3= false;
	
	CircleShape b4;
	b4.setRadius(132.f);
	b4.setFillColor(Color::Transparent);
	b4.setPosition(826.f, 435.f);
	bool hoverButton4= false;

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}

		// mouse on Buttons
		if (e.type == Event::MouseMoved) {
			mousePos = Mouse::getPosition(window);
			if (b1.getGlobalBounds().contains(mousePos.x,mousePos.y)) {
				hoverButton1 = true;
			}
			else if (b2.getGlobalBounds().contains(mousePos.x,mousePos.y)) {
				hoverButton2 = true;
			}
			else if (b3.getGlobalBounds().contains(mousePos.x,mousePos.y)) {
				hoverButton3 = true;
			}
			else if (b4.getGlobalBounds().contains(mousePos.x,mousePos.y)) {
				hoverButton4 = true;
			}
			else {
				hoverButton1 = false;
				hoverButton2 = false;
				hoverButton3 = false;
				hoverButton4 = false;
			}
		}

		/*b1.setFillColor(hoverButton1 ? Color::Red : Color::White);
		b2.setFillColor(hoverButton2 ? Color::Red : Color::White);
		b3.setFillColor(hoverButton3 ? Color::Red : Color::White);
		b4.setFillColor(hoverButton4 ? Color::Red : Color::White);*/
		
		//Open games on click
		if (e.type == Event::MouseButtonPressed) {
			if (e.mouseButton.button == Mouse::Left) {
				if (hoverButton1) {
					std::cout << "Button 1 clicked!\n";
					ShootBallGame(window);
					hoverButton1 = false;
				}
				else if (hoverButton2) {
					std::cout << "Button 2 clicked!\n";
					SikhAttacks(window);
					hoverButton2 = false;
				}
				else if (hoverButton3) {
					std::cout << "Button 3 clicked!\n";
					SpaceWar(window);
					hoverButton3 = false;
				}
				else if (hoverButton4) {
					std::cout << "Button 4 clicked!\n";
					FlappyBird(window);
					hoverButton4 = false;
				}
			}
		}


		// Open Games with Keyboard
		if (Keyboard::isKeyPressed(Keyboard::G))
			ShootBallGame(window);

		if (Keyboard::isKeyPressed(Keyboard::H))
			SikhAttacks(window);

		if (Keyboard::isKeyPressed(Keyboard::J))
			SpaceWar(window);
		
		if (Keyboard::isKeyPressed(Keyboard::F))
			FlappyBird(window);

		window.clear();
		window.draw(background);
		window.draw(b1);
		window.draw(b2);
		window.draw(b3);
		window.draw(b4);
		window.display();

	}
	return 0;
}
/**************************************************************************************************************/
/* Window Starts */
void startsGameUniverse(RenderWindow& window) {

	/* Background Screen */
	Texture bgtex;
	Sprite background;
	if (!bgtex.loadFromFile("Textures/bg.png"))
		throw "No background image load";

	background.setTexture(bgtex);
	background.setScale(1.1f, 1.12f);
	
	// Getting LeftSide Gate
	Texture Lefttex;
	Sprite LeftSide;
	if (!Lefttex.loadFromFile("Textures/Side_L.png"))
		throw "No background image load";

	LeftSide.setTexture(Lefttex);
	LeftSide.setScale(1.1f, 1.12f);

	// Getting RightSide Gate
	Texture Righttex;
	Sprite RightSide;
	if (!Righttex.loadFromFile("Textures/Side_R.png"))
		throw "No background image load";

	RightSide.setTexture(Righttex);
	RightSide.setPosition(700.f, 0.f);
	RightSide.setScale(1.1f, 1.12f);
	
	// Getting Lock for LeftSide Gate
	Texture Locktex;
	Sprite Lock;
	if (!Locktex.loadFromFile("Textures/Lock.png"))
		throw "No background image load";

	Lock.setTexture(Locktex);
	Lock.setOrigin(Lock.getGlobalBounds().width / 2, Lock.getGlobalBounds().height / 2);
	Lock.setScale(0.5f, 0.5f);

	/* start */
	bool StartAnimation = false;
	bool rotateAnimation = false;
	int rotateTime = 0;

	while (true) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			break;

		// Press enter to open
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			StartAnimation = true;
			rotateAnimation = true;
		}

		// match position with LeftSide
		Lock.setPosition(LeftSide.getPosition().x+600,LeftSide.getPosition().y+400);

		/* start animation program */
		if(rotateAnimation && rotateTime <= 140)
			rotateTime++;

		if (rotateAnimation && rotateTime<=120) {
			Lock.rotate(-1.f);
		}

		if (StartAnimation && rotateTime>=140) {
			LeftSide.move(-5.f, 0.f);
			RightSide.move(5.f, 0.f);
		}

		/* to exit function and loop*/
		if (RightSide.getPosition().x > window.getSize().x)
			break;

		window.clear(Color::White);
		window.draw(background);
		window.draw(LeftSide);
		window.draw(RightSide);
		window.draw(Lock);

		window.display();
	}
}
/**************************************************************************************************************/
/* Game - 01 */

int GetHighScoreShootBall() {
	if (!std::filesystem::exists("ShootBall.txt")) {
		return 0;
	}
	int Score;
	std::ifstream read("ShootBall.txt");
	read >> Score;
	read.close();
	return Score;
}

void SetHighScoreShootBall(int Score) {
		std::ofstream write("ShootBall.txt");
		write << Score;
		write.close();
}

void ShootBallGame(RenderWindow& window) {
	window.setFramerateLimit(50);

	/* Background Screen */
	Texture bgtex;
	Sprite background;
	if (!bgtex.loadFromFile("Textures/bg-1.png"))
		throw "No background image load";
	background.setTexture(bgtex);
	background.setScale(1.1f, 1.12f);

	/* Score , Game over */
	// Font
	Font font;
	font.loadFromFile("Fonts/CascadiaCode.ttf");
	Font font2;
	font2.loadFromFile("Fonts/HARNGTON.TTF");

	// High Score
	int highScore = GetHighScoreShootBall();	
	Text highScoreText;
	highScoreText.setFont(font);
	highScoreText.setCharacterSize(50.f);
	highScoreText.setPosition(500.f, -5.f);
	highScoreText.setFillColor(Color::Cyan);
	highScoreText.setString("High Score : " + std::to_string(highScore));
	
	// Score
	int score = 0;	
	Text Score;
	Score.setFont(font2);
	Score.setCharacterSize(50.f);
	Score.setPosition(10.f, 100.f);
	Score.setFillColor(Color::Blue);

	// GameOver
	Text GameOver;
	bool gameOver = false;
	GameOver.setFont(font);
	GameOver.setString("Game Over!");
	GameOver.setCharacterSize(200.f);
	GameOver.setPosition(175.f, 200.f);
	GameOver.setFillColor(Color::Red);

	// New Score
	Text newScore;
	newScore.Bold;
	newScore.setFont(font);
	newScore.setCharacterSize(120.f);
	newScore.setFillColor(Color::White);
	newScore.setPosition(Vector2f(220.f, 320.f));

	// Creating a target
	Texture hooptex;
	Sprite hoop;
	if (!hooptex.loadFromFile("Textures/Stone.png"))
		throw "No background image load";
	hoop.setTexture(hooptex);
	int dir = 0;							//var to move target
	hoop.setPosition(1190.f, 65.f);
	hoop.setScale(0.3f, 0.3f);

	// Creating a ball
	int startGame = 0;
	int Life = 2;
	CircleShape ball(20.f);
	bool isShot = false;
	ball.setPosition(0.f, window.getSize().y - ball.getRadius() * 6);
	ball.setFillColor(Color::Black);
	ball.setOutlineThickness(1.f);
	ball.setOutlineColor(Color::Red);

	// Life bar
	RectangleShape lifeBar;
	lifeBar.setPosition(50.f, 300.f);

	// Creating Cannon
	Texture cannonTex;
	Sprite Cannon;
	if (!cannonTex.loadFromFile("Textures/Cannon.png"))
		throw "No background image load";
	Cannon.setTexture(cannonTex);
	Cannon.setScale(0.3f, 0.3f);


	while (true) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			break;

		if (!gameOver) {
			// making boundary for hoop and change dir
			if (hoop.getPosition().x < 157)
				dir = 1;
			else if (hoop.getPosition().x > 1190.f)
				dir = 0;

			// moving hoop according dir
			if (dir)
				hoop.move(5.f, 0.f);
			else
				hoop.move(-5.f, 0.f);

			/* shoot ball */
			if (startGame <= 50)
				startGame++;
			if (Keyboard::isKeyPressed(Keyboard::Space))
				isShot = true;
			if (Mouse::isButtonPressed(Mouse::Left)&& startGame>=50)
				isShot = true;
			if (!isShot) {
				ball.setPosition(Mouse::getPosition(window).x, ball.getPosition().y);    // moving ball with mouse
				Cannon.setPosition(ball.getPosition().x - 28, ball.getPosition().y - 50);
			}
			else
				ball.move(0.f, -5.f);

			//	Coilision  and reset position of ball
			if (ball.getPosition().y < 65) {
				Life--;
				ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 6);
				isShot = false;
				if (Life <= 0) {
					gameOver = true;
				}
			}
			//	Coilision  and reset position of ball
			if (ball.getGlobalBounds().intersects(hoop.getGlobalBounds())) {
				score += 10;
				ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 6);
				isShot = false;
			}

			// Update Score and life
			Score.setString("Score: \n" + std::to_string(score));
			lifeBar.setSize(Vector2f(50.f, 50.f * Life));
			lifeBar.setFillColor(Life > 1 ? Color::Green : Color::Red);

			window.clear(Color::White);
			window.draw(background);
			window.draw(Score);
			window.draw(highScoreText);
			window.draw(lifeBar);
			window.draw(hoop);
			window.draw(ball);
			window.draw(Cannon);
			window.display();
		}
		else {
			window.clear(Color::White);
			window.draw(background);
			// Check Heigh Score
			if (score >= highScore) {
				highScore = score;
				SetHighScoreShootBall(score);
				highScoreText.setString("High Score : " + std::to_string(highScore));
				newScore.setString("New High Score: \n   " + std::to_string(score));
				GameOver.setPosition(175.f, 50.f);
				window.draw(newScore);
			}
			else
				GameOver.setPosition(175.f, 200.f);
			window.draw(highScoreText);
			window.draw(Score);
			window.draw(GameOver);
			window.display();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			gameOver = false;
			score = 0;
			Life = 2;
		}
	}
}

/**************************************************************************************************************/
/* Game - 02*/

int GetHighScoreSikhAttacks() {
	if (!std::filesystem::exists("SikhAttacks.txt")) {
		return 0;
	}
	int Score;
	std::ifstream read("SikhAttacks.txt");
	read >> Score;
	read.close();
	return Score;
}

void SetHighScoreSikhAttacks(int Score) {
	std::ofstream write("SikhAttacks.txt");
	write << Score;
	write.close();
}


class Bullet02{
public:

	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;

	Bullet02(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Red);
	}
};

void SikhAttacks(RenderWindow& window) {

	srand(time(NULL));
	window.setFramerateLimit(40);


	/* Background */
	Texture bgtex;
	Sprite background;
	if (!bgtex.loadFromFile("Textures/bg-2.png"))
		throw "No background image load";
	background.setTexture(bgtex);
	background.setScale(1.1f, 1.12f);

	// Font
	Font font;
	if (!font.loadFromFile("Fonts/HARNGTON.TTF"))
		throw "Not able to load Font!";
	Font font2;
	if (!font2.loadFromFile("Fonts/CascadiaCode.ttf"))
		throw "Not able to load Font!";

	// Score and Health
	Text Score, Health;
	int score = 00;
	Score.setFont(font);
	Score.setPosition(10.f, 100.f);
	Score.setFillColor(Color::Black);
	Score.setCharacterSize(60);
	int Hp = 3;
	Health.setFont(font);
	Health.setPosition(10.f, 300.f);
	Health.setFillColor(Color::Green);
	Health.setCharacterSize(60);

	// High Score
	int highScore = GetHighScoreSikhAttacks();
	Text highScoreText;
	highScoreText.setFont(font2);
	highScoreText.setCharacterSize(50.f);
	highScoreText.setPosition(500.f, -5.f);
	highScoreText.setFillColor(Color::Yellow);
	highScoreText.setString("High Score : " + std::to_string(highScore));

	// New Score
	Text newScore;
	newScore.Bold;
	newScore.setFont(font2);
	newScore.setCharacterSize(120.f);
	newScore.setFillColor(Color::White);
	newScore.setPosition(Vector2f(290.f, 320.f));

	// GameOver
	Text GameOver;
	bool gameOver = false;
	GameOver.setFont(font2);
	GameOver.setString("Game Over!");
	GameOver.setCharacterSize(180.f);
	GameOver.setPosition(280.f, 200.f);
	GameOver.setFillColor(Color::Red);

	/* Player information:- */
	Texture playerTex;
	if (!playerTex.loadFromFile("Textures/ak-47.png"))
		throw "Not able to load file";
	Sprite player(playerTex);
	player.setScale(0.3f, 0.3f);
	player.setPosition(400.f, 400.f);

	// Bullets:
	Bullet02 b1;
	std::vector<Bullet02> bullets;

	//Sounds
	SoundBuffer buffer;
	if (!buffer.loadFromFile("Sounds/akm.wav"))
		throw "no file of sound";
	Sound shootSound;
	shootSound.setBuffer(buffer);
	int soundTimmer = 100;

	// Enemy :
	Texture enemyTex1;
	Texture enemyTex2;
	if (!enemyTex1.loadFromFile("Textures/Enemy-1.png"))
		throw "Not able to load file";
	if (!enemyTex2.loadFromFile("Textures/Enemy-2.png"))
		throw "Not able to load file";
	Sprite enemy1(enemyTex1);
	Sprite enemy2(enemyTex2);
	enemy1.setScale(0.5, 0.5);
	enemy2.setScale(0.5, 0.5);
	int spawnCounter = 20;
	std::vector<Sprite> enemies;
	Vector2f emempyPosition;
	bool SpawnChangeEnemy = true;

	/* vector: */
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	while (true) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		// Close program
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			break;
		}
		if (!gameOver) {
			// Game Over
			if (Hp < 0) {
				gameOver = true;
			}

			//Update
			/*Vector*/
			playerCenter = Vector2f(player.getPosition().x + player.getGlobalBounds().width / 2, player.getPosition().y + player.getGlobalBounds().height / 2);
			mousePosWindow = Vector2f(Mouse::getPosition(window));
			aimDir = mousePosWindow - playerCenter;
			aimDirNorm = Vector2f(aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)), aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

			/* Player */
			if ((Keyboard::isKeyPressed(Keyboard::Up)|| Keyboard::isKeyPressed(Keyboard::W))&& player.getPosition().y > 80)
				player.move(0.f, -10.f);
			if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && player.getPosition().y < 620)
				player.move(0.f, 10.f);
			if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && player.getPosition().x < 1250)
				player.move(10.f, 0.f);
			if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && player.getPosition().x > 230)
				player.move(-10.f, 0.f);

			/* Enemies: */
			if (spawnCounter < 20)
				spawnCounter++;
			if (spawnCounter >= 20 && enemies.size() < 20) {
				emempyPosition = Vector2f((rand() % int(window.getSize().x - 340.f)) + 230.f, (rand() % int(window.getSize().y - 255.f)) + 75.f);
				if (SpawnChangeEnemy) {
					enemy1.setPosition(emempyPosition);
					enemies.push_back(Sprite(enemy1));
					SpawnChangeEnemy = false;
				}
				else {
					enemy2.setPosition(emempyPosition);
					enemies.push_back(Sprite(enemy2));
					SpawnChangeEnemy = true;
				}
				spawnCounter = 0;
			}
			// SoundTimmer
			if (soundTimmer <= 20)
				soundTimmer++;

			// Shooting
			if (Keyboard::isKeyPressed(Keyboard::Space)||Mouse::isButtonPressed(Mouse::Left)) {
				b1.shape.setPosition(playerCenter);
				b1.currVelocity = aimDirNorm * b1.maxSpeed;
				bullets.push_back(b1);
				if (soundTimmer >= 20) {
					shootSound.play();
					soundTimmer = 0;
				}
			}

			for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i].shape.move(bullets[i].currVelocity);

				if (bullets[i].shape.getPosition().x<230 || bullets[i].shape.getPosition().x > window.getSize().x - 45
					|| bullets[i].shape.getPosition().y < 75 || bullets[i].shape.getPosition().y > window.getSize().y - 77) {
					bullets.erase(bullets.begin() + i);

				}
				else {
					// Enemy Collision
					for (int j = 0; j < enemies.size(); j++)
					{
						if (bullets[i].shape.getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
							bullets.erase(bullets.begin() + i);
							enemies.erase(enemies.begin() + j);
							score += 1;
							break;
						}
					}
				}
			}
			// Enemy Touch
			for (int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
					Hp--;
					enemies.erase(enemies.begin() + i);
					break;
				}
			}

			Score.setString("Score :\n" + std::to_string(score));
			Health.setString("Health:\n" + std::to_string(Hp+1) + "/ 10");

			//Draw
			window.clear(Color::White);
			window.draw(background);

			for (int i = 0; i < enemies.size(); i++)
			{
				window.draw(enemies[i]);
			}

			for (int i = 0; i < bullets.size(); i++)
			{
				window.draw(bullets[i].shape);
			}
			window.draw(player);
			window.draw(Health);
			window.draw(Score);
			window.draw(highScoreText);
			window.display();
		}
		else
		{
			window.clear(Color::White);
			window.draw(background);
			// Check Score for High Score
			if (score >= highScore) {
				highScore = score;
				SetHighScoreSikhAttacks(score);
				highScoreText.setString("High Score : " + std::to_string(highScore));
				newScore.setString("New High Score: \n   " + std::to_string(score));
				GameOver.setPosition(280.f, 100.f);
				window.draw(newScore);
			}
			else
				GameOver.setPosition(280.f, 200.f);
			window.draw(Score);
			window.draw(Health);
			window.draw(highScoreText);
			window.draw(GameOver);
			window.display();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			gameOver = false;
			score = 0;
			Hp = 3;
		}
	}
}

/**************************************************************************************************************/
/* 3rd Game :*/
class Bullet {
public:
	Sprite bullet;
	Texture* texture;

	Bullet(Texture* texture, Vector2f pos) {
		this->bullet.setTexture(*texture);
		this->bullet.setScale(0.05f, 0.05f);
		this->bullet.setPosition(pos.x + 60.f, pos.y + 42.f);
	}

	~Bullet() {}
};

// read high Score from file
int GetHighScoreSpaceWar() {
	if (!std::filesystem::exists("spaceWar.txt")) {
		return 0;
	}
	int Score;
	std::ifstream file("spaceWar.txt");
	file >> Score;
	file.close();
	return Score;
}

// writing high score in file
void SetHighScoreSpaceWar(int Score) {
	std::ofstream file("spaceWar.txt");
	file << Score;
	file.close();
}

class Player {
public:
	Sprite shape;
	Texture* texture;
	RectangleShape HpBar;
	int Hp;
	int HpMax;

	std::vector<Bullet> bullets;

	Player(Texture* texture) {
		this->HpMax = 3;
		this->Hp = this->HpMax;
		this->texture = texture;
		this->shape.setTexture(*texture);
		this->shape.setScale(0.2f, 0.2f);
		this->HpBar.setPosition(40.f, 150.f);
	}
	~Player() {}
};

class Enemy {
public:
	int Hp;
	int HpMax;
	Sprite shape;
	Texture* texture;
	Enemy(Texture* texture, Vector2u windowSize) {
		this->HpMax = rand() % 3 + 1;
		this->Hp = this->HpMax;
		this->shape.setTexture(*texture);
		this->shape.setScale(0.3f, 0.3f);
		this->shape.setPosition(windowSize.x - 100, rand() % int(windowSize.y - this->shape.getGlobalBounds().height - 259) + 85);
	}
	~Enemy() {}
};

void SpaceWar(RenderWindow& window)
{
	/* Start Space war */
	srand(time(NULL));
	bool GamePause = false;
	int gameStart = 0;

	window.setFramerateLimit(40);

	/* Background */
	Texture bgtex;
	Sprite background;
	if (!bgtex.loadFromFile("Textures/bg-3.png"))
		throw "No background image load";
	background.setTexture(bgtex);
	background.setScale(1.1f, 1.12f);

	Texture bgtex2;
	Sprite background2;
	if (!bgtex2.loadFromFile("Textures/bg-3-2.png"))
		throw "No background image load";
	background2.setTexture(bgtex2);
	background2.setScale(1.1f, 1.12f);

	// Init Text
	Font font, font2;
	font.loadFromFile("Fonts/CascadiaCode.ttf");
	font2.loadFromFile("Fonts/HARNGTON.TTF");

	// Init Texture
	Texture playerTex;
	playerTex.loadFromFile("Textures/ship.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Textures/enemy.png");

	Texture bullteTex;
	bullteTex.loadFromFile("Textures/missile.png");

	// Player init		corner : 185.f, 85.f
	Player player(&playerTex);
	player.shape.setPosition(185.f, 385.f);
	int shootTimmer = 20;
	Text hpText;
	hpText.Bold;
	hpText.setFont(font2);
	hpText.setFillColor(Color::Green);
	hpText.setCharacterSize(50.f);
	hpText.setPosition(15.f, 80.f);
	hpText.setString("Health:");

	// High Score
	int highScore;
	highScore = GetHighScoreSpaceWar();
	Text HighScore;
	HighScore.setFont(font);
	HighScore.setFillColor(Color::White);
	HighScore.setCharacterSize(50.f);
	HighScore.setPosition(Vector2f(800.f, 5.f));
	HighScore.setString("High Score : " + std::to_string(highScore));

	// Score 
	int score = 0;
	Text Score;
	Score.setFont(font2);
	Score.setCharacterSize(60.f);
	Score.setFillColor(Color::Blue);
	Score.setPosition(Vector2f(200.f, 0.f));

	// Game Over
	Text GameOver;
	bool gameOver = false;
	GameOver.setFont(font2);
	GameOver.setString("Game Over!!");
	GameOver.setCharacterSize(200.f);
	GameOver.setFillColor(Color::Red);
	GameOver.Bold;

	// New Score
	Text newScore;
	newScore.Bold;
	newScore.setFont(font);
	newScore.setCharacterSize(135.f);
	newScore.setFillColor(Color::White);
	newScore.setPosition(Vector2f(200.f, 320.f));

	// Enemy init
	std::vector<Enemy> enemies;
	int spawnTimmer = 0;
	RectangleShape hpShape;
	hpShape.setFillColor(Color::Green);

	while (true) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
				if (player.Hp <= 0) {
					player.Hp = 3;
					score = 0;
					player.shape.setPosition(185.f, 385.f);
					gameOver = false;
					window.clear();
				}
				else if (GamePause)
					GamePause = false;
				else
					GamePause = true;
			}
		}
		// exit from game
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			break;
		}
		if (GamePause) {
			window.clear(Color::White);
			window.draw(background);
			window.draw(player.shape);
			for (int i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].bullet);
			}
			for (int i = 0; i < enemies.size(); i++)
			{
				window.draw(enemies[i].shape);
				hpShape.setSize(Vector2f((enemies[i].Hp + 1) * 20.f, 10.f));
				hpShape.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y + 20);
				window.draw(hpShape);
			}
			window.draw(hpText);
			window.draw(Score);
			window.draw(HighScore);
			window.draw(player.HpBar);
		}
		else if (!gameOver) {
			//Update

			// Player movement
			if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && player.shape.getPosition().y > 85)
				player.shape.move(0.f, -10.f);
			if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && player.shape.getPosition().y < window.getSize().y - 174)
				player.shape.move(0.f, 10.f);
			if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && player.shape.getPosition().x < window.getSize().x - 105)
				player.shape.move(10.f, 0.f);
			if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && player.shape.getPosition().x > 185)
				player.shape.move(-10.f, 0.f);
			if (gameStart <= 50)
				gameStart++;

			// Bullets
			if (shootTimmer <= 3)
				shootTimmer++;
			if (((Keyboard::isKeyPressed(Keyboard::Space) ||( Mouse::isButtonPressed(Mouse::Left))) && shootTimmer > 3) && gameStart >= 50) {
				player.bullets.push_back(Bullet(&bullteTex, player.shape.getPosition()));
				shootTimmer = 0;
			}
			for (int i = 0; i < player.bullets.size(); i++)
			{
				player.bullets[i].bullet.move(10.f, 0.f);
				if (player.bullets[i].bullet.getPosition().x >= window.getSize().x - 45) {
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}
				for (int k = 0; k < enemies.size(); k++)
				{
					if (player.bullets[i].bullet.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds())) {
						player.bullets.erase(player.bullets.begin() + i);
						if (enemies[k].Hp <= 0) {
							score += enemies[k].HpMax;
							enemies.erase(enemies.begin() + k);
							break;
						}
						else
							enemies[k].Hp--; // Damage to Enemy
						break;
					}
				}
			}
			// Enemy
			if (spawnTimmer < 15)
				spawnTimmer++;
			if (enemies.size() <= 50 && spawnTimmer >= 15) {
				enemies.push_back(Enemy(&enemyTex, window.getSize()));
				spawnTimmer = 0;
			}
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i].shape.move(-5.f, 0.f);
				if (enemies[i].shape.getPosition().x < 185) {
					enemies.erase(enemies.begin() + i);
					break;
				}
				if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
					enemies.erase(enemies.begin() + i);
					player.Hp--; // Damage to player
					if (player.Hp <= 0)
						gameOver = true;
					break;
				}
			}
			// Score
			Score.setString("Score : " + std::to_string(score));

			// Player HpBar
			player.HpBar.setSize(Vector2f(50.f, 50.f * player.Hp));
			player.HpBar.setFillColor(player.Hp <= 2 ? Color::Red : Color::Green);

			window.clear(Color::White);
			// Draw
			window.draw(background);
			// Player
			window.draw(player.shape);
			//vBullets
			for (int i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].bullet);
			}
			// Enemy
			for (int i = 0; i < enemies.size(); i++)
			{
				window.draw(enemies[i].shape);
				hpShape.setSize(Vector2f((enemies[i].Hp + 1) * 20.f, 10.f));
				hpShape.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y + 20);
				window.draw(hpShape);
			}
			window.draw(hpText);
			window.draw(Score);
			window.draw(HighScore);
			window.draw(player.HpBar);
		}
		else 
		{
			window.clear();
			// removing all enemimes ans bullets
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies.erase(enemies.begin() + i);
			}
			for (int i = 0; i < player.bullets.size(); i++)
			{
				player.bullets.erase(player.bullets.begin() + i);
			}
			window.draw(background2);
			if (score >= highScore) {
				SetHighScoreSpaceWar(score);
				highScore = score;
				HighScore.setString("High Score : " + std::to_string(highScore));
				newScore.setString("New High Score: \n   " + std::to_string(score));
				GameOver.setPosition(280.f, 100.f);
				window.draw(newScore);
			}
			else
				GameOver.setPosition(Vector2f(250.f, 200.f));
			window.draw(Score);
			window.draw(GameOver);
			window.draw(HighScore);
		}
		window.display();
	}
}

/**************************************************************************************************************/
/* 4th Game :*/

// High Score write and read from file
int GetHighScoreFlappyBird() {
	if (!std::filesystem::exists("FlappyBird.txt")) {
		return 0;
	}
	int Score;
	std::ifstream read("FlappyBird.txt");
	read >> Score;
	read.close();
	return Score;
}

void SetHighScoreFlappyBird(int Score) {
	std::ofstream write("FlappyBird.txt");
	write << Score;
	write.close();
}

// Making piller for game
class Pipe {
public:
	Texture pipTex1;
	Texture pipTex2;
	Sprite shape;
	Sprite shape2;

	Pipe() {
		pipTex1.loadFromFile("Textures/pipe-1.png");
		pipTex2.loadFromFile("Textures/pipe-2.png");

		this->shape.setTexture(pipTex1);
		this->shape.setOrigin(0.f, this->shape.getGlobalBounds().height);
		this->shape.setPosition(1400.f, 300.f);

		this->shape2.setTexture(pipTex2);
		this->shape2.setPosition(1400.f, this->shape.getPosition().y + 200);
	}
};
/* Game Starts*/
void FlappyBird(RenderWindow& window) {
	/* Background */
	Texture bgtex;
	Sprite background;
	if (!bgtex.loadFromFile("Textures/bg-4.png"))
		throw "No background image load";
	background.setTexture(bgtex);
	background.setScale(1.1f, 1.12f);

	/* path Movement Top*/
	RectangleShape top;
	top.setSize(Vector2f(1220.f, 90.f));
	top.setFillColor(Color::Black);
	top.setPosition(Vector2f(190.f, 0.f));

	/* path Movement Bottom */
	RectangleShape path;
	path.setSize(Vector2f(1220.f, 50.f));
	path.setFillColor(Color::Black);
	path.setPosition(Vector2f(190.f, 750.f));

	/* moving paint on Bottom Path */
	RectangleShape block;
	block.setSize(Vector2f(60.f, 50.f));
	block.setFillColor(Color::White);
	block.setPosition(Vector2f(1400.f, 750.f));
	int blockSpawnTimmer = 30;
	std::vector<RectangleShape> activePath;


	/* Bird actions image loading */
	Texture action1;
	action1.loadFromFile("Textures/bird-1.png");
	Texture action2;
	action2.loadFromFile("Textures/bird-2.png");
	Texture action3;
	action3.loadFromFile("Textures/bird-3.png");

	Sprite bird;
	bird.setTexture(action1);
	bird.setScale(Vector2f(0.1f, 0.1f));

	Sprite bird2;
	bird2.setTexture(action2);
	bird2.setScale(Vector2f(0.1f, 0.1f));

	Sprite bird3;
	bird3.setTexture(action3);
	bird3.setScale(Vector2f(0.1f, 0.1f));

	// Bird details
	std::vector<Sprite> Bird;
	Bird.push_back(bird);
	Bird.push_back(bird2);
	Bird.push_back(bird3);
	int changeTimmer = 10;
	int changeAction = 0;
	// actual rectangle bird :)
	RectangleShape centerBird;
	centerBird.setSize(Vector2f(50.f, 38.f));
	centerBird.setFillColor(Color::Transparent);
	centerBird.setOrigin(Vector2f(-5.f, -3.f));
	centerBird.setPosition(Vector2f(400.f, 500.f));

	// Font
	Font font;
	if (!font.loadFromFile("Fonts/HARNGTON.TTF"))
		throw "Not able to load Font!";
	Font font2;
	if (!font2.loadFromFile("Fonts/CascadiaCode.ttf"))
		throw "Not able to load Font!";

	/* Score */
	Text scoreText;
	int score = 0;
	scoreText.setFont(font2);
	scoreText.setPosition(0.f, 300.f);
	scoreText.setFillColor(Color::Yellow);
	scoreText.setCharacterSize(50);

	/* High Score */
	Text highScoreText;
	int highScore = GetHighScoreFlappyBird();
	highScoreText.setFont(font);
	highScoreText.setPosition(600.f, 0.f);
	highScoreText.setFillColor(Color::White);
	highScoreText.setCharacterSize(70);
	highScoreText.setString("High Score: " + std::to_string(highScore));

	/* Pillers details */
	Pipe pillar;
	Vector2f pipPos;
	int pillarNumber = 5;
	int ptime = 170;
	int pillarSpawnTimmer = ptime;
	std::vector<Pipe> pillars;

	/* Game Over and Pause */
	bool gamePause = false;
	Text gameOverText;
	bool gameOver = false;
	gameOverText.setFont(font);
	gameOverText.setString("Game Over!!");
	gameOverText.setCharacterSize(200.f);
	gameOverText.setFillColor(Color::Red);
	gameOverText.Bold;

	// New Score
	Text newScore;
	newScore.Bold;
	newScore.setFont(font2);
	newScore.setCharacterSize(135.f);
	newScore.setFillColor(Color(255, 215, 0));
	newScore.setPosition(Vector2f(210.f, 320.f));
	
	while (true) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			break;
		}
		/* Pause or Restart when game Over by press Enter */
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			if (gameOver) {
				for (int i = 0; i < pillars.size(); i++) {
					pillars.erase(pillars.begin() + i);
				}
				centerBird.setPosition(Vector2f(400.f, 500.f));
				gameOver = false;
				score = 0;
			}
			else if (gamePause)
				gamePause = false;
			else
				gamePause = true;
		}

		if (gamePause) {
			/* keep draw all elements on their loacation*/
			window.clear(Color::White);
			window.draw(background);
			for (int i = 0; i < pillars.size(); i++)
			{
				window.draw(pillars[i].shape);
				window.draw(pillars[i].shape2);
			}
			window.draw(centerBird);
			window.draw(Bird[changeAction]);
			window.draw(path);
			window.draw(top);
			for (int i = 0; i < activePath.size(); i++)
			{
				window.draw(activePath[i]);
			}
			window.draw(scoreText);
			window.draw(highScoreText);
		}
		else if (!gameOver) {
			// Update elements
			// setUp for change Bird Action
			if (changeTimmer <= 10)
				changeTimmer++;
			if (changeTimmer >= 10) {
				if (changeAction <= 1) {
					changeAction++;
				}
				else {
					changeAction = 0;
				}
				changeTimmer = 0;
			}
			// fly bird when pressed Space
			if (Keyboard::isKeyPressed(Keyboard::Space) && centerBird.getPosition().y > 80 && centerBird.getPosition().y < 670) {
				centerBird.move(0.f, -15.f);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && centerBird.getPosition().y > 80 && centerBird.getPosition().y < 670) {
				centerBird.move(0.f, -15.f);
			}
			// Gravity attracts Bird
			if (centerBird.getPosition().y < 660)
				centerBird.move(0.f, 5.f);

			// Show image on bird loaction with different actions
			Bird[changeAction].setPosition(centerBird.getPosition());

			// pillars setUp for Spawn
			if (pillarSpawnTimmer <= ptime)
				pillarSpawnTimmer++;
			if (pillarSpawnTimmer >= ptime) {
				pillars.push_back(pillar);
				pillars[pillars.size() - 1].shape.setPosition(1400.f, rand() % (window.getSize().y - 450) + 170);
				pipPos = pillars[pillars.size() - 1].shape.getPosition();
				pillars[pillars.size() - 1].shape2.setPosition(1400.f, pipPos.y + 200);
				pillarSpawnTimmer = 0;
			}
			for (int i = 0; i < pillars.size(); i++)
			{
				pillars[i].shape.move(-5.f, 0.f);
				pillars[i].shape2.move(-5.f, 0.f);

				if (centerBird.getGlobalBounds().intersects(pillars[i].shape.getGlobalBounds()) || centerBird.getGlobalBounds().intersects(pillars[i].shape2.getGlobalBounds())) {
					gameOver = true;
					break;
				}
				if (pillars[i].shape.getPosition().x < 200) {
					pillars.erase(pillars.begin() + i);
					score += 5;
					if (ptime >= 20)
						ptime -= 5;      // 8 for fast 
					break;
				}

			}
			// active Path
			if (blockSpawnTimmer <= 20)
				blockSpawnTimmer++;
			if (blockSpawnTimmer >= 20) {
				activePath.push_back(block);
				blockSpawnTimmer = 0;
			}
			for (int i = 0; i < activePath.size(); i++)
			{
				activePath[i].move(-5.f, 0.f);
				if (activePath[i].getPosition().x < 190) {
					activePath.erase(activePath.begin() + i);
				}
			}
			// Update Score
			scoreText.setString("Score:\n" + std::to_string(score));

			window.clear(Color::White);
			// Draw elements
			window.draw(background);


			for (int i = 0; i < pillars.size(); i++)
			{
				window.draw(pillars[i].shape);
				window.draw(pillars[i].shape2);
			}

			window.draw(centerBird);
			window.draw(Bird[changeAction]);

			window.draw(path);
			window.draw(top);
			for (int i = 0; i < activePath.size(); i++)
			{
				window.draw(activePath[i]);
			}

			window.draw(scoreText);
			window.draw(highScoreText);
		}
		else {

			window.clear();
			// removing all pillers
			window.draw(background);
			for (int i = 0; i < pillars.size(); i++)
			{
				window.draw(pillars[i].shape);
				window.draw(pillars[i].shape2);
			}
			window.draw(centerBird);
			window.draw(Bird[changeAction]);
			if (score >= highScore) {
				SetHighScoreFlappyBird(score);
				highScore = score;
				highScoreText.setString("High Score : " + std::to_string(highScore));
				newScore.setString("New High Score: \n   " + std::to_string(score));
				gameOverText.setPosition(280.f, 100.f);
				window.draw(newScore);
			}
			else
				gameOverText.setPosition(Vector2f(250.f, 200.f));
			window.draw(path);
			window.draw(top);
			for (int i = 0; i < activePath.size(); i++)
			{
				window.draw(activePath[i]);
			}
			window.draw(scoreText);
			window.draw(gameOverText);
			window.draw(highScoreText);
		}
		window.display();
	}
}