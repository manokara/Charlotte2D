
#include "stdafx.h"
#include "InstanceQueue.h"

bool WeakPtrForQueue::operator<(const WeakPtrForQueue& e)
	const
{
	return e.lock().get()->priority < lock().get()->priority;
}

WeakPtrForQueue::WeakPtrForQueue(std::shared_ptr<charlotte::Object>& obj) : weak_ptr(obj)
{

}

instanceQueue::instanceQueue()
{

}

instanceQueue::~instanceQueue()
{

}

std::vector<WeakPtrForQueue>::iterator instanceQueue::begin()
{
	return c.begin();
}
std::vector<WeakPtrForQueue>::iterator instanceQueue::end()
{
	return c.end();
}

std::vector<WeakPtrForQueue>& instanceQueue::getVector()
{
	return c;
}

WeakPtrForQueue& instanceQueue::operator[](int n)
{
	return *(c.begin() + n);
}

void instanceQueue::pushd(std::shared_ptr<charlotte::Object>& obj)
{
	push(WeakPtrForQueue(obj));
}
