#ifndef DEBUG_HELPER_HPP
#define DEBUG_HELPER_HPP

#include "GL/glew.h"

GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__);

#endif