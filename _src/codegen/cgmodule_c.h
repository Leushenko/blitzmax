
#ifndef CGMODULE_C_H
#define CGMODULE_C_H

#include "cgmodule.h"
#include "cgframe_c.h"

struct CGModule_C : public CGModule{
	string		seg;
	string file_main;
	
	CGModule_C( ostream &out );
	
	void		setSeg( string t );
	
	CGFrame*	frame( CGFun *fun );
	void		emitHeader();
	void		emitImport( string t );
	void		emitExport( string t );
	void emitVarDeclaration(CGDat * d);
	void emitFunDeclaration(CGFun * f);
	void		emitFrame( CGFrame *f );
	void		emitData( CGDat *d );
	void		emitFooter();
	
	void funDecl(CGFun* fun);
	void varDecl(CGDat * d);
	void emitData2(CGDat * d);
};

#endif
