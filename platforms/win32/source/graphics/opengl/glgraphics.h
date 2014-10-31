#ifndef WIN_OPENGL_H
#define WIN_OPENGL_H

#include <x2d/graphics.h>
#include <GL/glew.h>
#include <gl/wglew.h>

class Window;

extern const int INT_SIZE;
extern const int FLOAT_SIZE;

/**
  *	\brief 
  */
class OpenGL : public XGraphics
{
	friend class Window;
public:
	~OpenGL();
	void init(Window *window);

	void createContext();
	void destroyContext();

	void swapBuffers();

	void enableVsync();
	void disableVsync();

	void enableWireframe();
	void disableWireframe();

	void setOrthoProjection(const float l, const float r, const float b, const float t, const float n, const float f);
	void getOrthoProjection(float &l, float &r, float &b, float &t, float &n, float &f);
	
	void setViewport(const Recti&);
	void setViewport(const Vector2i&, Vector2i&);
	void setViewport(const int, const int, const int, const int);
	void getViewport(int &x, int &y, int &w, int &h);

private:
	void					renderBatch(const XBatch &batch);
	XTexture*				createTexture(const XPixmap &pixmap);
	XShader*				createShader(const string &vertFilePath, const string &fragFilePath);
	XVertexBufferObject*	createVertexBufferObject(const XVertexBuffer &buffer);
	XFrameBufferObject*		createFrameBufferObject();
	bool					isSupported(Feature feature);
	
	HGLRC m_context;
	HDC m_deviceContext;
	float m_currentOrtho[6];
	int m_currentViewport[4];
};

#endif // WIN_OPENGL_H