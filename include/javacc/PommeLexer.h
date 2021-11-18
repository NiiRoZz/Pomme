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

 inline bool jj_3R_header_372_9_40()
 {
    if (jj_done) return true;
    if (jj_3R_type_392_9_24()) return true;
    if (jj_3R_ident_132_4_3()) return true;
    return false;
  }

 inline bool jj_3R_classes_178_9_1()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_classes_178_9_7()) {
    jj_scanpos = xsp;
    if (jj_3R_classes_181_11_8()) return true;
    }
    return false;
  }

 inline bool jj_3R_classes_178_9_7()
 {
    if (jj_done) return true;
    if (jj_scan_token(CLASS)) return true;
    if (jj_3R_ident_132_4_3()) return true;
    return false;
  }

 inline bool jj_3R_headersP_366_11_47()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_headersP_364_9_41()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_headersP_364_9_46()) {
    jj_scanpos = xsp;
    if (jj_3R_headersP_366_11_47()) return true;
    }
    return false;
  }

 inline bool jj_3R_headersP_364_9_46()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMA)) return true;
    if (jj_3R_header_372_9_40()) return true;
    if (jj_3R_headersP_364_9_41()) return true;
    return false;
  }

 inline bool jj_3R_headers_359_11_32()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3_1()
 {
    if (jj_done) return true;
    if (jj_3R_classes_178_9_1()) return true;
    return false;
  }

 inline bool jj_3R_headers_357_9_22()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_headers_357_9_31()) {
    jj_scanpos = xsp;
    if (jj_3R_headers_359_11_32()) return true;
    }
    return false;
  }

 inline bool jj_3R_headers_357_9_31()
 {
    if (jj_done) return true;
    if (jj_3R_header_372_9_40()) return true;
    if (jj_3R_headersP_364_9_41()) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_495_59_104()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_vexp_352_11_91()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_494_57_103()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_505_9_35()) return true;
    if (jj_3R_listaccesP_491_9_83()) return true;
    return false;
  }

 inline bool jj_3R_vexp_350_9_90()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASSIGNEMENT)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_vexp_350_9_82()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_vexp_350_9_90()) {
    jj_scanpos = xsp;
    if (jj_3R_vexp_352_11_91()) return true;
    }
    return false;
  }

 inline bool jj_3R_var_344_11_11()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONST)) return true;
    if (jj_3R_type_392_9_24()) return true;
    if (jj_3R_ident_132_4_3()) return true;
    if (jj_3R_vexp_350_9_82()) return true;
    return false;
  }

 inline bool jj_3R_var_343_9_4()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_var_343_9_10()) {
    jj_scanpos = xsp;
    if (jj_3R_var_344_11_11()) return true;
    }
    return false;
  }

 inline bool jj_3R_var_343_9_10()
 {
    if (jj_done) return true;
    if (jj_3R_type_392_9_24()) return true;
    if (jj_3R_ident_132_4_3()) return true;
    if (jj_3R_vexp_350_9_82()) return true;
    return false;
  }

 inline bool jj_3R_pommeString_156_4_27()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_listexpP_338_11_122()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listexpP_336_9_121()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMA)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_3R_listexpP_336_9_112()) return true;
    return false;
  }

 inline bool jj_3R_listexpP_336_9_112()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexpP_336_9_121()) {
    jj_scanpos = xsp;
    if (jj_3R_listexpP_338_11_122()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommeFloat_150_4_45()
 {
    if (jj_done) return true;
    if (jj_scan_token(FLOAT)) return true;
    return false;
  }

 inline bool jj_3R_instr_301_43_72()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_301_43_71()
 {
    if (jj_done) return true;
    if (jj_scan_token(DECR)) return true;
    return false;
  }

 inline bool jj_3R_instr_300_43_70()
 {
    if (jj_done) return true;
    if (jj_scan_token(INCR)) return true;
    return false;
  }

 inline bool jj_3R_listexp_331_11_74()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_298_43_69()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTREQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_instr_297_43_68()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTLEQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_instr_296_43_67()
 {
    if (jj_done) return true;
    if (jj_scan_token(ANDEQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_pommeInt_144_4_44()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3R_listexp_329_9_73()
 {
    if (jj_done) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_3R_listexpP_336_9_112()) return true;
    return false;
  }

 inline bool jj_3R_instr_295_43_66()
 {
    if (jj_done) return true;
    if (jj_scan_token(OREQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_identOp_138_9_28()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIEROPERATOR)) return true;
    return false;
  }

 inline bool jj_3R_listexp_329_9_57()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexp_329_9_73()) {
    jj_scanpos = xsp;
    if (jj_3R_listexp_331_11_74()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_294_43_65()
 {
    if (jj_done) return true;
    if (jj_scan_token(MULTEQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_instr_293_43_64()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIVEQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_324_11_78()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_292_43_63()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUSEQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_instr_291_43_62()
 {
    if (jj_done) return true;
    if (jj_scan_token(ADDEQ)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_number_513_11_39()
 {
    if (jj_done) return true;
    if (jj_3R_pommeFloat_150_4_45()) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_322_9_77()
 {
    if (jj_done) return true;
    if (jj_scan_token(ELSE)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_274_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_322_9_59()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_pommeElse_322_9_77()) {
    jj_scanpos = xsp;
    if (jj_3R_pommeElse_324_11_78()) return true;
    }
    return false;
  }

 inline bool jj_3R_number_512_9_26()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_number_512_9_38()) {
    jj_scanpos = xsp;
    if (jj_3R_number_513_11_39()) return true;
    }
    return false;
  }

 inline bool jj_3R_number_512_9_38()
 {
    if (jj_done) return true;
    if (jj_3R_pommeInt_144_4_44()) return true;
    return false;
  }

 inline bool jj_3R_listacces_484_35_37()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_499_19_93()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_ident_132_4_3()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_access_506_11_43()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_3()) return true;
    return false;
  }

 inline bool jj_3R_pommecase_316_9_89()
 {
    if (jj_done) return true;
    if (jj_scan_token(CASE)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_scan_token(COLON)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_274_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3_6()
 {
    if (jj_done) return true;
    if (jj_3R_identmeth_385_9_6()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_329_9_57()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_access_505_9_35()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_6()) {
    jj_scanpos = xsp;
    if (jj_3R_access_506_11_43()) return true;
    }
    return false;
  }

 inline bool jj_3R_listcases_311_11_81()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listcases_309_11_80()
 {
    if (jj_done) return true;
    if (jj_scan_token(DEFAULTCASE)) return true;
    if (jj_scan_token(COLON)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_274_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_492_17_92()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_505_9_35()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccesP_494_57_103()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccesP_495_59_104()) return true;
    }
    return false;
  }

 inline bool jj_3R_listcases_308_9_79()
 {
    if (jj_done) return true;
    if (jj_3R_pommecase_316_9_89()) return true;
    if (jj_3R_listcases_308_9_60()) return true;
    return false;
  }

 inline bool jj_3R_listcases_308_9_60()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listcases_308_9_79()) {
    jj_scanpos = xsp;
    if (jj_3R_listcases_309_11_80()) {
    jj_scanpos = xsp;
    if (jj_3R_listcases_311_11_81()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_listacces_483_25_36()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_505_9_35()) return true;
    if (jj_3R_listaccesP_491_9_83()) return true;
    return false;
  }

 inline bool jj_3R_instr_290_25_61()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASSIGNEMENT)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_491_9_83()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccesP_492_17_92()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccesP_499_19_93()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_290_11_56()
 {
    if (jj_done) return true;
    if (jj_3R_listacces_483_9_25()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_instr_290_25_61()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_291_43_62()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_292_43_63()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_293_43_64()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_294_43_65()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_295_43_66()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_296_43_67()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_297_43_68()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_298_43_69()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_300_43_70()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_301_43_71()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_301_43_72()) return true;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_listacces_483_9_25()
 {
    if (jj_done) return true;
    if (jj_3R_access_505_9_35()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listacces_483_25_36()) {
    jj_scanpos = xsp;
    if (jj_3R_listacces_484_35_37()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_289_11_55()
 {
    if (jj_done) return true;
    if (jj_scan_token(SWITCH)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_listcases_308_9_60()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_instr_288_11_54()
 {
    if (jj_done) return true;
    if (jj_scan_token(PRINT)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_instr_287_11_52()
 {
    if (jj_done) return true;
    if (jj_scan_token(BREAK)) return true;
    return false;
  }

 inline bool jj_3R_instr_287_11_53()
 {
    if (jj_done) return true;
    if (jj_scan_token(IF)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_274_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    if (jj_3R_pommeElse_322_9_59()) return true;
    return false;
  }

 inline bool jj_3R_fact_478_11_18()
 {
    if (jj_done) return true;
    if (jj_scan_token(NULLEXP)) return true;
    return false;
  }

 inline bool jj_3R_instr_285_11_51()
 {
    if (jj_done) return true;
    if (jj_scan_token(WHILE)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_274_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_fact_476_11_17()
 {
    if (jj_done) return true;
    if (jj_3R_pommeString_156_4_27()) return true;
    return false;
  }

 inline bool jj_3R_instr_284_11_50()
 {
    if (jj_done) return true;
    if (jj_scan_token(RETURN)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    return false;
  }

 inline bool jj_3R_fact_475_11_16()
 {
    if (jj_done) return true;
    if (jj_3R_number_512_9_26()) return true;
    return false;
  }

 inline bool jj_3R_fact_475_11_15()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_instr_283_11_49()
 {
    if (jj_done) return true;
    if (jj_scan_token(DECR)) return true;
    if (jj_3R_listacces_483_9_25()) return true;
    return false;
  }

 inline bool jj_3R_fact_474_11_14()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_instr_282_11_48()
 {
    if (jj_done) return true;
    if (jj_scan_token(INCR)) return true;
    if (jj_3R_listacces_483_9_25()) return true;
    return false;
  }

 inline bool jj_3R_fact_472_11_13()
 {
    if (jj_done) return true;
    if (jj_3R_listacces_483_9_25()) return true;
    return false;
  }

 inline bool jj_3_4()
 {
    if (jj_done) return true;
    if (jj_3R_var_343_9_4()) return true;
    return false;
  }

 inline bool jj_3R_instr_281_9_42()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_4()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_282_11_48()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_283_11_49()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_284_11_50()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_285_11_51()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_287_11_52()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_287_11_53()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_288_11_54()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_289_11_55()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_290_11_56()) return true;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_fact_471_9_12()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEWEXP)) return true;
    if (jj_3R_ident_132_4_3()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_329_9_57()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_fact_471_9_5()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_fact_471_9_12()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_472_11_13()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_474_11_14()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_475_11_15()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_475_11_16()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_476_11_17()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_478_11_18()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_instrs_276_11_34()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_fact2_465_11_116()
 {
    if (jj_done) return true;
    if (jj_scan_token(TILDE)) return true;
    if (jj_3R_fact2_461_9_105()) return true;
    return false;
  }

 inline bool jj_3R_fact2_464_11_115()
 {
    if (jj_done) return true;
    if (jj_scan_token(EXCLAMATION)) return true;
    if (jj_3R_fact2_461_9_105()) return true;
    return false;
  }

 inline bool jj_3R_fact2_463_11_114()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    if (jj_3R_fact2_461_9_105()) return true;
    return false;
  }

 inline bool jj_3R_instrs_274_9_23()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_instrs_274_9_33()) {
    jj_scanpos = xsp;
    if (jj_3R_instrs_276_11_34()) return true;
    }
    return false;
  }

 inline bool jj_3R_instrs_274_9_33()
 {
    if (jj_done) return true;
    if (jj_3R_instr_281_9_42()) return true;
    if (jj_scan_token(SEMICOLON)) return true;
    if (jj_3R_instrs_274_9_23()) return true;
    return false;
  }

 inline bool jj_3R_fact2_462_11_113()
 {
    if (jj_done) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_398_9_58()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_fact2_461_9_105()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_5()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_462_11_113()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_463_11_114()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_464_11_115()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_465_11_116()) return true;
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3_5()
 {
    if (jj_done) return true;
    if (jj_3R_fact_471_9_5()) return true;
    return false;
  }

 inline bool jj_3R_termeP_455_11_120()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_termeP_454_11_119()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODULO)) return true;
    if (jj_3R_fact2_461_9_105()) return true;
    if (jj_3R_termeP_452_9_106()) return true;
    return false;
  }

 inline bool jj_3R_termeP_453_11_118()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIV)) return true;
    if (jj_3R_fact2_461_9_105()) return true;
    if (jj_3R_termeP_452_9_106()) return true;
    return false;
  }

 inline bool jj_3R_termeP_452_9_117()
 {
    if (jj_done) return true;
    if (jj_scan_token(MULT)) return true;
    if (jj_3R_fact2_461_9_105()) return true;
    if (jj_3R_termeP_452_9_106()) return true;
    return false;
  }

 inline bool jj_3R_termeP_452_9_106()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_termeP_452_9_117()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_453_11_118()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_454_11_119()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_455_11_120()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3R_terme_446_9_94()
 {
    if (jj_done) return true;
    if (jj_3R_fact2_461_9_105()) return true;
    if (jj_3R_termeP_452_9_106()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_440_11_111()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_exp2P_439_11_110()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTL)) return true;
    if (jj_3R_terme_446_9_94()) return true;
    if (jj_3R_exp2P_436_9_95()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_438_11_109()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTR)) return true;
    if (jj_3R_terme_446_9_94()) return true;
    if (jj_3R_exp2P_436_9_95()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_437_11_108()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    if (jj_3R_terme_446_9_94()) return true;
    if (jj_3R_exp2P_436_9_95()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_436_9_107()
 {
    if (jj_done) return true;
    if (jj_scan_token(ADD)) return true;
    if (jj_3R_terme_446_9_94()) return true;
    if (jj_3R_exp2P_436_9_95()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_436_9_95()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_exp2P_436_9_107()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_437_11_108()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_438_11_109()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_439_11_110()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_440_11_111()) return true;
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_exp2_430_9_84()
 {
    if (jj_done) return true;
    if (jj_3R_terme_446_9_94()) return true;
    if (jj_3R_exp2P_436_9_95()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_424_11_102()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_exp1P_423_11_101()
 {
    if (jj_done) return true;
    if (jj_scan_token(LET)) return true;
    if (jj_3R_exp2_430_9_84()) return true;
    if (jj_3R_exp1P_418_9_85()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_422_11_100()
 {
    if (jj_done) return true;
    if (jj_scan_token(LT)) return true;
    if (jj_3R_exp2_430_9_84()) return true;
    if (jj_3R_exp1P_418_9_85()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_421_11_99()
 {
    if (jj_done) return true;
    if (jj_scan_token(GET)) return true;
    if (jj_3R_exp2_430_9_84()) return true;
    if (jj_3R_exp1P_418_9_85()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_420_11_98()
 {
    if (jj_done) return true;
    if (jj_scan_token(GT)) return true;
    if (jj_3R_exp2_430_9_84()) return true;
    if (jj_3R_exp1P_418_9_85()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_419_11_97()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEQ)) return true;
    if (jj_3R_exp2_430_9_84()) return true;
    if (jj_3R_exp1P_418_9_85()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_418_9_96()
 {
    if (jj_done) return true;
    if (jj_scan_token(EQ)) return true;
    if (jj_3R_exp2_430_9_84()) return true;
    if (jj_3R_exp1P_418_9_85()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_418_9_85()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_exp1P_418_9_96()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_419_11_97()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_420_11_98()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_421_11_99()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_422_11_100()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_423_11_101()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_424_11_102()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_null_198_36_2()
 {
    if (jj_done) return true;
    if (jj_3R_methode_206_9_9()) return true;
    return false;
  }

 inline bool jj_3R_exp1_412_9_75()
 {
    if (jj_done) return true;
    if (jj_3R_exp2_430_9_84()) return true;
    if (jj_3R_exp1P_418_9_85()) return true;
    return false;
  }

 inline bool jj_3R_expP_406_11_88()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_expP_405_11_87()
 {
    if (jj_done) return true;
    if (jj_scan_token(OR)) return true;
    if (jj_3R_exp1_412_9_75()) return true;
    if (jj_3R_expP_404_9_76()) return true;
    return false;
  }

 inline bool jj_3_2()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_scan_token(55)) {
    jj_scanpos = xsp;
    if (jj_3R_null_198_36_2()) return true;
    }
    return false;
  }

 inline bool jj_3R_expP_404_9_86()
 {
    if (jj_done) return true;
    if (jj_scan_token(AND)) return true;
    if (jj_3R_exp1_412_9_75()) return true;
    if (jj_3R_expP_404_9_76()) return true;
    return false;
  }

 inline bool jj_3R_expP_404_9_76()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_expP_404_9_86()) {
    jj_scanpos = xsp;
    if (jj_3R_expP_405_11_87()) {
    jj_scanpos = xsp;
    if (jj_3R_expP_406_11_88()) return true;
    }
    }
    return false;
  }

 inline bool jj_3_3()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_3()) return true;
    if (jj_scan_token(PARENTL)) return true;
    return false;
  }

 inline bool jj_3R_exp_398_9_58()
 {
    if (jj_done) return true;
    if (jj_3R_exp1_412_9_75()) return true;
    if (jj_3R_expP_404_9_76()) return true;
    return false;
  }

 inline bool jj_3R_methode_206_9_9()
 {
    if (jj_done) return true;
    if (jj_3R_typemeth_378_9_21()) return true;
    if (jj_3R_identmeth_385_9_6()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_headers_357_9_22()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_274_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_type_392_9_24()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_3()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_386_11_20()
 {
    if (jj_done) return true;
    if (jj_3R_identOp_138_9_28()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_385_9_19()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_3()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_385_9_6()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_identmeth_385_9_19()) {
    jj_scanpos = xsp;
    if (jj_3R_identmeth_386_11_20()) return true;
    }
    return false;
  }

 inline bool jj_3R_typemeth_379_11_30()
 {
    if (jj_done) return true;
    if (jj_3R_type_392_9_24()) return true;
    return false;
  }

 inline bool jj_3R_typemeth_378_9_29()
 {
    if (jj_done) return true;
    if (jj_scan_token(VOID)) return true;
    return false;
  }

 inline bool jj_3R_typemeth_378_9_21()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_typemeth_378_9_29()) {
    jj_scanpos = xsp;
    if (jj_3R_typemeth_379_11_30()) return true;
    }
    return false;
  }

 inline bool jj_3R_classes_181_11_8()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODDED)) return true;
    if (jj_scan_token(CLASS)) return true;
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
  int           jj_la1[42];
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
