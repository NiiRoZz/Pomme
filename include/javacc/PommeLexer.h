#ifndef POMMELEXER_H
#define POMMELEXER_H
#include "JavaCC.h"
#include "CharStream.h"
#include "Token.h"
#include "TokenManager.h"
#include "PommeLexerConstants.h"
#include "JJTPommeLexerState.h"
#include "ErrorHandler.h"
#include "PommeLexerTree.h"
namespace Pomme {
  struct JJCalls {
    int        gen;
    int        arg;
    JJCalls*   next;
    Token*     first;
    ~JJCalls() { if (next) delete next; }
     JJCalls() { next = nullptr; arg = 0; gen = -1; first = nullptr; }
  };

class PommeLexer {
public:
SimpleNode          * input();
void ident();
void identOp();
void pommeInt();
void pommeFloat();
void pommeString();
void scopes();
void scope();
void classes();
void decls();
void decl();
void methode();
void identfuncs();
void pommeStatic();
void visibility();
void pommeOverride();
void enumerate();
void declenums();
void declenum();
void globalFunction();
void instrs();
void instr();
void listcases();
void pommecase();
void pommeElse();
void listexp();
void listexpP();
void var();
void vexp();
void headers();
void headersP();
void header();
void typemeth();
void identmeth();
void type();
void exp();
void expP();
void exp1();
void exp1P();
void exp2();
void exp2P();
void terme();
void termeP();
void fact2();
void fact();
void listacces();
void listaccesP();
void access();
void number();
 inline bool jj_2_1(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_1() || jj_done);
 { jj_save(0, xla); }
  }

 inline bool jj_2_2(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_2() || jj_done);
 { jj_save(1, xla); }
  }

 inline bool jj_2_3(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_3() || jj_done);
 { jj_save(2, xla); }
  }

 inline bool jj_2_4(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_4() || jj_done);
 { jj_save(3, xla); }
  }

 inline bool jj_2_5(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_5() || jj_done);
 { jj_save(4, xla); }
  }

 inline bool jj_3R_fact2_462_11_66()
 {
    if (jj_done) return true;
    if (jj_scan_token(TILDE)) return true;
    return false;
  }

 inline bool jj_3R_fact2_461_11_65()
 {
    if (jj_done) return true;
    if (jj_scan_token(EXCLAMATION)) return true;
    return false;
  }

 inline bool jj_3R_header_368_9_51()
 {
    if (jj_done) return true;
    if (jj_3R_type_389_9_28()) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_classes_178_9_6()
 {
    if (jj_done) return true;
    if (jj_scan_token(CLASS)) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_classes_178_9_1()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_classes_178_9_6()) {
    jj_scanpos = xsp;
    if (jj_3R_classes_181_11_7()) return true;
    }
    return false;
  }

 inline bool jj_3R_fact2_460_11_64()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    return false;
  }

 inline bool jj_3R_fact2_459_11_63()
 {
    if (jj_done) return true;
    if (jj_scan_token(PARENTL)) return true;
    return false;
  }

 inline bool jj_3R_fact2_458_9_62()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_4()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_459_11_63()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_460_11_64()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_461_11_65()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_462_11_66()) return true;
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3_4()
 {
    if (jj_done) return true;
    if (jj_3R_fact_468_9_4()) return true;
    return false;
  }

 inline bool jj_3_1()
 {
    if (jj_done) return true;
    if (jj_3R_classes_178_9_1()) return true;
    return false;
  }

 inline bool jj_3R_headers_355_11_37()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_headers_353_9_36()
 {
    if (jj_done) return true;
    if (jj_3R_header_368_9_51()) return true;
    return false;
  }

 inline bool jj_3R_headers_353_9_25()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_headers_353_9_36()) {
    jj_scanpos = xsp;
    if (jj_3R_headers_355_11_37()) return true;
    }
    return false;
  }

 inline bool jj_3R_terme_443_9_61()
 {
    if (jj_done) return true;
    if (jj_3R_fact2_458_9_62()) return true;
    return false;
  }

 inline bool jj_3R_var_340_11_11()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONST)) return true;
    if (jj_3R_type_389_9_28()) return true;
    return false;
  }

 inline bool jj_3R_pommeString_156_4_31()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_var_339_9_10()
 {
    if (jj_done) return true;
    if (jj_3R_type_389_9_28()) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_var_339_9_3()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_var_339_9_10()) {
    jj_scanpos = xsp;
    if (jj_3R_var_340_11_11()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommeFloat_150_4_54()
 {
    if (jj_done) return true;
    if (jj_scan_token(FLOAT)) return true;
    return false;
  }

 inline bool jj_3R_exp2_427_9_60()
 {
    if (jj_done) return true;
    if (jj_3R_terme_443_9_61()) return true;
    return false;
  }

 inline bool jj_3R_listexp_327_11_57()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_pommeInt_144_4_53()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3R_pommeOverride_232_11_50()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_identOp_138_9_32()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIEROPERATOR)) return true;
    return false;
  }

 inline bool jj_3R_listexp_325_9_56()
 {
    if (jj_done) return true;
    if (jj_3R_exp_395_9_58()) return true;
    return false;
  }

 inline bool jj_3R_listexp_325_9_55()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexp_325_9_56()) {
    jj_scanpos = xsp;
    if (jj_3R_listexp_327_11_57()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommeOverride_230_9_49()
 {
    if (jj_done) return true;
    if (jj_scan_token(OVERRIDE)) return true;
    return false;
  }

 inline bool jj_3R_pommeOverride_230_9_33()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_pommeOverride_230_9_49()) {
    jj_scanpos = xsp;
    if (jj_3R_pommeOverride_232_11_50()) return true;
    }
    return false;
  }

 inline bool jj_3R_number_510_11_48()
 {
    if (jj_done) return true;
    if (jj_3R_pommeFloat_150_4_54()) return true;
    return false;
  }

 inline bool jj_3R_visibility_225_11_43()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_visibility_224_11_42()
 {
    if (jj_done) return true;
    if (jj_scan_token(PROTECTED)) return true;
    return false;
  }

 inline bool jj_3R_visibility_223_11_41()
 {
    if (jj_done) return true;
    if (jj_scan_token(PRIVATE)) return true;
    return false;
  }

 inline bool jj_3R_number_509_9_47()
 {
    if (jj_done) return true;
    if (jj_3R_pommeInt_144_4_53()) return true;
    return false;
  }

 inline bool jj_3R_number_509_9_30()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_number_509_9_47()) {
    jj_scanpos = xsp;
    if (jj_3R_number_510_11_48()) return true;
    }
    return false;
  }

 inline bool jj_3R_listacces_481_35_46()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_ident_132_4_22()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_visibility_221_9_40()
 {
    if (jj_done) return true;
    if (jj_scan_token(PUBLIC)) return true;
    return false;
  }

 inline bool jj_3R_visibility_221_9_27()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_visibility_221_9_40()) {
    jj_scanpos = xsp;
    if (jj_3R_visibility_223_11_41()) {
    jj_scanpos = xsp;
    if (jj_3R_visibility_224_11_42()) {
    jj_scanpos = xsp;
    if (jj_3R_visibility_225_11_43()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3R_access_503_11_52()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_exp1_409_9_59()
 {
    if (jj_done) return true;
    if (jj_3R_exp2_427_9_60()) return true;
    return false;
  }

 inline bool jj_3R_pommeStatic_216_11_39()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_access_502_9_44()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_5()) {
    jj_scanpos = xsp;
    if (jj_3R_access_503_11_52()) return true;
    }
    return false;
  }

 inline bool jj_3_5()
 {
    if (jj_done) return true;
    if (jj_3R_identmeth_381_9_5()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_325_9_55()) return true;
    return false;
  }

 inline bool jj_3R_pommeStatic_214_9_38()
 {
    if (jj_done) return true;
    if (jj_scan_token(STATIC)) return true;
    return false;
  }

 inline bool jj_3R_pommeStatic_214_9_26()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_pommeStatic_214_9_38()) {
    jj_scanpos = xsp;
    if (jj_3R_pommeStatic_216_11_39()) return true;
    }
    return false;
  }

 inline bool jj_3R_listacces_480_25_45()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_502_9_44()) return true;
    return false;
  }

 inline bool jj_3R_identfuncs_208_9_23()
 {
    if (jj_done) return true;
    if (jj_3R_pommeStatic_214_9_26()) return true;
    if (jj_3R_visibility_221_9_27()) return true;
    if (jj_3R_pommeOverride_230_9_33()) return true;
    return false;
  }

 inline bool jj_3R_exp_395_9_58()
 {
    if (jj_done) return true;
    if (jj_3R_exp1_409_9_59()) return true;
    return false;
  }

 inline bool jj_3R_methode_202_11_9()
 {
    if (jj_done) return true;
    if (jj_scan_token(NATIVE)) return true;
    if (jj_3R_pommeStatic_214_9_26()) return true;
    if (jj_3R_visibility_221_9_27()) return true;
    if (jj_3R_typemeth_374_9_24()) return true;
    if (jj_3R_identmeth_381_9_5()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_headers_353_9_25()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_methode_201_9_8()
 {
    if (jj_done) return true;
    if (jj_3R_identfuncs_208_9_23()) return true;
    if (jj_3R_typemeth_374_9_24()) return true;
    if (jj_3R_identmeth_381_9_5()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_headers_353_9_25()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    return false;
  }

 inline bool jj_3R_methode_201_9_2()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_methode_201_9_8()) {
    jj_scanpos = xsp;
    if (jj_3R_methode_202_11_9()) return true;
    }
    return false;
  }

 inline bool jj_3R_type_389_9_28()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_383_11_21()
 {
    if (jj_done) return true;
    if (jj_scan_token(TILDE)) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_listacces_480_9_29()
 {
    if (jj_done) return true;
    if (jj_3R_access_502_9_44()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listacces_480_25_45()) {
    jj_scanpos = xsp;
    if (jj_3R_listacces_481_35_46()) return true;
    }
    return false;
  }

 inline bool jj_3_2()
 {
    if (jj_done) return true;
    if (jj_3R_methode_201_9_2()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_382_11_20()
 {
    if (jj_done) return true;
    if (jj_3R_identOp_138_9_32()) return true;
    return false;
  }

 inline bool jj_3R_fact_475_11_18()
 {
    if (jj_done) return true;
    if (jj_scan_token(NULLEXP)) return true;
    return false;
  }

 inline bool jj_3R_identmeth_381_9_5()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_identmeth_381_9_19()) {
    jj_scanpos = xsp;
    if (jj_3R_identmeth_382_11_20()) {
    jj_scanpos = xsp;
    if (jj_3R_identmeth_383_11_21()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_identmeth_381_9_19()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_fact_473_11_17()
 {
    if (jj_done) return true;
    if (jj_3R_pommeString_156_4_31()) return true;
    return false;
  }

 inline bool jj_3R_fact_472_11_15()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_fact_472_11_16()
 {
    if (jj_done) return true;
    if (jj_3R_number_509_9_30()) return true;
    return false;
  }

 inline bool jj_3R_fact_471_11_14()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_typemeth_375_11_35()
 {
    if (jj_done) return true;
    if (jj_3R_type_389_9_28()) return true;
    return false;
  }

 inline bool jj_3R_fact_469_11_13()
 {
    if (jj_done) return true;
    if (jj_3R_listacces_480_9_29()) return true;
    return false;
  }

 inline bool jj_3R_typemeth_374_9_34()
 {
    if (jj_done) return true;
    if (jj_scan_token(VOID)) return true;
    return false;
  }

 inline bool jj_3R_typemeth_374_9_24()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_typemeth_374_9_34()) {
    jj_scanpos = xsp;
    if (jj_3R_typemeth_375_11_35()) return true;
    }
    return false;
  }

 inline bool jj_3R_classes_181_11_7()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODDED)) return true;
    if (jj_scan_token(CLASS)) return true;
    return false;
  }

 inline bool jj_3R_fact_468_9_12()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEWEXP)) return true;
    if (jj_3R_ident_132_4_22()) return true;
    if (jj_scan_token(PARENTL)) return true;
    return false;
  }

 inline bool jj_3R_fact_468_9_4()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_fact_468_9_12()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_469_11_13()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_471_11_14()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_472_11_15()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_472_11_16()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_473_11_17()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_475_11_18()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3_3()
 {
    if (jj_done) return true;
    if (jj_3R_var_339_9_3()) return true;
    return false;
  }


public: 
  void setErrorHandler(ErrorHandler *eh) {
    if (errorHandler) delete errorHandler;
    errorHandler = eh;
  }

  TokenManager *token_source = nullptr;
  CharStream   *jj_input_stream = nullptr;
  /** Current token. */
  Token        *token = nullptr;
  /** Next token. */
  Token        *jj_nt = nullptr;

private: 
  int           jj_ntk;
  JJCalls       jj_2_rtns[6];
  bool          jj_rescan;
  int           jj_gc;
  Token        *jj_scanpos, *jj_lastpos;
  int           jj_la;
  /** Whether we are looking ahead. */
  bool          jj_lookingAhead;
  bool          jj_semLA;
  int           jj_gen;
  int           jj_la1[41];
  ErrorHandler *errorHandler = nullptr;

protected: 
  bool          hasError;

  Token *head; 
public: 
  PommeLexer(TokenManager *tokenManager);
  virtual ~PommeLexer();
void ReInit(TokenManager* tokenManager);
void clear();
Token * jj_consume_token(int kind);
bool  jj_scan_token(int kind);
Token * getNextToken();
Token * getToken(int index);
int jj_ntk_f();
private:
  int jj_kind;
  int **jj_expentries;
  int *jj_expentry;
  void jj_add_error_token(int kind, int pos);
protected:
  /** Generate ParseException. */
  virtual void  parseError();
private:
  int  indent;	// trace indentation
  bool trace = false; // trace enabled if true

public:
  bool trace_enabled();
  void enable_tracing();
  void disable_tracing();
  void jj_rescan_token();
  void jj_save(int index, int xla);
        void jjtreeOpenNodeScope(PommeNode *n)
        {
        if (n == nullptr) return;
        n->setLineNumber( getToken(1)->beginLine );
        n->setLineColumn( getToken(1)->beginColumn );
        }

        void jjtreeCloseNodeScope(PommeNode *n)
        {
        }

  JJTPommeLexerState jjtree;
private:
  bool jj_done;
};
}
#endif
