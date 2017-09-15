#pragma once
#include<queue>
#include "miwa.h"

class Core
{
private:
	sf::Event _events;
	uint32_t _fps = 60;
public:
	void changeFrameRate(uint32_t fps);
	sf::RenderWindow* _window;
	static miwa::GameRoom* currentRoomPointer;
	void initialise(sf::RenderWindow& window);
	Core();
	~Core();
	void loop();
};

class WeakPtrForQueue : public std::weak_ptr < miwa::Object >
{
public:
	bool operator<(const WeakPtrForQueue& e)
		const;

	WeakPtrForQueue(std::shared_ptr<miwa::Object>& obj);
};

class instanceQueue : public std::priority_queue<WeakPtrForQueue>
{
public:
	instanceQueue();

	~instanceQueue();

	decltype(c.begin()) begin();

	decltype(c.end()) end();

	decltype(*(c.begin()))& operator[](int n);

	decltype(c)& getVector();

	void pushd(std::shared_ptr<miwa::Object>& obj);
};