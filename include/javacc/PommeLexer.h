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
void listaccess();
void listaccessP();
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

 inline bool jj_3R_headersP_369_9_42()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_headersP_369_9_50()) {
    jj_scanpos = xsp;
    if (jj_3R_headersP_371_11_51()) return true;
    }
    return false;
  }

 inline bool jj_3R_headersP_369_9_50()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMA)) return true;
    if (jj_3R_header_377_9_41()) return true;
    if (jj_3R_headersP_369_9_42()) return true;
    return false;
  }

 inline bool jj_3R_headers_364_11_32()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3_1()
 {
    if (jj_done) return true;
    if (jj_3R_classes_182_9_1()) return true;
    return false;
  }

 inline bool jj_3R_listaccessP_503_59_114()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_headers_362_9_22()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_headers_362_9_31()) {
    jj_scanpos = xsp;
    if (jj_3R_headers_364_11_32()) return true;
    }
    return false;
  }

 inline bool jj_3R_headers_362_9_31()
 {
    if (jj_done) return true;
    if (jj_3R_header_377_9_41()) return true;
    if (jj_3R_headersP_369_9_42()) return true;
    return false;
  }

 inline bool jj_3R_listaccessP_502_59_113()
 {
    if (jj_done) return true;
    if (jj_scan_token(BRACKETL)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(BRACKETR)) return true;
    if (jj_3R_listaccessP_498_9_89()) return true;
    return false;
  }

 inline bool jj_3R_vexp_357_11_97()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccessP_501_57_112()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_513_9_35()) return true;
    if (jj_3R_listaccessP_498_9_89()) return true;
    return false;
  }

 inline bool jj_3R_vexp_355_9_96()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASSIGNEMENT)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_vexp_355_9_88()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_vexp_355_9_96()) {
    jj_scanpos = xsp;
    if (jj_3R_vexp_357_11_97()) return true;
    }
    return false;
  }

 inline bool jj_3R_var_349_11_11()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONST)) return true;
    if (jj_3R_type_398_9_24()) return true;
    if (jj_3R_ident_136_4_3()) return true;
    if (jj_3R_vexp_355_9_88()) return true;
    return false;
  }

 inline bool jj_3R_var_348_9_4()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_var_348_9_10()) {
    jj_scanpos = xsp;
    if (jj_3R_var_349_11_11()) return true;
    }
    return false;
  }

 inline bool jj_3R_var_348_9_10()
 {
    if (jj_done) return true;
    if (jj_3R_type_398_9_24()) return true;
    if (jj_3R_ident_136_4_3()) return true;
    if (jj_3R_vexp_355_9_88()) return true;
    return false;
  }

 inline bool jj_3R_pommeString_160_4_27()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_listexpP_343_11_127()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listexpP_341_9_126()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMA)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_3R_listexpP_341_9_121()) return true;
    return false;
  }

 inline bool jj_3R_listexpP_341_9_121()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexpP_341_9_126()) {
    jj_scanpos = xsp;
    if (jj_3R_listexpP_343_11_127()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_306_43_77()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_306_43_76()
 {
    if (jj_done) return true;
    if (jj_scan_token(DECR)) return true;
    return false;
  }

 inline bool jj_3R_pommeFloat_154_4_47()
 {
    if (jj_done) return true;
    if (jj_scan_token(FLOAT)) return true;
    return false;
  }

 inline bool jj_3R_instr_305_43_75()
 {
    if (jj_done) return true;
    if (jj_scan_token(INCR)) return true;
    return false;
  }

 inline bool jj_3R_listexp_336_11_79()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_303_43_74()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTREQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_instr_302_43_73()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTLEQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_instr_301_43_72()
 {
    if (jj_done) return true;
    if (jj_scan_token(ANDEQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_listexp_334_9_78()
 {
    if (jj_done) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_3R_listexpP_341_9_121()) return true;
    return false;
  }

 inline bool jj_3R_instr_300_43_71()
 {
    if (jj_done) return true;
    if (jj_scan_token(OREQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_pommeInt_148_4_46()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3R_listexp_334_9_62()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexp_334_9_78()) {
    jj_scanpos = xsp;
    if (jj_3R_listexp_336_11_79()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_299_43_70()
 {
    if (jj_done) return true;
    if (jj_scan_token(MULTEQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_identOp_142_9_28()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIEROPERATOR)) return true;
    return false;
  }

 inline bool jj_3R_instr_298_43_69()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIVEQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_number_521_11_40()
 {
    if (jj_done) return true;
    if (jj_3R_pommeFloat_154_4_47()) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_329_11_83()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_297_43_68()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUSEQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_instr_296_43_67()
 {
    if (jj_done) return true;
    if (jj_scan_token(ADDEQ)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_number_520_9_26()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_number_520_9_39()) {
    jj_scanpos = xsp;
    if (jj_3R_number_521_11_40()) return true;
    }
    return false;
  }

 inline bool jj_3R_number_520_9_39()
 {
    if (jj_done) return true;
    if (jj_3R_pommeInt_148_4_46()) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_327_9_82()
 {
    if (jj_done) return true;
    if (jj_scan_token(ELSE)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_278_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_327_9_64()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_pommeElse_327_9_82()) {
    jj_scanpos = xsp;
    if (jj_3R_pommeElse_329_11_83()) return true;
    }
    return false;
  }

 inline bool jj_3R_listaccessP_507_19_99()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccess_491_35_38()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccess_490_35_37()
 {
    if (jj_done) return true;
    if (jj_scan_token(BRACKETL)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(BRACKETR)) return true;
    if (jj_3R_listaccessP_498_9_89()) return true;
    return false;
  }

 inline bool jj_3R_access_514_11_44()
 {
    if (jj_done) return true;
    if (jj_3R_ident_136_4_3()) return true;
    return false;
  }

 inline bool jj_3R_ident_136_4_3()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3_6()
 {
    if (jj_done) return true;
    if (jj_3R_identmeth_391_9_6()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_334_9_62()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_access_513_9_35()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_6()) {
    jj_scanpos = xsp;
    if (jj_3R_access_514_11_44()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommecase_321_9_94()
 {
    if (jj_done) return true;
    if (jj_scan_token(CASE)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(COLON)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_278_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_listcases_316_11_86()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccessP_499_17_98()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_513_9_35()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccessP_501_57_112()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccessP_502_59_113()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccessP_503_59_114()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_listcases_314_11_85()
 {
    if (jj_done) return true;
    if (jj_scan_token(DEFAULTCASE)) return true;
    if (jj_scan_token(COLON)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_278_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_listaccess_489_25_36()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_513_9_35()) return true;
    if (jj_3R_listaccessP_498_9_89()) return true;
    return false;
  }

 inline bool jj_3R_listcases_313_9_84()
 {
    if (jj_done) return true;
    if (jj_3R_pommecase_321_9_94()) return true;
    if (jj_3R_listcases_313_9_65()) return true;
    return false;
  }

 inline bool jj_3R_listcases_313_9_65()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listcases_313_9_84()) {
    jj_scanpos = xsp;
    if (jj_3R_listcases_314_11_85()) {
    jj_scanpos = xsp;
    if (jj_3R_listcases_316_11_86()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_instr_295_26_66()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASSIGNEMENT)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_listaccessP_498_9_89()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccessP_499_17_98()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccessP_507_19_99()) return true;
    }
    return false;
  }

 inline bool jj_3R_listaccess_489_9_25()
 {
    if (jj_done) return true;
    if (jj_3R_access_513_9_35()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccess_489_25_36()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccess_490_35_37()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccess_491_35_38()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_instr_295_11_61()
 {
    if (jj_done) return true;
    if (jj_3R_listaccess_489_9_25()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_instr_295_26_66()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_296_43_67()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_297_43_68()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_298_43_69()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_299_43_70()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_300_43_71()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_301_43_72()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_302_43_73()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_303_43_74()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_305_43_75()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_306_43_76()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_306_43_77()) return true;
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

 inline bool jj_3R_instr_294_11_60()
 {
    if (jj_done) return true;
    if (jj_scan_token(SWITCH)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_listcases_313_9_65()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_instr_293_11_59()
 {
    if (jj_done) return true;
    if (jj_scan_token(PRINT)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_fact_484_11_18()
 {
    if (jj_done) return true;
    if (jj_scan_token(NULLEXP)) return true;
    return false;
  }

 inline bool jj_3R_instr_292_11_57()
 {
    if (jj_done) return true;
    if (jj_scan_token(BREAK)) return true;
    return false;
  }

 inline bool jj_3R_instr_292_11_58()
 {
    if (jj_done) return true;
    if (jj_scan_token(IF)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_278_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    if (jj_3R_pommeElse_327_9_64()) return true;
    return false;
  }

 inline bool jj_3R_fact_482_11_17()
 {
    if (jj_done) return true;
    if (jj_3R_pommeString_160_4_27()) return true;
    return false;
  }

 inline bool jj_3R_instr_290_11_56()
 {
    if (jj_done) return true;
    if (jj_scan_token(WHILE)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_278_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_fact_481_11_16()
 {
    if (jj_done) return true;
    if (jj_3R_number_520_9_26()) return true;
    return false;
  }

 inline bool jj_3R_fact_481_11_15()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_instr_289_11_55()
 {
    if (jj_done) return true;
    if (jj_scan_token(RETURN)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    return false;
  }

 inline bool jj_3R_fact_480_11_14()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_instr_288_11_54()
 {
    if (jj_done) return true;
    if (jj_scan_token(DELETEEXP)) return true;
    if (jj_3R_listaccess_489_9_25()) return true;
    return false;
  }

 inline bool jj_3R_instr_287_11_53()
 {
    if (jj_done) return true;
    if (jj_scan_token(DECR)) return true;
    if (jj_3R_listaccess_489_9_25()) return true;
    return false;
  }

 inline bool jj_3R_fact_478_11_13()
 {
    if (jj_done) return true;
    if (jj_3R_listaccess_489_9_25()) return true;
    return false;
  }

 inline bool jj_3R_instr_286_11_52()
 {
    if (jj_done) return true;
    if (jj_scan_token(INCR)) return true;
    if (jj_3R_listaccess_489_9_25()) return true;
    return false;
  }

 inline bool jj_3R_fact_477_9_12()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEWEXP)) return true;
    if (jj_3R_ident_136_4_3()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_334_9_62()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_fact_477_9_5()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_fact_477_9_12()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_478_11_13()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_480_11_14()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_481_11_15()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_481_11_16()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_482_11_17()) {
    jj_scanpos = xsp;
    if (jj_3R_fact_484_11_18()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3_4()
 {
    if (jj_done) return true;
    if (jj_3R_var_348_9_4()) return true;
    return false;
  }

 inline bool jj_3R_instr_285_9_43()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_4()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_286_11_52()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_287_11_53()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_288_11_54()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_289_11_55()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_290_11_56()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_292_11_57()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_292_11_58()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_293_11_59()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_294_11_60()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_295_11_61()) return true;
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

 inline bool jj_3R_fact2_471_11_111()
 {
    if (jj_done) return true;
    if (jj_scan_token(TILDE)) return true;
    if (jj_3R_fact2_467_9_95()) return true;
    return false;
  }

 inline bool jj_3R_instrs_280_11_34()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_fact2_470_11_110()
 {
    if (jj_done) return true;
    if (jj_scan_token(EXCLAMATION)) return true;
    if (jj_3R_fact2_467_9_95()) return true;
    return false;
  }

 inline bool jj_3R_fact2_469_11_109()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    if (jj_3R_fact2_467_9_95()) return true;
    return false;
  }

 inline bool jj_3R_fact2_468_11_108()
 {
    if (jj_done) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_404_9_45()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_instrs_278_9_23()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_instrs_278_9_33()) {
    jj_scanpos = xsp;
    if (jj_3R_instrs_280_11_34()) return true;
    }
    return false;
  }

 inline bool jj_3R_instrs_278_9_33()
 {
    if (jj_done) return true;
    if (jj_3R_instr_285_9_43()) return true;
    if (jj_scan_token(SEMICOLON)) return true;
    if (jj_3R_instrs_278_9_23()) return true;
    return false;
  }

 inline bool jj_3R_fact2_467_9_95()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_5()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_468_11_108()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_469_11_109()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_470_11_110()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_471_11_111()) return true;
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3_5()
 {
    if (jj_done) return true;
    if (jj_3R_fact_477_9_5()) return true;
    return false;
  }

 inline bool jj_3R_termeP_461_11_125()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_termeP_460_11_124()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODULO)) return true;
    if (jj_3R_fact2_467_9_95()) return true;
    if (jj_3R_termeP_458_9_115()) return true;
    return false;
  }

 inline bool jj_3R_termeP_459_11_123()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIV)) return true;
    if (jj_3R_fact2_467_9_95()) return true;
    if (jj_3R_termeP_458_9_115()) return true;
    return false;
  }

 inline bool jj_3R_termeP_458_9_122()
 {
    if (jj_done) return true;
    if (jj_scan_token(MULT)) return true;
    if (jj_3R_fact2_467_9_95()) return true;
    if (jj_3R_termeP_458_9_115()) return true;
    return false;
  }

 inline bool jj_3R_termeP_458_9_115()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_termeP_458_9_122()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_459_11_123()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_460_11_124()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_461_11_125()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3R_terme_452_9_87()
 {
    if (jj_done) return true;
    if (jj_3R_fact2_467_9_95()) return true;
    if (jj_3R_termeP_458_9_115()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_446_11_120()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_exp2P_445_11_119()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTL)) return true;
    if (jj_3R_terme_452_9_87()) return true;
    if (jj_3R_exp2P_442_9_100()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_444_11_118()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTR)) return true;
    if (jj_3R_terme_452_9_87()) return true;
    if (jj_3R_exp2P_442_9_100()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_443_11_117()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    if (jj_3R_terme_452_9_87()) return true;
    if (jj_3R_exp2P_442_9_100()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_442_9_116()
 {
    if (jj_done) return true;
    if (jj_scan_token(ADD)) return true;
    if (jj_3R_terme_452_9_87()) return true;
    if (jj_3R_exp2P_442_9_100()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_442_9_100()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_exp2P_442_9_116()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_443_11_117()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_444_11_118()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_445_11_119()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_446_11_120()) return true;
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_exp2_436_9_80()
 {
    if (jj_done) return true;
    if (jj_3R_terme_452_9_87()) return true;
    if (jj_3R_exp2P_442_9_100()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_430_11_107()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_exp1P_429_11_106()
 {
    if (jj_done) return true;
    if (jj_scan_token(LET)) return true;
    if (jj_3R_exp2_436_9_80()) return true;
    if (jj_3R_exp1P_424_9_90()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_428_11_105()
 {
    if (jj_done) return true;
    if (jj_scan_token(LT)) return true;
    if (jj_3R_exp2_436_9_80()) return true;
    if (jj_3R_exp1P_424_9_90()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_427_11_104()
 {
    if (jj_done) return true;
    if (jj_scan_token(GET)) return true;
    if (jj_3R_exp2_436_9_80()) return true;
    if (jj_3R_exp1P_424_9_90()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_426_11_103()
 {
    if (jj_done) return true;
    if (jj_scan_token(GT)) return true;
    if (jj_3R_exp2_436_9_80()) return true;
    if (jj_3R_exp1P_424_9_90()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_425_11_102()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEQ)) return true;
    if (jj_3R_exp2_436_9_80()) return true;
    if (jj_3R_exp1P_424_9_90()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_424_9_101()
 {
    if (jj_done) return true;
    if (jj_scan_token(EQ)) return true;
    if (jj_3R_exp2_436_9_80()) return true;
    if (jj_3R_exp1P_424_9_90()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_424_9_90()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_exp1P_424_9_101()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_425_11_102()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_426_11_103()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_427_11_104()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_428_11_105()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_429_11_106()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_430_11_107()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_null_202_36_2()
 {
    if (jj_done) return true;
    if (jj_3R_methode_210_9_9()) return true;
    return false;
  }

 inline bool jj_3R_exp1_418_9_63()
 {
    if (jj_done) return true;
    if (jj_3R_exp2_436_9_80()) return true;
    if (jj_3R_exp1P_424_9_90()) return true;
    return false;
  }

 inline bool jj_3R_expP_412_11_93()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_expP_411_11_92()
 {
    if (jj_done) return true;
    if (jj_scan_token(OR)) return true;
    if (jj_3R_exp1_418_9_63()) return true;
    if (jj_3R_expP_410_9_81()) return true;
    return false;
  }

 inline bool jj_3_2()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_scan_token(57)) {
    jj_scanpos = xsp;
    if (jj_3R_null_202_36_2()) return true;
    }
    return false;
  }

 inline bool jj_3R_expP_410_9_91()
 {
    if (jj_done) return true;
    if (jj_scan_token(AND)) return true;
    if (jj_3R_exp1_418_9_63()) return true;
    if (jj_3R_expP_410_9_81()) return true;
    return false;
  }

 inline bool jj_3R_expP_410_9_81()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_expP_410_9_91()) {
    jj_scanpos = xsp;
    if (jj_3R_expP_411_11_92()) {
    jj_scanpos = xsp;
    if (jj_3R_expP_412_11_93()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_exp_404_9_45()
 {
    if (jj_done) return true;
    if (jj_3R_exp1_418_9_63()) return true;
    if (jj_3R_expP_410_9_81()) return true;
    return false;
  }

 inline bool jj_3_3()
 {
    if (jj_done) return true;
    if (jj_3R_ident_136_4_3()) return true;
    if (jj_scan_token(PARENTL)) return true;
    return false;
  }

 inline bool jj_3R_methode_210_9_9()
 {
    if (jj_done) return true;
    if (jj_3R_typemeth_384_9_21()) return true;
    if (jj_3R_identmeth_391_9_6()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_headers_362_9_22()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_278_9_23()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_type_398_9_24()
 {
    if (jj_done) return true;
    if (jj_3R_ident_136_4_3()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_392_11_20()
 {
    if (jj_done) return true;
    if (jj_3R_identOp_142_9_28()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_391_9_19()
 {
    if (jj_done) return true;
    if (jj_3R_ident_136_4_3()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_391_9_6()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_identmeth_391_9_19()) {
    jj_scanpos = xsp;
    if (jj_3R_identmeth_392_11_20()) return true;
    }
    return false;
  }

 inline bool jj_3R_typemeth_385_11_30()
 {
    if (jj_done) return true;
    if (jj_3R_type_398_9_24()) return true;
    return false;
  }

 inline bool jj_3R_typemeth_384_9_29()
 {
    if (jj_done) return true;
    if (jj_scan_token(VOID)) return true;
    return false;
  }

 inline bool jj_3R_typemeth_384_9_21()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_typemeth_384_9_29()) {
    jj_scanpos = xsp;
    if (jj_3R_typemeth_385_11_30()) return true;
    }
    return false;
  }

 inline bool jj_3R_header_378_12_49()
 {
    if (jj_done) return true;
    if (jj_3R_type_398_9_24()) return true;
    if (jj_3R_ident_136_4_3()) return true;
    return false;
  }

 inline bool jj_3R_classes_185_11_8()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODDED)) return true;
    if (jj_scan_token(CLASS)) return true;
    return false;
  }

 inline bool jj_3R_header_377_9_41()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_header_377_9_48()) {
    jj_scanpos = xsp;
    if (jj_3R_header_378_12_49()) return true;
    }
    return false;
  }

 inline bool jj_3R_header_377_9_48()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONST)) return true;
    if (jj_3R_type_398_9_24()) return true;
    if (jj_3R_ident_136_4_3()) return true;
    return false;
  }

 inline bool jj_3R_classes_182_9_1()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_classes_182_9_7()) {
    jj_scanpos = xsp;
    if (jj_3R_classes_185_11_8()) return true;
    }
    return false;
  }

 inline bool jj_3R_classes_182_9_7()
 {
    if (jj_done) return true;
    if (jj_scan_token(CLASS)) return true;
    if (jj_3R_ident_136_4_3()) return true;
    return false;
  }

 inline bool jj_3R_headersP_371_11_51()
 {
    if (jj_done) return true;
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
  int           jj_la1[43];
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
