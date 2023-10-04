﻿#pragma once
#include "XPlatform.h"
#include "Object.h"
#include "String.h"
#include "Node.h"


namespace XPlatform
{
	class Scene : public Object
	{
	private:
		typedef Object Base;
		friend class Application;
		friend class SceneManager;

	protected:
		String m_Name;
		bool m_IsVisible;
		Ref<Node> m_RootNode;

	protected:
		virtual void OnCreate();
		virtual void OnLoadStarted();
		virtual void OnLoadCompleted();
		virtual void OnUnloadStarted();
		virtual void OnUnloadCompleted();
		virtual void OnDestroy();
		virtual void OnPause();
		virtual void OnResume();
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender(Ref<XPlatform::IGL> gl);

	public:
		Scene();
		virtual ~Scene();

		void SetVisible(bool visible);
		bool IsVisible();

		Ref<Node> GetRootNode();
	};
}
