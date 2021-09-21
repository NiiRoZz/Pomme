/* Generated By:JavaCC: Do not edit this line. Token.h Version 7.0 */
/* JavaCCOptions:STATIC=false,SUPPORT_CLASS_VISIBILITY_PUBLIC=true,TOKEN_INCLUDE=,TOKEN_SUPER_CLASS=null */
#ifndef JAVACC_TOKEN_H
#define JAVACC_TOKEN_H

#include "JavaCC.h"


namespace Pomme {

/**
 * Describes the input token stream.
 */

class Token
{
 public:

  /**
   * An integer that describes the kind of this token.  This numbering
   * system is determined by JavaCCParser, and a table of these numbers is
   * stored in the file ...Constants.java.
   */
  int kind = 0;

  /** The line number of the first character of this Token. */
  int beginLine = 0;
  /** The column number of the first character of this Token. */
  int beginColumn = 0;
  /** The line number of the last character of this Token. */
  int endLine = 0;
  /** The column number of the last character of this Token. */
  int endColumn = 0;

  /**
   * The string image of the token.
   */
  JJString image;

  /**
   * A reference to the next regular (non-special) token from the input
   * stream.  If this is the last token from the input stream, or if the
   * token manager has not read tokens beyond this one, this field is
   * set to NULL.  This is true only if this token is also a regular
   * token.  Otherwise, see below for a description of the contents of
   * this field.
   */
  Token *next = 0;

  /**
   * This field is used to access special tokens that occur prior to this
   * token, but after the immediately preceding regular (non-special) token.
   * If there are no such special tokens, this field is set to NULL.
   * When there are more than one such special token, this field refers
   * to the last of these special tokens, which in turn refers to the next
   * previous special token through its specialToken field, and so on
   * until the first special token (whose specialToke_ field is NULL).
   * The next fields of special tokens refer to other special tokens that
   * immediately follow it (without an intervening regular token).  If there
   * is no such token, this field is NULL.
   */
  Token *specialToken = 0;

  /**
   * An optional attribute value of the Token.
   * Tokens which are not used as syntactic sugar will often contain
   * meaningful values that will be used later on by the compiler or
   * interpreter. This attribute value is often different from the image.
   * Any subclass of Token that actually wants to return a non-NULL value can
   * override this method as appropriate.
   */
  void * getValue();

  /**
   * No-argument constructor
   */
  Token();

  /**
   * Constructs a new token for the specified Image.
   */
  Token(int kind);

  /**
   * Constructs a new token for the specified Image and Kind.
   */
  Token(int kind, const JJString& image);

  virtual ~Token();

  /**
   * Returns the image.
   */
  const JJString& toString();


  /**
   * Returns a new Token void *, by default. However, if you want, you
   * can create and return subclass objects based on the value of ofKind.
   * Simply add the cases to the switch for all those special cases.
   * For example, if you have a subclass of Token called IDToken that
   * you want to create if ofKind is ID, simply add something like :
   *
   *    case MyParserConstants.ID : return new IDToken(ofKind, image);
   *
   * to the following switch statement. Then you can cast matchedToken
   * variable to the appropriate type and use sit in your lexical actions.
   */
  static Token *newToken(int ofKind, const JJString& image);

  static Token *newToken(int ofKind);
};

}

#endif
/* JavaCC - OriginalChecksum=8c82027e570173552a6880e622c52e0d (do not edit this line) */
