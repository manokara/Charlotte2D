#pragma once

#include<SFML/Graphics.hpp>
/*
namespace charlotte 
{
	class DrawableWrapper : public sf::Drawable
	{
	protected:
		std::reference_wrapper<charlotte::DrawableWrapper> m_drawable;
	public:
		charlotte::DrawableWrapper& getDrawable() const;
		void setDrawable(charlotte::DrawableWrapper&);
	};
	void DrawableWrapper::setDrawable(charlotte::DrawableWrapper& drawable)
	{
		this->m_drawable = std::ref(drawable);
	}
	charlotte::DrawableWrapper& DrawableWrapper::getDrawable() const
	{
		return this->m_drawable;
	}
	typedef DrawableWrapper Drawable;
}*/