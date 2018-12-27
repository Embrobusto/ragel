/*
 * Copyright 2001-2018 Adrian Thurston <thurston@colm.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "inputdata.h"

extern struct colm_sections rl_parse;
extern struct colm_sections rlhc;

/*
 * Java
 */

const char *java_defaultOutFn( const char *inputFileName )
{
	return fileNameFromStem( inputFileName, ".java" );
}

HostType hostTypesJava[] = 
{
	{ "byte",    0,  "byte",   true,   true,  false,  CHAR_MIN,  CHAR_MAX,    0, 0,           1 },
	{ "short",   0,  "short",  true,   true,  false,  SHRT_MIN,  SHRT_MAX,    0, 0,           2 },
	{ "char",    0,  "char",   false,  true,  false,  0, 0,                   0, USHRT_MAX,   2 },
	{ "int",     0,  "int",    true,   true,  false,  INT_MIN,   INT_MAX,     0, 0,           4 },
};

const HostLang hostLangJava = {
	"Java",
	"-J",
	hostTypesJava, 4,
	hostTypesJava+2,
	false,
	true,
	"java",
	&java_defaultOutFn,
	&makeCodeGen,
	Translated,
	VarFeature,
	&genLineDirectiveTrans
};


int main( int argc, const char **argv )
{
	InputData id( &hostLangJava, &rl_parse, &rlhc );
	return id.rlhcMain( argc, argv );
}
