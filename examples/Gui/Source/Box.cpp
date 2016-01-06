#include "Box.h"

Box::Box() :
	m_texture(ResourceManager::get<Texture2D>("Button.png")),
	m_textureHover(ResourceManager::get<Texture2D>("Hover.png")),
	m_textureActive(ResourceManager::get<Texture2D>("Active.png")),
	m_font(ResourceManager::get<Font>("Font.fnt")),
	m_text("Button")
{
	m_font->setColor(Color(0, 0, 0, 255));
}

void Box::onClick(ClickEvent *e)
{
	switch(e->getType())
	{
		case ClickEvent::DONE:
			LOG("Clicked!");
			break;

		case ClickEvent::BEGIN:
			LOG("Click Begin");
			break;

		case ClickEvent::CANCELED:
			LOG("Click Canceled");
			break;
	}

	UiObject::onClick(e);
}

void Box::onDraw(DrawEvent *e)
{
	Rect rect = getRect();
	GraphicsContext *g = e->getGraphicsContext();
	if(isPressed() && isHovered())
	{
		g->setTexture(m_textureActive);
	}
	else if(isHovered())
	{
		g->setTexture(m_textureHover);
	}
	else
	{
		g->setTexture(m_texture);
	}
	
	g->drawRectangle(rect.position, Vector2(16.0f), Color(255), TextureRegion(0.0f, 0.0f, 1.0f / 3.0f, 1.0f / 3.0f));
	g->drawRectangle(rect.position.x + rect.size.x - 16.0f, rect.position.y, 16.0f, 16.0f, Color(255), TextureRegion(2.0f / 3.0f, 0.0f, 1.0f, 1.0f / 3.0f));
	g->drawRectangle(rect.position.x, rect.position.y + rect.size.y - 16.0f, 16.0f, 16.0f, Color(255), TextureRegion(0.0f, 2.0f / 3.0f, 1.0f / 3.0f, 1.0f));
	g->drawRectangle(rect.position + rect.size - Vector2(16.0f), Vector2(16.0f), Color(255), TextureRegion(2.0f / 3.0f, 2.0f / 3.0f, 1.0f, 1.0f));

	g->drawRectangle(rect.position.x + 16.0f,               rect.position.y,                       rect.size.x - 32.0f, 16.0f,               Color(255), TextureRegion(1.0f / 3.0f, 0.0f / 3.0f, 2.0f / 3.0f, 1.0f / 3.0f));
	g->drawRectangle(rect.position.x + 16.0f,               rect.position.y + rect.size.y - 16.0f, rect.size.x - 32.0f, 16.0f,               Color(255), TextureRegion(1.0f / 3.0f, 2.0f / 3.0f, 2.0f / 3.0f, 3.0f / 3.0f));
	g->drawRectangle(rect.position.x,                       rect.position.y + 16.0f,               16.0f,               rect.size.y - 32.0f, Color(255), TextureRegion(0.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f));
	g->drawRectangle(rect.position.x + rect.size.x - 16.0f, rect.position.y + 16.0f,               16.0f,               rect.size.y - 32.0f, Color(255), TextureRegion(2.0f / 3.0f, 1.0f / 3.0f, 3.0f / 3.0f, 2.0f / 3.0f));

	g->drawRectangle(rect.position + Vector2(16.0f), rect.size - Vector2(32.0f), Color(255), TextureRegion(1.0f / 3.0f, 1.0f / 3.0f, 2.0f / 3.0f, 2.0f / 3.0f));

	SpriteBatch *spriteBatch = (SpriteBatch*) e->getUserData();
	m_font->setHeight(max(rect.size.y - 34.0f, 16.0f));
	m_font->draw(spriteBatch, rect.getCenter() - Vector2(0.0f, m_font->getHeight() * 0.5f), m_text, FONT_ALIGN_CENTER);

	m_font->draw(spriteBatch, 0, 0, "Button: [" + util::floatToStr(rect.position.x) + ", " + util::floatToStr(rect.position.y) + ", " + util::floatToStr(rect.size.x) + ", " + util::floatToStr(rect.size.y) + "]");
}