#ifndef PLUGIN_SKELETON_H
#define PLUGIN_SKELETON_H

#include <x2d/base.h>
#include <x2d/math.h>
#include <spine/spine.h>

class spAnimationWrapper;

class spSkeletonWrapper
{
public:
	spSkeletonWrapper(spSkeletonData *data, spAtlas *atlas);
	~spSkeletonWrapper();

	spAnimationWrapper *findAnimation(const string &name);

	void setPosition(const Vector2 &pos);
	Vector2 getPosition() const;

	void setFlipX(const bool flip);
	bool getFlipX() const;

	void setFlipY(const bool flip);
	bool getFlipY() const;

	void draw(class Batch *batch);

	spSkeletonData *data() const;
	spSkeleton *get() const;

	static spSkeletonWrapper *Factory(const string &jsonFile, const string &atlasFile, const float scale);
	
	void addRef() { refCounter.add(); }
	void release() { if(refCounter.release() == 0) delete this; }

private:
	RefCounter refCounter;
	spSkeleton *m_self;
	spSkeletonData *m_data;
	spAtlas* m_atlas;
	float *m_worldVertices;
	map<string, spAnimationWrapper*> m_animations;
};

#endif // PLUGIN_SKELETON_H