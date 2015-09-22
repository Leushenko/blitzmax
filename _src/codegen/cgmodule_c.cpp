
#include "cgstd.h"
#include "cgcode.h"

#include "cgmodule_c.h"

static const char * typeName(int i) {
	switch(i) {
		case CG_VOID: return "void";
		case CG_PTR: return "void *";
		case CG_INT8: return "int8_t";
		case CG_INT16: return "int16_t";
		case CG_INT32: return "int32_t";
		case CG_INT64: return "int64_t";
		case CG_FLOAT32: return "float";
		case CG_FLOAT64: return "double";
		case CG_CSTRING: return "char *";
		case CG_BSTRING: return "void *";
		default:
			assert(0);
	}
	return 0;//nullptr;
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
	out << "#include <stdint.h>\n";
	out << "//#define ASSERT(C) ...\n";
  out << "#ifdef BMAX_64_BIT\n";
	out << "  //typedef union {} ANY;\n";
	out << "#else\n";
	out << "  typedef union { int32_t i; float f; void * p; void *(*f)(void); } ANY;\n";
	out << "  //ASSERT(sizeof(ANY) == ...)\n";
	out << "#endif\n";
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
	out << "ANY " << name << "[]"; // using an array is the easiest way to vary the storage size here
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
	out << "}\n";
}

void CGModule_C::emitData( CGDat *d ){

	if( env_platform=="win32" ){
		setSeg( "\"data\" data writeable align 8" );
	}else if( env_platform=="linux" ){
		setSeg( "\"data\" writeable align 8" );
	}else if( env_platform=="macos" ){
		setSeg( "data" );
	}
	
	int align=4;
	if( d->exps.size()==1 ){
		switch( d->exps[0]->type ){
		case CG_INT8:
		case CG_CSTRING:
			align=1;
			break;
		case CG_INT16:
			align=2;
			break;
		case CG_INT64:case CG_FLOAT64:
			align=8;
			break;
		}
	}
	if( align!=1 ){
		out<<"\talign\t"<<align<<"\n";
	}
	
	out<<d->value<<":\n";

	for( int k=0;k<d->exps.size();++k ){

		CGExp *e=d->exps[k];

		if( CGLit *t=e->lit() ){
			if( t->type==CG_INT8 ){
				out<<"\tdb\t"<<unsigned(t->int_value)<<'\n';
			}else if( t->type==CG_INT16 ){
				out<<"\tdw\t"<<unsigned(t->int_value)<<'\n';
			}else if( t->type==CG_INT32 ){
				out<<"\tdd\t"<<int(t->int_value)<<'\n';
			}else if( t->type==CG_INT64 ){
				out<<"\tdd\t"<<int(t->int_value)<<','<<int(t->int_value>>int64(32))<<'\n';
			}else if( t->type==CG_FLOAT32 ){
				float f=t->float_value;
				int n=*(int*)&f;
				out<<"\tdd\t0x"<<hex<<n<<dec<<'\n';
//				float f=t->float_value;
//				out<<"\tdd\t0x"<<hex<<*((int*)&f)<<dec<<'\n';
			}else if( t->type==CG_FLOAT64 ){
				double f=t->float_value;
				int64 n=*(int64*)&f;
				out<<"\tdd\t0x"<<hex<<int(n)<<",0x"<<int(n>>int64(32))<<dec<<'\n';
//				double f=t->float_value;
//#if __APPLE__ && __BIG_ENDIAN__
//				out<<"\tdd\t0x"<<hex<<*((int*)&f+1)<<",0x"<<*((int*)&f)<<dec<<'\n';
//#else
//				out<<"\tdd\t0x"<<hex<<*((int*)&f)<<",0x"<<*((int*)&f+1)<<dec<<'\n';
//#endif
			}else if( t->type==CG_CSTRING ){
				bstring s=t->string_value;
				out<<"\tdb\t\"";
				for( int k=0;k<s.size();++k ){
					if( s[k]==34 ){
						if( env_platform=="macos" ){
							out<<"\\\"";
						}else{
							out<<"\",34,\"";
						}
					}else{
					 	out<<(char)s[k];
					}
				}
				out<<"\",0\n";
			}else if( t->type==CG_BSTRING ){
				bstring s=t->string_value;
				out<<"\tdd\t"<<s.size();
				for( int k=0;k<s.size();++k ){
					if( k%16 ) out<<','<<(unsigned)s[k];
					else out<<"\n\tdw\t"<<(unsigned)s[k];
				}
				out<<"\n";
			}else if( t->type==CG_BINFILE ){
				string file=tostring(t->string_value);
				out<<"\tfile\t\""+file+"\"\n";
			}else if( t->type==CG_LABEL ){
				out<<tostring(t->string_value)<<":\n";
			}else{
				assert(0);
			}
		}else if( CGSym *t=e->sym() ){
			out<<"\tdd\t"<<t->value<<'\n';
		}else if( CGLea *t=e->lea() ){
			CGMem *m=t->exp->mem();
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
			}
		}else{
			fail( "cgmodule_c::emitData - unrecognized data format" );
		}
	}
}

void CGModule_C::emitFooter(){
}
