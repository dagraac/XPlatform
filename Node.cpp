#include "Node.h"
#include <sstream>
#include <cwchar>


namespace XPlatform
{
	Node::Node()
	{
		m_Parent = nullptr;
		m_Name.Clear();
		m_FullName.Clear();
		m_Children.clear();
		m_IsActive = true;
	}

	Node::~Node()
	{
		RemoveChildren();
	}

	void Node::SetFullName()
	{
		std::stringstream stringStream;
		std::vector<Node*> nodes;

		auto currentNode = this;
		while (currentNode != nullptr)
		{
			nodes.push_back(currentNode);
			currentNode = currentNode->m_Parent;
		}

		for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
		{
			auto node = *it;

			if (it == nodes.rbegin())
			{
				stringStream << UTF8("") << node->m_Name.GetConstCharArray();
			}
			else
			{
				stringStream << UTF8("/") << node->m_Name.GetConstCharArray();
			}
		}

		auto fullname = stringStream.str();
		m_FullName.Set(fullname.c_str());
	}

	void Node::SetActiveSelf(bool isActive)
	{
		m_IsActive = isActive;
	}

	bool Node::IsActiveSelf()
	{
		return m_IsActive;
	}

	bool Node::IsActiveInHierarchy()
	{
		if (!IsActiveSelf())
			return false;

		auto parent = m_Parent;
		while (parent != nullptr)
		{
			if (!parent->IsActiveSelf())
				return false;

			parent = parent->m_Parent;
		}

		return true;
	}

	void Node::SetName(const XString& nodeName)
	{
		m_Name.Set(nodeName);
		SetFullName();
	}

	void Node::SetSiblingIndex(uint32_t siblingIndex)
	{
		if (m_Parent == nullptr)
			return;


	}

	void Node::SetFirstSibling()
	{
	}

	void Node::SetLastSibling()
	{
	}

	bool Node::Contains(Node* childNode, bool checkHierarchy)
	{
		if (childNode == nullptr)
			return false;

		for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
		{
			auto currentNode = *it;
			if (currentNode == childNode)
				return true;

			if (checkHierarchy)
			{
				if (currentNode->Contains(childNode, true))
					return true;
			}
		}

		return false;
	}

	Node* Node::FindChild(XString& nodeName)
	{
		for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
		{
			auto childNode = *it;
			if (childNode->m_Name.Equals(nodeName))
				return childNode;
		}

		return nullptr;
	}

	void Node::AddChild(Node* childNode)
	{
		if (childNode == nullptr)
			return;

		if (childNode->m_Parent == this)
			return;

		if (childNode->m_Parent != nullptr)
		{
			childNode->m_Parent->RemoveChild(childNode);
			childNode->m_Parent = nullptr;
		}

		m_Children.emplace_back(childNode);
		childNode->m_Parent = this;
		childNode->SetFullName();
	}

	void Node::RemoveChild(Node* childNode)
	{
		if (childNode == nullptr)
			return;

		auto it = std::find(m_Children.begin(), m_Children.end(), childNode);
		if (it == m_Children.end())
			return;

		m_Children.erase(it);

		if (childNode->m_Parent == this)
			childNode->m_Parent = nullptr;

		childNode->SetFullName();
	}

	void Node::RemoveChildren()
	{
		for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
		{
			auto childNode = *it;
			m_Children.erase(it);

			if (childNode->m_Parent == this)
				childNode->m_Parent = nullptr;
		}
	}

	bool Node::IsRootNode()
	{
		return m_Parent == nullptr;
	}

	XString& Node::GetName()
	{
		return m_Name;
	}

	XString& Node::GetFullName()
	{
		return m_FullName;
	}

	unsigned int Node::GetChildCount()
	{
		return m_Children.size();
	}

	const Node* Node::GetParent()
	{
		return m_Parent;
	}

	const Node* Node::GetChild(uint32_t childIndex)
	{
		if (childIndex < m_Children.size())
			return nullptr;

		return m_Children[childIndex];
	}
}