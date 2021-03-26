#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);

    Texture t1, t3, t4;
    t1.loadFromFile("resources/block01.png");
    t3.loadFromFile("resources/ball.png");
    t4.loadFromFile("resources/paddle.png");

    Sprite sBall(t3), sPaddle(t4);
    sPaddle.setPosition(300, 440);

    Sprite block[1000];

    int n = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            block[n].setTexture(t1);
            block[n].setPosition(i * 43, j * 20);
            n++;
        }

    float dx = 4, dy = 3;
    float x = 300, y = 300;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        x += dx;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0); dx = -dx;
            }

        y += dy;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0); dy = -dy;
            }

        if (x < 0 || x>520)  dx = -dx;
        //option 1 (ball doesn't stop):
        //if (y < 0 || y>450)  dy = -dy;

        //option2  - Press Space to release the ball (delete/comment option1):
        if (y < 0)  dy = -dy;
        if (y>450)
        {
        dx = 0, dy = 0;
        x = 300, y = 300;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) dx = 4, dy = 3;
        //until here

        if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
        if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

        sBall.setPosition(x, y);

        app.clear(Color::Black);
        app.draw(sBall);
        app.draw(sPaddle);

        for (int i = 0; i < n; i++)
            app.draw(block[i]);

        app.display();
    }

    return 0;
}
