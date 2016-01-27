#ifndef CGF_SHADER_H
#define CGF_SHADER_H

#include <CGF/Common.h>
#include <CGF/Graphics/Texture.h>

BEGIN_CGF_NAMESPACE

class CGF_API Shader
{
	friend class GraphicsContext;
public:
	Shader(const string &vertexSource, const string &fragmentSource);
	Shader(ResourceDesc *desc);
	~Shader();

	void bindFragLocation(const uint location, const string &name);

	void link();
	
	// Instance ->
	void setUniform1i(const string &name, const int v0);
	void setUniform2i(const string &name, const int v0, const int v1);
	void setUniform3i(const string &name, const int v0, const int v1, const int v2);
	void setUniform4i(const string &name, const int v0, const int v1, const int v2, const int v3);

	void setUniform1ui(const string &name, const uint v0);
	void setUniform2ui(const string &name, const uint v0, const uint v1);
	void setUniform3ui(const string &name, const uint v0, const uint v1, const uint v2);
	void setUniform4ui(const string &name, const uint v0, const uint v1, const uint v2, const uint v3);

	void setUniform1f(const string &name, const float v0);
	void setUniform2f(const string &name, const float v0, const float v1);
	void setUniform2f(const string &name, const float *v);
	void setUniform3f(const string &name, const float v0, const float v1, const float v2);
	void setUniform4f(const string &name, const float v0, const float v1, const float v2, const float v3);
	void setUniformMatrix4f(const string &name, const float *v0);
	void setSampler2D(const string &name, Texture2D *texture);
	// <- Instance

	void exportAssembly(const string &fileName);

private:
	
	// Uniform struct
	struct Uniform
	{
		Uniform() :
			type(0),
			loc(0),
			count(0),
			data(0)
		{
		}

		~Uniform()
		{
			delete[] data;
		}

		GLenum type;
		int loc;
		int count;
		void *data;
	};

	GLuint m_id, m_vertShaderID, m_fragShaderID;
	map<string, Uniform*> m_uniforms;
};

template CGF_API class shared_ptr<Shader>;

END_CGF_NAMESPACE

#endif // CGF_SHADER_H
