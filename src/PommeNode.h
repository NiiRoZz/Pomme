#pragma once

#include "SimpleNode.h"

namespace Pomme
{
	class PommeLexer;

	class PommeNode : public SimpleNode
	{
	public:
		PommeNode(int id);
		PommeNode(PommeLexer* parser, int id);

	public:
		void setLineNumber(int lineNumber);
		int getLineNumber() const;
		void setLineColumn(int columnNumber);
		int getLineColumn();

  private:
    int m_LineNumber;
		int m_ColumnNumber;
	};
}