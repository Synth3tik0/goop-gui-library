#ifndef TREEVIEW_H
#define TREEVIEW_H
#include <ddraw.h>
#include <CommCtrl.h>
#include "Base.h"

namespace Goop
{
	class TreeView : public Base
	{
	public:
		GOOP_API TreeView(Base *parent = 0);
		GOOP_API ~TreeView();

	private:

	};

	class TreeNode : public Base
	{
	public:
		TreeNode();
		~TreeNode();

	private:
		TVITEM m_info;
	};
}

#endif