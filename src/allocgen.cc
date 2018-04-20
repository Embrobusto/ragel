/*
 * Copyright 2005-2018 Adrian Thurston <thurston@colm.net>
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

#include "ragel.h"
#include "parsedata.h"
#include "fsmgraph.h"
#include "gendata.h"
#include "inputdata.h"
#include "version.h"

/*
 * Code generators.
 */
#include "binvar.h"
#include "bingoto.h"
#include "flatgotoloop.h"
#include "flatvarloop.h"
#include "flatgotoexp.h"
#include "flatvarexp.h"
#include "gotoloop.h"
#include "gotoexp.h"
#include "ipgoto.h"
#include "asm.h"

CodeGenData *asm_makeCodeGen( const HostLang *hostLang, const CodeGenArgs &args )
{
	return new AsmCodeGen( args );
}

/* Invoked by the parser when a ragel definition is opened. */
CodeGenData *makeCodeGen( const HostLang *hostLang, const CodeGenArgs &args )
{
	FsmGbl *id = args.id;
	CodeGenData *codeGen = 0;

	switch ( args.codeStyle ) {
	case GenBinaryLoop:
		if ( hostLang->feature == GotoFeature )
			codeGen = new BinGotoLoop( args );
		else
			codeGen = new BinVarLoop( args );
		break;

	case GenBinaryExp:
		if ( hostLang->feature == GotoFeature )
			codeGen = new BinGotoExp( args );
		else
			codeGen = new BinVarExp( args );
		break;

	case GenFlatLoop:
		if ( hostLang->feature == GotoFeature )
			codeGen = new FlatGotoLoop( args );
		else
			codeGen = new FlatVarLoop( args );
		break;

	case GenFlatExp:
		if ( hostLang->feature == GotoFeature )
			codeGen = new FlatGotoExp( args );
		else
			codeGen = new FlatVarExp( args );
		break;

	case GenSwitchLoop:
		if ( hostLang->feature == GotoFeature )
			codeGen = new SwitchGotoLoop(args);
		else
			id->error() << "unsupported lang/style combination" << endp;
		break;
	case GenSwitchExp:
		if ( hostLang->feature == GotoFeature )
			codeGen = new SwitchGotoExp(args);
		else
			id->error() << "unsupported lang/style combination" << endp;
		break;

	case GenIpGoto:
		if ( hostLang->feature == GotoFeature )
			codeGen = new IpGoto(args);
		else
			id->error() << "unsupported lang/style combination" << endp;
		break;
	}

	return codeGen;
}
