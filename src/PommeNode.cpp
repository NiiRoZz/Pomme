#include "PommeNode.h"
#include "PommeLexer.h"

namespace Pomme
{
	PommeNode::PommeNode(int id)
	: SimpleNode(id)
	{
	}

	PommeNode::PommeNode(PommeLexer* parser, int id)
	: SimpleNode(parser, id)
	{
	}

	void PommeNode::setLineNumber(int lineNumber)
	{
		m_LineNumber = lineNumber;
	}
	int PommeNode::getLineNumber() const
	{
		return m_LineNumber;
	}
	void PommeNode::setLineColumn(int columnNumber)
	{
		m_ColumnNumber = columnNumber;
	}
	int PommeNode::getLineColumn()
	{
		return m_ColumnNumber;
	}
}

