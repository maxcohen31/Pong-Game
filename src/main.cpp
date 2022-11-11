#include "raylib.h"

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;


struct Paddle
{
	float x_coord;// Paddle x coordinate
	float y_coord; // Paddle y coordinate
	float width; 
	float height;
	float speed; 
	unsigned int paddle_score;

	
	Rectangle GetRect()
	{
		return Rectangle{ x_coord - width / 2, y_coord - height / 2, 15, 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), GREEN);
	}

};

struct Ball
{	
	float x_coord; // Ball x coordinate
	float y_coord; // Ball y coordinate
	float radius;
	float ball_speedX; // Ball x axis speed
	float ball_speedY; // Ball y axis speed
};

int main ()
{	

	// Trigger the game
	bool start_game;

	// Winner text
	const char* winner = nullptr;

	// Object paddle1 - left paddle
	Paddle paddle1;
	paddle1.x_coord = 50;
	paddle1.y_coord = WINDOW_HEIGHT / 2;
	paddle1.width = 15;
	paddle1.height = 100;
	paddle1.speed = 600;
	paddle1.paddle_score = 0;

	// Object paddle2 - Right paddle 
	Paddle paddle2;
	paddle2.x_coord = WINDOW_WIDTH - 50;
	paddle2.y_coord = WINDOW_HEIGHT / 2;
	paddle2.width = 15;
	paddle2.height = 100;
	paddle2.speed = 600;
	paddle2.paddle_score = 0;

	// Object ball
	Ball ball;
	ball.x_coord = WINDOW_WIDTH / 2.0f;
	ball.y_coord = WINDOW_HEIGHT / 2.0f;
	ball.radius = 8;
	ball.ball_speedX = 300.0f;
	ball.ball_speedY = 300.0f;

	// Set up the windows
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
	SetTargetFPS(60); // Set FPS
	
	// game loop
	while (!WindowShouldClose())
	{	
		
		if(!start_game)
		{
			DrawText("Press <enter> to play", WINDOW_HEIGHT / 2 - 110, WINDOW_WIDTH / 2 - 200, 50, BLUE);
			DrawText("Press <Q> to quit", WINDOW_HEIGHT / 2 - 50, WINDOW_WIDTH / 2 - 150, 50, BLUE);
			DrawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, WHITE);

			if(IsKeyPressed(KEY_ENTER))
			{
				// Moving the ball
				ball.x_coord += ball.ball_speedX * GetFrameTime();
				ball.y_coord += ball.ball_speedY * GetFrameTime();	
				start_game = true;

			}
			else if(IsKeyPressed(KEY_Q))
			{
				SetExitKey(KEY_Q); // Close window 
			}
		}

		// Ball movements
		else
		{	
			DrawCircle(ball.x_coord, ball.y_coord, ball.radius, GREEN); 
			ball.x_coord += ball.ball_speedX * GetFrameTime(); 
			ball.y_coord += ball.ball_speedY * GetFrameTime();

			if(ball.y_coord < 0) // Check lower limit
			{
				ball.y_coord = 0;
				ball.ball_speedY *= -1;
			}
			if(ball.y_coord > WINDOW_HEIGHT) // Check uppper limit
			{
				ball.y_coord = WINDOW_HEIGHT;
				ball.ball_speedY *= -1;
			}
			if(ball.x_coord < 0) // Check left limit
			{
				winner = "Player 2 wins!";
			}
			if(ball.x_coord > WINDOW_WIDTH) // Check right limit
			{
				winner = "Player 1 wins!";
			}

			// Collision left paddle - ball 
			if(CheckCollisionCircleRec(Vector2{ ball.x_coord, ball.y_coord }, ball.radius, paddle1.GetRect()))
			{
				if(ball.ball_speedX < 0)
				{	
					ball.ball_speedX *= -1.1f;
				}
			}

			// Collision left paddle - ball 
			if(CheckCollisionCircleRec(Vector2{ ball.x_coord, ball.y_coord }, ball.radius, paddle2.GetRect()))
			{
				if(ball.ball_speedX > 0)
				{	
					ball.ball_speedX *= -1.1f;
				}
			}
			
			// Paddles control 
			if(IsKeyDown(KEY_DOWN) && paddle2.y_coord < (WINDOW_HEIGHT - (paddle2.height / 2.0)))
			{	
				paddle2.y_coord += paddle2.speed * GetFrameTime(); // Move right paddle down		
			}
			if(IsKeyDown(KEY_UP) && paddle2.y_coord > (paddle2.height / 2.0))
			{
				paddle2.y_coord -= paddle2.speed * GetFrameTime(); // Move right paddle up
			}
			if(IsKeyDown(KEY_W) && paddle1.y_coord > (paddle1.height / 2.0))
			{
				paddle1.y_coord -= paddle1.speed * GetFrameTime(); // Move left paddle up
			}
			if(IsKeyDown(KEY_S) && paddle1.y_coord < (WINDOW_HEIGHT -  (paddle1.height / 2.0)))
			{
				paddle1.y_coord += paddle1.speed * GetFrameTime(); // Move left paddle down
			}
			
			// Check winner
			if(winner && IsKeyPressed(KEY_ENTER))
			{	
				if(ball.x_coord < 0)
				{
					paddle2.paddle_score++;
				}
				if(ball.x_coord > WINDOW_WIDTH)
				{
					paddle1.paddle_score++;
				}

				// Reset ball settings
				ball.x_coord = WINDOW_WIDTH / 2.0f;
				ball.y_coord = 0;
				ball.ball_speedX = 300.0f;
				ball.ball_speedY= 300.0f;
				winner = nullptr;

			}
			if(winner)
			{
				DrawText(winner, (WINDOW_WIDTH / 2.0) - 170, (WINDOW_HEIGHT / 2.0), 50, YELLOW);
			}
		}	

		// drawing
		BeginDrawing();

		paddle1.Draw();
		paddle2.Draw();
		DrawText(TextFormat("%i", paddle1.paddle_score), (WINDOW_WIDTH / 2) - 200, 25, 30, YELLOW);
		DrawText(TextFormat("%i", paddle2.paddle_score), (WINDOW_WIDTH / 2) + 200, 25, 30, YELLOW);
		DrawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, WHITE);

		ClearBackground(BLACK);
		
		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;

}
