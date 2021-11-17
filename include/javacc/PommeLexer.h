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

 inline bool jj_3R_classes_178_9_6()
 {
    if (jj_done) return true;
    if (jj_scan_token(CLASS)) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_header_368_9_54()
 {
    if (jj_done) return true;
    if (jj_3R_type_389_9_29()) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_headersP_362_11_61()
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

 inline bool jj_3R_headersP_360_9_55()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_headersP_360_9_60()) {
    jj_scanpos = xsp;
    if (jj_3R_headersP_362_11_61()) return true;
    }
    return false;
  }

 inline bool jj_3R_headersP_360_9_60()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMA)) return true;
    if (jj_3R_header_368_9_54()) return true;
    if (jj_3R_headersP_360_9_55()) return true;
    return false;
  }

 inline bool jj_3R_headers_355_11_38()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_headers_353_9_25()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_headers_353_9_37()) {
    jj_scanpos = xsp;
    if (jj_3R_headers_355_11_38()) return true;
    }
    return false;
  }

 inline bool jj_3R_headers_353_9_37()
 {
    if (jj_done) return true;
    if (jj_3R_header_368_9_54()) return true;
    if (jj_3R_headersP_360_9_55()) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_493_59_118()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_vexp_348_11_105()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_491_57_117()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_502_9_47()) return true;
    if (jj_3R_listaccesP_488_9_97()) return true;
    return false;
  }

 inline bool jj_3R_vexp_346_9_104()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASSIGNEMENT)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_vexp_346_9_96()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_vexp_346_9_104()) {
    jj_scanpos = xsp;
    if (jj_3R_vexp_348_11_105()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommeString_156_4_32()
 {
    if (jj_done) return true;
    if (jj_scan_token(STRING)) return true;
    return false;
  }

 inline bool jj_3R_var_340_11_11()
 {
    if (jj_done) return true;
    if (jj_scan_token(CONST)) return true;
    if (jj_3R_type_389_9_29()) return true;
    if (jj_3R_ident_132_4_22()) return true;
    if (jj_3R_vexp_346_9_96()) return true;
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

 inline bool jj_3R_var_339_9_10()
 {
    if (jj_done) return true;
    if (jj_3R_type_389_9_29()) return true;
    if (jj_3R_ident_132_4_22()) return true;
    if (jj_3R_vexp_346_9_96()) return true;
    return false;
  }

 inline bool jj_3R_listexpP_334_11_136()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_pommeFloat_150_4_59()
 {
    if (jj_done) return true;
    if (jj_scan_token(FLOAT)) return true;
    return false;
  }

 inline bool jj_3R_listexpP_332_9_135()
 {
    if (jj_done) return true;
    if (jj_scan_token(COMMA)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_3R_listexpP_332_9_126()) return true;
    return false;
  }

 inline bool jj_3R_listexpP_332_9_126()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexpP_332_9_135()) {
    jj_scanpos = xsp;
    if (jj_3R_listexpP_334_11_136()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_297_43_86()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_297_43_85()
 {
    if (jj_done) return true;
    if (jj_scan_token(DECR)) return true;
    return false;
  }

 inline bool jj_3R_instr_296_43_84()
 {
    if (jj_done) return true;
    if (jj_scan_token(INCR)) return true;
    return false;
  }

 inline bool jj_3R_pommeInt_144_4_58()
 {
    if (jj_done) return true;
    if (jj_scan_token(INT)) return true;
    return false;
  }

 inline bool jj_3R_listexp_327_11_88()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_identOp_138_9_33()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIEROPERATOR)) return true;
    return false;
  }

 inline bool jj_3R_instr_294_43_83()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTREQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_instr_293_43_82()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTLEQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_instr_292_43_81()
 {
    if (jj_done) return true;
    if (jj_scan_token(ANDEQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_listexp_325_9_87()
 {
    if (jj_done) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_3R_listexpP_332_9_126()) return true;
    return false;
  }

 inline bool jj_3R_instr_291_43_80()
 {
    if (jj_done) return true;
    if (jj_scan_token(OREQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_listexp_325_9_71()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listexp_325_9_87()) {
    jj_scanpos = xsp;
    if (jj_3R_listexp_327_11_88()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_290_43_79()
 {
    if (jj_done) return true;
    if (jj_scan_token(MULTEQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_instr_289_43_78()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIVEQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_320_11_92()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_instr_288_43_77()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUSEQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_instr_287_43_76()
 {
    if (jj_done) return true;
    if (jj_scan_token(ADDEQ)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_number_510_11_51()
 {
    if (jj_done) return true;
    if (jj_3R_pommeFloat_150_4_59()) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_318_9_91()
 {
    if (jj_done) return true;
    if (jj_scan_token(ELSE)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_270_9_26()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_pommeElse_318_9_73()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_pommeElse_318_9_91()) {
    jj_scanpos = xsp;
    if (jj_3R_pommeElse_320_11_92()) return true;
    }
    return false;
  }

 inline bool jj_3R_ident_132_4_22()
 {
    if (jj_done) return true;
    if (jj_scan_token(IDENTIFIER)) return true;
    return false;
  }

 inline bool jj_3R_number_509_9_31()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_number_509_9_50()) {
    jj_scanpos = xsp;
    if (jj_3R_number_510_11_51()) return true;
    }
    return false;
  }

 inline bool jj_3R_number_509_9_50()
 {
    if (jj_done) return true;
    if (jj_3R_pommeInt_144_4_58()) return true;
    return false;
  }

 inline bool jj_3R_listacces_481_35_49()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_496_19_107()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_access_503_11_57()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_22()) return true;
    return false;
  }

 inline bool jj_3R_pommecase_312_9_103()
 {
    if (jj_done) return true;
    if (jj_scan_token(CASE)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_scan_token(COLON)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_270_9_26()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3_5()
 {
    if (jj_done) return true;
    if (jj_3R_identmeth_381_9_5()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_325_9_71()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_access_502_9_47()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_5()) {
    jj_scanpos = xsp;
    if (jj_3R_access_503_11_57()) return true;
    }
    return false;
  }

 inline bool jj_3R_listcases_307_11_95()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_listcases_305_11_94()
 {
    if (jj_done) return true;
    if (jj_scan_token(DEFAULTCASE)) return true;
    if (jj_scan_token(COLON)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_270_9_26()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_489_17_106()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_502_9_47()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccesP_491_57_117()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccesP_493_59_118()) return true;
    }
    return false;
  }

 inline bool jj_3R_listacces_480_25_48()
 {
    if (jj_done) return true;
    if (jj_scan_token(POINT)) return true;
    if (jj_3R_access_502_9_47()) return true;
    if (jj_3R_listaccesP_488_9_97()) return true;
    return false;
  }

 inline bool jj_3R_listcases_304_9_93()
 {
    if (jj_done) return true;
    if (jj_3R_pommecase_312_9_103()) return true;
    if (jj_3R_listcases_304_9_74()) return true;
    return false;
  }

 inline bool jj_3R_listcases_304_9_74()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listcases_304_9_93()) {
    jj_scanpos = xsp;
    if (jj_3R_listcases_305_11_94()) {
    jj_scanpos = xsp;
    if (jj_3R_listcases_307_11_95()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_instr_286_25_75()
 {
    if (jj_done) return true;
    if (jj_scan_token(ASSIGNEMENT)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_listaccesP_488_9_97()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listaccesP_489_17_106()) {
    jj_scanpos = xsp;
    if (jj_3R_listaccesP_496_19_107()) return true;
    }
    return false;
  }

 inline bool jj_3R_listacces_480_9_30()
 {
    if (jj_done) return true;
    if (jj_3R_access_502_9_47()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_listacces_480_25_48()) {
    jj_scanpos = xsp;
    if (jj_3R_listacces_481_35_49()) return true;
    }
    return false;
  }

 inline bool jj_3R_instr_286_11_70()
 {
    if (jj_done) return true;
    if (jj_3R_listacces_480_9_30()) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_instr_286_25_75()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_287_43_76()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_288_43_77()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_289_43_78()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_290_43_79()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_291_43_80()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_292_43_81()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_293_43_82()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_294_43_83()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_296_43_84()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_297_43_85()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_297_43_86()) return true;
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

 inline bool jj_3R_instr_285_11_69()
 {
    if (jj_done) return true;
    if (jj_scan_token(SWITCH)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_listcases_304_9_74()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_instr_284_11_68()
 {
    if (jj_done) return true;
    if (jj_scan_token(PRINT)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_fact_475_11_18()
 {
    if (jj_done) return true;
    if (jj_scan_token(NULLEXP)) return true;
    return false;
  }

 inline bool jj_3R_instr_283_11_67()
 {
    if (jj_done) return true;
    if (jj_scan_token(IF)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_270_9_26()) return true;
    if (jj_scan_token(BRACER)) return true;
    if (jj_3R_pommeElse_318_9_73()) return true;
    return false;
  }

 inline bool jj_3R_instr_283_11_66()
 {
    if (jj_done) return true;
    if (jj_scan_token(BREAK)) return true;
    return false;
  }

 inline bool jj_3R_fact_473_11_17()
 {
    if (jj_done) return true;
    if (jj_3R_pommeString_156_4_32()) return true;
    return false;
  }

 inline bool jj_3R_instr_281_11_65()
 {
    if (jj_done) return true;
    if (jj_scan_token(WHILE)) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_scan_token(PARENTR)) return true;
    if (jj_scan_token(BRACEL)) return true;
    if (jj_3R_instrs_270_9_26()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_fact_472_11_16()
 {
    if (jj_done) return true;
    if (jj_3R_number_509_9_31()) return true;
    return false;
  }

 inline bool jj_3R_fact_472_11_15()
 {
    if (jj_done) return true;
    if (jj_scan_token(FALSE)) return true;
    return false;
  }

 inline bool jj_3R_instr_280_11_64()
 {
    if (jj_done) return true;
    if (jj_scan_token(RETURN)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    return false;
  }

 inline bool jj_3R_fact_471_11_14()
 {
    if (jj_done) return true;
    if (jj_scan_token(TRUE)) return true;
    return false;
  }

 inline bool jj_3R_instr_279_11_63()
 {
    if (jj_done) return true;
    if (jj_scan_token(DECR)) return true;
    if (jj_3R_listacces_480_9_30()) return true;
    return false;
  }

 inline bool jj_3R_instr_278_11_62()
 {
    if (jj_done) return true;
    if (jj_scan_token(INCR)) return true;
    if (jj_3R_listacces_480_9_30()) return true;
    return false;
  }

 inline bool jj_3R_fact_469_11_13()
 {
    if (jj_done) return true;
    if (jj_3R_listacces_480_9_30()) return true;
    return false;
  }

 inline bool jj_3_3()
 {
    if (jj_done) return true;
    if (jj_3R_var_339_9_3()) return true;
    return false;
  }

 inline bool jj_3R_instr_277_9_56()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_3()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_278_11_62()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_279_11_63()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_280_11_64()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_281_11_65()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_283_11_66()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_283_11_67()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_284_11_68()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_285_11_69()) {
    jj_scanpos = xsp;
    if (jj_3R_instr_286_11_70()) return true;
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

 inline bool jj_3R_fact_468_9_12()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEWEXP)) return true;
    if (jj_3R_ident_132_4_22()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_listexp_325_9_71()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_instrs_272_11_40()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_fact2_462_11_130()
 {
    if (jj_done) return true;
    if (jj_scan_token(TILDE)) return true;
    if (jj_3R_fact2_458_9_119()) return true;
    return false;
  }

 inline bool jj_3R_fact2_461_11_129()
 {
    if (jj_done) return true;
    if (jj_scan_token(EXCLAMATION)) return true;
    if (jj_3R_fact2_458_9_119()) return true;
    return false;
  }

 inline bool jj_3R_fact2_460_11_128()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    if (jj_3R_fact2_458_9_119()) return true;
    return false;
  }

 inline bool jj_3R_fact2_459_11_127()
 {
    if (jj_done) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_exp_395_9_72()) return true;
    if (jj_scan_token(PARENTR)) return true;
    return false;
  }

 inline bool jj_3R_instrs_270_9_26()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_instrs_270_9_39()) {
    jj_scanpos = xsp;
    if (jj_3R_instrs_272_11_40()) return true;
    }
    return false;
  }

 inline bool jj_3R_instrs_270_9_39()
 {
    if (jj_done) return true;
    if (jj_3R_instr_277_9_56()) return true;
    if (jj_scan_token(SEMICOLON)) return true;
    if (jj_3R_instrs_270_9_26()) return true;
    return false;
  }

 inline bool jj_3R_fact2_458_9_119()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3_4()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_459_11_127()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_460_11_128()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_461_11_129()) {
    jj_scanpos = xsp;
    if (jj_3R_fact2_462_11_130()) return true;
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

 inline bool jj_3R_termeP_452_11_134()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_termeP_451_11_133()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODULO)) return true;
    if (jj_3R_fact2_458_9_119()) return true;
    if (jj_3R_termeP_449_9_120()) return true;
    return false;
  }

 inline bool jj_3R_termeP_450_11_132()
 {
    if (jj_done) return true;
    if (jj_scan_token(DIV)) return true;
    if (jj_3R_fact2_458_9_119()) return true;
    if (jj_3R_termeP_449_9_120()) return true;
    return false;
  }

 inline bool jj_3R_termeP_449_9_131()
 {
    if (jj_done) return true;
    if (jj_scan_token(MULT)) return true;
    if (jj_3R_fact2_458_9_119()) return true;
    if (jj_3R_termeP_449_9_120()) return true;
    return false;
  }

 inline bool jj_3R_termeP_449_9_120()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_termeP_449_9_131()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_450_11_132()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_451_11_133()) {
    jj_scanpos = xsp;
    if (jj_3R_termeP_452_11_134()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3R_terme_443_9_108()
 {
    if (jj_done) return true;
    if (jj_3R_fact2_458_9_119()) return true;
    if (jj_3R_termeP_449_9_120()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_437_11_125()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_exp2P_436_11_124()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTL)) return true;
    if (jj_3R_terme_443_9_108()) return true;
    if (jj_3R_exp2P_433_9_109()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_435_11_123()
 {
    if (jj_done) return true;
    if (jj_scan_token(SHIFTR)) return true;
    if (jj_3R_terme_443_9_108()) return true;
    if (jj_3R_exp2P_433_9_109()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_434_11_122()
 {
    if (jj_done) return true;
    if (jj_scan_token(MINUS)) return true;
    if (jj_3R_terme_443_9_108()) return true;
    if (jj_3R_exp2P_433_9_109()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_433_9_121()
 {
    if (jj_done) return true;
    if (jj_scan_token(ADD)) return true;
    if (jj_3R_terme_443_9_108()) return true;
    if (jj_3R_exp2P_433_9_109()) return true;
    return false;
  }

 inline bool jj_3R_exp2P_433_9_109()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_exp2P_433_9_121()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_434_11_122()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_435_11_123()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_436_11_124()) {
    jj_scanpos = xsp;
    if (jj_3R_exp2P_437_11_125()) return true;
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_exp2_427_9_98()
 {
    if (jj_done) return true;
    if (jj_3R_terme_443_9_108()) return true;
    if (jj_3R_exp2P_433_9_109()) return true;
    return false;
  }

 inline bool jj_3R_pommeOverride_232_11_53()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_exp1P_421_11_116()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_exp1P_420_11_115()
 {
    if (jj_done) return true;
    if (jj_scan_token(LET)) return true;
    if (jj_3R_exp2_427_9_98()) return true;
    if (jj_3R_exp1P_415_9_99()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_419_11_114()
 {
    if (jj_done) return true;
    if (jj_scan_token(LT)) return true;
    if (jj_3R_exp2_427_9_98()) return true;
    if (jj_3R_exp1P_415_9_99()) return true;
    return false;
  }

 inline bool jj_3R_pommeOverride_230_9_34()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_pommeOverride_230_9_52()) {
    jj_scanpos = xsp;
    if (jj_3R_pommeOverride_232_11_53()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommeOverride_230_9_52()
 {
    if (jj_done) return true;
    if (jj_scan_token(OVERRIDE)) return true;
    return false;
  }

 inline bool jj_3R_exp1P_418_11_113()
 {
    if (jj_done) return true;
    if (jj_scan_token(GET)) return true;
    if (jj_3R_exp2_427_9_98()) return true;
    if (jj_3R_exp1P_415_9_99()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_417_11_112()
 {
    if (jj_done) return true;
    if (jj_scan_token(GT)) return true;
    if (jj_3R_exp2_427_9_98()) return true;
    if (jj_3R_exp1P_415_9_99()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_416_11_111()
 {
    if (jj_done) return true;
    if (jj_scan_token(NEQ)) return true;
    if (jj_3R_exp2_427_9_98()) return true;
    if (jj_3R_exp1P_415_9_99()) return true;
    return false;
  }

 inline bool jj_3R_visibility_225_11_46()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_visibility_224_11_45()
 {
    if (jj_done) return true;
    if (jj_scan_token(PROTECTED)) return true;
    return false;
  }

 inline bool jj_3R_visibility_223_11_44()
 {
    if (jj_done) return true;
    if (jj_scan_token(PRIVATE)) return true;
    return false;
  }

 inline bool jj_3R_exp1P_415_9_110()
 {
    if (jj_done) return true;
    if (jj_scan_token(EQ)) return true;
    if (jj_3R_exp2_427_9_98()) return true;
    if (jj_3R_exp1P_415_9_99()) return true;
    return false;
  }

 inline bool jj_3R_exp1P_415_9_99()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_exp1P_415_9_110()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_416_11_111()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_417_11_112()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_418_11_113()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_419_11_114()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_420_11_115()) {
    jj_scanpos = xsp;
    if (jj_3R_exp1P_421_11_116()) return true;
    }
    }
    }
    }
    }
    }
    return false;
  }

 inline bool jj_3R_visibility_221_9_28()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_visibility_221_9_43()) {
    jj_scanpos = xsp;
    if (jj_3R_visibility_223_11_44()) {
    jj_scanpos = xsp;
    if (jj_3R_visibility_224_11_45()) {
    jj_scanpos = xsp;
    if (jj_3R_visibility_225_11_46()) return true;
    }
    }
    }
    return false;
  }

 inline bool jj_3R_visibility_221_9_43()
 {
    if (jj_done) return true;
    if (jj_scan_token(PUBLIC)) return true;
    return false;
  }

 inline bool jj_3R_exp1_409_9_89()
 {
    if (jj_done) return true;
    if (jj_3R_exp2_427_9_98()) return true;
    if (jj_3R_exp1P_415_9_99()) return true;
    return false;
  }

 inline bool jj_3R_pommeStatic_216_11_42()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_expP_403_11_102()
 {
    if (jj_done) return true;
    return false;
  }

 inline bool jj_3R_pommeStatic_214_9_27()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_pommeStatic_214_9_41()) {
    jj_scanpos = xsp;
    if (jj_3R_pommeStatic_216_11_42()) return true;
    }
    return false;
  }

 inline bool jj_3R_pommeStatic_214_9_41()
 {
    if (jj_done) return true;
    if (jj_scan_token(STATIC)) return true;
    return false;
  }

 inline bool jj_3R_expP_402_11_101()
 {
    if (jj_done) return true;
    if (jj_scan_token(OR)) return true;
    if (jj_3R_exp1_409_9_89()) return true;
    if (jj_3R_expP_401_9_90()) return true;
    return false;
  }

 inline bool jj_3R_expP_401_9_100()
 {
    if (jj_done) return true;
    if (jj_scan_token(AND)) return true;
    if (jj_3R_exp1_409_9_89()) return true;
    if (jj_3R_expP_401_9_90()) return true;
    return false;
  }

 inline bool jj_3R_expP_401_9_90()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_expP_401_9_100()) {
    jj_scanpos = xsp;
    if (jj_3R_expP_402_11_101()) {
    jj_scanpos = xsp;
    if (jj_3R_expP_403_11_102()) return true;
    }
    }
    return false;
  }

 inline bool jj_3R_identfuncs_208_9_23()
 {
    if (jj_done) return true;
    if (jj_3R_pommeStatic_214_9_27()) return true;
    if (jj_3R_visibility_221_9_28()) return true;
    if (jj_3R_pommeOverride_230_9_34()) return true;
    return false;
  }

 inline bool jj_3R_exp_395_9_72()
 {
    if (jj_done) return true;
    if (jj_3R_exp1_409_9_89()) return true;
    if (jj_3R_expP_401_9_90()) return true;
    return false;
  }

 inline bool jj_3_2()
 {
    if (jj_done) return true;
    if (jj_3R_methode_201_9_2()) return true;
    return false;
  }

 inline bool jj_3R_methode_202_11_9()
 {
    if (jj_done) return true;
    if (jj_scan_token(NATIVE)) return true;
    if (jj_3R_pommeStatic_214_9_27()) return true;
    if (jj_3R_visibility_221_9_28()) return true;
    if (jj_3R_typemeth_374_9_24()) return true;
    if (jj_3R_identmeth_381_9_5()) return true;
    if (jj_scan_token(PARENTL)) return true;
    if (jj_3R_headers_353_9_25()) return true;
    if (jj_scan_token(PARENTR)) return true;
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
    if (jj_3R_instrs_270_9_26()) return true;
    if (jj_scan_token(BRACER)) return true;
    return false;
  }

 inline bool jj_3R_type_389_9_29()
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

 inline bool jj_3R_identmeth_382_11_20()
 {
    if (jj_done) return true;
    if (jj_3R_identOp_138_9_33()) return true;
    return false;
  }

 inline bool jj_3R_identmeth_381_9_19()
 {
    if (jj_done) return true;
    if (jj_3R_ident_132_4_22()) return true;
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

 inline bool jj_3R_typemeth_375_11_36()
 {
    if (jj_done) return true;
    if (jj_3R_type_389_9_29()) return true;
    return false;
  }

 inline bool jj_3R_classes_181_11_7()
 {
    if (jj_done) return true;
    if (jj_scan_token(MODDED)) return true;
    if (jj_scan_token(CLASS)) return true;
    return false;
  }

 inline bool jj_3R_typemeth_374_9_24()
 {
    if (jj_done) return true;
    Token * xsp;
    xsp = jj_scanpos;
    if (jj_3R_typemeth_374_9_35()) {
    jj_scanpos = xsp;
    if (jj_3R_typemeth_375_11_36()) return true;
    }
    return false;
  }

 inline bool jj_3R_typemeth_374_9_35()
 {
    if (jj_done) return true;
    if (jj_scan_token(VOID)) return true;
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
