// SFMLHelloWorld.cpp : Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include"miwa.h"
#include<iostream>
#include<experimental\filesystem>
#include"assetDB.h"
#include"Box2D.h"

using namespace miwa;

ResContainer data;
auto SCALE = 30.f;

b2World* WorldPtr = nullptr;

class MyListerner : public b2ContactListener
{
public:
	MyListerner()
	{
		
	}

	void BeginContact()
	{

	}

	void EndContact()
	{

	}
};

b2Body* CreateBox(b2World& World, int MouseX, int MouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((32.f/1.5)/SCALE, (32.f/1.5)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	return Body;
}


b2Body* CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2.f) / SCALE, (16.f / 2.f) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	return Body;
}

class Floor : public miwa::Object
{
public:
	b2Body* ptr = nullptr;
	Floor()
	{
		ptr = CreateGround(*WorldPtr, 400.f, 500.f);
		this->render = [this]()
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(800.0f, 16.f / 2.f));
			rectangle.setOutlineColor(sf::Color::White);
			rectangle.setOutlineThickness(5);
			rectangle.setPosition(ptr->GetPosition().x * SCALE, ptr->GetPosition().y * SCALE);
			rectangle.setRotation((180 / b2_pi * ptr->GetAngle()));
			rectangle.setOrigin(sf::Vector2f(400.f, rectangle.getSize().y / 2.0f));
			draw(rectangle);
		};
	}
	~Floor()
	{
		WorldPtr->DestroyBody(ptr);
	}
};



class Quad : public miwa::Object
{
public:
	sf::Color color = sf::Color::White;
	size_t ticks = 0;
	b2Body* ptr = nullptr;
	bool destroy = false;
	Quad()
	{
		ptr = CreateBox(*WorldPtr, sf::Mouse::getPosition(miwa::getWindow()).x, sf::Mouse::getPosition(miwa::getWindow()).y);
		size_t ticksMax = rand() % 100;
		priority = -1;
		render = [this, ticksMax]()
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(32.0f, 32.0f));
			if (ticks < ticksMax)
			{
				ticks++;
			}
			else {
				color = sf::Color::Red;
				if (destroy)
				{
					miwa::loop::destroyObject(this);
				}
				destroy = true;
			}
			rectangle.setOutlineColor(color);
			rectangle.setFillColor(color);
			rectangle.setOutlineThickness(5);
			rectangle.setPosition(SCALE * ptr->GetPosition().x, ptr->GetPosition().y * SCALE);
			rectangle.rotate((180 / b2_pi * ptr->GetAngle()));
			rectangle.setOrigin(sf::Vector2f(16.0, 16.0));
			draw(rectangle);
		};
	}
	~Quad()
	{
		WorldPtr->DestroyBody(ptr);
	}
};

class Controller : public miwa::Object
{
public:
	Controller()
	{
		update = []()
		{
			WorldPtr->Step(2.f/60.f, 8, 3);
			if (input::Keyboard::getKeyState(sf::Keyboard::Key::R) == input::Keyboard::KeyStates::Pressed)
			{
				data.getRoom("r0").execute(60);
			}	
			if (input::Keyboard::getKeyState(sf::Keyboard::Key::X) == input::Keyboard::KeyStates::Pressed)
			{	
				makeObject<Quad>();
			}	
		};
		render = [this]()
		{
			makeObject<Quad>();
		};
	}
	~Controller()
	{
		
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Xab");
	initialise(window);
	b2World World(b2Vec2(0.f, 9.8f));
	WorldPtr = &World;
	auto& it = data.makeRoom("r0", [&World]()
	{
		auto& controller = miwa::makeObject<Controller>();
		miwa::makeObject<Floor>();
	});
	it.changeBackgroundColor(sf::Color(45, 0, 25, 255));
	it.execute(60);
	loop::startLoop();
	return 0;
}