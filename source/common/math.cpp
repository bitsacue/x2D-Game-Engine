//       ____  ____     ____                        _____             _            
// __  _|___ \|  _ \   / ___| __ _ _ __ ___   ___  | ____|_ __   __ _(_)_ __   ___ 
// \ \/ / __) | | | | | |  _ / _  |  _   _ \ / _ \ |  _| |  _ \ / _  | |  _ \ / _ \
//  >  < / __/| |_| | | |_| | (_| | | | | | |  __/ | |___| | | | (_| | | | | |  __/
// /_/\_\_____|____/   \____|\__ _|_| |_| |_|\___| |_____|_| |_|\__, |_|_| |_|\___|
//                                                              |___/     
//				Originally written by Marcus Loo Vergara (aka. Bitsauce)
//									2011-2014 (C)

#include <x2d/math.h>

AS_REG_SINGLETON(XMath)

int XMath::Register(asIScriptEngine *scriptEngine)
{
	int r = 0;

	// Type Conversion
	/*r = scriptEngine->RegisterObjectMethod("XMath", "string intToStr(const int)", asMETHOD(XMath, intToStr), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "string floatToStr(const float)", asMETHOD(XMath, floatToStr), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "string boolToStr(const bool)", asMETHOD(XMath, boolToStr), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "int strToInt(const string &in)", asMETHOD(XMath, strToInt), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float strToFloat(const string &in)", asMETHOD(XMath, strToFloat), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "bool strToBool(const string &in)", asMETHOD(XMath, strToBool), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "string strToAscii(const uint8)", asMETHOD(XMath, strToAscii), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "uint8 asciiToStr(const string &in)", asMETHOD(XMath, asciiToStr), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "void setEnumValue(?&out, const int value)", asMETHOD(XMath, setEnumValue), asCALL_THISCALL); AS_ASSERT*/

	// Supplementary math funcs
	/*r = scriptEngine->RegisterObjectMethod("XMath", "string tolower(string &in, const int begin = 0, const int end = 0)", asMETHOD(XMath, toLower), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "string toupper(string &in, const int begin = 0, const int end = 0)", asMETHOD(XMath, toUpper), asCALL_THISCALL); AS_ASSERT*/
	r = scriptEngine->RegisterObjectMethod("XMath", "float round(const float)", asMETHOD(XMath, round), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float ceil(const float)", asMETHOD(XMath, ceil), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float floor(const float)", asMETHOD(XMath, floor), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float clamp(const float, const float, const float)", asMETHOD(XMath, clamp), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float max(const float, const float)", asMETHOD(XMath, maximum), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float min(const float, const float)", asMETHOD(XMath, minimum), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float abs(const float)", asMETHOD(XMath, abs), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float sqrt(const float)", asMETHOD(XMath, sqrt), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float pow(const float, const float)", asMETHOD(XMath, pow), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "int mod(const int, const int)", asMETHOD(XMath, mod), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "uint ror(const uint, const uint)", asMETHOD(XMath, ror), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "uint rol(const uint, const uint)", asMETHOD(XMath, rol), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float lerp(const float, const float, const float)", asMETHOD(XMath, lerp), asCALL_THISCALL); AS_ASSERT
	
	// Trigonometry
	r = scriptEngine->RegisterObjectMethod("XMath", "float cos(const float)", asMETHOD(XMath, cos), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float sin(const float)", asMETHOD(XMath, sin), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float tan(const float)", asMETHOD(XMath, tan), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float acos(const float)", asMETHOD(XMath, acos), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float asin(const float)", asMETHOD(XMath, asin), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float atan(const float)", asMETHOD(XMath, atan), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float atan2(const float, const float)", asMETHOD(XMath, atan2), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("XMath", "float get_PI() const", asMETHOD(XMath, getPI), asCALL_THISCALL); AS_ASSERT

	return r;
}

float XMath::radToDeg(const float rad)
{
	return rad*(180.0f/PI);
}

float XMath::degToRad(const float deg)
{
	return deg*(PI/180.0f);
}

float XMath::clamp(const float x, const float min, const float max)
{
	return x < min ? min : (x > max ? max : x);
}

float XMath::maximum(const float a, const float b)
{
	return (a > b ? a : b);
}

float XMath::minimum(const float a, const float b)
{
	return (a < b ? a : b);
}

uint XMath::ror(const uint a, const uint b)
{
	return (a << b) | (a >> (sizeof(uint)*CHAR_BIT-b));
}

uint XMath::rol(const uint a, const uint b)
{
	return (a >> b) | (a << (sizeof(uint)*CHAR_BIT-b));
}