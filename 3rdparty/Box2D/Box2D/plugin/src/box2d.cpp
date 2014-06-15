#include "box2d.h"
#include "debugdraw.h"

Box2D *b2d = 0;

b2Vec2 toB2Vec(const Vector2 &vec)
{
	return b2Vec2(vec.x/b2d->getScale(), vec.y/b2d->getScale());
}

Vector2 toXDVec(const b2Vec2 &vec)
{
	return Vector2(vec.x*b2d->getScale(), vec.y*b2d->getScale());
}

Box2D::Box2D() :
	m_scale(1.0f)
{
	m_world = new b2World(b2Vec2(0.0f, 10.0f));
	m_world->SetAllowSleeping(true);

	LOG("Initializing Box2D %i.%i.%i", b2_version.major, b2_version.minor, b2_version.revision);
		
	uint drawFlags = b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit;
	m_debugDraw = new DebugDraw;
	m_debugDraw->SetFlags(drawFlags);
	m_world->SetDebugDraw(m_debugDraw);
	
#ifdef OLD
	contactListener = new ContactListener;
	m_world->SetContactListener(contactListener);
#endif
}

Box2D::~Box2D()
{
	delete m_world;
	delete m_debugDraw;
	//delete m_contactListener;
}

void Box2D::step(float timeStep)
{
	m_world->Step(timeStep, 8, 3);
}

void Box2D::draw()
{
	m_world->DrawDebugData();
}

void Box2D::setDrawFlags(int flags)
{
	m_debugDraw->SetFlags(flags);
}

void Box2D::setScale(float scale)
{
	m_scale = scale;
}

float Box2D::getScale() const
{
	return m_scale;
}

b2World *Box2D::getWorld() const
{
	return m_world;
}