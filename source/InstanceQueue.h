#pragma once

#include<queue>
#include "Object.h"
#include<memory>


class WeakPtrForQueue : public std::weak_ptr < charlotte::Object >
{
	public:
	bool operator<(const WeakPtrForQueue& e)
		const;

	WeakPtrForQueue(std::shared_ptr<charlotte::Object>& obj);
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

	void pushd(std::shared_ptr<charlotte::Object>& obj);
};