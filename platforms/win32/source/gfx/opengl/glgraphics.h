#ifndef GFX_OPENGL_H
#define GFX_OPENGL_H

#include <x2d/graphics.h>
#include <GL/glew.h>
#include <gl/wglew.h>

class Window;

extern const int INT_SIZE;
extern const int FLOAT_SIZE;

/**
  *	\brief 
  */
class OpenGL : public xdGraphics
{
	friend class Window;
public:
	~OpenGL();
	void init(Window *window);

	HGLRC createContext();
	void destroyContext(HGLRC context);

	void swapBuffers();

	void enableVsync();
	void disableVsync();

	void setOrthoProjection(const float l, const float r, const float b, const float t, const float n, const float f);
	void getOrthoProjection(float &l, float &r, float &b, float &t, float &n, float &f);
	
	void setViewport(const Recti&);
	void setViewport(const Vector2i&, Vector2i&);
	void setViewport(const int, const int, const int, const int);
	void getViewport(int &x, int &y, int &w, int &h);

private:
	void renderBatch(const Batch &batch);
	Texture *createTexture(const Pixmap &pixmap);
	Shader *createShader(const string &vertFilePath, const string &fragFilePath);
	VertexBufferObject *createVertexBufferObject();
	FrameBufferObject *createFrameBufferObject();
	bool isSupported(Feature feature);

	list<HGLRC> m_contexts;
	HDC m_deviceContext;
	float m_currentOrtho[6];
	int m_currentViewport[4];
};

class xdIThreadManager
{
protected:
	virtual void setupThread() = 0;
	virtual void cleanupThread() = 0;
};

class ThreadManager : public xdIThreadManager
{
protected:
	void setupThread();
	void cleanupThread();
};

#endif // GFX_OPENGL_H