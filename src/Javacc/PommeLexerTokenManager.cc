/* PommeLexerTokenManager.cc */
#include "PommeLexerTokenManager.h"
#include "TokenMgrError.h"
#include "SimpleNode.h"
namespace Pomme {
static const unsigned long long jjbitVec0[] = {
   0x0ULL, 0x0ULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL
};
static const int jjnextStates[] = {
   37, 38, 40, 46, 47, 33, 36, 41, 2, 3, 4, 5, 6, 7, 8, 12, 
   13, 15, 17, 19, 31, 32, 42, 43, 
};
static JJChar jjstrLiteralChars_0[] = {0};
static JJChar jjstrLiteralChars_1[] = {0};
static JJChar jjstrLiteralChars_2[] = {0};
static JJChar jjstrLiteralChars_3[] = {0};
static JJChar jjstrLiteralChars_4[] = {0};
static JJChar jjstrLiteralChars_5[] = {0};
static JJChar jjstrLiteralChars_6[] = {0};

static JJChar jjstrLiteralChars_7[] = {0x3d, 0};
static JJChar jjstrLiteralChars_8[] = {0x2b, 0};

static JJChar jjstrLiteralChars_9[] = {0x2b, 0x3d, 0};
static JJChar jjstrLiteralChars_10[] = {0x2d, 0};

static JJChar jjstrLiteralChars_11[] = {0x2d, 0x3d, 0};
static JJChar jjstrLiteralChars_12[] = {0x2a, 0};

static JJChar jjstrLiteralChars_13[] = {0x2a, 0x3d, 0};
static JJChar jjstrLiteralChars_14[] = {0x2f, 0};

static JJChar jjstrLiteralChars_15[] = {0x2f, 0x3d, 0};
static JJChar jjstrLiteralChars_16[] = {0x7c, 0x3d, 0};

static JJChar jjstrLiteralChars_17[] = {0x26, 0x3d, 0};
static JJChar jjstrLiteralChars_18[] = {0x3c, 0x3c, 0};

static JJChar jjstrLiteralChars_19[] = {0x3c, 0x3c, 0x3d, 0};
static JJChar jjstrLiteralChars_20[] = {0x3e, 0x3e, 0};

static JJChar jjstrLiteralChars_21[] = {0x3e, 0x3e, 0x3d, 0};
static JJChar jjstrLiteralChars_22[] = {0x2b, 0x2b, 0};

static JJChar jjstrLiteralChars_23[] = {0x2d, 0x2d, 0};
static JJChar jjstrLiteralChars_24[] = {0x25, 0};

static JJChar jjstrLiteralChars_25[] = {0x63, 0x6c, 0x61, 0x73, 0x73, 0};
static JJChar jjstrLiteralChars_26[] = {0x65, 0x6e, 0x75, 0x6d, 0};

static JJChar jjstrLiteralChars_27[] = {0x74, 0x79, 0x70, 0x65, 0x64, 0x65, 0x66, 0};
static JJChar jjstrLiteralChars_28[] = {0x69, 0x66, 0};

static JJChar jjstrLiteralChars_29[] = {0x65, 0x6c, 0x73, 0x65, 0};
static JJChar jjstrLiteralChars_30[] = {0x77, 0x68, 0x69, 0x6c, 0x65, 0};

static JJChar jjstrLiteralChars_31[] = {0x70, 0x72, 0x69, 0x6e, 0x74, 0};
static JJChar jjstrLiteralChars_32[] = {0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0};

static JJChar jjstrLiteralChars_33[] = {0x62, 0x72, 0x65, 0x61, 0x6b, 0};
static JJChar jjstrLiteralChars_34[] = {0x73, 0x77, 0x69, 0x74, 0x63, 0x68, 0};

static JJChar jjstrLiteralChars_35[] = {0x63, 0x61, 0x73, 0x65, 0};

static JJChar jjstrLiteralChars_36[] = {0x64, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0};
static JJChar jjstrLiteralChars_37[] = {0x28, 0};

static JJChar jjstrLiteralChars_38[] = {0x29, 0};
static JJChar jjstrLiteralChars_39[] = {0x7b, 0};

static JJChar jjstrLiteralChars_40[] = {0x7d, 0};
static JJChar jjstrLiteralChars_41[] = {0x5b, 0};

static JJChar jjstrLiteralChars_42[] = {0x5d, 0};
static JJChar jjstrLiteralChars_43[] = {0x3a, 0};

static JJChar jjstrLiteralChars_44[] = {0x3b, 0};
static JJChar jjstrLiteralChars_45[] = {0x2c, 0};

static JJChar jjstrLiteralChars_46[] = {0x2e, 0};
static JJChar jjstrLiteralChars_47[] = {0x21, 0};

static JJChar jjstrLiteralChars_48[] = {0x7e, 0};
static JJChar jjstrLiteralChars_49[] = {0x3d, 0x3d, 0};

static JJChar jjstrLiteralChars_50[] = {0x21, 0x3d, 0};
static JJChar jjstrLiteralChars_51[] = {0x3e, 0};

static JJChar jjstrLiteralChars_52[] = {0x3e, 0x3d, 0};
static JJChar jjstrLiteralChars_53[] = {0x3c, 0};

static JJChar jjstrLiteralChars_54[] = {0x3c, 0x3d, 0};
static JJChar jjstrLiteralChars_55[] = {0x7c, 0x7c, 0};

static JJChar jjstrLiteralChars_56[] = {0x26, 0x26, 0};
static JJChar jjstrLiteralChars_57[] = {0x76, 0x6f, 0x69, 0x64, 0};

static JJChar jjstrLiteralChars_58[] = {0x63, 0x6f, 0x6e, 0x73, 0x74, 0};
static JJChar jjstrLiteralChars_59[] = {0x6e, 0x61, 0x74, 0x69, 0x76, 0x65, 0};

static JJChar jjstrLiteralChars_60[] = {0x65, 0x78, 0x74, 0x65, 0x6e, 0x64, 0x73, 0};
static JJChar jjstrLiteralChars_61[] = {0x6d, 0x6f, 0x64, 0x64, 0x65, 0x64, 0};

static JJChar jjstrLiteralChars_62[] = {0x73, 0x74, 0x61, 0x74, 0x69, 0x63, 0};
static JJChar jjstrLiteralChars_63[] = {0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0};

static JJChar jjstrLiteralChars_64[] = {0x70, 0x72, 0x69, 0x76, 0x61, 0x74, 0x65, 0};

static JJChar jjstrLiteralChars_65[] = {0x70, 0x72, 0x6f, 0x74, 0x65, 0x63, 0x74, 0x65, 0x64, 0};

static JJChar jjstrLiteralChars_66[] = {0x6f, 0x76, 0x65, 0x72, 0x72, 0x69, 0x64, 0x65, 0};
static JJChar jjstrLiteralChars_67[] = {0x74, 0x72, 0x75, 0x65, 0};

static JJChar jjstrLiteralChars_68[] = {0x66, 0x61, 0x6c, 0x73, 0x65, 0};
static JJChar jjstrLiteralChars_69[] = {0x6e, 0x75, 0x6c, 0x6c, 0};

static JJChar jjstrLiteralChars_70[] = {0x6e, 0x65, 0x77, 0};
static JJChar jjstrLiteralChars_71[] = {0x64, 0x65, 0x6c, 0x65, 0x74, 0x65, 0};

static JJChar jjstrLiteralChars_72[] = {0};
static JJChar jjstrLiteralChars_73[] = {0};
static JJChar jjstrLiteralChars_74[] = {0};
static JJChar jjstrLiteralChars_75[] = {0};
static JJChar jjstrLiteralChars_76[] = {0};
static const JJString jjstrLiteralImages[] = {
jjstrLiteralChars_0, 
jjstrLiteralChars_1, 
jjstrLiteralChars_2, 
jjstrLiteralChars_3, 
jjstrLiteralChars_4, 
jjstrLiteralChars_5, 
jjstrLiteralChars_6, 
jjstrLiteralChars_7, 
jjstrLiteralChars_8, 
jjstrLiteralChars_9, 
jjstrLiteralChars_10, 
jjstrLiteralChars_11, 
jjstrLiteralChars_12, 
jjstrLiteralChars_13, 
jjstrLiteralChars_14, 
jjstrLiteralChars_15, 
jjstrLiteralChars_16, 
jjstrLiteralChars_17, 
jjstrLiteralChars_18, 
jjstrLiteralChars_19, 
jjstrLiteralChars_20, 
jjstrLiteralChars_21, 
jjstrLiteralChars_22, 
jjstrLiteralChars_23, 
jjstrLiteralChars_24, 
jjstrLiteralChars_25, 
jjstrLiteralChars_26, 
jjstrLiteralChars_27, 
jjstrLiteralChars_28, 
jjstrLiteralChars_29, 
jjstrLiteralChars_30, 
jjstrLiteralChars_31, 
jjstrLiteralChars_32, 
jjstrLiteralChars_33, 
jjstrLiteralChars_34, 
jjstrLiteralChars_35, 
jjstrLiteralChars_36, 
jjstrLiteralChars_37, 
jjstrLiteralChars_38, 
jjstrLiteralChars_39, 
jjstrLiteralChars_40, 
jjstrLiteralChars_41, 
jjstrLiteralChars_42, 
jjstrLiteralChars_43, 
jjstrLiteralChars_44, 
jjstrLiteralChars_45, 
jjstrLiteralChars_46, 
jjstrLiteralChars_47, 
jjstrLiteralChars_48, 
jjstrLiteralChars_49, 
jjstrLiteralChars_50, 
jjstrLiteralChars_51, 
jjstrLiteralChars_52, 
jjstrLiteralChars_53, 
jjstrLiteralChars_54, 
jjstrLiteralChars_55, 
jjstrLiteralChars_56, 
jjstrLiteralChars_57, 
jjstrLiteralChars_58, 
jjstrLiteralChars_59, 
jjstrLiteralChars_60, 
jjstrLiteralChars_61, 
jjstrLiteralChars_62, 
jjstrLiteralChars_63, 
jjstrLiteralChars_64, 
jjstrLiteralChars_65, 
jjstrLiteralChars_66, 
jjstrLiteralChars_67, 
jjstrLiteralChars_68, 
jjstrLiteralChars_69, 
jjstrLiteralChars_70, 
jjstrLiteralChars_71, 
jjstrLiteralChars_72, 
jjstrLiteralChars_73, 
jjstrLiteralChars_74, 
jjstrLiteralChars_75, 
jjstrLiteralChars_76, 
};

/** Lexer state names. */
static const JJChar lexStateNames_arr_0[] = 
{0x44, 0x45, 0x46, 0x41, 0x55, 0x4c, 0x54, 0};
static const JJString lexStateNames[] = {
lexStateNames_arr_0, 
};
static const unsigned long long jjtoToken[] = {
   0xffffffffffffff81ULL, 0x1fffULL, 
};
static const unsigned long long jjtoSkip[] = {
   0x7eULL, 0x0ULL, 
};

  void  PommeLexerTokenManager::setDebugStream(FILE *ds){ debugStream = ds; }

 int PommeLexerTokenManager::jjStopStringLiteralDfa_0(int pos, unsigned long long active0, unsigned long long active1){
   switch (pos)
   {
      case 0:
         if ((active0 & 0x400000000000ULL) != 0L)
            return 34;
         if ((active0 & 0xfe00001ffe000000ULL) != 0L || (active1 & 0xfbULL) != 0L)
         {
            jjmatchedKind = 74;
            return 29;
         }
         if ((active1 & 0x4ULL) != 0L)
         {
            jjmatchedKind = 74;
            return 26;
         }
         if ((active0 & 0xc000ULL) != 0L)
            return 36;
         return -1;
      case 1:
         if ((active0 & 0xfe00001fee000000ULL) != 0L || (active1 & 0xffULL) != 0L)
         {
            if (jjmatchedPos != 1)
            {
               jjmatchedKind = 74;
               jjmatchedPos = 1;
            }
            return 29;
         }
         if ((active0 & 0x10000000ULL) != 0L)
            return 29;
         return -1;
      case 2:
         if ((active0 & 0xfe00001fee000000ULL) != 0L || (active1 & 0xbfULL) != 0L)
         {
            jjmatchedKind = 74;
            jjmatchedPos = 2;
            return 29;
         }
         if ((active1 & 0x40ULL) != 0L)
            return 29;
         return -1;
      case 3:
         if ((active0 & 0xfc000017ca000000ULL) != 0L || (active1 & 0x97ULL) != 0L)
         {
            jjmatchedKind = 74;
            jjmatchedPos = 3;
            return 29;
         }
         if ((active0 & 0x200000824000000ULL) != 0L || (active1 & 0x28ULL) != 0L)
            return 29;
         return -1;
      case 4:
         if ((active0 & 0x4000002c2000000ULL) != 0L || (active1 & 0x10ULL) != 0L)
            return 29;
         if ((active0 & 0xf800001508000000ULL) != 0L || (active1 & 0x87ULL) != 0L)
         {
            jjmatchedKind = 74;
            jjmatchedPos = 4;
            return 29;
         }
         return -1;
      case 5:
         if ((active0 & 0x1000001008000000ULL) != 0L || (active1 & 0x7ULL) != 0L)
         {
            jjmatchedKind = 74;
            jjmatchedPos = 5;
            return 29;
         }
         if ((active0 & 0xe800000500000000ULL) != 0L || (active1 & 0x80ULL) != 0L)
            return 29;
         return -1;
      case 6:
         if ((active1 & 0x6ULL) != 0L)
         {
            jjmatchedKind = 74;
            jjmatchedPos = 6;
            return 29;
         }
         if ((active0 & 0x1000001008000000ULL) != 0L || (active1 & 0x1ULL) != 0L)
            return 29;
         return -1;
      case 7:
         if ((active1 & 0x4ULL) != 0L)
            return 29;
         if ((active1 & 0x2ULL) != 0L)
         {
            jjmatchedKind = 74;
            jjmatchedPos = 7;
            return 29;
         }
         return -1;
      default :
         return -1;
   }
}

int  PommeLexerTokenManager::jjStartNfa_0(int pos, unsigned long long active0, unsigned long long active1){
   return jjMoveNfa_0(jjStopStringLiteralDfa_0(pos, active0, active1), pos + 1);
}

 int  PommeLexerTokenManager::jjStopAtPos(int pos, int kind){
   jjmatchedKind = kind;
   jjmatchedPos = pos;
   return pos + 1;
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa0_0(){
   switch(curChar)
   {
      case 33:
         jjmatchedKind = 47;
         return jjMoveStringLiteralDfa1_0(0x4000000000000ULL, 0x0ULL);
      case 37:
         return jjStopAtPos(0, 24);
      case 38:
         return jjMoveStringLiteralDfa1_0(0x100000000020000ULL, 0x0ULL);
      case 40:
         return jjStopAtPos(0, 37);
      case 41:
         return jjStopAtPos(0, 38);
      case 42:
         jjmatchedKind = 12;
         return jjMoveStringLiteralDfa1_0(0x2000ULL, 0x0ULL);
      case 43:
         jjmatchedKind = 8;
         return jjMoveStringLiteralDfa1_0(0x400200ULL, 0x0ULL);
      case 44:
         return jjStopAtPos(0, 45);
      case 45:
         jjmatchedKind = 10;
         return jjMoveStringLiteralDfa1_0(0x800800ULL, 0x0ULL);
      case 46:
         return jjStartNfaWithStates_0(0, 46, 34);
      case 47:
         jjmatchedKind = 14;
         return jjMoveStringLiteralDfa1_0(0x8000ULL, 0x0ULL);
      case 58:
         return jjStopAtPos(0, 43);
      case 59:
         return jjStopAtPos(0, 44);
      case 60:
         jjmatchedKind = 53;
         return jjMoveStringLiteralDfa1_0(0x400000000c0000ULL, 0x0ULL);
      case 61:
         jjmatchedKind = 7;
         return jjMoveStringLiteralDfa1_0(0x2000000000000ULL, 0x0ULL);
      case 62:
         jjmatchedKind = 51;
         return jjMoveStringLiteralDfa1_0(0x10000000300000ULL, 0x0ULL);
      case 91:
         return jjStopAtPos(0, 41);
      case 93:
         return jjStopAtPos(0, 42);
      case 98:
         return jjMoveStringLiteralDfa1_0(0x200000000ULL, 0x0ULL);
      case 99:
         return jjMoveStringLiteralDfa1_0(0x400000802000000ULL, 0x0ULL);
      case 100:
         return jjMoveStringLiteralDfa1_0(0x1000000000ULL, 0x80ULL);
      case 101:
         return jjMoveStringLiteralDfa1_0(0x1000000024000000ULL, 0x0ULL);
      case 102:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x10ULL);
      case 105:
         return jjMoveStringLiteralDfa1_0(0x10000000ULL, 0x0ULL);
      case 109:
         return jjMoveStringLiteralDfa1_0(0x2000000000000000ULL, 0x0ULL);
      case 110:
         return jjMoveStringLiteralDfa1_0(0x800000000000000ULL, 0x60ULL);
      case 111:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x4ULL);
      case 112:
         return jjMoveStringLiteralDfa1_0(0x8000000080000000ULL, 0x3ULL);
      case 114:
         return jjMoveStringLiteralDfa1_0(0x100000000ULL, 0x0ULL);
      case 115:
         return jjMoveStringLiteralDfa1_0(0x4000000400000000ULL, 0x0ULL);
      case 116:
         return jjMoveStringLiteralDfa1_0(0x8000000ULL, 0x8ULL);
      case 118:
         return jjMoveStringLiteralDfa1_0(0x200000000000000ULL, 0x0ULL);
      case 119:
         return jjMoveStringLiteralDfa1_0(0x40000000ULL, 0x0ULL);
      case 123:
         return jjStopAtPos(0, 39);
      case 124:
         return jjMoveStringLiteralDfa1_0(0x80000000010000ULL, 0x0ULL);
      case 125:
         return jjStopAtPos(0, 40);
      case 126:
         return jjStopAtPos(0, 48);
      default :
         return jjMoveNfa_0(27, 0);
   }
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa1_0(unsigned long long active0, unsigned long long active1){
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(0, active0, active1);
      return 1;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 38:
         if ((active0 & 0x100000000000000ULL) != 0L)
            return jjStopAtPos(1, 56);
         break;
      case 43:
         if ((active0 & 0x400000ULL) != 0L)
            return jjStopAtPos(1, 22);
         break;
      case 45:
         if ((active0 & 0x800000ULL) != 0L)
            return jjStopAtPos(1, 23);
         break;
      case 60:
         if ((active0 & 0x40000ULL) != 0L)
         {
            jjmatchedKind = 18;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0x80000ULL, active1, 0L);
      case 61:
         if ((active0 & 0x200ULL) != 0L)
            return jjStopAtPos(1, 9);
         else if ((active0 & 0x800ULL) != 0L)
            return jjStopAtPos(1, 11);
         else if ((active0 & 0x2000ULL) != 0L)
            return jjStopAtPos(1, 13);
         else if ((active0 & 0x8000ULL) != 0L)
            return jjStopAtPos(1, 15);
         else if ((active0 & 0x10000ULL) != 0L)
            return jjStopAtPos(1, 16);
         else if ((active0 & 0x20000ULL) != 0L)
            return jjStopAtPos(1, 17);
         else if ((active0 & 0x2000000000000ULL) != 0L)
            return jjStopAtPos(1, 49);
         else if ((active0 & 0x4000000000000ULL) != 0L)
            return jjStopAtPos(1, 50);
         else if ((active0 & 0x10000000000000ULL) != 0L)
            return jjStopAtPos(1, 52);
         else if ((active0 & 0x40000000000000ULL) != 0L)
            return jjStopAtPos(1, 54);
         break;
      case 62:
         if ((active0 & 0x100000ULL) != 0L)
         {
            jjmatchedKind = 20;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0x200000ULL, active1, 0L);
      case 97:
         return jjMoveStringLiteralDfa2_0(active0, 0x800000800000000ULL, active1, 0x10ULL);
      case 101:
         return jjMoveStringLiteralDfa2_0(active0, 0x1100000000ULL, active1, 0xc0ULL);
      case 102:
         if ((active0 & 0x10000000ULL) != 0L)
            return jjStartNfaWithStates_0(1, 28, 29);
         break;
      case 104:
         return jjMoveStringLiteralDfa2_0(active0, 0x40000000ULL, active1, 0L);
      case 108:
         return jjMoveStringLiteralDfa2_0(active0, 0x22000000ULL, active1, 0L);
      case 110:
         return jjMoveStringLiteralDfa2_0(active0, 0x4000000ULL, active1, 0L);
      case 111:
         return jjMoveStringLiteralDfa2_0(active0, 0x2600000000000000ULL, active1, 0L);
      case 114:
         return jjMoveStringLiteralDfa2_0(active0, 0x280000000ULL, active1, 0xbULL);
      case 116:
         return jjMoveStringLiteralDfa2_0(active0, 0x4000000000000000ULL, active1, 0L);
      case 117:
         return jjMoveStringLiteralDfa2_0(active0, 0x8000000000000000ULL, active1, 0x20ULL);
      case 118:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x4ULL);
      case 119:
         return jjMoveStringLiteralDfa2_0(active0, 0x400000000ULL, active1, 0L);
      case 120:
         return jjMoveStringLiteralDfa2_0(active0, 0x1000000000000000ULL, active1, 0L);
      case 121:
         return jjMoveStringLiteralDfa2_0(active0, 0x8000000ULL, active1, 0L);
      case 124:
         if ((active0 & 0x80000000000000ULL) != 0L)
            return jjStopAtPos(1, 55);
         break;
      default :
         break;
   }
   return jjStartNfa_0(0, active0, active1);
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa2_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1){
   if (((active0 &= old0) | (active1 &= old1)) == 0L)
      return jjStartNfa_0(0, old0, old1);
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(1, active0, active1);
      return 2;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 61:
         if ((active0 & 0x80000ULL) != 0L)
            return jjStopAtPos(2, 19);
         else if ((active0 & 0x200000ULL) != 0L)
            return jjStopAtPos(2, 21);
         break;
      case 97:
         return jjMoveStringLiteralDfa3_0(active0, 0x4000000002000000ULL, active1, 0L);
      case 98:
         return jjMoveStringLiteralDfa3_0(active0, 0x8000000000000000ULL, active1, 0L);
      case 100:
         return jjMoveStringLiteralDfa3_0(active0, 0x2000000000000000ULL, active1, 0L);
      case 101:
         return jjMoveStringLiteralDfa3_0(active0, 0x200000000ULL, active1, 0x4ULL);
      case 102:
         return jjMoveStringLiteralDfa3_0(active0, 0x1000000000ULL, active1, 0L);
      case 105:
         return jjMoveStringLiteralDfa3_0(active0, 0x2000004c0000000ULL, active1, 0x1ULL);
      case 108:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0xb0ULL);
      case 110:
         return jjMoveStringLiteralDfa3_0(active0, 0x400000000000000ULL, active1, 0L);
      case 111:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x2ULL);
      case 112:
         return jjMoveStringLiteralDfa3_0(active0, 0x8000000ULL, active1, 0L);
      case 115:
         return jjMoveStringLiteralDfa3_0(active0, 0x820000000ULL, active1, 0L);
      case 116:
         return jjMoveStringLiteralDfa3_0(active0, 0x1800000100000000ULL, active1, 0L);
      case 117:
         return jjMoveStringLiteralDfa3_0(active0, 0x4000000ULL, active1, 0x8ULL);
      case 119:
         if ((active1 & 0x40ULL) != 0L)
            return jjStartNfaWithStates_0(2, 70, 29);
         break;
      default :
         break;
   }
   return jjStartNfa_0(1, active0, active1);
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa3_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1){
   if (((active0 &= old0) | (active1 &= old1)) == 0L)
      return jjStartNfa_0(1, old0, old1);
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(2, active0, active1);
      return 3;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 97:
         return jjMoveStringLiteralDfa4_0(active0, 0x1200000000ULL, active1, 0L);
      case 100:
         if ((active0 & 0x200000000000000ULL) != 0L)
            return jjStartNfaWithStates_0(3, 57, 29);
         return jjMoveStringLiteralDfa4_0(active0, 0x2000000000000000ULL, active1, 0L);
      case 101:
         if ((active0 & 0x20000000ULL) != 0L)
            return jjStartNfaWithStates_0(3, 29, 29);
         else if ((active0 & 0x800000000ULL) != 0L)
            return jjStartNfaWithStates_0(3, 35, 29);
         else if ((active1 & 0x8ULL) != 0L)
            return jjStartNfaWithStates_0(3, 67, 29);
         return jjMoveStringLiteralDfa4_0(active0, 0x1000000008000000ULL, active1, 0x80ULL);
      case 105:
         return jjMoveStringLiteralDfa4_0(active0, 0x800000000000000ULL, active1, 0L);
      case 108:
         if ((active1 & 0x20ULL) != 0L)
            return jjStartNfaWithStates_0(3, 69, 29);
         return jjMoveStringLiteralDfa4_0(active0, 0x8000000040000000ULL, active1, 0L);
      case 109:
         if ((active0 & 0x4000000ULL) != 0L)
            return jjStartNfaWithStates_0(3, 26, 29);
         break;
      case 110:
         return jjMoveStringLiteralDfa4_0(active0, 0x80000000ULL, active1, 0L);
      case 114:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x4ULL);
      case 115:
         return jjMoveStringLiteralDfa4_0(active0, 0x400000002000000ULL, active1, 0x10ULL);
      case 116:
         return jjMoveStringLiteralDfa4_0(active0, 0x4000000400000000ULL, active1, 0x2ULL);
      case 117:
         return jjMoveStringLiteralDfa4_0(active0, 0x100000000ULL, active1, 0L);
      case 118:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x1ULL);
      default :
         break;
   }
   return jjStartNfa_0(2, active0, active1);
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa4_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1){
   if (((active0 &= old0) | (active1 &= old1)) == 0L)
      return jjStartNfa_0(2, old0, old1);
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(3, active0, active1);
      return 4;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 97:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x1ULL);
      case 99:
         return jjMoveStringLiteralDfa5_0(active0, 0x400000000ULL, active1, 0L);
      case 100:
         return jjMoveStringLiteralDfa5_0(active0, 0x8000000ULL, active1, 0L);
      case 101:
         if ((active0 & 0x40000000ULL) != 0L)
            return jjStartNfaWithStates_0(4, 30, 29);
         else if ((active1 & 0x10ULL) != 0L)
            return jjStartNfaWithStates_0(4, 68, 29);
         return jjMoveStringLiteralDfa5_0(active0, 0x2000000000000000ULL, active1, 0x2ULL);
      case 105:
         return jjMoveStringLiteralDfa5_0(active0, 0xc000000000000000ULL, active1, 0L);
      case 107:
         if ((active0 & 0x200000000ULL) != 0L)
            return jjStartNfaWithStates_0(4, 33, 29);
         break;
      case 110:
         return jjMoveStringLiteralDfa5_0(active0, 0x1000000000000000ULL, active1, 0L);
      case 114:
         return jjMoveStringLiteralDfa5_0(active0, 0x100000000ULL, active1, 0x4ULL);
      case 115:
         if ((active0 & 0x2000000ULL) != 0L)
            return jjStartNfaWithStates_0(4, 25, 29);
         break;
      case 116:
         if ((active0 & 0x80000000ULL) != 0L)
            return jjStartNfaWithStates_0(4, 31, 29);
         else if ((active0 & 0x400000000000000ULL) != 0L)
            return jjStartNfaWithStates_0(4, 58, 29);
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x80ULL);
      case 117:
         return jjMoveStringLiteralDfa5_0(active0, 0x1000000000ULL, active1, 0L);
      case 118:
         return jjMoveStringLiteralDfa5_0(active0, 0x800000000000000ULL, active1, 0L);
      default :
         break;
   }
   return jjStartNfa_0(3, active0, active1);
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa5_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1){
   if (((active0 &= old0) | (active1 &= old1)) == 0L)
      return jjStartNfa_0(3, old0, old1);
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(4, active0, active1);
      return 5;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 99:
         if ((active0 & 0x4000000000000000ULL) != 0L)
            return jjStartNfaWithStates_0(5, 62, 29);
         else if ((active0 & 0x8000000000000000ULL) != 0L)
            return jjStartNfaWithStates_0(5, 63, 29);
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x2ULL);
      case 100:
         if ((active0 & 0x2000000000000000ULL) != 0L)
            return jjStartNfaWithStates_0(5, 61, 29);
         return jjMoveStringLiteralDfa6_0(active0, 0x1000000000000000ULL, active1, 0L);
      case 101:
         if ((active0 & 0x800000000000000ULL) != 0L)
            return jjStartNfaWithStates_0(5, 59, 29);
         else if ((active1 & 0x80ULL) != 0L)
            return jjStartNfaWithStates_0(5, 71, 29);
         return jjMoveStringLiteralDfa6_0(active0, 0x8000000ULL, active1, 0L);
      case 104:
         if ((active0 & 0x400000000ULL) != 0L)
            return jjStartNfaWithStates_0(5, 34, 29);
         break;
      case 105:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x4ULL);
      case 108:
         return jjMoveStringLiteralDfa6_0(active0, 0x1000000000ULL, active1, 0L);
      case 110:
         if ((active0 & 0x100000000ULL) != 0L)
            return jjStartNfaWithStates_0(5, 32, 29);
         break;
      case 116:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x1ULL);
      default :
         break;
   }
   return jjStartNfa_0(4, active0, active1);
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa6_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1){
   if (((active0 &= old0) | (active1 &= old1)) == 0L)
      return jjStartNfa_0(4, old0, old1);
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(5, active0, active1);
      return 6;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 100:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0x4ULL);
      case 101:
         if ((active1 & 0x1ULL) != 0L)
            return jjStartNfaWithStates_0(6, 64, 29);
         break;
      case 102:
         if ((active0 & 0x8000000ULL) != 0L)
            return jjStartNfaWithStates_0(6, 27, 29);
         break;
      case 115:
         if ((active0 & 0x1000000000000000ULL) != 0L)
            return jjStartNfaWithStates_0(6, 60, 29);
         break;
      case 116:
         if ((active0 & 0x1000000000ULL) != 0L)
            return jjStartNfaWithStates_0(6, 36, 29);
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0x2ULL);
      default :
         break;
   }
   return jjStartNfa_0(5, active0, active1);
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa7_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1){
   if (((active0 &= old0) | (active1 &= old1)) == 0L)
      return jjStartNfa_0(5, old0, old1);
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(6, 0L, active1);
      return 7;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 101:
         if ((active1 & 0x4ULL) != 0L)
            return jjStartNfaWithStates_0(7, 66, 29);
         return jjMoveStringLiteralDfa8_0(active1, 0x2ULL);
      default :
         break;
   }
   return jjStartNfa_0(6, 0L, active1);
}

 int  PommeLexerTokenManager::jjMoveStringLiteralDfa8_0(unsigned long long old1, unsigned long long active1){
   if (((active1 &= old1)) == 0L)
      return jjStartNfa_0(6, 0L, old1);
   if (input_stream->endOfInput()) {
      jjStopStringLiteralDfa_0(7, 0L, active1);
      return 8;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 100:
         if ((active1 & 0x2ULL) != 0L)
            return jjStartNfaWithStates_0(8, 65, 29);
         break;
      default :
         break;
   }
   return jjStartNfa_0(7, 0L, active1);
}

int PommeLexerTokenManager::jjStartNfaWithStates_0(int pos, int kind, int state){
   jjmatchedKind = kind;
   jjmatchedPos = pos;
   if (input_stream->endOfInput()) { return pos + 1; }
   curChar = input_stream->readChar();
   return jjMoveNfa_0(state, pos + 1);
}

int PommeLexerTokenManager::jjMoveNfa_0(int startState, int curPos){
   int startsAt = 0;
   jjnewStateCnt = 48;
   int i = 1;
   jjstateSet[0] = startState;
   int kind = 0x7fffffff;
   for (;;)
   {
      if (++jjround == 0x7fffffff)
         ReInitRounds();
      if (curChar < 64)
      {
         unsigned long long l = 1ULL << curChar;
         (void)l;
         do
         {
            switch(jjstateSet[--i])
            {
               case 26:
               case 29:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 74)
                     kind = 74;
                  { jjCheckNAdd(29); }
                  break;
               case 36:
                  if (curChar == 42)
                     { jjCheckNAddTwoStates(42, 43); }
                  else if (curChar == 47)
                     { jjCheckNAddStates(0, 2); }
                  break;
               case 27:
                  if ((0x3ff000000000000ULL & l) != 0L)
                  {
                     if (kind > 72)
                        kind = 72;
                     { jjCheckNAddStates(3, 5); }
                  }
                  else if (curChar == 47)
                     { jjAddStates(6, 7); }
                  else if (curChar == 46)
                     { jjCheckNAdd(34); }
                  else if (curChar == 34)
                     { jjCheckNAddTwoStates(31, 32); }
                  break;
               case 1:
                  if (curChar == 61 && kind > 73)
                     kind = 73;
                  break;
               case 2:
                  if (curChar == 42)
                     { jjCheckNAdd(1); }
                  break;
               case 3:
                  if (curChar == 47)
                     { jjCheckNAdd(1); }
                  break;
               case 5:
                  if (curChar == 38)
                     { jjCheckNAdd(1); }
                  break;
               case 6:
                  if ((0x5000ac2000000000ULL & l) != 0L && kind > 73)
                     kind = 73;
                  break;
               case 7:
                  if (curChar == 61)
                     { jjCheckNAdd(1); }
                  break;
               case 8:
                  if (curChar == 33)
                     { jjCheckNAdd(1); }
                  break;
               case 13:
                  if (curChar == 43)
                     { jjCheckNAddTwoStates(1, 14); }
                  break;
               case 14:
                  if (curChar == 43 && kind > 73)
                     kind = 73;
                  break;
               case 15:
                  if (curChar == 45)
                     { jjCheckNAddTwoStates(1, 16); }
                  break;
               case 16:
                  if (curChar == 45 && kind > 73)
                     kind = 73;
                  break;
               case 17:
                  if (curChar == 62)
                     { jjCheckNAddTwoStates(18, 1); }
                  break;
               case 18:
                  if (curChar == 62)
                     { jjCheckNAdd(1); }
                  break;
               case 19:
                  if (curChar == 60)
                     { jjCheckNAddTwoStates(20, 1); }
                  break;
               case 20:
                  if (curChar == 60)
                     { jjCheckNAdd(1); }
                  break;
               case 30:
                  if (curChar == 34)
                     { jjCheckNAddTwoStates(31, 32); }
                  break;
               case 31:
                  if ((0xffffffffffffdbffULL & l) != 0L)
                     { jjCheckNAddTwoStates(31, 32); }
                  break;
               case 32:
                  if (curChar == 34 && kind > 75)
                     kind = 75;
                  break;
               case 33:
                  if (curChar == 46)
                     { jjCheckNAdd(34); }
                  break;
               case 34:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 76)
                     kind = 76;
                  { jjCheckNAdd(34); }
                  break;
               case 35:
                  if (curChar == 47)
                     { jjAddStates(6, 7); }
                  break;
               case 37:
                  if ((0xffffffffffffdbffULL & l) != 0L)
                     { jjCheckNAddStates(0, 2); }
                  break;
               case 38:
                  if ((0x2400ULL & l) != 0L && kind > 5)
                     kind = 5;
                  break;
               case 39:
                  if (curChar == 10 && kind > 5)
                     kind = 5;
                  break;
               case 40:
                  if (curChar == 13)
                     jjstateSet[jjnewStateCnt++] = 39;
                  break;
               case 41:
                  if (curChar == 42)
                     { jjCheckNAddTwoStates(42, 43); }
                  break;
               case 42:
                  if ((0xffff7fffffffffffULL & l) != 0L)
                     { jjCheckNAddTwoStates(42, 43); }
                  break;
               case 43:
                  if (curChar == 42)
                     jjstateSet[jjnewStateCnt++] = 44;
                  break;
               case 44:
                  if (curChar == 47 && kind > 6)
                     kind = 6;
                  break;
               case 45:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 72)
                     kind = 72;
                  { jjCheckNAddStates(3, 5); }
                  break;
               case 46:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 72)
                     kind = 72;
                  { jjCheckNAdd(46); }
                  break;
               case 47:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(47, 33); }
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else if (curChar < 128)
      {
         unsigned long long l = 1ULL << (curChar & 077);
         (void)l;
         do
         {
            switch(jjstateSet[--i])
            {
               case 26:
                  if ((0x7fffffe87fffffeULL & l) != 0L)
                  {
                     if (kind > 74)
                        kind = 74;
                     { jjCheckNAdd(29); }
                  }
                  if (curChar == 112)
                     jjstateSet[jjnewStateCnt++] = 25;
                  break;
               case 27:
                  if ((0x7fffffe07fffffeULL & l) != 0L)
                  {
                     if (kind > 74)
                        kind = 74;
                     { jjCheckNAdd(29); }
                  }
                  if (curChar == 111)
                     jjstateSet[jjnewStateCnt++] = 26;
                  break;
               case 0:
                  if (curChar == 114)
                     { jjAddStates(8, 19); }
                  break;
               case 4:
                  if (curChar == 124)
                     jjstateSet[jjnewStateCnt++] = 1;
                  break;
               case 9:
                  if (curChar == 108 && kind > 73)
                     kind = 73;
                  break;
               case 10:
                  if (curChar == 111)
                     jjstateSet[jjnewStateCnt++] = 9;
                  break;
               case 11:
                  if (curChar == 111)
                     jjstateSet[jjnewStateCnt++] = 10;
                  break;
               case 12:
                  if (curChar == 98)
                     jjstateSet[jjnewStateCnt++] = 11;
                  break;
               case 21:
                  if (curChar == 111)
                     jjstateSet[jjnewStateCnt++] = 0;
                  break;
               case 22:
                  if (curChar == 116)
                     jjstateSet[jjnewStateCnt++] = 21;
                  break;
               case 23:
                  if (curChar == 97)
                     jjstateSet[jjnewStateCnt++] = 22;
                  break;
               case 24:
                  if (curChar == 114)
                     jjstateSet[jjnewStateCnt++] = 23;
                  break;
               case 25:
                  if (curChar == 101)
                     jjstateSet[jjnewStateCnt++] = 24;
                  break;
               case 28:
                  if ((0x7fffffe07fffffeULL & l) == 0L)
                     break;
                  if (kind > 74)
                     kind = 74;
                  { jjCheckNAdd(29); }
                  break;
               case 29:
                  if ((0x7fffffe87fffffeULL & l) == 0L)
                     break;
                  if (kind > 74)
                     kind = 74;
                  { jjCheckNAdd(29); }
                  break;
               case 31:
                  { jjAddStates(20, 21); }
                  break;
               case 37:
                  { jjAddStates(0, 2); }
                  break;
               case 42:
                  { jjAddStates(22, 23); }
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else
      {
         int i2 = (curChar & 0xff) >> 6;
         unsigned long long l2 = 1ULL << (curChar & 077);
         do
         {
            switch(jjstateSet[--i])
            {
               case 31:
                  if ((jjbitVec0[i2] & l2) != 0L)
                     { jjAddStates(20, 21); }
                  break;
               case 37:
                  if ((jjbitVec0[i2] & l2) != 0L)
                     { jjAddStates(0, 2); }
                  break;
               case 42:
                  if ((jjbitVec0[i2] & l2) != 0L)
                     { jjAddStates(22, 23); }
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      if (kind != 0x7fffffff)
      {
         jjmatchedKind = kind;
         jjmatchedPos = curPos;
         kind = 0x7fffffff;
      }
      ++curPos;
      if ((i = jjnewStateCnt), (jjnewStateCnt = startsAt), (i == (startsAt = 48 - startsAt)))
         return curPos;
      if (input_stream->endOfInput()) { return curPos; }
      curChar = input_stream->readChar();
   }
}

/** Token literal values. */

Token * PommeLexerTokenManager::jjFillToken(){
   Token *t;
   JJString curTokenImage;
   int beginLine   = -1;
   int endLine     = -1;
   int beginColumn = -1;
   int endColumn   = -1;
   JJString im = jjstrLiteralImages[jjmatchedKind];
   curTokenImage = (im.length() == 0) ? input_stream->GetImage() : im;
   if (input_stream->getTrackLineColumn()) {
     beginLine = input_stream->getBeginLine();
     beginColumn = input_stream->getBeginColumn();
     endLine = input_stream->getEndLine();
     endColumn = input_stream->getEndColumn();
   }
   t = Token::newToken(jjmatchedKind, curTokenImage);
   t->specialToken = nullptr;
   t->next = nullptr;

   if (input_stream->getTrackLineColumn()) {
   t->beginLine = beginLine;
   t->endLine = endLine;
   t->beginColumn = beginColumn;
   t->endColumn = endColumn;
   }

   return t;
}
const int defaultLexState = 0;
/** Get the next Token. */

Token * PommeLexerTokenManager::getNextToken(){
  Token *matchedToken = nullptr;
  int curPos = 0;

  for (;;)
  {
   EOFLoop: 
   if (input_stream->endOfInput())
   {
      jjmatchedKind = 0;
      jjmatchedPos = -1;
      matchedToken = jjFillToken();
      return matchedToken;
   }
   curChar = input_stream->BeginToken();

   { input_stream->backup(0);
      while (curChar <= 32 && (0x100002600ULL & (1ULL << curChar)) != 0L)
   {
   if (input_stream->endOfInput()) { goto EOFLoop; }
   curChar = input_stream->BeginToken();
   }
   }
   jjmatchedKind = 0x7fffffff;
   jjmatchedPos = 0;
   curPos = jjMoveStringLiteralDfa0_0();
   if (jjmatchedKind != 0x7fffffff)
   {
      if (jjmatchedPos + 1 < curPos)
         input_stream->backup(curPos - jjmatchedPos - 1);
      if ((jjtoToken[jjmatchedKind >> 6] & (1ULL << (jjmatchedKind & 077))) != 0L)
      {
         matchedToken = jjFillToken();
         return matchedToken;
      }
      else
      {
         goto EOFLoop;
      }
   }
   int error_line = input_stream->getEndLine();
   int error_column = input_stream->getEndColumn();
   JJString error_after;
   bool EOFSeen = false;
   if (input_stream->endOfInput()) {
      EOFSeen = true;
      error_after = curPos <= 1 ? EMPTY : input_stream->GetImage();
      if (curChar == '\n' || curChar == '\r') {
         error_line++;
         error_column = 0;
      }
      else
         error_column++;
   }
   if (!EOFSeen) {
      error_after = curPos <= 1 ? EMPTY : input_stream->GetImage();
   }
   errorHandler->lexicalError(EOFSeen, curLexState, error_line, error_column, error_after, curChar, this);
  }
}

  /** Reinitialise parser. */
  void PommeLexerTokenManager::ReInit(JAVACC_CHARSTREAM *stream, int lexState) {
    clear();
    jjmatchedPos = jjnewStateCnt = 0;
    curLexState = lexState;
    input_stream = stream;
    ReInitRounds();
    debugStream = stdout; // init
    SwitchTo(lexState);
    errorHandler = new TokenManagerErrorHandler();
  }

  void PommeLexerTokenManager::ReInitRounds() {
    int i;
    jjround = 0x80000001;
    for (i = 48; i-- > 0;)
      jjrounds[i] = 0x80000000;
  }

  /** Switch to specified lex state. */
  void PommeLexerTokenManager::SwitchTo(int lexState) {
    if (lexState >= 1 || lexState < 0) {
      JJString message;
#ifdef WIDE_CHAR
      message += L"Error: Ignoring invalid lexical state : ";
      message += lexState; message += L". State unchanged.";
#else
      message += "Error: Ignoring invalid lexical state : ";
      message += lexState; message += ". State unchanged.";
#endif
      throw new TokenMgrError(message, INVALID_LEXICAL_STATE);
    } else
      curLexState = lexState;
  }

  /** Constructor. */
  PommeLexerTokenManager::PommeLexerTokenManager (JAVACC_CHARSTREAM *stream, int lexState)
  {
    input_stream = nullptr;
    ReInit(stream, lexState);
  }

  // Destructor
  PommeLexerTokenManager::~PommeLexerTokenManager () {
    clear();
  }

  // clear
  void PommeLexerTokenManager::clear() {
    //Since input_stream was generated outside of TokenManager
    //TokenManager should not take care of deleting it
    //if (input_stream) delete input_stream;
    if (errorHandler) delete errorHandler, errorHandler = nullptr;    
  }


}
