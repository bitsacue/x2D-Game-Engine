//       ____  ____     ____                        _____             _            
// __  _|___ \|  _ \   / ___| __ _ _ __ ___   ___  | ____|_ __   __ _(_)_ __   ___ 
// \ \/ / __) | | | | | |  _ / _  |  _   _ \ / _ \ |  _| |  _ \ / _  | |  _ \ / _ \
//  >  < / __/| |_| | | |_| | (_| | | | | | |  __/ | |___| | | | (_| | | | | |  __/
// /_/\_\_____|____/   \____|\__ _|_| |_| |_|\___| |_____|_| |_|\__, |_|_| |_|\___|
//                                                              |___/     
//				Originally written by Marcus Loo Vergara (aka. Bitsauce)
//									2011-2014 (C)

#include <x2d/engine.h>
#include <x2d/graphics.h>

const int INT_SIZE = sizeof(GLint);
const int FLOAT_SIZE = sizeof(GLfloat);
const int PTR_SIZE = sizeof(void*);

BEGIN_XD_NAMESPACE

Shader::Shader(const string &vertexSource, const string &fragmentSource)
{
	// Create vertex and fragment shaders
    m_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    m_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Result variables
    int result = 0;
    int logLength = 0;

	// Create modified shader code
	string vertexSourceModified = "#version 130\n" + vertexSource;
	string fragmentSourceModified = "#version 130\n" + fragmentSource;

	LOG("Compiling vertex shader...");
	
    // Compile vertex shader
	const char *data = vertexSourceModified.c_str();
	int len = vertexSourceModified.length();
	glShaderSource(m_vertShaderID, 1, &data, &len);
    glCompileShader(m_vertShaderID);

    // Validate vertex shader
    glGetShaderiv(m_vertShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(m_vertShaderID, GL_INFO_LOG_LENGTH, &logLength);

	// Get error log
    char *compileLog = new char[logLength];
    glGetShaderInfoLog(m_vertShaderID, logLength, NULL, compileLog);

	// Print shader error to console
	if(logLength > 1) {
		LOG("%s", compileLog);
	}

	LOG("Compiling fragment shader...");

    // Compile fragment shader
	data = fragmentSourceModified.c_str();
	len = fragmentSourceModified.length();
	glShaderSource(m_fragShaderID, 1, &data, &len);
    glCompileShader(m_fragShaderID);

    // Check fragment shader
    glGetShaderiv(m_fragShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(m_fragShaderID, GL_INFO_LOG_LENGTH, &logLength);

	// Get error log
	delete[] compileLog;
	compileLog = new char[logLength];
    glGetShaderInfoLog(m_fragShaderID, logLength, NULL, compileLog);

	// Print shader error to console
	if(logLength > 1) {
		LOG("%s", compileLog);
	}

    // Create shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, m_vertShaderID);
    glAttachShader(m_id, m_fragShaderID);

	glBindAttribLocation(m_id, 0, "in_Position");
	glBindAttribLocation(m_id, 1, "in_VertexColor");
	glBindAttribLocation(m_id, 2, "in_TexCoord");
	glBindFragDataLocation(m_id, 0, "out_FragColor");

	link();

	// Delete log buffers
	delete[] compileLog;

	// Setup uniform variables
	GLint count;
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &count);
	GLint length, size;
	GLenum type;
	GLchar name[256];
	for(int i = 0; i < count; i++)
	{
		glGetActiveUniform(m_id, i, 256, &length, &size, &type, name);

		if(strncmp(name, "gl_", 3) == 0) // Skip gl_ uniforms
			continue;

		Uniform *uniform = new Uniform;
		uniform->type = type;
		uniform->loc = glGetUniformLocation(m_id, name);
		
		size_t dataSize = 0;
		switch(type)
		{
		case GL_UNSIGNED_INT_SAMPLER_2D:
		case GL_INT_SAMPLER_2D:
		case GL_SAMPLER_2D:
		case GL_INT:		dataSize = INT_SIZE; break;
		case GL_INT_VEC2:	dataSize = INT_SIZE * 2; break;
		case GL_INT_VEC3:	dataSize = INT_SIZE * 3; break;
		case GL_INT_VEC4:	dataSize = INT_SIZE * 4; break;
		case GL_FLOAT:		dataSize = FLOAT_SIZE; break;
		case GL_FLOAT_VEC2:	dataSize = FLOAT_SIZE * 2; break;
		case GL_FLOAT_VEC3:	dataSize = FLOAT_SIZE * 3; break;
		case GL_FLOAT_VEC4:	dataSize = FLOAT_SIZE * 4; break;
		case GL_FLOAT_MAT4:	dataSize = FLOAT_SIZE * 16; break;
		}
		uniform->data = new char[dataSize];
		m_uniforms[name] = uniform;
	}
}

Shader::~Shader()
{
	// Delete shader buffers as they are loaded into the shader program
	glDeleteShader(m_vertShaderID);
	glDeleteShader(m_fragShaderID);
	for(map<string, Uniform*>::iterator itr = m_uniforms.begin(); itr != m_uniforms.end(); ++itr) {
		delete itr->second;
	}
}

void Shader::bindFragLocation(const uint location, const string &name)
{
	glBindFragDataLocation(m_id, location, name.c_str());
}

void Shader::link()
{
	LOG("Linking shader program...");

	int result = 0;
	int logLength = 0;

	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &result);
	glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

	// Get error log
	char* programLog = new char[(logLength > 1) ? logLength : 1];
	glGetProgramInfoLog(m_id, logLength, NULL, programLog);

	// Print program error to console
	if(logLength > 1)
	{
		LOG("%s", programLog);
	}

	delete[] programLog;
}

void Shader::setUniform1i(const string &name, const int v0)
{
	map<string, Uniform*>::iterator itr;
	if((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_INT)
		{
			((GLint*)uniform->data)[0] = v0;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniform2i(const string &name, const int v0, const int v1)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_INT_VEC2)
		{
			((GLint*)uniform->data)[0] = v0;
			((GLint*)uniform->data)[1] = v1;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniform3i(const string &name, const int v0, const int v1, const int v2)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_INT_VEC3)
		{
			((GLint*)uniform->data)[0] = v0;
			((GLint*)uniform->data)[1] = v1;
			((GLint*)uniform->data)[2] = v2;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniform4i(const string &name, const int v0, const int v1, const int v2, const int v3)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_INT_VEC4)
		{
			((GLint*)uniform->data)[0] = v0;
			((GLint*)uniform->data)[1] = v1;
			((GLint*)uniform->data)[2] = v2;
			((GLint*)uniform->data)[3] = v3;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniform1f(const string &name, const float v0)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_FLOAT)
		{
			((GLfloat*)uniform->data)[0] = v0;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniform2f(const string &name, const float v0, const float v1)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_FLOAT_VEC2)
		{
			((GLfloat*)uniform->data)[0] = v0;
			((GLfloat*)uniform->data)[1] = v1;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniform3f(const string &name, const float v0, const float v1, const float v2)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_FLOAT_VEC3)
		{
			((GLfloat*)uniform->data)[0] = v0;
			((GLfloat*)uniform->data)[1] = v1;
			((GLfloat*)uniform->data)[2] = v2;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniform4f(const string &name, const float v0, const float v1, const float v2, const float v3)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_FLOAT_VEC4)
		{
			((GLfloat*)uniform->data)[0] = v0;
			((GLfloat*)uniform->data)[1] = v1;
			((GLfloat*)uniform->data)[2] = v2;
			((GLfloat*)uniform->data)[3] = v3;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setUniformMatrix4f(const string & name, const float * v0)
{
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if (uniform->type == GL_FLOAT_MAT4)
		{
			for (int i = 0; i < 16; ++i)
			{
				((GLfloat*)uniform->data)[i] = v0[i];
			}
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::setSampler2D(const string &name, Texture2DPtr texture)
{
	// TODO: We should actually store a handle to the texture object to avoid it being destroyed
	map<string, Uniform*>::iterator itr;
	if ((itr = m_uniforms.find(name)) != m_uniforms.end())
	{
		Uniform *uniform = itr->second;
		if(uniform->type == GL_SAMPLER_2D ||
			uniform->type == GL_INT_SAMPLER_2D ||
			uniform->type == GL_UNSIGNED_INT_SAMPLER_2D)
		{
			((GLuint*)uniform->data)[0] = texture != 0 ? texture->m_id : 0;
		}
	}
	else
	{
		LOG("Uniform '%s' does not exist.", name.c_str());
	}
}

void Shader::exportAssembly(const string & fileName)
{
	// Max file size
	const size_t MAX_SIZE = 1 << 24;

	// Get binary program
	char *binary = new char[MAX_SIZE];
	GLenum format;
	GLint length;
	glGetProgramBinary(m_id, MAX_SIZE, &length, &format, binary);

	// Copy to string
	string content;
	content.resize(length);
	memcpy(&content[0], binary, length);

	// Write to file
	FileSystem::WriteFile(fileName, content);

	// Clean up
	delete[] binary;
}

ShaderPtr Shader::loadResource(const string &name)
{
	FileReader *fileReader;

	fileReader = new FileReader(util::getAbsoluteFilePath(name + ".vert"));
	string vertexSource = fileReader->readAll();
	fileReader->close();
	delete fileReader;

	fileReader = new FileReader(util::getAbsoluteFilePath(name + ".frag"));
	string fragmentSource = fileReader->readAll();
	fileReader->close();
	delete fileReader;

	LOG("Compiling shader program: %s", name.c_str());

	return ShaderPtr(new Shader(vertexSource, fragmentSource));
}

END_XD_NAMESPACE