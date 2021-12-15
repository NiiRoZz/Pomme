/* PommeLexer.cc */
#include "PommeLexer.h"
#include "TokenMgrError.h"
#include "SimpleNode.h"
namespace Pomme {
  unsigned int jj_la1_0[] = {
0xe000000,0xc000000,0x0,0x2000000,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4000000,0x0,0x0,0x80,0x0,0xd0c00000,0xebaa80,0xd0c00000,0x0,0x20000000,0x400,0x0,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x140500,0x1005000,0x400,0x0,0x0,0x0,0x0,0x0,0x0,};
  unsigned int jj_la1_1[] = {
0x2a000000,0x2a000000,0x10000080,0x20000000,0xce010000,0x4000000,0x8010000,0xc6000000,0x40000000,0x80000000,0x0,0x10000080,0x20000000,0x2000,0x0,0x0,0xa000000,0x4000007,0x0,0x7,0x18,0x0,0x18020,0x2000,0x4000000,0x0,0x4000000,0x2000,0x4000000,0x2000000,0x0,0x1800000,0x7e0000,0x0,0x0,0x18020,0x0,0x4200,0x4200,0x4000,0x0,0x0,};
  unsigned int jj_la1_2[] = {
0x400,0x400,0x0,0x0,0x407,0x400,0x0,0x407,0x0,0x3,0x4,0x0,0x0,0x0,0x400,0x0,0x400,0x680,0x0,0x680,0x0,0x0,0x1f78,0x0,0x400,0x0,0x400,0x0,0x400,0x400,0x600,0x0,0x0,0x0,0x0,0x0,0x1f78,0x0,0x0,0x0,0x400,0x1100,};

  /** Constructor with user supplied TokenManager. */




SimpleNode          * PommeLexer::input() {/*@bgen(jjtree) PommeInput */
  ASTPommeInput *jjtn000 = new ASTPommeInput(JJTPOMMEINPUT);
  bool jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
  jjtreeOpenNodeScope(jjtn000);
    try {
      scopes();
jjtree.closeNodeScope(jjtn000, true);
                   jjtc000 = false;
                   if (jjtree.nodeCreated()) {
                    jjtreeCloseNodeScope(jjtn000);
                   }
return jjtn000;
    } catch ( ...) {
if (jjtc000) {
            jjtree.clearNodeScope(jjtn000);
            jjtc000 = false;
          } else {
            jjtree.popNode();
          }
    }
if (jjtc000) {
            jjtree.closeNodeScope(jjtn000, true);
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn000);
            }
          }
assert(false);
}


void PommeLexer::ident() {Token *t;/*@bgen(jjtree) PommeIdent */
  ASTPommeIdent *jjtn000 = new ASTPommeIdent(JJTPOMMEIDENT);
  bool jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
  jjtreeOpenNodeScope(jjtn000);
    try {
      t = jj_consume_token(IDENTIFIER);
jjtree.closeNodeScope(jjtn000, true);
                      jjtc000 = false;
                      if (jjtree.nodeCreated()) {
                       jjtreeCloseNodeScope(jjtn000);
                      }
jjtn000->m_Identifier = t->image;
    } catch ( ...) {
if (jjtc000) {
       jjtree.clearNodeScope(jjtn000);
       jjtc000 = false;
     } else {
       jjtree.popNode();
     }
    }
if (jjtc000) {
       jjtree.closeNodeScope(jjtn000, true);
       if (jjtree.nodeCreated()) {
        jjtreeCloseNodeScope(jjtn000);
       }
     }
}


void PommeLexer::identOp() {Token *t;/*@bgen(jjtree) PommeIdentOp */
  ASTPommeIdentOp *jjtn000 = new ASTPommeIdentOp(JJTPOMMEIDENTOP);
  bool jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
  jjtreeOpenNodeScope(jjtn000);
    try {
      t = jj_consume_token(IDENTIFIEROPERATOR);
jjtree.closeNodeScope(jjtn000, true);
                                   jjtc000 = false;
                                   if (jjtree.nodeCreated()) {
                                    jjtreeCloseNodeScope(jjtn000);
                                   }
jjtn000->m_Identifier = t->image;
    } catch ( ...) {
if (jjtc000) {
            jjtree.clearNodeScope(jjtn000);
            jjtc000 = false;
          } else {
            jjtree.popNode();
          }
    }
if (jjtc000) {
            jjtree.closeNodeScope(jjtn000, true);
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn000);
            }
          }
}


void PommeLexer::pommeInt() {Token *t;/*@bgen(jjtree) PommeInt */
  ASTPommeInt *jjtn000 = new ASTPommeInt(JJTPOMMEINT);
  bool jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
  jjtreeOpenNodeScope(jjtn000);
    try {
      t = jj_consume_token(INT);
jjtree.closeNodeScope(jjtn000, true);
              jjtc000 = false;
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn000);
              }
jjtn000->m_Value = std::stoull(t->image);
    } catch ( ...) {
if (jjtc000) {
       jjtree.clearNodeScope(jjtn000);
       jjtc000 = false;
     } else {
       jjtree.popNode();
     }
    }
if (jjtc000) {
       jjtree.closeNodeScope(jjtn000, true);
       if (jjtree.nodeCreated()) {
        jjtreeCloseNodeScope(jjtn000);
       }
     }
}


void PommeLexer::pommeFloat() {Token *t;/*@bgen(jjtree) PommeFloat */
  ASTPommeFloat *jjtn000 = new ASTPommeFloat(JJTPOMMEFLOAT);
  bool jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
  jjtreeOpenNodeScope(jjtn000);
    try {
      t = jj_consume_token(FLOAT);
jjtree.closeNodeScope(jjtn000, true);
                jjtc000 = false;
                if (jjtree.nodeCreated()) {
                 jjtreeCloseNodeScope(jjtn000);
                }
jjtn000->m_Value = std::stod(t->image);
    } catch ( ...) {
if (jjtc000) {
       jjtree.clearNodeScope(jjtn000);
       jjtc000 = false;
     } else {
       jjtree.popNode();
     }
    }
if (jjtc000) {
       jjtree.closeNodeScope(jjtn000, true);
       if (jjtree.nodeCreated()) {
        jjtreeCloseNodeScope(jjtn000);
       }
     }
}


void PommeLexer::pommeString() {Token *t;/*@bgen(jjtree) PommeString */
  ASTPommeString *jjtn000 = new ASTPommeString(JJTPOMMESTRING);
  bool jjtc000 = true;
  jjtree.openNodeScope(jjtn000);
  jjtreeOpenNodeScope(jjtn000);
    try {
      t = jj_consume_token(STRING);
jjtree.closeNodeScope(jjtn000, true);
                 jjtc000 = false;
                 if (jjtree.nodeCreated()) {
                  jjtreeCloseNodeScope(jjtn000);
                 }
jjtn000->m_Value = t->image;
    } catch ( ...) {
if (jjtc000) {
       jjtree.clearNodeScope(jjtn000);
       jjtc000 = false;
     } else {
       jjtree.popNode();
     }
    }
if (jjtc000) {
       jjtree.closeNodeScope(jjtn000, true);
       if (jjtree.nodeCreated()) {
        jjtreeCloseNodeScope(jjtn000);
       }
     }
}


void PommeLexer::scopes() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case CLASS:
    case ENUM:
    case TYPEDEF:
    case VOID:
    case NATIVE:
    case MODDED:
    case IDENTIFIER:{
      scope();
      jj_consume_token(SEMICOLON);
ASTPommeScopes *jjtn001 = new ASTPommeScopes(JJTPOMMESCOPES);
                              bool jjtc001 = true;
                              jjtree.openNodeScope(jjtn001);
                              jjtreeOpenNodeScope(jjtn001);
      try {
        scopes();
      } catch ( ...) {
if (jjtc001) {
                                jjtree.clearNodeScope(jjtn001);
                                jjtc001 = false;
                              } else {
                                jjtree.popNode();
                              }
      }
if (jjtc001) {
                                jjtree.closeNodeScope(jjtn001,  2);
                                if (jjtree.nodeCreated()) {
                                 jjtreeCloseNodeScope(jjtn001);
                                }
                              }
      break;
      }
    default:
      jj_la1[0] = jj_gen;
ASTPommeScinil *jjtn002 = new ASTPommeScinil(JJTPOMMESCINIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::scope() {
    if (jj_2_1(2)) {
      classes();
    } else {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case VOID:
      case NATIVE:
      case IDENTIFIER:{
        globalFunction();
        break;
        }
      case ENUM:
      case MODDED:{
        enumerate();
        break;
        }
      case TYPEDEF:{
        jj_consume_token(TYPEDEF);
        ident();
ASTPommeTypeDef *jjtn001 = new ASTPommeTypeDef(JJTPOMMETYPEDEF);
                              bool jjtc001 = true;
                              jjtree.openNodeScope(jjtn001);
                              jjtreeOpenNodeScope(jjtn001);
        try {
          ident();
        } catch ( ...) {
if (jjtc001) {
                                jjtree.clearNodeScope(jjtn001);
                                jjtc001 = false;
                              } else {
                                jjtree.popNode();
                              }
        }
if (jjtc001) {
                                jjtree.closeNodeScope(jjtn001,  2);
                                if (jjtree.nodeCreated()) {
                                 jjtreeCloseNodeScope(jjtn001);
                                }
                              }
        break;
        }
      default:
        jj_la1[1] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
    }
}


void PommeLexer::classes() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case CLASS:{
      jj_consume_token(CLASS);
      ident();
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case BRACEL:{
        jj_consume_token(BRACEL);
        decls();
ASTPommeClass *jjtn001 = new ASTPommeClass(JJTPOMMECLASS);
                                                   bool jjtc001 = true;
                                                   jjtree.openNodeScope(jjtn001);
                                                   jjtreeOpenNodeScope(jjtn001);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc001) {
                                                     jjtree.clearNodeScope(jjtn001);
                                                     jjtc001 = false;
                                                   } else {
                                                     jjtree.popNode();
                                                   }
        }
if (jjtc001) {
                                                     jjtree.closeNodeScope(jjtn001,  2);
                                                     if (jjtree.nodeCreated()) {
                                                      jjtreeCloseNodeScope(jjtn001);
                                                     }
                                                   }
        break;
        }
      case EXTENDS:{
        jj_consume_token(EXTENDS);
        ident();
        jj_consume_token(BRACEL);
        decls();
ASTPommeClassChild *jjtn002 = new ASTPommeClassChild(JJTPOMMECLASSCHILD);
                                                                                       bool jjtc002 = true;
                                                                                       jjtree.openNodeScope(jjtn002);
                                                                                       jjtreeOpenNodeScope(jjtn002);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc002) {
                                                                                         jjtree.clearNodeScope(jjtn002);
                                                                                         jjtc002 = false;
                                                                                       } else {
                                                                                         jjtree.popNode();
                                                                                       }
        }
if (jjtc002) {
                                                                                         jjtree.closeNodeScope(jjtn002,  3);
                                                                                         if (jjtree.nodeCreated()) {
                                                                                          jjtreeCloseNodeScope(jjtn002);
                                                                                         }
                                                                                       }
        break;
        }
      default:
        jj_la1[2] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
      break;
      }
    case MODDED:{
      jj_consume_token(MODDED);
      jj_consume_token(CLASS);
      ident();
      jj_consume_token(BRACEL);
      decls();
ASTPommeModdedClass *jjtn003 = new ASTPommeModdedClass(JJTPOMMEMODDEDCLASS);
                                                      bool jjtc003 = true;
                                                      jjtree.openNodeScope(jjtn003);
                                                      jjtreeOpenNodeScope(jjtn003);
      try {
        jj_consume_token(BRACER);
      } catch ( ...) {
if (jjtc003) {
                                                        jjtree.clearNodeScope(jjtn003);
                                                        jjtc003 = false;
                                                      } else {
                                                        jjtree.popNode();
                                                      }
      }
if (jjtc003) {
                                                        jjtree.closeNodeScope(jjtn003,  2);
                                                        if (jjtree.nodeCreated()) {
                                                         jjtreeCloseNodeScope(jjtn003);
                                                        }
                                                      }
      break;
      }
    default:
      jj_la1[3] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::decls() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case TILDE:
    case VOID:
    case CONST:
    case NATIVE:
    case STATIC:
    case PUBLIC:
    case PRIVATE:
    case PROTECTED:
    case OVERRIDE:
    case IDENTIFIER:{
      decl();
      jj_consume_token(SEMICOLON);
ASTPommeDecls *jjtn001 = new ASTPommeDecls(JJTPOMMEDECLS);
                             bool jjtc001 = true;
                             jjtree.openNodeScope(jjtn001);
                             jjtreeOpenNodeScope(jjtn001);
      try {
        decls();
      } catch ( ...) {
if (jjtc001) {
                               jjtree.clearNodeScope(jjtn001);
                               jjtc001 = false;
                             } else {
                               jjtree.popNode();
                             }
      }
if (jjtc001) {
                               jjtree.closeNodeScope(jjtn001,  2);
                               if (jjtree.nodeCreated()) {
                                jjtreeCloseNodeScope(jjtn001);
                               }
                             }
      break;
      }
    default:
      jj_la1[4] = jj_gen;
ASTPommeDnil *jjtn002 = new ASTPommeDnil(JJTPOMMEDNIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::decl() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case TILDE:{
      jj_consume_token(TILDE);
      ident();
      jj_consume_token(PARENTL);
      jj_consume_token(PARENTR);
      jj_consume_token(BRACEL);
      instrs();
ASTPommeDestructor *jjtn001 = new ASTPommeDestructor(JJTPOMMEDESTRUCTOR);
                                                                bool jjtc001 = true;
                                                                jjtree.openNodeScope(jjtn001);
                                                                jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(BRACER);
      } catch ( ...) {
if (jjtc001) {
                                                                  jjtree.clearNodeScope(jjtn001);
                                                                  jjtc001 = false;
                                                                } else {
                                                                  jjtree.popNode();
                                                                }
      }
if (jjtc001) {
                                                                  jjtree.closeNodeScope(jjtn001,  2);
                                                                  if (jjtree.nodeCreated()) {
                                                                   jjtreeCloseNodeScope(jjtn001);
                                                                  }
                                                                }
      break;
      }
    case NATIVE:{
      jj_consume_token(NATIVE);
      pommeStatic();
      visibility();
      typemeth();
      identmeth();
      jj_consume_token(PARENTL);
      headers();
ASTPommeMethodeNative *jjtn002 = new ASTPommeMethodeNative(JJTPOMMEMETHODENATIVE);
                                                                                           bool jjtc002 = true;
                                                                                           jjtree.openNodeScope(jjtn002);
                                                                                           jjtreeOpenNodeScope(jjtn002);
      try {
        jj_consume_token(PARENTR);
      } catch ( ...) {
if (jjtc002) {
                                                                                             jjtree.clearNodeScope(jjtn002);
                                                                                             jjtc002 = false;
                                                                                           } else {
                                                                                             jjtree.popNode();
                                                                                           }
      }
if (jjtc002) {
                                                                                             jjtree.closeNodeScope(jjtn002,  5);
                                                                                             if (jjtree.nodeCreated()) {
                                                                                              jjtreeCloseNodeScope(jjtn002);
                                                                                             }
                                                                                           }
      break;
      }
    default:
      jj_la1[6] = jj_gen;
      if (jj_2_3(2147483647)) {
        ident();
        jj_consume_token(PARENTL);
        headers();
        jj_consume_token(PARENTR);
        jj_consume_token(BRACEL);
        instrs();
ASTPommeConstructor *jjtn003 = new ASTPommeConstructor(JJTPOMMECONSTRUCTOR);
                                                                                                 bool jjtc003 = true;
                                                                                                 jjtree.openNodeScope(jjtn003);
                                                                                                 jjtreeOpenNodeScope(jjtn003);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc003) {
                                                                                                   jjtree.clearNodeScope(jjtn003);
                                                                                                   jjtc003 = false;
                                                                                                 } else {
                                                                                                   jjtree.popNode();
                                                                                                 }
        }
if (jjtc003) {
                                                                                                   jjtree.closeNodeScope(jjtn003,  3);
                                                                                                   if (jjtree.nodeCreated()) {
                                                                                                    jjtreeCloseNodeScope(jjtn003);
                                                                                                   }
                                                                                                 }
      } else {
        switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
        case VOID:
        case CONST:
        case STATIC:
        case PUBLIC:
        case PRIVATE:
        case PROTECTED:
        case OVERRIDE:
        case IDENTIFIER:{
          identfuncs();
          if (jj_2_2(2147483647)) {
            methode();
          } else {
            switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
            case CONST:
            case IDENTIFIER:{
ASTPommeVarDecls *jjtn004 = new ASTPommeVarDecls(JJTPOMMEVARDECLS);
                    bool jjtc004 = true;
                    jjtree.openNodeScope(jjtn004);
                    jjtreeOpenNodeScope(jjtn004);
              try {
                var();
              } catch ( ...) {
if (jjtc004) {
                      jjtree.clearNodeScope(jjtn004);
                      jjtc004 = false;
                    } else {
                      jjtree.popNode();
                    }
              }
if (jjtc004) {
                      jjtree.closeNodeScope(jjtn004,  2);
                      if (jjtree.nodeCreated()) {
                       jjtreeCloseNodeScope(jjtn004);
                      }
                    }
              break;
              }
            default:
              jj_la1[5] = jj_gen;
              jj_consume_token(-1);
              errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
            }
          }
          break;
          }
        default:
          jj_la1[7] = jj_gen;
          jj_consume_token(-1);
          errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
        }
      }
    }
}


void PommeLexer::methode() {
    typemeth();
    identmeth();
    jj_consume_token(PARENTL);
    headers();
    jj_consume_token(PARENTR);
    jj_consume_token(BRACEL);
    instrs();
ASTPommeMethode *jjtn001 = new ASTPommeMethode(JJTPOMMEMETHODE);
                                                                                 bool jjtc001 = true;
                                                                                 jjtree.openNodeScope(jjtn001);
                                                                                 jjtreeOpenNodeScope(jjtn001);
    try {
      jj_consume_token(BRACER);
    } catch ( ...) {
if (jjtc001) {
                                                                                   jjtree.clearNodeScope(jjtn001);
                                                                                   jjtc001 = false;
                                                                                 } else {
                                                                                   jjtree.popNode();
                                                                                 }
    }
if (jjtc001) {
                                                                                   jjtree.closeNodeScope(jjtn001,  5);
                                                                                   if (jjtree.nodeCreated()) {
                                                                                    jjtreeCloseNodeScope(jjtn001);
                                                                                   }
                                                                                 }
}


void PommeLexer::identfuncs() {
    pommeStatic();
    visibility();
ASTPommeIdentFuncs *jjtn001 = new ASTPommeIdentFuncs(JJTPOMMEIDENTFUNCS);
                                     bool jjtc001 = true;
                                     jjtree.openNodeScope(jjtn001);
                                     jjtreeOpenNodeScope(jjtn001);
    try {
      pommeOverride();
    } catch ( ...) {
if (jjtc001) {
                                       jjtree.clearNodeScope(jjtn001);
                                       jjtc001 = false;
                                     } else {
                                       jjtree.popNode();
                                     }
    }
if (jjtc001) {
                                       jjtree.closeNodeScope(jjtn001,  3);
                                       if (jjtree.nodeCreated()) {
                                        jjtreeCloseNodeScope(jjtn001);
                                       }
                                     }
}


void PommeLexer::pommeStatic() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case STATIC:{
ASTPommeStatic *jjtn001 = new ASTPommeStatic(JJTPOMMESTATIC);
          bool jjtc001 = true;
          jjtree.openNodeScope(jjtn001);
          jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(STATIC);
      } catch ( ...) {
if (jjtc001) {
            jjtree.clearNodeScope(jjtn001);
            jjtc001 = false;
          } else {
            jjtree.popNode();
          }
      }
if (jjtc001) {
            jjtree.closeNodeScope(jjtn001, true);
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn001);
            }
          }
      break;
      }
    default:
      jj_la1[8] = jj_gen;
ASTPommeSnil *jjtn002 = new ASTPommeSnil(JJTPOMMESNIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::visibility() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case PUBLIC:{
ASTPommePublic *jjtn001 = new ASTPommePublic(JJTPOMMEPUBLIC);
          bool jjtc001 = true;
          jjtree.openNodeScope(jjtn001);
          jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(PUBLIC);
      } catch ( ...) {
if (jjtc001) {
            jjtree.clearNodeScope(jjtn001);
            jjtc001 = false;
          } else {
            jjtree.popNode();
          }
      }
if (jjtc001) {
            jjtree.closeNodeScope(jjtn001, true);
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn001);
            }
          }
      break;
      }
    case PRIVATE:{
ASTPommePrivate *jjtn002 = new ASTPommePrivate(JJTPOMMEPRIVATE);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
        jj_consume_token(PRIVATE);
      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
      break;
      }
    case PROTECTED:{
ASTPommeProtected *jjtn003 = new ASTPommeProtected(JJTPOMMEPROTECTED);
            bool jjtc003 = true;
            jjtree.openNodeScope(jjtn003);
            jjtreeOpenNodeScope(jjtn003);
      try {
        jj_consume_token(PROTECTED);
      } catch ( ...) {
if (jjtc003) {
              jjtree.clearNodeScope(jjtn003);
              jjtc003 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc003) {
              jjtree.closeNodeScope(jjtn003, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn003);
              }
            }
      break;
      }
    default:
      jj_la1[9] = jj_gen;
ASTPommeVinil *jjtn004 = new ASTPommeVinil(JJTPOMMEVINIL);
            bool jjtc004 = true;
            jjtree.openNodeScope(jjtn004);
            jjtreeOpenNodeScope(jjtn004);
      try {
jjtree.closeNodeScope(jjtn004, true);
            jjtc004 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn004);
            }

      } catch ( ...) {
if (jjtc004) {
              jjtree.clearNodeScope(jjtn004);
              jjtc004 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc004) {
              jjtree.closeNodeScope(jjtn004, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn004);
              }
            }
    }
}


void PommeLexer::pommeOverride() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case OVERRIDE:{
ASTPommeOverride *jjtn001 = new ASTPommeOverride(JJTPOMMEOVERRIDE);
          bool jjtc001 = true;
          jjtree.openNodeScope(jjtn001);
          jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(OVERRIDE);
      } catch ( ...) {
if (jjtc001) {
            jjtree.clearNodeScope(jjtn001);
            jjtc001 = false;
          } else {
            jjtree.popNode();
          }
      }
if (jjtc001) {
            jjtree.closeNodeScope(jjtn001, true);
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn001);
            }
          }
      break;
      }
    default:
      jj_la1[10] = jj_gen;
ASTPommeOnil *jjtn002 = new ASTPommeOnil(JJTPOMMEONIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::enumerate() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case ENUM:{
      jj_consume_token(ENUM);
      ident();
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case BRACEL:{
        jj_consume_token(BRACEL);
        declenums();
ASTPommeEnum *jjtn001 = new ASTPommeEnum(JJTPOMMEENUM);
                                                       bool jjtc001 = true;
                                                       jjtree.openNodeScope(jjtn001);
                                                       jjtreeOpenNodeScope(jjtn001);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc001) {
                                                         jjtree.clearNodeScope(jjtn001);
                                                         jjtc001 = false;
                                                       } else {
                                                         jjtree.popNode();
                                                       }
        }
if (jjtc001) {
                                                         jjtree.closeNodeScope(jjtn001,  2);
                                                         if (jjtree.nodeCreated()) {
                                                          jjtreeCloseNodeScope(jjtn001);
                                                         }
                                                       }
        break;
        }
      case EXTENDS:{
        jj_consume_token(EXTENDS);
        ident();
        jj_consume_token(BRACEL);
        declenums();
ASTPommeExtendsEnum *jjtn002 = new ASTPommeExtendsEnum(JJTPOMMEEXTENDSENUM);
                                                                                           bool jjtc002 = true;
                                                                                           jjtree.openNodeScope(jjtn002);
                                                                                           jjtreeOpenNodeScope(jjtn002);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc002) {
                                                                                             jjtree.clearNodeScope(jjtn002);
                                                                                             jjtc002 = false;
                                                                                           } else {
                                                                                             jjtree.popNode();
                                                                                           }
        }
if (jjtc002) {
                                                                                             jjtree.closeNodeScope(jjtn002,  3);
                                                                                             if (jjtree.nodeCreated()) {
                                                                                              jjtreeCloseNodeScope(jjtn002);
                                                                                             }
                                                                                           }
        break;
        }
      default:
        jj_la1[11] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
      break;
      }
    case MODDED:{
      jj_consume_token(MODDED);
      jj_consume_token(ENUM);
      ident();
      jj_consume_token(BRACEL);
      declenums();
ASTPommeModdedEnum *jjtn003 = new ASTPommeModdedEnum(JJTPOMMEMODDEDENUM);
                                                         bool jjtc003 = true;
                                                         jjtree.openNodeScope(jjtn003);
                                                         jjtreeOpenNodeScope(jjtn003);
      try {
        jj_consume_token(BRACER);
      } catch ( ...) {
if (jjtc003) {
                                                           jjtree.clearNodeScope(jjtn003);
                                                           jjtc003 = false;
                                                         } else {
                                                           jjtree.popNode();
                                                         }
      }
if (jjtc003) {
                                                           jjtree.closeNodeScope(jjtn003,  2);
                                                           if (jjtree.nodeCreated()) {
                                                            jjtreeCloseNodeScope(jjtn003);
                                                           }
                                                         }
      break;
      }
    default:
      jj_la1[12] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::declenums() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case IDENTIFIER:{
      declenum();
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case COMMA:{
        jj_consume_token(COMMA);
ASTPommeDeclEnums *jjtn001 = new ASTPommeDeclEnums(JJTPOMMEDECLENUMS);
                                          bool jjtc001 = true;
                                          jjtree.openNodeScope(jjtn001);
                                          jjtreeOpenNodeScope(jjtn001);
        try {
          declenums();
        } catch ( ...) {
if (jjtc001) {
                                            jjtree.clearNodeScope(jjtn001);
                                            jjtc001 = false;
                                          } else {
                                            jjtree.popNode();
                                          }
        }
if (jjtc001) {
                                            jjtree.closeNodeScope(jjtn001,  2);
                                            if (jjtree.nodeCreated()) {
                                             jjtreeCloseNodeScope(jjtn001);
                                            }
                                          }
        break;
        }
      default:
        jj_la1[13] = jj_gen;

      }
      break;
      }
    default:
      jj_la1[14] = jj_gen;
ASTPommeEnnil *jjtn002 = new ASTPommeEnnil(JJTPOMMEENNIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::declenum() {
    ident();
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case ASSIGNEMENT:{
      jj_consume_token(ASSIGNEMENT);
ASTPommeEnumAssign *jjtn001 = new ASTPommeEnumAssign(JJTPOMMEENUMASSIGN);
                                        bool jjtc001 = true;
                                        jjtree.openNodeScope(jjtn001);
                                        jjtreeOpenNodeScope(jjtn001);
      try {
        pommeInt();
      } catch ( ...) {
if (jjtc001) {
                                          jjtree.clearNodeScope(jjtn001);
                                          jjtc001 = false;
                                        } else {
                                          jjtree.popNode();
                                        }
      }
if (jjtc001) {
                                          jjtree.closeNodeScope(jjtn001,  2);
                                          if (jjtree.nodeCreated()) {
                                           jjtreeCloseNodeScope(jjtn001);
                                          }
                                        }
      break;
      }
    default:
      jj_la1[15] = jj_gen;
ASTPommeEnumDefault *jjtn002 = new ASTPommeEnumDefault(JJTPOMMEENUMDEFAULT);
                                    bool jjtc002 = true;
                                    jjtree.openNodeScope(jjtn002);
                                    jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002,  1);
                                    jjtc002 = false;
                                    if (jjtree.nodeCreated()) {
                                     jjtreeCloseNodeScope(jjtn002);
                                    }

      } catch ( ...) {
if (jjtc002) {
                                      jjtree.clearNodeScope(jjtn002);
                                      jjtc002 = false;
                                    } else {
                                      jjtree.popNode();
                                    }
      }
if (jjtc002) {
                                      jjtree.closeNodeScope(jjtn002,  1);
                                      if (jjtree.nodeCreated()) {
                                       jjtreeCloseNodeScope(jjtn002);
                                      }
                                    }
    }
}


void PommeLexer::globalFunction() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case VOID:
    case IDENTIFIER:{
      typemeth();
      ident();
      jj_consume_token(PARENTL);
      headers();
      jj_consume_token(PARENTR);
      jj_consume_token(BRACEL);
      instrs();
ASTPommeGlobalFunction *jjtn001 = new ASTPommeGlobalFunction(JJTPOMMEGLOBALFUNCTION);
                                                                             bool jjtc001 = true;
                                                                             jjtree.openNodeScope(jjtn001);
                                                                             jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(BRACER);
      } catch ( ...) {
if (jjtc001) {
                                                                               jjtree.clearNodeScope(jjtn001);
                                                                               jjtc001 = false;
                                                                             } else {
                                                                               jjtree.popNode();
                                                                             }
      }
if (jjtc001) {
                                                                               jjtree.closeNodeScope(jjtn001,  4);
                                                                               if (jjtree.nodeCreated()) {
                                                                                jjtreeCloseNodeScope(jjtn001);
                                                                               }
                                                                             }
      break;
      }
    case NATIVE:{
      jj_consume_token(NATIVE);
      typemeth();
      ident();
      jj_consume_token(PARENTL);
      headers();
ASTPommeGlobalFunctionNative *jjtn002 = new ASTPommeGlobalFunctionNative(JJTPOMMEGLOBALFUNCTIONNATIVE);
                                                            bool jjtc002 = true;
                                                            jjtree.openNodeScope(jjtn002);
                                                            jjtreeOpenNodeScope(jjtn002);
      try {
        jj_consume_token(PARENTR);
      } catch ( ...) {
if (jjtc002) {
                                                              jjtree.clearNodeScope(jjtn002);
                                                              jjtc002 = false;
                                                            } else {
                                                              jjtree.popNode();
                                                            }
      }
if (jjtc002) {
                                                              jjtree.closeNodeScope(jjtn002,  3);
                                                              if (jjtree.nodeCreated()) {
                                                               jjtreeCloseNodeScope(jjtn002);
                                                              }
                                                            }
      break;
      }
    default:
      jj_la1[16] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::instrs() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case INCR:
    case DECR:
    case IF:
    case WHILE:
    case PRINT:
    case RETURN:
    case BREAK:
    case SWITCH:
    case CONST:
    case DELETEEXP:
    case IDENTIFIEROPERATOR:
    case IDENTIFIER:{
      instr();
      jj_consume_token(SEMICOLON);
ASTPommeInstrs *jjtn001 = new ASTPommeInstrs(JJTPOMMEINSTRS);
                              bool jjtc001 = true;
                              jjtree.openNodeScope(jjtn001);
                              jjtreeOpenNodeScope(jjtn001);
      try {
        instrs();
      } catch ( ...) {
if (jjtc001) {
                                jjtree.clearNodeScope(jjtn001);
                                jjtc001 = false;
                              } else {
                                jjtree.popNode();
                              }
      }
if (jjtc001) {
                                jjtree.closeNodeScope(jjtn001,  2);
                                if (jjtree.nodeCreated()) {
                                 jjtreeCloseNodeScope(jjtn001);
                                }
                              }
      break;
      }
    default:
      jj_la1[17] = jj_gen;
ASTPommeInil *jjtn002 = new ASTPommeInil(JJTPOMMEINIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::instr() {
    if (jj_2_4(2)) {
      var();
    } else {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case INCR:{
        jj_consume_token(INCR);
ASTPommeIncrPre *jjtn001 = new ASTPommeIncrPre(JJTPOMMEINCRPRE);
                   bool jjtc001 = true;
                   jjtree.openNodeScope(jjtn001);
                   jjtreeOpenNodeScope(jjtn001);
        try {
          listaccess();
        } catch ( ...) {
if (jjtc001) {
                     jjtree.clearNodeScope(jjtn001);
                     jjtc001 = false;
                   } else {
                     jjtree.popNode();
                   }
        }
if (jjtc001) {
                     jjtree.closeNodeScope(jjtn001,  1);
                     if (jjtree.nodeCreated()) {
                      jjtreeCloseNodeScope(jjtn001);
                     }
                   }
        break;
        }
      case DECR:{
        jj_consume_token(DECR);
ASTPommeDecrPre *jjtn002 = new ASTPommeDecrPre(JJTPOMMEDECRPRE);
                   bool jjtc002 = true;
                   jjtree.openNodeScope(jjtn002);
                   jjtreeOpenNodeScope(jjtn002);
        try {
          listaccess();
        } catch ( ...) {
if (jjtc002) {
                     jjtree.clearNodeScope(jjtn002);
                     jjtc002 = false;
                   } else {
                     jjtree.popNode();
                   }
        }
if (jjtc002) {
                     jjtree.closeNodeScope(jjtn002,  1);
                     if (jjtree.nodeCreated()) {
                      jjtreeCloseNodeScope(jjtn002);
                     }
                   }
        break;
        }
      case DELETEEXP:{
        jj_consume_token(DELETEEXP);
ASTPommeDelete *jjtn003 = new ASTPommeDelete(JJTPOMMEDELETE);
                        bool jjtc003 = true;
                        jjtree.openNodeScope(jjtn003);
                        jjtreeOpenNodeScope(jjtn003);
        try {
          listaccess();
        } catch ( ...) {
if (jjtc003) {
                          jjtree.clearNodeScope(jjtn003);
                          jjtc003 = false;
                        } else {
                          jjtree.popNode();
                        }
        }
if (jjtc003) {
                          jjtree.closeNodeScope(jjtn003,  1);
                          if (jjtree.nodeCreated()) {
                           jjtreeCloseNodeScope(jjtn003);
                          }
                        }
        break;
        }
      case RETURN:{
        jj_consume_token(RETURN);
ASTPommeReturn *jjtn004 = new ASTPommeReturn(JJTPOMMERETURN);
                     bool jjtc004 = true;
                     jjtree.openNodeScope(jjtn004);
                     jjtreeOpenNodeScope(jjtn004);
        try {
          exp();
        } catch ( ...) {
if (jjtc004) {
                       jjtree.clearNodeScope(jjtn004);
                       jjtc004 = false;
                     } else {
                       jjtree.popNode();
                     }
        }
if (jjtc004) {
                       jjtree.closeNodeScope(jjtn004,  1);
                       if (jjtree.nodeCreated()) {
                        jjtreeCloseNodeScope(jjtn004);
                       }
                     }
        break;
        }
      case WHILE:{
        jj_consume_token(WHILE);
        jj_consume_token(PARENTL);
        exp();
        jj_consume_token(PARENTR);
        jj_consume_token(BRACEL);
        instrs();
ASTPommeWhile *jjtn005 = new ASTPommeWhile(JJTPOMMEWHILE);
                                                                bool jjtc005 = true;
                                                                jjtree.openNodeScope(jjtn005);
                                                                jjtreeOpenNodeScope(jjtn005);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc005) {
                                                                  jjtree.clearNodeScope(jjtn005);
                                                                  jjtc005 = false;
                                                                } else {
                                                                  jjtree.popNode();
                                                                }
        }
if (jjtc005) {
                                                                  jjtree.closeNodeScope(jjtn005,  2);
                                                                  if (jjtree.nodeCreated()) {
                                                                   jjtreeCloseNodeScope(jjtn005);
                                                                  }
                                                                }
        break;
        }
      case BREAK:{
ASTPommeBreak *jjtn006 = new ASTPommeBreak(JJTPOMMEBREAK);
            bool jjtc006 = true;
            jjtree.openNodeScope(jjtn006);
            jjtreeOpenNodeScope(jjtn006);
        try {
          jj_consume_token(BREAK);
        } catch ( ...) {
if (jjtc006) {
              jjtree.clearNodeScope(jjtn006);
              jjtc006 = false;
            } else {
              jjtree.popNode();
            }
        }
if (jjtc006) {
              jjtree.closeNodeScope(jjtn006, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn006);
              }
            }
        break;
        }
      case IF:{
        jj_consume_token(IF);
        jj_consume_token(PARENTL);
        exp();
        jj_consume_token(PARENTR);
        jj_consume_token(BRACEL);
        instrs();
        jj_consume_token(BRACER);
ASTPommeIf *jjtn007 = new ASTPommeIf(JJTPOMMEIF);
                                                                      bool jjtc007 = true;
                                                                      jjtree.openNodeScope(jjtn007);
                                                                      jjtreeOpenNodeScope(jjtn007);
        try {
          pommeElse();
        } catch ( ...) {
if (jjtc007) {
                                                                        jjtree.clearNodeScope(jjtn007);
                                                                        jjtc007 = false;
                                                                      } else {
                                                                        jjtree.popNode();
                                                                      }
        }
if (jjtc007) {
                                                                        jjtree.closeNodeScope(jjtn007,  3);
                                                                        if (jjtree.nodeCreated()) {
                                                                         jjtreeCloseNodeScope(jjtn007);
                                                                        }
                                                                      }
        break;
        }
      case PRINT:{
        jj_consume_token(PRINT);
        jj_consume_token(PARENTL);
        exp();
ASTPommePrint *jjtn008 = new ASTPommePrint(JJTPOMMEPRINT);
                                    bool jjtc008 = true;
                                    jjtree.openNodeScope(jjtn008);
                                    jjtreeOpenNodeScope(jjtn008);
        try {
          jj_consume_token(PARENTR);
        } catch ( ...) {
if (jjtc008) {
                                      jjtree.clearNodeScope(jjtn008);
                                      jjtc008 = false;
                                    } else {
                                      jjtree.popNode();
                                    }
        }
if (jjtc008) {
                                      jjtree.closeNodeScope(jjtn008,  1);
                                      if (jjtree.nodeCreated()) {
                                       jjtreeCloseNodeScope(jjtn008);
                                      }
                                    }
        break;
        }
      case SWITCH:{
        jj_consume_token(SWITCH);
        jj_consume_token(PARENTL);
        exp();
        jj_consume_token(PARENTR);
        jj_consume_token(BRACEL);
        listcases();
ASTPommeSwitch *jjtn009 = new ASTPommeSwitch(JJTPOMMESWITCH);
                                                                    bool jjtc009 = true;
                                                                    jjtree.openNodeScope(jjtn009);
                                                                    jjtreeOpenNodeScope(jjtn009);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc009) {
                                                                      jjtree.clearNodeScope(jjtn009);
                                                                      jjtc009 = false;
                                                                    } else {
                                                                      jjtree.popNode();
                                                                    }
        }
if (jjtc009) {
                                                                      jjtree.closeNodeScope(jjtn009,  2);
                                                                      if (jjtree.nodeCreated()) {
                                                                       jjtreeCloseNodeScope(jjtn009);
                                                                      }
                                                                    }
        break;
        }
      case IDENTIFIEROPERATOR:
      case IDENTIFIER:{
        listaccess();
        switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
        case ASSIGNEMENT:{
          jj_consume_token(ASSIGNEMENT);
ASTPommeAssign *jjtn010 = new ASTPommeAssign(JJTPOMMEASSIGN);
                                         bool jjtc010 = true;
                                         jjtree.openNodeScope(jjtn010);
                                         jjtreeOpenNodeScope(jjtn010);
          try {
            exp();
          } catch ( ...) {
if (jjtc010) {
                                           jjtree.clearNodeScope(jjtn010);
                                           jjtc010 = false;
                                         } else {
                                           jjtree.popNode();
                                         }
          }
if (jjtc010) {
                                           jjtree.closeNodeScope(jjtn010,  2);
                                           if (jjtree.nodeCreated()) {
                                            jjtreeCloseNodeScope(jjtn010);
                                           }
                                         }
          break;
          }
        case ADDEQ:{
          jj_consume_token(ADDEQ);
ASTPommeAddEq *jjtn011 = new ASTPommeAddEq(JJTPOMMEADDEQ);
                                                    bool jjtc011 = true;
                                                    jjtree.openNodeScope(jjtn011);
                                                    jjtreeOpenNodeScope(jjtn011);
          try {
            exp();
          } catch ( ...) {
if (jjtc011) {
                                                      jjtree.clearNodeScope(jjtn011);
                                                      jjtc011 = false;
                                                    } else {
                                                      jjtree.popNode();
                                                    }
          }
if (jjtc011) {
                                                      jjtree.closeNodeScope(jjtn011,  2);
                                                      if (jjtree.nodeCreated()) {
                                                       jjtreeCloseNodeScope(jjtn011);
                                                      }
                                                    }
          break;
          }
        case MINUSEQ:{
          jj_consume_token(MINUSEQ);
ASTPommeMinusEq *jjtn012 = new ASTPommeMinusEq(JJTPOMMEMINUSEQ);
                                                      bool jjtc012 = true;
                                                      jjtree.openNodeScope(jjtn012);
                                                      jjtreeOpenNodeScope(jjtn012);
          try {
            exp();
          } catch ( ...) {
if (jjtc012) {
                                                        jjtree.clearNodeScope(jjtn012);
                                                        jjtc012 = false;
                                                      } else {
                                                        jjtree.popNode();
                                                      }
          }
if (jjtc012) {
                                                        jjtree.closeNodeScope(jjtn012,  2);
                                                        if (jjtree.nodeCreated()) {
                                                         jjtreeCloseNodeScope(jjtn012);
                                                        }
                                                      }
          break;
          }
        case DIVEQ:{
          jj_consume_token(DIVEQ);
ASTPommeDivEq *jjtn013 = new ASTPommeDivEq(JJTPOMMEDIVEQ);
                                                    bool jjtc013 = true;
                                                    jjtree.openNodeScope(jjtn013);
                                                    jjtreeOpenNodeScope(jjtn013);
          try {
            exp();
          } catch ( ...) {
if (jjtc013) {
                                                      jjtree.clearNodeScope(jjtn013);
                                                      jjtc013 = false;
                                                    } else {
                                                      jjtree.popNode();
                                                    }
          }
if (jjtc013) {
                                                      jjtree.closeNodeScope(jjtn013,  2);
                                                      if (jjtree.nodeCreated()) {
                                                       jjtreeCloseNodeScope(jjtn013);
                                                      }
                                                    }
          break;
          }
        case MULTEQ:{
          jj_consume_token(MULTEQ);
ASTPommeMultEq *jjtn014 = new ASTPommeMultEq(JJTPOMMEMULTEQ);
                                                     bool jjtc014 = true;
                                                     jjtree.openNodeScope(jjtn014);
                                                     jjtreeOpenNodeScope(jjtn014);
          try {
            exp();
          } catch ( ...) {
if (jjtc014) {
                                                       jjtree.clearNodeScope(jjtn014);
                                                       jjtc014 = false;
                                                     } else {
                                                       jjtree.popNode();
                                                     }
          }
if (jjtc014) {
                                                       jjtree.closeNodeScope(jjtn014,  2);
                                                       if (jjtree.nodeCreated()) {
                                                        jjtreeCloseNodeScope(jjtn014);
                                                       }
                                                     }
          break;
          }
        case OREQ:{
          jj_consume_token(OREQ);
ASTPommeOrEq *jjtn015 = new ASTPommeOrEq(JJTPOMMEOREQ);
                                                   bool jjtc015 = true;
                                                   jjtree.openNodeScope(jjtn015);
                                                   jjtreeOpenNodeScope(jjtn015);
          try {
            exp();
          } catch ( ...) {
if (jjtc015) {
                                                     jjtree.clearNodeScope(jjtn015);
                                                     jjtc015 = false;
                                                   } else {
                                                     jjtree.popNode();
                                                   }
          }
if (jjtc015) {
                                                     jjtree.closeNodeScope(jjtn015,  2);
                                                     if (jjtree.nodeCreated()) {
                                                      jjtreeCloseNodeScope(jjtn015);
                                                     }
                                                   }
          break;
          }
        case ANDEQ:{
          jj_consume_token(ANDEQ);
ASTPommeAndEq *jjtn016 = new ASTPommeAndEq(JJTPOMMEANDEQ);
                                                    bool jjtc016 = true;
                                                    jjtree.openNodeScope(jjtn016);
                                                    jjtreeOpenNodeScope(jjtn016);
          try {
            exp();
          } catch ( ...) {
if (jjtc016) {
                                                      jjtree.clearNodeScope(jjtn016);
                                                      jjtc016 = false;
                                                    } else {
                                                      jjtree.popNode();
                                                    }
          }
if (jjtc016) {
                                                      jjtree.closeNodeScope(jjtn016,  2);
                                                      if (jjtree.nodeCreated()) {
                                                       jjtreeCloseNodeScope(jjtn016);
                                                      }
                                                    }
          break;
          }
        case SHIFTLEQ:{
          jj_consume_token(SHIFTLEQ);
ASTPommeShiftLEq *jjtn017 = new ASTPommeShiftLEq(JJTPOMMESHIFTLEQ);
                                                       bool jjtc017 = true;
                                                       jjtree.openNodeScope(jjtn017);
                                                       jjtreeOpenNodeScope(jjtn017);
          try {
            exp();
          } catch ( ...) {
if (jjtc017) {
                                                         jjtree.clearNodeScope(jjtn017);
                                                         jjtc017 = false;
                                                       } else {
                                                         jjtree.popNode();
                                                       }
          }
if (jjtc017) {
                                                         jjtree.closeNodeScope(jjtn017,  2);
                                                         if (jjtree.nodeCreated()) {
                                                          jjtreeCloseNodeScope(jjtn017);
                                                         }
                                                       }
          break;
          }
        case SHIFTREQ:{
          jj_consume_token(SHIFTREQ);
ASTPommeShiftREq *jjtn018 = new ASTPommeShiftREq(JJTPOMMESHIFTREQ);
                                                       bool jjtc018 = true;
                                                       jjtree.openNodeScope(jjtn018);
                                                       jjtreeOpenNodeScope(jjtn018);
          try {
            exp();
          } catch ( ...) {
if (jjtc018) {
                                                         jjtree.clearNodeScope(jjtn018);
                                                         jjtc018 = false;
                                                       } else {
                                                         jjtree.popNode();
                                                       }
          }
if (jjtc018) {
                                                         jjtree.closeNodeScope(jjtn018,  2);
                                                         if (jjtree.nodeCreated()) {
                                                          jjtreeCloseNodeScope(jjtn018);
                                                         }
                                                       }
          break;
          }
        case INCR:{
ASTPommeIncrPost *jjtn019 = new ASTPommeIncrPost(JJTPOMMEINCRPOST);
                                            bool jjtc019 = true;
                                            jjtree.openNodeScope(jjtn019);
                                            jjtreeOpenNodeScope(jjtn019);
          try {
            jj_consume_token(INCR);
          } catch ( ...) {
if (jjtc019) {
                                              jjtree.clearNodeScope(jjtn019);
                                              jjtc019 = false;
                                            } else {
                                              jjtree.popNode();
                                            }
          }
if (jjtc019) {
                                              jjtree.closeNodeScope(jjtn019,  1);
                                              if (jjtree.nodeCreated()) {
                                               jjtreeCloseNodeScope(jjtn019);
                                              }
                                            }
          break;
          }
        case DECR:{
ASTPommeDecrPost *jjtn020 = new ASTPommeDecrPost(JJTPOMMEDECRPOST);
                                            bool jjtc020 = true;
                                            jjtree.openNodeScope(jjtn020);
                                            jjtreeOpenNodeScope(jjtn020);
          try {
            jj_consume_token(DECR);
          } catch ( ...) {
if (jjtc020) {
                                              jjtree.clearNodeScope(jjtn020);
                                              jjtc020 = false;
                                            } else {
                                              jjtree.popNode();
                                            }
          }
if (jjtc020) {
                                              jjtree.closeNodeScope(jjtn020,  1);
                                              if (jjtree.nodeCreated()) {
                                               jjtreeCloseNodeScope(jjtn020);
                                              }
                                            }
          break;
          }
        default:
          jj_la1[18] = jj_gen;

        }
        break;
        }
      default:
        jj_la1[19] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
    }
}


void PommeLexer::listcases() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case CASE:{
      pommecase();
ASTPommeCases *jjtn001 = new ASTPommeCases(JJTPOMMECASES);
                      bool jjtc001 = true;
                      jjtree.openNodeScope(jjtn001);
                      jjtreeOpenNodeScope(jjtn001);
      try {
        listcases();
      } catch ( ...) {
if (jjtc001) {
                        jjtree.clearNodeScope(jjtn001);
                        jjtc001 = false;
                      } else {
                        jjtree.popNode();
                      }
      }
if (jjtc001) {
                        jjtree.closeNodeScope(jjtn001,  2);
                        if (jjtree.nodeCreated()) {
                         jjtreeCloseNodeScope(jjtn001);
                        }
                      }
      break;
      }
    case DEFAULTCASE:{
      jj_consume_token(DEFAULTCASE);
      jj_consume_token(COLON);
      jj_consume_token(BRACEL);
      instrs();
ASTPommeDefault *jjtn002 = new ASTPommeDefault(JJTPOMMEDEFAULT);
                                                    bool jjtc002 = true;
                                                    jjtree.openNodeScope(jjtn002);
                                                    jjtreeOpenNodeScope(jjtn002);
      try {
        jj_consume_token(BRACER);
      } catch ( ...) {
if (jjtc002) {
                                                      jjtree.clearNodeScope(jjtn002);
                                                      jjtc002 = false;
                                                    } else {
                                                      jjtree.popNode();
                                                    }
      }
if (jjtc002) {
                                                      jjtree.closeNodeScope(jjtn002,  1);
                                                      if (jjtree.nodeCreated()) {
                                                       jjtreeCloseNodeScope(jjtn002);
                                                      }
                                                    }
      break;
      }
    default:
      jj_la1[20] = jj_gen;
ASTPommeSwinil *jjtn003 = new ASTPommeSwinil(JJTPOMMESWINIL);
            bool jjtc003 = true;
            jjtree.openNodeScope(jjtn003);
            jjtreeOpenNodeScope(jjtn003);
      try {
jjtree.closeNodeScope(jjtn003, true);
            jjtc003 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn003);
            }

      } catch ( ...) {
if (jjtc003) {
              jjtree.clearNodeScope(jjtn003);
              jjtc003 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc003) {
              jjtree.closeNodeScope(jjtn003, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn003);
              }
            }
    }
}


void PommeLexer::pommecase() {
    jj_consume_token(CASE);
    exp();
    jj_consume_token(COLON);
    jj_consume_token(BRACEL);
    instrs();
ASTPommeCase *jjtn001 = new ASTPommeCase(JJTPOMMECASE);
                                                 bool jjtc001 = true;
                                                 jjtree.openNodeScope(jjtn001);
                                                 jjtreeOpenNodeScope(jjtn001);
    try {
      jj_consume_token(BRACER);
    } catch ( ...) {
if (jjtc001) {
                                                   jjtree.clearNodeScope(jjtn001);
                                                   jjtc001 = false;
                                                 } else {
                                                   jjtree.popNode();
                                                 }
    }
if (jjtc001) {
                                                   jjtree.closeNodeScope(jjtn001,  2);
                                                   if (jjtree.nodeCreated()) {
                                                    jjtreeCloseNodeScope(jjtn001);
                                                   }
                                                 }
}


void PommeLexer::pommeElse() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case ELSE:{
      jj_consume_token(ELSE);
      jj_consume_token(BRACEL);
      instrs();
      jj_consume_token(BRACER);
      break;
      }
    default:
      jj_la1[21] = jj_gen;
ASTPommeInil *jjtn001 = new ASTPommeInil(JJTPOMMEINIL);
            bool jjtc001 = true;
            jjtree.openNodeScope(jjtn001);
            jjtreeOpenNodeScope(jjtn001);
      try {
jjtree.closeNodeScope(jjtn001, true);
            jjtc001 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn001);
            }

      } catch ( ...) {
if (jjtc001) {
              jjtree.clearNodeScope(jjtn001);
              jjtc001 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc001) {
              jjtree.closeNodeScope(jjtn001, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn001);
              }
            }
    }
}


void PommeLexer::listexp() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case MINUS:
    case PARENTL:
    case EXCLAMATION:
    case TILDE:
    case TRUE:
    case FALSE:
    case NULLEXP:
    case NEWEXP:
    case INT:
    case IDENTIFIEROPERATOR:
    case IDENTIFIER:
    case STRING:
    case FLOAT:{
      exp();
ASTPommeListExp *jjtn001 = new ASTPommeListExp(JJTPOMMELISTEXP);
                bool jjtc001 = true;
                jjtree.openNodeScope(jjtn001);
                jjtreeOpenNodeScope(jjtn001);
      try {
        listexpP();
      } catch ( ...) {
if (jjtc001) {
                  jjtree.clearNodeScope(jjtn001);
                  jjtc001 = false;
                } else {
                  jjtree.popNode();
                }
      }
if (jjtc001) {
                  jjtree.closeNodeScope(jjtn001,  2);
                  if (jjtree.nodeCreated()) {
                   jjtreeCloseNodeScope(jjtn001);
                  }
                }
      break;
      }
    default:
      jj_la1[22] = jj_gen;
ASTPommeExnil *jjtn002 = new ASTPommeExnil(JJTPOMMEEXNIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::listexpP() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case COMMA:{
      jj_consume_token(COMMA);
      exp();
ASTPommeListExp *jjtn001 = new ASTPommeListExp(JJTPOMMELISTEXP);
                        bool jjtc001 = true;
                        jjtree.openNodeScope(jjtn001);
                        jjtreeOpenNodeScope(jjtn001);
      try {
        listexpP();
      } catch ( ...) {
if (jjtc001) {
                          jjtree.clearNodeScope(jjtn001);
                          jjtc001 = false;
                        } else {
                          jjtree.popNode();
                        }
      }
if (jjtc001) {
                          jjtree.closeNodeScope(jjtn001,  2);
                          if (jjtree.nodeCreated()) {
                           jjtreeCloseNodeScope(jjtn001);
                          }
                        }
      break;
      }
    default:
      jj_la1[23] = jj_gen;
ASTPommeExnil *jjtn002 = new ASTPommeExnil(JJTPOMMEEXNIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::var() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case IDENTIFIER:{
      type();
      ident();
ASTPommeVariable *jjtn001 = new ASTPommeVariable(JJTPOMMEVARIABLE);
                         bool jjtc001 = true;
                         jjtree.openNodeScope(jjtn001);
                         jjtreeOpenNodeScope(jjtn001);
      try {
        vexp();
      } catch ( ...) {
if (jjtc001) {
                           jjtree.clearNodeScope(jjtn001);
                           jjtc001 = false;
                         } else {
                           jjtree.popNode();
                         }
      }
if (jjtc001) {
                           jjtree.closeNodeScope(jjtn001,  3);
                           if (jjtree.nodeCreated()) {
                            jjtreeCloseNodeScope(jjtn001);
                           }
                         }
      break;
      }
    case CONST:{
      jj_consume_token(CONST);
      type();
      ident();
ASTPommeConstant *jjtn002 = new ASTPommeConstant(JJTPOMMECONSTANT);
                                   bool jjtc002 = true;
                                   jjtree.openNodeScope(jjtn002);
                                   jjtreeOpenNodeScope(jjtn002);
      try {
        vexp();
      } catch ( ...) {
if (jjtc002) {
                                     jjtree.clearNodeScope(jjtn002);
                                     jjtc002 = false;
                                   } else {
                                     jjtree.popNode();
                                   }
      }
if (jjtc002) {
                                     jjtree.closeNodeScope(jjtn002,  3);
                                     if (jjtree.nodeCreated()) {
                                      jjtreeCloseNodeScope(jjtn002);
                                     }
                                   }
      break;
      }
    default:
      jj_la1[24] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::vexp() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case ASSIGNEMENT:{
      jj_consume_token(ASSIGNEMENT);
      exp();
      break;
      }
    default:
      jj_la1[25] = jj_gen;
ASTPommeOmega *jjtn001 = new ASTPommeOmega(JJTPOMMEOMEGA);
            bool jjtc001 = true;
            jjtree.openNodeScope(jjtn001);
            jjtreeOpenNodeScope(jjtn001);
      try {
jjtree.closeNodeScope(jjtn001, true);
            jjtc001 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn001);
            }

      } catch ( ...) {
if (jjtc001) {
              jjtree.clearNodeScope(jjtn001);
              jjtc001 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc001) {
              jjtree.closeNodeScope(jjtn001, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn001);
              }
            }
    }
}


void PommeLexer::headers() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case CONST:
    case IDENTIFIER:{
      header();
ASTPommeHeaders *jjtn001 = new ASTPommeHeaders(JJTPOMMEHEADERS);
                   bool jjtc001 = true;
                   jjtree.openNodeScope(jjtn001);
                   jjtreeOpenNodeScope(jjtn001);
      try {
        headersP();
      } catch ( ...) {
if (jjtc001) {
                     jjtree.clearNodeScope(jjtn001);
                     jjtc001 = false;
                   } else {
                     jjtree.popNode();
                   }
      }
if (jjtc001) {
                     jjtree.closeNodeScope(jjtn001,  2);
                     if (jjtree.nodeCreated()) {
                      jjtreeCloseNodeScope(jjtn001);
                     }
                   }
      break;
      }
    default:
      jj_la1[26] = jj_gen;
ASTPommeEnil *jjtn002 = new ASTPommeEnil(JJTPOMMEENIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::headersP() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case COMMA:{
      jj_consume_token(COMMA);
      header();
ASTPommeHeaders *jjtn001 = new ASTPommeHeaders(JJTPOMMEHEADERS);
                           bool jjtc001 = true;
                           jjtree.openNodeScope(jjtn001);
                           jjtreeOpenNodeScope(jjtn001);
      try {
        headersP();
      } catch ( ...) {
if (jjtc001) {
                             jjtree.clearNodeScope(jjtn001);
                             jjtc001 = false;
                           } else {
                             jjtree.popNode();
                           }
      }
if (jjtc001) {
                             jjtree.closeNodeScope(jjtn001,  2);
                             if (jjtree.nodeCreated()) {
                              jjtreeCloseNodeScope(jjtn001);
                             }
                           }
      break;
      }
    default:
      jj_la1[27] = jj_gen;
ASTPommeEnil *jjtn002 = new ASTPommeEnil(JJTPOMMEENIL);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
jjtree.closeNodeScope(jjtn002, true);
            jjtc002 = false;
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn002);
            }

      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
    }
}


void PommeLexer::header() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case CONST:{
      jj_consume_token(CONST);
      type();
ASTPommeConstHeader *jjtn001 = new ASTPommeConstHeader(JJTPOMMECONSTHEADER);
                         bool jjtc001 = true;
                         jjtree.openNodeScope(jjtn001);
                         jjtreeOpenNodeScope(jjtn001);
      try {
        ident();
      } catch ( ...) {
if (jjtc001) {
                           jjtree.clearNodeScope(jjtn001);
                           jjtc001 = false;
                         } else {
                           jjtree.popNode();
                         }
      }
if (jjtc001) {
                           jjtree.closeNodeScope(jjtn001,  2);
                           if (jjtree.nodeCreated()) {
                            jjtreeCloseNodeScope(jjtn001);
                           }
                         }
      break;
      }
    case IDENTIFIER:{
      type();
ASTPommeHeader *jjtn002 = new ASTPommeHeader(JJTPOMMEHEADER);
                    bool jjtc002 = true;
                    jjtree.openNodeScope(jjtn002);
                    jjtreeOpenNodeScope(jjtn002);
      try {
        ident();
      } catch ( ...) {
if (jjtc002) {
                      jjtree.clearNodeScope(jjtn002);
                      jjtc002 = false;
                    } else {
                      jjtree.popNode();
                    }
      }
if (jjtc002) {
                      jjtree.closeNodeScope(jjtn002,  2);
                      if (jjtree.nodeCreated()) {
                       jjtreeCloseNodeScope(jjtn002);
                      }
                    }
      break;
      }
    default:
      jj_la1[28] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::typemeth() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case VOID:{
ASTPommeVoidType *jjtn001 = new ASTPommeVoidType(JJTPOMMEVOIDTYPE);
          bool jjtc001 = true;
          jjtree.openNodeScope(jjtn001);
          jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(VOID);
      } catch ( ...) {
if (jjtc001) {
            jjtree.clearNodeScope(jjtn001);
            jjtc001 = false;
          } else {
            jjtree.popNode();
          }
      }
if (jjtc001) {
            jjtree.closeNodeScope(jjtn001, true);
            if (jjtree.nodeCreated()) {
             jjtreeCloseNodeScope(jjtn001);
            }
          }
      break;
      }
    case IDENTIFIER:{
      type();
      break;
      }
    default:
      jj_la1[29] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::identmeth() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case IDENTIFIER:{
      ident();
      break;
      }
    case IDENTIFIEROPERATOR:{
      identOp();
      break;
      }
    default:
      jj_la1[30] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::type() {
    ident();
}


void PommeLexer::exp() {
    exp1();
    expP();
}


void PommeLexer::expP() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case AND:{
      jj_consume_token(AND);
      exp1();
ASTPommeAnd *jjtn001 = new ASTPommeAnd(JJTPOMMEAND);
                       bool jjtc001 = true;
                       jjtree.openNodeScope(jjtn001);
                       jjtreeOpenNodeScope(jjtn001);
      try {
        expP();
      } catch ( ...) {
if (jjtc001) {
                         jjtree.clearNodeScope(jjtn001);
                         jjtc001 = false;
                       } else {
                         jjtree.popNode();
                       }
      }
if (jjtc001) {
                         jjtree.closeNodeScope(jjtn001,  2);
                         if (jjtree.nodeCreated()) {
                          jjtreeCloseNodeScope(jjtn001);
                         }
                       }
      break;
      }
    case OR:{
      jj_consume_token(OR);
      exp1();
ASTPommeOr *jjtn002 = new ASTPommeOr(JJTPOMMEOR);
                        bool jjtc002 = true;
                        jjtree.openNodeScope(jjtn002);
                        jjtreeOpenNodeScope(jjtn002);
      try {
        expP();
      } catch ( ...) {
if (jjtc002) {
                          jjtree.clearNodeScope(jjtn002);
                          jjtc002 = false;
                        } else {
                          jjtree.popNode();
                        }
      }
if (jjtc002) {
                          jjtree.closeNodeScope(jjtn002,  2);
                          if (jjtree.nodeCreated()) {
                           jjtreeCloseNodeScope(jjtn002);
                          }
                        }
      break;
      }
    default:
      jj_la1[31] = jj_gen;

    }
}


void PommeLexer::exp1() {
    exp2();
    exp1P();
}


void PommeLexer::exp1P() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case EQ:{
      jj_consume_token(EQ);
      exp2();
ASTPommeEQ *jjtn001 = new ASTPommeEQ(JJTPOMMEEQ);
                      bool jjtc001 = true;
                      jjtree.openNodeScope(jjtn001);
                      jjtreeOpenNodeScope(jjtn001);
      try {
        exp1P();
      } catch ( ...) {
if (jjtc001) {
                        jjtree.clearNodeScope(jjtn001);
                        jjtc001 = false;
                      } else {
                        jjtree.popNode();
                      }
      }
if (jjtc001) {
                        jjtree.closeNodeScope(jjtn001,  2);
                        if (jjtree.nodeCreated()) {
                         jjtreeCloseNodeScope(jjtn001);
                        }
                      }
      break;
      }
    case NEQ:{
      jj_consume_token(NEQ);
      exp2();
ASTPommeNEQ *jjtn002 = new ASTPommeNEQ(JJTPOMMENEQ);
                         bool jjtc002 = true;
                         jjtree.openNodeScope(jjtn002);
                         jjtreeOpenNodeScope(jjtn002);
      try {
        exp1P();
      } catch ( ...) {
if (jjtc002) {
                           jjtree.clearNodeScope(jjtn002);
                           jjtc002 = false;
                         } else {
                           jjtree.popNode();
                         }
      }
if (jjtc002) {
                           jjtree.closeNodeScope(jjtn002,  2);
                           if (jjtree.nodeCreated()) {
                            jjtreeCloseNodeScope(jjtn002);
                           }
                         }
      break;
      }
    case GT:{
      jj_consume_token(GT);
      exp2();
ASTPommeGT *jjtn003 = new ASTPommeGT(JJTPOMMEGT);
                        bool jjtc003 = true;
                        jjtree.openNodeScope(jjtn003);
                        jjtreeOpenNodeScope(jjtn003);
      try {
        exp1P();
      } catch ( ...) {
if (jjtc003) {
                          jjtree.clearNodeScope(jjtn003);
                          jjtc003 = false;
                        } else {
                          jjtree.popNode();
                        }
      }
if (jjtc003) {
                          jjtree.closeNodeScope(jjtn003,  2);
                          if (jjtree.nodeCreated()) {
                           jjtreeCloseNodeScope(jjtn003);
                          }
                        }
      break;
      }
    case GET:{
      jj_consume_token(GET);
      exp2();
ASTPommeGET *jjtn004 = new ASTPommeGET(JJTPOMMEGET);
                         bool jjtc004 = true;
                         jjtree.openNodeScope(jjtn004);
                         jjtreeOpenNodeScope(jjtn004);
      try {
        exp1P();
      } catch ( ...) {
if (jjtc004) {
                           jjtree.clearNodeScope(jjtn004);
                           jjtc004 = false;
                         } else {
                           jjtree.popNode();
                         }
      }
if (jjtc004) {
                           jjtree.closeNodeScope(jjtn004,  2);
                           if (jjtree.nodeCreated()) {
                            jjtreeCloseNodeScope(jjtn004);
                           }
                         }
      break;
      }
    case LT:{
      jj_consume_token(LT);
      exp2();
ASTPommeLT *jjtn005 = new ASTPommeLT(JJTPOMMELT);
                        bool jjtc005 = true;
                        jjtree.openNodeScope(jjtn005);
                        jjtreeOpenNodeScope(jjtn005);
      try {
        exp1P();
      } catch ( ...) {
if (jjtc005) {
                          jjtree.clearNodeScope(jjtn005);
                          jjtc005 = false;
                        } else {
                          jjtree.popNode();
                        }
      }
if (jjtc005) {
                          jjtree.closeNodeScope(jjtn005,  2);
                          if (jjtree.nodeCreated()) {
                           jjtreeCloseNodeScope(jjtn005);
                          }
                        }
      break;
      }
    case LET:{
      jj_consume_token(LET);
      exp2();
ASTPommeLET *jjtn006 = new ASTPommeLET(JJTPOMMELET);
                         bool jjtc006 = true;
                         jjtree.openNodeScope(jjtn006);
                         jjtreeOpenNodeScope(jjtn006);
      try {
        exp1P();
      } catch ( ...) {
if (jjtc006) {
                           jjtree.clearNodeScope(jjtn006);
                           jjtc006 = false;
                         } else {
                           jjtree.popNode();
                         }
      }
if (jjtc006) {
                           jjtree.closeNodeScope(jjtn006,  2);
                           if (jjtree.nodeCreated()) {
                            jjtreeCloseNodeScope(jjtn006);
                           }
                         }
      break;
      }
    default:
      jj_la1[32] = jj_gen;

    }
}


void PommeLexer::exp2() {
    terme();
    exp2P();
}


void PommeLexer::exp2P() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case ADD:{
      jj_consume_token(ADD);
      terme();
ASTPommeAdd *jjtn001 = new ASTPommeAdd(JJTPOMMEADD);
                        bool jjtc001 = true;
                        jjtree.openNodeScope(jjtn001);
                        jjtreeOpenNodeScope(jjtn001);
      try {
        exp2P();
      } catch ( ...) {
if (jjtc001) {
                          jjtree.clearNodeScope(jjtn001);
                          jjtc001 = false;
                        } else {
                          jjtree.popNode();
                        }
      }
if (jjtc001) {
                          jjtree.closeNodeScope(jjtn001,  2);
                          if (jjtree.nodeCreated()) {
                           jjtreeCloseNodeScope(jjtn001);
                          }
                        }
      break;
      }
    case MINUS:{
      jj_consume_token(MINUS);
      terme();
ASTPommeMinus *jjtn002 = new ASTPommeMinus(JJTPOMMEMINUS);
                            bool jjtc002 = true;
                            jjtree.openNodeScope(jjtn002);
                            jjtreeOpenNodeScope(jjtn002);
      try {
        exp2P();
      } catch ( ...) {
if (jjtc002) {
                              jjtree.clearNodeScope(jjtn002);
                              jjtc002 = false;
                            } else {
                              jjtree.popNode();
                            }
      }
if (jjtc002) {
                              jjtree.closeNodeScope(jjtn002,  2);
                              if (jjtree.nodeCreated()) {
                               jjtreeCloseNodeScope(jjtn002);
                              }
                            }
      break;
      }
    case SHIFTR:{
      jj_consume_token(SHIFTR);
      terme();
ASTPommeShiftR *jjtn003 = new ASTPommeShiftR(JJTPOMMESHIFTR);
                             bool jjtc003 = true;
                             jjtree.openNodeScope(jjtn003);
                             jjtreeOpenNodeScope(jjtn003);
      try {
        exp2P();
      } catch ( ...) {
if (jjtc003) {
                               jjtree.clearNodeScope(jjtn003);
                               jjtc003 = false;
                             } else {
                               jjtree.popNode();
                             }
      }
if (jjtc003) {
                               jjtree.closeNodeScope(jjtn003,  2);
                               if (jjtree.nodeCreated()) {
                                jjtreeCloseNodeScope(jjtn003);
                               }
                             }
      break;
      }
    case SHIFTL:{
      jj_consume_token(SHIFTL);
      terme();
ASTPommeShiftL *jjtn004 = new ASTPommeShiftL(JJTPOMMESHIFTL);
                             bool jjtc004 = true;
                             jjtree.openNodeScope(jjtn004);
                             jjtreeOpenNodeScope(jjtn004);
      try {
        exp2P();
      } catch ( ...) {
if (jjtc004) {
                               jjtree.clearNodeScope(jjtn004);
                               jjtc004 = false;
                             } else {
                               jjtree.popNode();
                             }
      }
if (jjtc004) {
                               jjtree.closeNodeScope(jjtn004,  2);
                               if (jjtree.nodeCreated()) {
                                jjtreeCloseNodeScope(jjtn004);
                               }
                             }
      break;
      }
    default:
      jj_la1[33] = jj_gen;

    }
}


void PommeLexer::terme() {
    fact2();
    termeP();
}


void PommeLexer::termeP() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case MULT:{
      jj_consume_token(MULT);
      fact2();
ASTPommeMult *jjtn001 = new ASTPommeMult(JJTPOMMEMULT);
                         bool jjtc001 = true;
                         jjtree.openNodeScope(jjtn001);
                         jjtreeOpenNodeScope(jjtn001);
      try {
        termeP();
      } catch ( ...) {
if (jjtc001) {
                           jjtree.clearNodeScope(jjtn001);
                           jjtc001 = false;
                         } else {
                           jjtree.popNode();
                         }
      }
if (jjtc001) {
                           jjtree.closeNodeScope(jjtn001,  2);
                           if (jjtree.nodeCreated()) {
                            jjtreeCloseNodeScope(jjtn001);
                           }
                         }
      break;
      }
    case DIV:{
      jj_consume_token(DIV);
      fact2();
ASTPommeDiv *jjtn002 = new ASTPommeDiv(JJTPOMMEDIV);
                          bool jjtc002 = true;
                          jjtree.openNodeScope(jjtn002);
                          jjtreeOpenNodeScope(jjtn002);
      try {
        termeP();
      } catch ( ...) {
if (jjtc002) {
                            jjtree.clearNodeScope(jjtn002);
                            jjtc002 = false;
                          } else {
                            jjtree.popNode();
                          }
      }
if (jjtc002) {
                            jjtree.closeNodeScope(jjtn002,  2);
                            if (jjtree.nodeCreated()) {
                             jjtreeCloseNodeScope(jjtn002);
                            }
                          }
      break;
      }
    case MODULO:{
      jj_consume_token(MODULO);
      fact2();
ASTPommeModulo *jjtn003 = new ASTPommeModulo(JJTPOMMEMODULO);
                             bool jjtc003 = true;
                             jjtree.openNodeScope(jjtn003);
                             jjtreeOpenNodeScope(jjtn003);
      try {
        termeP();
      } catch ( ...) {
if (jjtc003) {
                               jjtree.clearNodeScope(jjtn003);
                               jjtc003 = false;
                             } else {
                               jjtree.popNode();
                             }
      }
if (jjtc003) {
                               jjtree.closeNodeScope(jjtn003,  2);
                               if (jjtree.nodeCreated()) {
                                jjtreeCloseNodeScope(jjtn003);
                               }
                             }
      break;
      }
    default:
      jj_la1[34] = jj_gen;

    }
}


void PommeLexer::fact2() {
    if (jj_2_5(3)) {
      fact();
    } else {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case PARENTL:{
        jj_consume_token(PARENTL);
        exp();
        jj_consume_token(PARENTR);
        break;
        }
      case MINUS:{
        jj_consume_token(MINUS);
ASTPommeUnary *jjtn001 = new ASTPommeUnary(JJTPOMMEUNARY);
                    bool jjtc001 = true;
                    jjtree.openNodeScope(jjtn001);
                    jjtreeOpenNodeScope(jjtn001);
        try {
          fact2();
        } catch ( ...) {
if (jjtc001) {
                      jjtree.clearNodeScope(jjtn001);
                      jjtc001 = false;
                    } else {
                      jjtree.popNode();
                    }
        }
if (jjtc001) {
                      jjtree.closeNodeScope(jjtn001,  1);
                      if (jjtree.nodeCreated()) {
                       jjtreeCloseNodeScope(jjtn001);
                      }
                    }
        break;
        }
      case EXCLAMATION:{
        jj_consume_token(EXCLAMATION);
ASTPommeNot *jjtn002 = new ASTPommeNot(JJTPOMMENOT);
                          bool jjtc002 = true;
                          jjtree.openNodeScope(jjtn002);
                          jjtreeOpenNodeScope(jjtn002);
        try {
          fact2();
        } catch ( ...) {
if (jjtc002) {
                            jjtree.clearNodeScope(jjtn002);
                            jjtc002 = false;
                          } else {
                            jjtree.popNode();
                          }
        }
if (jjtc002) {
                            jjtree.closeNodeScope(jjtn002,  1);
                            if (jjtree.nodeCreated()) {
                             jjtreeCloseNodeScope(jjtn002);
                            }
                          }
        break;
        }
      case TILDE:{
        jj_consume_token(TILDE);
ASTPommeTilde *jjtn003 = new ASTPommeTilde(JJTPOMMETILDE);
                    bool jjtc003 = true;
                    jjtree.openNodeScope(jjtn003);
                    jjtreeOpenNodeScope(jjtn003);
        try {
          fact2();
        } catch ( ...) {
if (jjtc003) {
                      jjtree.clearNodeScope(jjtn003);
                      jjtc003 = false;
                    } else {
                      jjtree.popNode();
                    }
        }
if (jjtc003) {
                      jjtree.closeNodeScope(jjtn003,  1);
                      if (jjtree.nodeCreated()) {
                       jjtreeCloseNodeScope(jjtn003);
                      }
                    }
        break;
        }
      default:
        jj_la1[35] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
    }
}


void PommeLexer::fact() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case NEWEXP:{
      jj_consume_token(NEWEXP);
      ident();
      jj_consume_token(PARENTL);
      listexp();
ASTPommeNew *jjtn001 = new ASTPommeNew(JJTPOMMENEW);
                                               bool jjtc001 = true;
                                               jjtree.openNodeScope(jjtn001);
                                               jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(PARENTR);
      } catch ( ...) {
if (jjtc001) {
                                                 jjtree.clearNodeScope(jjtn001);
                                                 jjtc001 = false;
                                               } else {
                                                 jjtree.popNode();
                                               }
      }
if (jjtc001) {
                                                 jjtree.closeNodeScope(jjtn001,  2);
                                                 if (jjtree.nodeCreated()) {
                                                  jjtreeCloseNodeScope(jjtn001);
                                                 }
                                               }
      break;
      }
    case IDENTIFIEROPERATOR:
    case IDENTIFIER:{
      listaccess();
      break;
      }
    case TRUE:{
ASTPommeTrue *jjtn002 = new ASTPommeTrue(JJTPOMMETRUE);
            bool jjtc002 = true;
            jjtree.openNodeScope(jjtn002);
            jjtreeOpenNodeScope(jjtn002);
      try {
        jj_consume_token(TRUE);
      } catch ( ...) {
if (jjtc002) {
              jjtree.clearNodeScope(jjtn002);
              jjtc002 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc002) {
              jjtree.closeNodeScope(jjtn002, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn002);
              }
            }
      break;
      }
    case FALSE:{
ASTPommeFalse *jjtn003 = new ASTPommeFalse(JJTPOMMEFALSE);
            bool jjtc003 = true;
            jjtree.openNodeScope(jjtn003);
            jjtreeOpenNodeScope(jjtn003);
      try {
        jj_consume_token(FALSE);
      } catch ( ...) {
if (jjtc003) {
              jjtree.clearNodeScope(jjtn003);
              jjtc003 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc003) {
              jjtree.closeNodeScope(jjtn003, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn003);
              }
            }
      break;
      }
    case INT:
    case FLOAT:{
      number();
      break;
      }
    case STRING:{
      pommeString();
      break;
      }
    case NULLEXP:{
ASTPommeNull *jjtn004 = new ASTPommeNull(JJTPOMMENULL);
            bool jjtc004 = true;
            jjtree.openNodeScope(jjtn004);
            jjtreeOpenNodeScope(jjtn004);
      try {
        jj_consume_token(NULLEXP);
      } catch ( ...) {
if (jjtc004) {
              jjtree.clearNodeScope(jjtn004);
              jjtc004 = false;
            } else {
              jjtree.popNode();
            }
      }
if (jjtc004) {
              jjtree.closeNodeScope(jjtn004, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn004);
              }
            }
      break;
      }
    default:
      jj_la1[36] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::listaccess() {
    access();
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case POINT:{
      jj_consume_token(POINT);
      access();
ASTPommeListAccess *jjtn001 = new ASTPommeListAccess(JJTPOMMELISTACCESS);
                                           bool jjtc001 = true;
                                           jjtree.openNodeScope(jjtn001);
                                           jjtreeOpenNodeScope(jjtn001);
      try {
        listaccessP();
      } catch ( ...) {
if (jjtc001) {
                                             jjtree.clearNodeScope(jjtn001);
                                             jjtc001 = false;
                                           } else {
                                             jjtree.popNode();
                                           }
      }
if (jjtc001) {
                                             jjtree.closeNodeScope(jjtn001,  3);
                                             if (jjtree.nodeCreated()) {
                                              jjtreeCloseNodeScope(jjtn001);
                                             }
                                           }
      break;
      }
    case BRACKETL:{
      jj_consume_token(BRACKETL);
      exp();
      jj_consume_token(BRACKETR);
ASTPommeAccessTab *jjtn002 = new ASTPommeAccessTab(JJTPOMMEACCESSTAB);
                                                                bool jjtc002 = true;
                                                                jjtree.openNodeScope(jjtn002);
                                                                jjtreeOpenNodeScope(jjtn002);
      try {
        listaccessP();
      } catch ( ...) {
if (jjtc002) {
                                                                  jjtree.clearNodeScope(jjtn002);
                                                                  jjtc002 = false;
                                                                } else {
                                                                  jjtree.popNode();
                                                                }
      }
if (jjtc002) {
                                                                  jjtree.closeNodeScope(jjtn002,  3);
                                                                  if (jjtree.nodeCreated()) {
                                                                   jjtreeCloseNodeScope(jjtn002);
                                                                  }
                                                                }
      break;
      }
    default:
      jj_la1[37] = jj_gen;

    }
}


void PommeLexer::listaccessP() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case POINT:{
      jj_consume_token(POINT);
      access();
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case POINT:{
        jj_consume_token(POINT);
        access();
ASTPommeListAccessP *jjtn001 = new ASTPommeListAccessP(JJTPOMMELISTACCESSP);
                                                                           bool jjtc001 = true;
                                                                           jjtree.openNodeScope(jjtn001);
                                                                           jjtreeOpenNodeScope(jjtn001);
        try {
          listaccessP();
        } catch ( ...) {
if (jjtc001) {
                                                                             jjtree.clearNodeScope(jjtn001);
                                                                             jjtc001 = false;
                                                                           } else {
                                                                             jjtree.popNode();
                                                                           }
        }
if (jjtc001) {
                                                                             jjtree.closeNodeScope(jjtn001,  3);
                                                                             if (jjtree.nodeCreated()) {
                                                                              jjtreeCloseNodeScope(jjtn001);
                                                                             }
                                                                           }
        break;
        }
      case BRACKETL:{
        jj_consume_token(BRACKETL);
        exp();
        jj_consume_token(BRACKETR);
ASTPommeAccessTab *jjtn002 = new ASTPommeAccessTab(JJTPOMMEACCESSTAB);
                                                                                        bool jjtc002 = true;
                                                                                        jjtree.openNodeScope(jjtn002);
                                                                                        jjtreeOpenNodeScope(jjtn002);
        try {
          listaccessP();
        } catch ( ...) {
if (jjtc002) {
                                                                                          jjtree.clearNodeScope(jjtn002);
                                                                                          jjtc002 = false;
                                                                                        } else {
                                                                                          jjtree.popNode();
                                                                                        }
        }
if (jjtc002) {
                                                                                          jjtree.closeNodeScope(jjtn002,  3);
                                                                                          if (jjtree.nodeCreated()) {
                                                                                           jjtreeCloseNodeScope(jjtn002);
                                                                                          }
                                                                                        }
        break;
        }
      default:
        jj_la1[38] = jj_gen;

      }
      break;
      }
    default:
      jj_la1[39] = jj_gen;
ASTPommeAcnil *jjtn003 = new ASTPommeAcnil(JJTPOMMEACNIL);
                    bool jjtc003 = true;
                    jjtree.openNodeScope(jjtn003);
                    jjtreeOpenNodeScope(jjtn003);
      try {
jjtree.closeNodeScope(jjtn003, true);
                    jjtc003 = false;
                    if (jjtree.nodeCreated()) {
                     jjtreeCloseNodeScope(jjtn003);
                    }

      } catch ( ...) {
if (jjtc003) {
                      jjtree.clearNodeScope(jjtn003);
                      jjtc003 = false;
                    } else {
                      jjtree.popNode();
                    }
      }
if (jjtc003) {
                      jjtree.closeNodeScope(jjtn003, true);
                      if (jjtree.nodeCreated()) {
                       jjtreeCloseNodeScope(jjtn003);
                      }
                    }
    }
}


void PommeLexer::access() {
    if (jj_2_6(2)) {
      identmeth();
      jj_consume_token(PARENTL);
      listexp();
ASTPommeAccessMethode *jjtn001 = new ASTPommeAccessMethode(JJTPOMMEACCESSMETHODE);
                                                       bool jjtc001 = true;
                                                       jjtree.openNodeScope(jjtn001);
                                                       jjtreeOpenNodeScope(jjtn001);
      try {
        jj_consume_token(PARENTR);
      } catch ( ...) {
if (jjtc001) {
                                                         jjtree.clearNodeScope(jjtn001);
                                                         jjtc001 = false;
                                                       } else {
                                                         jjtree.popNode();
                                                       }
      }
if (jjtc001) {
                                                         jjtree.closeNodeScope(jjtn001,  2);
                                                         if (jjtree.nodeCreated()) {
                                                          jjtreeCloseNodeScope(jjtn001);
                                                         }
                                                       }
    } else {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case IDENTIFIER:{
        ident();
        break;
        }
      default:
        jj_la1[40] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
    }
}


void PommeLexer::number() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case INT:{
      pommeInt();
      break;
      }
    case FLOAT:{
      pommeFloat();
      break;
      }
    default:
      jj_la1[41] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


  PommeLexer::PommeLexer(TokenManager *tokenManager){
    head = nullptr;
    ReInit(tokenManager);
}
PommeLexer::~PommeLexer()
{
  clear();
}

void PommeLexer::ReInit(TokenManager* tokenManager){
    clear();
    errorHandler = new ErrorHandler();
    hasError = false;
    token_source = tokenManager;
    head = token = new Token();
    token->kind = 0;
    token->next = nullptr;
    jj_lookingAhead = false;
    jj_rescan = false;
    jj_done = false;
    jj_scanpos = jj_lastpos = nullptr;
    jj_gc = 0;
    jj_kind = -1;
    indent = 0;
    trace = false;
    jj_ntk = -1;
    jjtree.reset();
    jj_gen = 0;
    for (int i = 0; i < 42; i++) jj_la1[i] = -1;
  }


void PommeLexer::clear(){
  //Since token manager was generate from outside,
  //parser should not take care of deleting
  //if (token_source) delete token_source;
  if (head) {
    Token *next, *t = head;
    while (t) {
      next = t->next;
      delete t;
      t = next;
    }
  }
  if (errorHandler) {
    delete errorHandler, errorHandler = nullptr;
  }
}


Token * PommeLexer::jj_consume_token(int kind)  {
    Token *oldToken;
    if ((oldToken = token)->next != nullptr) token = token->next;
    else token = token->next = token_source->getNextToken();
    jj_ntk = -1;
    if (token->kind == kind) {
      jj_gen++;
      if (++jj_gc > 100) {
        jj_gc = 0;
        for (int i = 0; i < 6; i++) {
          JJCalls *c = &jj_2_rtns[i];
          while (c != nullptr) {
            if (c->gen < jj_gen) c->first = nullptr;
            c = c->next;
          }
        }
      }
      return token;
    }
    token = oldToken;
    jj_kind = kind;
    JJString image = kind >= 0 ? tokenImage[kind] : tokenImage[0];
    errorHandler->handleUnexpectedToken(kind, image.substr(1, image.size() - 2), getToken(1), this);
    hasError = true;
    return token;
  }


bool  PommeLexer::jj_scan_token(int kind){
    if (jj_scanpos == jj_lastpos) {
      jj_la--;
      if (jj_scanpos->next == nullptr) {
        jj_lastpos = jj_scanpos = jj_scanpos->next = token_source->getNextToken();
      } else {
        jj_lastpos = jj_scanpos = jj_scanpos->next;
      }
    } else {
      jj_scanpos = jj_scanpos->next;
    }
    if (jj_rescan) {
      int i = 0; Token *tok = token;
      while (tok != nullptr && tok != jj_scanpos) { i++; tok = tok->next; }
      if (tok != nullptr) jj_add_error_token(kind, i);
    }
    if (jj_scanpos->kind != kind) return true;
    if (jj_la == 0 && jj_scanpos == jj_lastpos) { return jj_done = true; }
    return false;
  }


/** Get the next Token. */

Token * PommeLexer::getNextToken(){
    if (token->next != nullptr) token = token->next;
    else token = token->next = token_source->getNextToken();
    jj_ntk = -1;
    jj_gen++;
    return token;
  }

/** Get the specific Token. */

Token * PommeLexer::getToken(int index){
    Token *t = token;
    for (int i = 0; i < index; i++) {
      if (t->next != nullptr) t = t->next;
      else t = t->next = token_source->getNextToken();
    }
    return t;
  }


int PommeLexer::jj_ntk_f(){
    if ((jj_nt=token->next) == nullptr)
      return (jj_ntk = (token->next=token_source->getNextToken())->kind);
    else
      return (jj_ntk = jj_nt->kind);
  }


  void PommeLexer::jj_add_error_token(int kind, int pos)  {
  }


 void  PommeLexer::parseError()   {
      fprintf(stderr, "Parse error at: %d:%d, after token: %s encountered: %s\n", token->beginLine, token->beginColumn, addUnicodeEscapes(token->image).c_str(), addUnicodeEscapes(getToken(1)->image).c_str());
   }


  bool PommeLexer::trace_enabled()  {
    return trace;
  }


  void PommeLexer::enable_tracing()  {
  }

  void PommeLexer::disable_tracing()  {
  }


  void PommeLexer::jj_rescan_token(){
    jj_rescan = true;
    for (int i = 0; i < 6; i++) {
      JJCalls *p = &jj_2_rtns[i];
      do {
        if (p->gen > jj_gen) {
          jj_la = p->arg; jj_lastpos = jj_scanpos = p->first;
          switch (i) {
            case 0: jj_3_1(); break;
            case 1: jj_3_2(); break;
            case 2: jj_3_3(); break;
            case 3: jj_3_4(); break;
            case 4: jj_3_5(); break;
            case 5: jj_3_6(); break;
          }
        }
        p = p->next;
      } while (p != nullptr);
    }
    jj_rescan = false;
  }


  void PommeLexer::jj_save(int index, int xla){
    JJCalls *p = &jj_2_rtns[index];
    while (p->gen > jj_gen) {
      if (p->next == nullptr) { p = p->next = new JJCalls(); break; }
      p = p->next;
    }
    p->gen = jj_gen + xla - jj_la; p->first = token; p->arg = xla;
  }


}
