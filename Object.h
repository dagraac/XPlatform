#pragma once

#include <map>
#include <string>
#include <functional>


#define REGISTEROBJECT(CLASS) g_ObjectFactory[#CLASS] = []() -> Object* { return new CLASS(); }
#define CREATEINSTANCE(CLASS) g_ObjectFactory[#CLASS]()


namespace XPlatform
{
	/////////////////////////////////////////////////////////////////////////////
	// @ ������Ʈ : new �� �����Ǵ� ��� ���̺귯�� ��ü���� �⺻ Ŭ����.
	/////////////////////////////////////////////////////////////////////////////
	class Object
	{
	private:
		unsigned int m_ReferenceCount;

	public:
		Object();
		virtual ~Object();

	protected:
		virtual void OnCreate();
		virtual void OnDestroy();

	public:
		Object* Clone();
		static void Destroy(Object* object);
		static void DestroyImmediate(Object* object);
	};

	extern std::map<std::string, std::function<Object*(void)>> g_ObjectFactory;
}