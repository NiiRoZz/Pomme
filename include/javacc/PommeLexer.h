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

 inline bool jj_2_6(int xla)
 {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    jj_done = false;
    return (!jj_3_6() || jj_done);
 { jj_save(5, xla); }
  }

 inline bool jj_3R_fact2_463_11_47()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    return false;
  }

 inline bool jj_3R_classes_180_9_6()
 {
    if (jj_done) return true;
    if (jj_scan_token(CLASS)) return true;
    if (jj_3R_ident_134_4_4()) return true;
    return false;
  }

 inline bool jj_3R_classes_180_9_1()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_classes_180_9_6()) {
    jj_scanpos = xsp;
    if (jj_3R_classes_183_11_7()) return true;
    }
    return false;
  }

 inline bool jj_3R_fact2_462_11_46()
 {
    if (jj_done) return true;
    if (jj_scan_token(PARENTL)) return true;
    return false;
  }

 inline bool jj_3R_fact2_461_9_45()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_4()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_462_11_46()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_463_11_47()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_464_11_48()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_465_11_49()) return true;
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3_4()
 {
    if (jj_done) return true;
    if (jj_3R_fact_471_9_3()) return true;
    return false;
  }

 inline bool jj_3_1()
 {
    if (jj_done) return true;
    if (jj_3R_classes_180_9_1()) return true;
    return false;
  }

 inline bool jj_3R_vexp_351_11_28()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_terme_446_9_44()
 {
    if (jj_done) return true;
    if (jj_3R_fact2_461_9_45()) return true;
    return false;
  }

 inline bool jj_3R_vexp_349_11_27()
 {
    if (jj_done) return true;
    if (jj_scan_token(BRACKETL)) return true;
    return false;
  }

 inline bool jj_3R_vexp_348_9_21()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_vexp_348_9_26()) {
    jj_scanpos = xsp;
    if (jj_3R_vexp_349_11_27()) {
    jj_scanpos = xsp;
    if (jj_3R_vexp_351_11_28()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_vexp_348_9_26()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASSIGNEMENT)) return true;
    return false;
  }

 inline bool jj_3R_var_342_11_9()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONST)) return true;
    if (jj_3R_type_392_9_20()) return true;
    if (jj_3R_ident_134_4_4()) return true;
    return false;
  }

 inline bool jj_3R_pommeString_158_4_24()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_var_341_9_8()
 {
    if (jj_done) return true;
    if (jj_3R_type_392_9_20()) return true;
    if (jj_3R_ident_134_4_4()) return true;
    if (jj_3R_vexp_348_9_21()) return true;
    return false;
  }

 inline bool jj_3R_var_341_9_2()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_var_341_9_8()) {
    jj_scanpos = xsp;
    if (jj_3R_var_342_11_9()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommeFloat_152_4_37()
 {
    if (jj_done) return true;
    if (jj_scan_token(FLOAT)) return true;
    return false;
  }

 inline bool jj_3R_exp2_430_9_43()
 {
    if (jj_done) return true;
    if (jj_3R_terme_446_9_44()) return true;
    return false;
  }

 inline bool jj_3R_listexp_329_11_42()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_pommeInt_146_4_36()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3R_identOp_140_9_25()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIEROPERATOR)) return true;
    return false;
  }

 inline bool jj_3R_listexp_327_9_41()
 {
    if (jj_done) return true;
    if (jj_3R_exp_398_9_38()) return true;
    return false;
  }

 inline bool jj_3R_listexp_327_9_39()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexp_327_9_41()) {
    jj_scanpos = xsp;
    if (jj_3R_listexp_329_11_42()) return true;
    }
    return false;
  }

 inline bool jj_3R_ident_134_4_4()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_exp1_412_9_40()
 {
    if (jj_done) return true;
    if (jj_3R_exp2_430_9_43()) return true;
    return false;
  }

 inline bool jj_3R_number_505_11_32()
 {
    if (jj_done) return true;
    if (jj_3R_pommeFloat_152_4_37()) return true;
    return false;
  }

 inline bool jj_3R_number_504_9_31()
 {
    if (jj_done) return true;
    if (jj_3R_pommeInt_146_4_36()) return true;
    return false;
  }

 inline bool jj_3R_number_504_9_23()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_number_504_9_31()) {
    jj_scanpos = xsp;
    if (jj_3R_number_505_11_32()) return true;
    }
    return false;
  }

 inline bool jj_3R_access_498_11_33()
 {
    if (jj_done) return true;
    if (jj_3R_ident_134_4_4()) return true;
    return false;
  }

 inline bool jj_3_6()
 {
    if (jj_done) return true;
    if (jj_3R_identmeth_384_9_5()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_327_9_39()) return true;
    return false;
  }

 inline bool jj_3_5()
 {
    if (jj_done) return true;
    if (jj_3R_ident_134_4_4()) return true;
    if (jj_scan_token(BRACKETL)) return true;
    if (jj_3R_exp_398_9_38()) return true;
    return false;
  }

 inline bool jj_3R_access_496_9_29()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_5()) {
    jj_scanpos = xsp;
    if (jj_3_6()) {
    jj_scanpos = xsp;
    if (jj_3R_access_498_11_33()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_exp_398_9_38()
 {
    if (jj_done) return true;
    if (jj_3R_exp1_412_9_40()) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_491_11_35()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_489_9_34()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_496_9_29()) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_489_9_30()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccesP_489_9_34()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccesP_491_11_35()) return true;
    }
    return false;
  }

 inline bool jj_3R_type_392_9_20()
 {
    if (jj_done) return true;
    if (jj_3R_ident_134_4_4()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_386_11_19()
 {
    if (jj_done) return true;
    if (jj_scan_token(TILDE)) return true;
    if (jj_3R_ident_134_4_4()) return true;
    return false;
  }

 inline bool jj_3R_listacces_483_9_22()
 {
    if (jj_done) return true;
    if (jj_3R_access_496_9_29()) return true;
    if (jj_3R_listaccesP_489_9_30()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_385_11_18()
 {
    if (jj_done) return true;
    if (jj_3R_identOp_140_9_25()) return true;
    return false;
  }

 inline bool jj_3_2()
 {
    if (jj_done) return true;
    if (jj_3R_var_341_9_2()) return true;
    return false;
  }

 inline bool jj_3R_fact_478_11_16()
 {
    if (jj_done) return true;
    if (jj_scan_token(NULLEXP)) return true;
    return false;
  }

 inline bool jj_3R_identmeth_384_9_5()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_identmeth_384_9_17()) {
    jj_scanpos = xsp;
    if (jj_3R_identmeth_385_11_18()) {
    jj_scanpos = xsp;
    if (jj_3R_identmeth_386_11_19()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_identmeth_384_9_17()
 {
    if (jj_done) return true;
    if (jj_3R_ident_134_4_4()) return true;
    return false;
  }

 inline bool jj_3R_fact_476_11_15()
 {
    if (jj_done) return true;
    if (jj_3R_pommeString_158_4_24()) return true;
    return false;
  }

 inline bool jj_3R_fact_475_11_13()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_fact_475_11_14()
 {
    if (jj_done) return true;
    if (jj_3R_number_504_9_23()) return true;
    return false;
  }

 inline bool jj_3R_fact_474_11_12()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_fact_472_11_11()
 {
    if (jj_done) return true;
    if (jj_3R_listacces_483_9_22()) return true;
    return false;
  }

 inline bool jj_3R_fact_471_9_10()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEWEXP)) return true;
    if (jj_3R_ident_134_4_4()) return true;
    if (jj_scan_token(PARENTL)) return true;
    return false;
  }

 inline bool jj_3R_fact_471_9_3()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_fact_471_9_10()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_472_11_11()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_474_11_12()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_475_11_13()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_475_11_14()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_476_11_15()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_478_11_16()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_classes_183_11_7()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODDED)) return true;
    if (jj_scan_token(CLASS)) return true;
    return false;
  }

 inline bool jj_3_3()
 {
    if (jj_done) return true;
    if (jj_3R_var_341_9_2()) return true;
    return false;
  }

 inline bool jj_3R_fact2_465_11_49()
 {
    if (jj_done) return true;
    if (jj_scan_token(TILDE)) return true;
    return false;
  }

 inline bool jj_3R_fact2_464_11_48()
 {
    if (jj_done) return true;
    if (jj_scan_token(EXCLAMATION)) return true;
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
  JJCalls       jj_2_rtns[7];
  bool          jj_rescan;
  int           jj_gc;
  Token        *jj_scanpos, *jj_lastpos;
  int           jj_la;
  /** Whether we are looking ahead. */
  bool          jj_lookingAhead;
  bool          jj_semLA;
  int           jj_gen;
  int           jj_la1[39];
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
