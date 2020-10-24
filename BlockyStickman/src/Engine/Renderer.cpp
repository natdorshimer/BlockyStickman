#include "blocky-pch.h"
#include "Renderer.h"

void Blocky::Renderer::Render(sf::Drawable& d)
{
	mainRenderWindow->draw(d);
}

void Blocky::Renderer::SetRenderer(sf::RenderWindow* m_Window)
{
	mainRenderWindow = m_Window;
}

sf::RenderWindow* Blocky::Renderer::GetRenderer()
{
	return mainRenderWindow;
}

bool Blocky::Renderer::isInWindow(sf::FloatRect bounds)
{
	auto viewCenter = GetRenderer()->getView().getCenter();
	auto viewSize = GetRenderer()->getView().getSize();

	sf::FloatRect viewRect(viewCenter - viewSize / 2.f, viewSize);

	return bounds.intersects(viewRect);

}
