#include "TreeView.h"

using namespace Goop;

TreeNode::TreeNode()
{
	m_info.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE | TVIF_STATE | TVIF_TEXT;
}

TreeNode::~TreeNode()
{

}