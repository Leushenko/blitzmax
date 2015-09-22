
#include "cgstd.h"
#include "cgcode.h"

#include "cgmodule_c.h"

static const std::string typeName(int i) {
	switch(i) {
		case CG_VOID: return "void";
		case CG_PTR: return "void *";
		case CG_INT8: return "uint8_t";
		case CG_INT16: return "uint16_t";
		case CG_INT32: return "int32_t";
		case CG_INT64: return "int64_t";
		case CG_FLOAT32: return "float";
		case CG_FLOAT64: return "double";
		case CG_CSTRING: return "char *";
		case CG_BSTRING: return "uint16_t *";
		default:
			assert(0);
	}
	return 0;//nullptr;
}
static const std::string anyGet(int i) {  // access member for the given type
	switch(i) {
		case CG_PTR: return "p";
		case CG_INT8: return "c";
		case CG_INT16: return "s";
		case CG_INT32: return "i";
		case CG_INT64: return "l";  // for use with extended version
		case CG_FLOAT32: return "f";
		case CG_FLOAT64: return "d";
		case CG_CSTRING: return "ca";
		case CG_BSTRING: return "sa";
		default:
			assert(0);
	}
	return 0;//nullptr;
}
static const std::string varType(CGDat * d) {
	if (d->exps.size() > 1) {
		return "ANY";
	} else {
		return typeName(d->exps[0]->type);
	}
}

CGModule_C::CGModule_C( ostream &o ):CGModule(o){
}

void CGModule_C::setSeg( string t ){
	if( seg==t ) return;
	seg=t;
	out<<"\tsection\t"<<seg<<'\n';
}

CGFrame *CGModule_C::frame( CGFun *fun ){
	return new CGFrame_C( fun,this );
}

void CGModule_C::emitHeader(){
	out << "#include <stdint.h>\n"
				 "//#define ASSERT(C) ...\n"
  			 "#ifdef BMAX_64_BIT\n"
				 "  //typedef union { ... } ANY;\n"
				 "  #error 64-bit not supported; try the NG compiler\n"
				 "#else\n"
				 "  typedef union { \n"
	       "    int32_t i; float f; void * p; void *(*k)(void);\n"
				 "    uint8_t c; uint16_t s; uint8_t ca[4]; uint16_t sa[2];\n"
				 "  } ANY;\n"
				 "  //ASSERT(sizeof(ANY) == ...)\n"
				 "  //ASSERT(sizeof(int32_t) == sizeof(intptr_t))\n"
				 "#endif\n";
}

void CGModule_C::emitImport( string t ){
out << "extern ANY " << t << ";\n"; // we can reinterpret as necessary at point of use
}

void CGModule_C::emitExport( string t ) {}

static void funDecl(CGFun* fun, std::ostream & out) {
	const string name = fun->sym->value;
	if (name[0] == '_' && isdigit(name[1])) {
		out << "static ";
	}
	out << typeName(fun->type) << " " << name <<"(";
	if (fun->self) {
		out << "ANY * self" << (fun->args.size() ? ", " : "");
	} else if (fun->args.size() == 0) {
		out << "void";
	}
	for (std::vector<CGExp*>::size_type i = 0, sz = fun->args.size(); i < sz; i ++) {
		out << typeName(fun->args[i]->type) << " p" << i;
		if (i < sz - 1) { out << ", "; }
	}
	out << ")";
}
static void varDecl(CGDat * d, std::ostream & out) {
	const string name = d->value;
	if (name[0] == '_' && isdigit(name[1])) {
		out << "static ";
	}
	if (d->exps.size() > 1) {
		out << "ANY " << name << "[]";
	} else {
		out << typeName(d->exps[0]->type) << " " << name;
	}
}

void CGModule_C::emitVarDeclaration(CGDat * d) {
	varDecl(d, out);
	out << ";\n";
}
void CGModule_C::emitFunDeclaration(CGFun * f) {
	funDecl(f, out);
	out << ";\n";
}

void CGModule_C::emitFrame( CGFrame *f ){
	CGFrame_C *frame=dynamic_cast<CGFrame_C*>(f);
	assert( frame );

	int k,n_use[7]={0};

	for( k=0;k<frame->regs.size();++k ){
		CGReg *r=frame->regs[k];
		if( r->isint() && r->id>=14 && r->color>=0 && r->color<7 ) ++n_use[r->color];
	}
	
	if( frame->extern_jsrs ){
		n_use[3]=n_use[4]=n_use[5]=-1;
	}

	int local_sz=frame->local_sz;

	//create frame
	funDecl(frame->fun, out);
	out << " {\n";
	
	out << "  ANY eax, edx, ecx, ebx, esi, edi;\n";
	if (local_sz > 0) {
		out << "  ANY";
		for (int i = 0; i < local_sz; i ++) {
			out << " v" << i;
			if (i < local_sz - 1) { out << ","; }
		}
		out << ";\n";
	}
	
	CGAsm *as;

	for( as=frame->assem.begin;as!=frame->assem.end;as=as->succ ){
		const char *p=as->assem;
		if( !p ) continue;
		out<<p;
	}
	out << "  return ((" << typeName(frame->fun->type) << ")0);\n}\n";
}

void CGModule_C::emitData( CGDat *d ){
	varDecl(d, out);
	out << " = ";
	
	int elems = d->exps.size();
	if (elems > 1) { out << "{\n"; }
	
	for( int k=0;k < elems;++k ){
		CGExp *e=d->exps[k];

		if( CGLit *t=e->lit() ){
			if (elems > 1) {
				out << "  (ANY){ ." << anyGet(t->type) << " = ";
			}
			
			if( t->type==CG_INT8 ){
				out<<"\tdb\t"<<unsigned(t->int_value)<<'\n';
			}else if( t->type==CG_INT16 ){
				out<<"\tdw\t"<<unsigned(t->int_value)<<'\n';
			}else if( t->type==CG_INT32 ){
				out << t->int_value;
			}else if( t->type==CG_INT64 ){
				out << t->int_value;
			}else if( t->type==CG_FLOAT32 ){
				out << t->float_value;
			}else if( t->type==CG_FLOAT64 ){
				out << t->float_value;
			}else if( t->type==CG_CSTRING ){
				bstring s=t->string_value;
				if (elems == 1) {
					out << "(char[]){\"";
					for( int k=0;k<s.size();++k ){
						if( s[k]==34 ){
							out<<"\\\"";
						}else{
						 	out<<(char)s[k];
						}
					}
					out << "\"}";
				} else {
					for (int k = 0; k < s.size(); k += 4) {  //TODO 64-bit aware please
						if (k) { out << " },\n  (ANY){ .ca = "; }
						out << "{" << s[k] << "," << s[k + 1] << ","
						    << s[k + 2] << "," << s[k + 3] << "}";
					}
				}
			}else if( t->type==CG_BSTRING ){
				bstring s=t->string_value;
				if (elems == 1) {
					out << "(uint16_t[]){";
					for( int k=0;k<s.size();++k ){
						out << s[k] << ",";
					}
					out << "}";
				} else {
					for (int k = 0; k < s.size(); k += 2) {  //TODO 64-bit aware please
						if (k) { out << " },\n  (ANY){ .sa = "; }
						out << "{" << s[k] << "," << s[k + 1] << "}";
					}
				}
			}else if( t->type==CG_BINFILE ){
				//string file=tostring(t->string_value);
				//out<<"\tfile\t\""+file+"\"\n";
				out << "\n#error IncBin not yet supported\n";
			}else if( t->type==CG_LABEL ){
				//out<<tostring(t->string_value)<<":\n";
				out << "\n#error CG_LABEL not yet supported\n";  //TODO what is this anyway?
			}else{
				assert(0);
			}
			
			if (elems > 1) { out << " },\n"; }
		}else if( CGSym *t=e->sym() ){
			if (elems > 1) {
				out << "  (ANY){ .p = " << t->value << " },\n";  // (ugh) it's either a fptr or an ANY[]
			} else {
				out << t->value << ".i";
			}
		}else if( CGLea *t=e->lea() ){
			//TODO what does this do?
			out << "\n#error CGLea not yet supported\n";
			/*CGMem *m=t->exp->mem();
			assert(m);
			if( CGReg *t=m->exp->reg() ){
				out<<"\tdd\t"<<m->offset<<'\n';
			}else if( CGSym *t=m->exp->sym() ){
				assert(t);
				if( m->offset ){
					out<<"\tdd\t"<<t->value<<'+'<<m->offset<<'\n';
				}else{
					out<<"\tdd\t"<<t->value<<'\n';
				}
			}else{
				assert(0);
			}*/
		}else{
			fail( "cgmodule_c::emitData - unrecognized data format" );
		}
	}
	out << (elems > 1 ? "};\n" : ";\n");
}

void CGModule_C::emitFooter(){
}
