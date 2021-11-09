/* PommeLexer.cc */
#include "PommeLexer.h"
#include "TokenMgrError.h"
#include "SimpleNode.h"
namespace Pomme {
  unsigned int jj_la1_0[] = {
0xe000000,0xc000000,0x0,0x2000000,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4000000,0x0,0x0,0x80,0x0,0xd0c00000,0xebaa80,0xd0c00000,0x0,0x20000000,0x400,0x0,0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x140500,0x1005000,0x400,0x0,0x0,0x0,0x0,};
  unsigned int jj_la1_1[] = {
0xa800000,0xa800000,0x4000080,0x8000000,0xf3800000,0x1000000,0xf2800000,0x10000000,0xe0000000,0x0,0x4000080,0x8000000,0x800,0x0,0x0,0x2800000,0x1004007,0x0,0x4007,0x18,0x0,0x6020,0x800,0x1000000,0x0,0x0,0x800,0x800000,0x4000,0x600000,0x1f8000,0x0,0x0,0x6020,0x4000,0x1000,0x0,0x0,};
  unsigned int jj_la1_2[] = {
0x80,0x80,0x0,0x0,0x81,0x80,0x81,0x0,0x0,0x1,0x0,0x0,0x0,0x80,0x0,0x80,0xc0,0x0,0xc0,0x0,0x0,0x3fe,0x0,0x80,0x0,0x80,0x0,0x80,0xc0,0x0,0x0,0x0,0x0,0x0,0x3fe,0x0,0x80,0x220,};

  /** Constructor with user supplied TokenManager. */




SimpleNode          * PommeLexer::input() {/*@bgen(jjtree) input */
  ASTinput *jjtn000 = new ASTinput(JJTINPUT);
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


void PommeLexer::ident() {Token *t;/*@bgen(jjtree) ident */
  ASTident *jjtn000 = new ASTident(JJTIDENT);
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


void PommeLexer::identOp() {Token *t;/*@bgen(jjtree) identOp */
  ASTidentOp *jjtn000 = new ASTidentOp(JJTIDENTOP);
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


void PommeLexer::pommeInt() {Token *t;/*@bgen(jjtree) pommeInt */
  ASTpommeInt *jjtn000 = new ASTpommeInt(JJTPOMMEINT);
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


void PommeLexer::pommeFloat() {Token *t;/*@bgen(jjtree) pommeFloat */
  ASTpommeFloat *jjtn000 = new ASTpommeFloat(JJTPOMMEFLOAT);
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
jjtn000->m_Value = std::stof(t->image);
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


void PommeLexer::pommeString() {Token *t;/*@bgen(jjtree) pommeString */
  ASTpommeString *jjtn000 = new ASTpommeString(JJTPOMMESTRING);
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
ASTscopes *jjtn001 = new ASTscopes(JJTSCOPES);
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
ASTscinil *jjtn002 = new ASTscinil(JJTSCINIL);
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
ASTpommeTypeDef *jjtn001 = new ASTpommeTypeDef(JJTPOMMETYPEDEF);
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
ASTpommeClass *jjtn001 = new ASTpommeClass(JJTPOMMECLASS);
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
ASTpommeClassChild *jjtn002 = new ASTpommeClassChild(JJTPOMMECLASSCHILD);
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
ASTpommeModdedClass *jjtn003 = new ASTpommeModdedClass(JJTPOMMEMODDEDCLASS);
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
ASTdecls *jjtn001 = new ASTdecls(JJTDECLS);
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
ASTdnil *jjtn002 = new ASTdnil(JJTDNIL);
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
    if (jj_2_2(8)) {
      methode();
    } else {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case CONST:
      case IDENTIFIER:{
        var();
        break;
        }
      default:
        jj_la1[5] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
    }
}


void PommeLexer::methode() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case VOID:
    case STATIC:
    case PUBLIC:
    case PRIVATE:
    case PROTECTED:
    case OVERRIDE:
    case IDENTIFIER:{
      identfuncs();
      typemeth();
      identmeth();
      jj_consume_token(PARENTL);
      headers();
      jj_consume_token(PARENTR);
      jj_consume_token(BRACEL);
      instrs();
ASTpommeMethode *jjtn001 = new ASTpommeMethode(JJTPOMMEMETHODE);
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
ASTpommeMethodeNative *jjtn002 = new ASTpommeMethodeNative(JJTPOMMEMETHODENATIVE);
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
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::identfuncs() {
    pommeStatic();
    visibility();
ASTidentFuncs *jjtn001 = new ASTidentFuncs(JJTIDENTFUNCS);
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
ASTpommeStatic *jjtn001 = new ASTpommeStatic(JJTPOMMESTATIC);
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
      jj_la1[7] = jj_gen;
ASTsnil *jjtn002 = new ASTsnil(JJTSNIL);
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
ASTpommePublic *jjtn001 = new ASTpommePublic(JJTPOMMEPUBLIC);
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
ASTpommePrivate *jjtn002 = new ASTpommePrivate(JJTPOMMEPRIVATE);
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
ASTpommeProtected *jjtn003 = new ASTpommeProtected(JJTPOMMEPROTECTED);
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
      jj_la1[8] = jj_gen;
ASTvinil *jjtn004 = new ASTvinil(JJTVINIL);
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
ASTpommeOverride *jjtn001 = new ASTpommeOverride(JJTPOMMEOVERRIDE);
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
      jj_la1[9] = jj_gen;
ASTonil *jjtn002 = new ASTonil(JJTONIL);
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
ASTpommeEnum *jjtn001 = new ASTpommeEnum(JJTPOMMEENUM);
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
ASTpommeExtendsEnum *jjtn002 = new ASTpommeExtendsEnum(JJTPOMMEEXTENDSENUM);
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
        jj_la1[10] = jj_gen;
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
ASTpommeModdedEnum *jjtn003 = new ASTpommeModdedEnum(JJTPOMMEMODDEDENUM);
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
      jj_la1[11] = jj_gen;
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
ASTdeclenums *jjtn001 = new ASTdeclenums(JJTDECLENUMS);
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
        jj_la1[12] = jj_gen;

      }
      break;
      }
    default:
      jj_la1[13] = jj_gen;
ASTennil *jjtn002 = new ASTennil(JJTENNIL);
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
ASTenumassign *jjtn001 = new ASTenumassign(JJTENUMASSIGN);
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
      jj_la1[14] = jj_gen;
ASTenumdefault *jjtn002 = new ASTenumdefault(JJTENUMDEFAULT);
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
ASTpommeGlobalFunction *jjtn001 = new ASTpommeGlobalFunction(JJTPOMMEGLOBALFUNCTION);
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
ASTpommeGlobalFunctionNative *jjtn002 = new ASTpommeGlobalFunctionNative(JJTPOMMEGLOBALFUNCTIONNATIVE);
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
      jj_la1[15] = jj_gen;
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
    case TILDE:
    case CONST:
    case IDENTIFIEROPERATOR:
    case IDENTIFIER:{
      instr();
      jj_consume_token(SEMICOLON);
ASTinstrs *jjtn001 = new ASTinstrs(JJTINSTRS);
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
      jj_la1[16] = jj_gen;
ASTinil *jjtn002 = new ASTinil(JJTINIL);
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
    if (jj_2_3(2)) {
      var();
    } else {
      switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
      case INCR:{
        jj_consume_token(INCR);
ASTincrementPre *jjtn001 = new ASTincrementPre(JJTINCREMENTPRE);
                   bool jjtc001 = true;
                   jjtree.openNodeScope(jjtn001);
                   jjtreeOpenNodeScope(jjtn001);
        try {
          listacces();
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
ASTdecrementPre *jjtn002 = new ASTdecrementPre(JJTDECREMENTPRE);
                   bool jjtc002 = true;
                   jjtree.openNodeScope(jjtn002);
                   jjtreeOpenNodeScope(jjtn002);
        try {
          listacces();
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
      case RETURN:{
        jj_consume_token(RETURN);
ASTpommeReturn *jjtn003 = new ASTpommeReturn(JJTPOMMERETURN);
                     bool jjtc003 = true;
                     jjtree.openNodeScope(jjtn003);
                     jjtreeOpenNodeScope(jjtn003);
        try {
          exp();
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
      case WHILE:{
        jj_consume_token(WHILE);
        jj_consume_token(PARENTL);
        exp();
        jj_consume_token(PARENTR);
        jj_consume_token(BRACEL);
        instrs();
ASTpommeWhile *jjtn004 = new ASTpommeWhile(JJTPOMMEWHILE);
                                                                bool jjtc004 = true;
                                                                jjtree.openNodeScope(jjtn004);
                                                                jjtreeOpenNodeScope(jjtn004);
        try {
          jj_consume_token(BRACER);
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
      case BREAK:{
ASTpommeBreak *jjtn005 = new ASTpommeBreak(JJTPOMMEBREAK);
            bool jjtc005 = true;
            jjtree.openNodeScope(jjtn005);
            jjtreeOpenNodeScope(jjtn005);
        try {
          jj_consume_token(BREAK);
        } catch ( ...) {
if (jjtc005) {
              jjtree.clearNodeScope(jjtn005);
              jjtc005 = false;
            } else {
              jjtree.popNode();
            }
        }
if (jjtc005) {
              jjtree.closeNodeScope(jjtn005, true);
              if (jjtree.nodeCreated()) {
               jjtreeCloseNodeScope(jjtn005);
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
ASTpommeIf *jjtn006 = new ASTpommeIf(JJTPOMMEIF);
                                                                      bool jjtc006 = true;
                                                                      jjtree.openNodeScope(jjtn006);
                                                                      jjtreeOpenNodeScope(jjtn006);
        try {
          pommeElse();
        } catch ( ...) {
if (jjtc006) {
                                                                        jjtree.clearNodeScope(jjtn006);
                                                                        jjtc006 = false;
                                                                      } else {
                                                                        jjtree.popNode();
                                                                      }
        }
if (jjtc006) {
                                                                        jjtree.closeNodeScope(jjtn006,  3);
                                                                        if (jjtree.nodeCreated()) {
                                                                         jjtreeCloseNodeScope(jjtn006);
                                                                        }
                                                                      }
        break;
        }
      case PRINT:{
        jj_consume_token(PRINT);
        jj_consume_token(PARENTL);
        exp();
ASTpommePrint *jjtn007 = new ASTpommePrint(JJTPOMMEPRINT);
                                    bool jjtc007 = true;
                                    jjtree.openNodeScope(jjtn007);
                                    jjtreeOpenNodeScope(jjtn007);
        try {
          jj_consume_token(PARENTR);
        } catch ( ...) {
if (jjtc007) {
                                      jjtree.clearNodeScope(jjtn007);
                                      jjtc007 = false;
                                    } else {
                                      jjtree.popNode();
                                    }
        }
if (jjtc007) {
                                      jjtree.closeNodeScope(jjtn007,  1);
                                      if (jjtree.nodeCreated()) {
                                       jjtreeCloseNodeScope(jjtn007);
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
ASTpommeSwitch *jjtn008 = new ASTpommeSwitch(JJTPOMMESWITCH);
                                                                    bool jjtc008 = true;
                                                                    jjtree.openNodeScope(jjtn008);
                                                                    jjtreeOpenNodeScope(jjtn008);
        try {
          jj_consume_token(BRACER);
        } catch ( ...) {
if (jjtc008) {
                                                                      jjtree.clearNodeScope(jjtn008);
                                                                      jjtc008 = false;
                                                                    } else {
                                                                      jjtree.popNode();
                                                                    }
        }
if (jjtc008) {
                                                                      jjtree.closeNodeScope(jjtn008,  2);
                                                                      if (jjtree.nodeCreated()) {
                                                                       jjtreeCloseNodeScope(jjtn008);
                                                                      }
                                                                    }
        break;
        }
      case TILDE:
      case IDENTIFIEROPERATOR:
      case IDENTIFIER:{
        listacces();
        switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
        case ASSIGNEMENT:{
          jj_consume_token(ASSIGNEMENT);
ASTassignement *jjtn009 = new ASTassignement(JJTASSIGNEMENT);
                                        bool jjtc009 = true;
                                        jjtree.openNodeScope(jjtn009);
                                        jjtreeOpenNodeScope(jjtn009);
          try {
            exp();
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
        case ADDEQ:{
          jj_consume_token(ADDEQ);
ASTaddeq *jjtn010 = new ASTaddeq(JJTADDEQ);
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
        case MINUSEQ:{
          jj_consume_token(MINUSEQ);
ASTminuseq *jjtn011 = new ASTminuseq(JJTMINUSEQ);
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
        case DIVEQ:{
          jj_consume_token(DIVEQ);
ASTdiveq *jjtn012 = new ASTdiveq(JJTDIVEQ);
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
        case MULTEQ:{
          jj_consume_token(MULTEQ);
ASTmulteq *jjtn013 = new ASTmulteq(JJTMULTEQ);
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
        case OREQ:{
          jj_consume_token(OREQ);
ASToreq *jjtn014 = new ASToreq(JJTOREQ);
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
        case ANDEQ:{
          jj_consume_token(ANDEQ);
ASTandeq *jjtn015 = new ASTandeq(JJTANDEQ);
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
        case SHIFTLEQ:{
          jj_consume_token(SHIFTLEQ);
ASTshiftleq *jjtn016 = new ASTshiftleq(JJTSHIFTLEQ);
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
        case SHIFTREQ:{
          jj_consume_token(SHIFTREQ);
ASTshiftreq *jjtn017 = new ASTshiftreq(JJTSHIFTREQ);
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
        case INCR:{
ASTincrementPost *jjtn018 = new ASTincrementPost(JJTINCREMENTPOST);
                                            bool jjtc018 = true;
                                            jjtree.openNodeScope(jjtn018);
                                            jjtreeOpenNodeScope(jjtn018);
          try {
            jj_consume_token(INCR);
          } catch ( ...) {
if (jjtc018) {
                                              jjtree.clearNodeScope(jjtn018);
                                              jjtc018 = false;
                                            } else {
                                              jjtree.popNode();
                                            }
          }
if (jjtc018) {
                                              jjtree.closeNodeScope(jjtn018,  1);
                                              if (jjtree.nodeCreated()) {
                                               jjtreeCloseNodeScope(jjtn018);
                                              }
                                            }
          break;
          }
        case DECR:{
ASTdecrementPost *jjtn019 = new ASTdecrementPost(JJTDECREMENTPOST);
                                            bool jjtc019 = true;
                                            jjtree.openNodeScope(jjtn019);
                                            jjtreeOpenNodeScope(jjtn019);
          try {
            jj_consume_token(DECR);
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
        default:
          jj_la1[17] = jj_gen;

        }
        break;
        }
      default:
        jj_la1[18] = jj_gen;
        jj_consume_token(-1);
        errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
      }
    }
}


void PommeLexer::listcases() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case CASE:{
      pommecase();
ASTpommeCases *jjtn001 = new ASTpommeCases(JJTPOMMECASES);
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
ASTpommeDefault *jjtn002 = new ASTpommeDefault(JJTPOMMEDEFAULT);
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
      jj_la1[19] = jj_gen;
ASTswinil *jjtn003 = new ASTswinil(JJTSWINIL);
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
ASTpommeCase *jjtn001 = new ASTpommeCase(JJTPOMMECASE);
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
      jj_la1[20] = jj_gen;
ASTinil *jjtn001 = new ASTinil(JJTINIL);
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
ASTlistexp *jjtn001 = new ASTlistexp(JJTLISTEXP);
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
      jj_la1[21] = jj_gen;
ASTexnil *jjtn002 = new ASTexnil(JJTEXNIL);
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
ASTlistexp *jjtn001 = new ASTlistexp(JJTLISTEXP);
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
ASTexnil *jjtn002 = new ASTexnil(JJTEXNIL);
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
ASTpommeVariable *jjtn001 = new ASTpommeVariable(JJTPOMMEVARIABLE);
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
ASTpommeConstant *jjtn002 = new ASTpommeConstant(JJTPOMMECONSTANT);
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
      jj_la1[23] = jj_gen;
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
      jj_la1[24] = jj_gen;
ASTomega *jjtn001 = new ASTomega(JJTOMEGA);
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
    case IDENTIFIER:{
      header();
ASTheaders *jjtn001 = new ASTheaders(JJTHEADERS);
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
      jj_la1[25] = jj_gen;
ASTenil *jjtn002 = new ASTenil(JJTENIL);
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
ASTheaders *jjtn001 = new ASTheaders(JJTHEADERS);
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
ASTenil *jjtn002 = new ASTenil(JJTENIL);
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
    type();
ASTheader *jjtn001 = new ASTheader(JJTHEADER);
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
}


void PommeLexer::typemeth() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case VOID:{
ASTvoidType *jjtn001 = new ASTvoidType(JJTVOIDTYPE);
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
      jj_la1[27] = jj_gen;
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
    case TILDE:{
      jj_consume_token(TILDE);
ASTpommeDestructor *jjtn001 = new ASTpommeDestructor(JJTPOMMEDESTRUCTOR);
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
                      jjtree.closeNodeScope(jjtn001,  1);
                      if (jjtree.nodeCreated()) {
                       jjtreeCloseNodeScope(jjtn001);
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
ASTpommeAnd *jjtn001 = new ASTpommeAnd(JJTPOMMEAND);
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
ASTpommeOr *jjtn002 = new ASTpommeOr(JJTPOMMEOR);
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
      jj_la1[29] = jj_gen;

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
ASTpommeEQ *jjtn001 = new ASTpommeEQ(JJTPOMMEEQ);
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
ASTpommeNEQ *jjtn002 = new ASTpommeNEQ(JJTPOMMENEQ);
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
ASTpommeGT *jjtn003 = new ASTpommeGT(JJTPOMMEGT);
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
ASTpommeGET *jjtn004 = new ASTpommeGET(JJTPOMMEGET);
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
ASTpommeLT *jjtn005 = new ASTpommeLT(JJTPOMMELT);
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
ASTpommeLET *jjtn006 = new ASTpommeLET(JJTPOMMELET);
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
      jj_la1[30] = jj_gen;

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
ASTpommeAdd *jjtn001 = new ASTpommeAdd(JJTPOMMEADD);
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
ASTpommeMinus *jjtn002 = new ASTpommeMinus(JJTPOMMEMINUS);
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
ASTpommeShiftR *jjtn003 = new ASTpommeShiftR(JJTPOMMESHIFTR);
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
ASTpommeShiftL *jjtn004 = new ASTpommeShiftL(JJTPOMMESHIFTL);
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
      jj_la1[31] = jj_gen;

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
ASTpommeMult *jjtn001 = new ASTpommeMult(JJTPOMMEMULT);
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
ASTpommeDiv *jjtn002 = new ASTpommeDiv(JJTPOMMEDIV);
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
ASTpommeModulo *jjtn003 = new ASTpommeModulo(JJTPOMMEMODULO);
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
      jj_la1[32] = jj_gen;

    }
}


void PommeLexer::fact2() {
    if (jj_2_4(3)) {
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
ASTpommeUnary *jjtn001 = new ASTpommeUnary(JJTPOMMEUNARY);
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
ASTpommeNot *jjtn002 = new ASTpommeNot(JJTPOMMENOT);
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
ASTpommeTilde *jjtn003 = new ASTpommeTilde(JJTPOMMETILDE);
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
        jj_la1[33] = jj_gen;
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
ASTpommeNew *jjtn001 = new ASTpommeNew(JJTPOMMENEW);
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
    case TILDE:
    case IDENTIFIEROPERATOR:
    case IDENTIFIER:{
      listacces();
      break;
      }
    case TRUE:{
ASTpommeTrue *jjtn002 = new ASTpommeTrue(JJTPOMMETRUE);
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
ASTpommeFalse *jjtn003 = new ASTpommeFalse(JJTPOMMEFALSE);
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
ASTpommeNull *jjtn004 = new ASTpommeNull(JJTPOMMENULL);
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
      jj_la1[34] = jj_gen;
      jj_consume_token(-1);
      errorHandler->handleParseError(token, getToken(1), __FUNCTION__, this), hasError = true;
    }
}


void PommeLexer::listacces() {
    access();
ASTlistacces *jjtn001 = new ASTlistacces(JJTLISTACCES);
                   bool jjtc001 = true;
                   jjtree.openNodeScope(jjtn001);
                   jjtreeOpenNodeScope(jjtn001);
    try {
      listaccesP();
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


void PommeLexer::listaccesP() {
    switch ((jj_ntk==-1)?jj_ntk_f():jj_ntk) {
    case POINT:{
      jj_consume_token(POINT);
      access();
ASTlistacces *jjtn001 = new ASTlistacces(JJTLISTACCES);
                           bool jjtc001 = true;
                           jjtree.openNodeScope(jjtn001);
                           jjtreeOpenNodeScope(jjtn001);
      try {
        listaccesP();
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
      jj_la1[35] = jj_gen;
ASTacnil *jjtn002 = new ASTacnil(JJTACNIL);
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


void PommeLexer::access() {
    if (jj_2_5(2)) {
      identmeth();
      jj_consume_token(PARENTL);
      listexp();
ASTaccessMethode *jjtn001 = new ASTaccessMethode(JJTACCESSMETHODE);
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
        jj_la1[36] = jj_gen;
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
      jj_la1[37] = jj_gen;
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
    for (int i = 0; i < 38; i++) jj_la1[i] = -1;
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
        for (int i = 0; i < 5; i++) {
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
    for (int i = 0; i < 5; i++) {
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
