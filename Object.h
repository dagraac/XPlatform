#pragma once

#include <map>
#include <string>
#include <functional>
#include <cstdint>


/////////////////////////////////////////////////////////////////////////////
// @ ���� �ν��Ͻ� �����⿡ ������Ʈ�� ��ӹ��� ��ü�� �߰�.
/////////////////////////////////////////////////////////////////////////////
#define RegisterObject(CLASS) \
    namespace { \
        struct __##CLASS##Register__ { \
            __##CLASS##Register__() { \
				SetObjectCreator(L#CLASS, []() -> Object* { return new CLASS(); });\
            } \
        }; \
    } \
    static __##CLASS##Register__ g_##CLASS##RegisterInstance;


/////////////////////////////////////////////////////////////////////////////
// @ ������Ʈ�� ��ӹ��� ��ü�� ����.
/////////////////////////////////////////////////////////////////////////////
#define CreateInstance(CLASS) (CLASS*)Object::Instantiate(L#CLASS)


namespace XPlatform
{
	/////////////////////////////////////////////////////////////////////////////
	// @ ������Ʈ : CreateInstance �� �����Ǵ� ��� ���̺귯�� ��ü���� �⺻ Ŭ����.
	/////////////////////////////////////////////////////////////////////////////
	class Object
	{
	private:
		uint64_t m_ReferenceCount;
		uint64_t m_InstanceID;
		
	public:
		Object();
		virtual ~Object();

	protected:
		virtual void OnCreate();
		virtual void OnDestroy();

	public:
		uint64_t GetReferenceCount();
		uint64_t GetInstanceID();

	public:
		static Object* Instantiate(const std::wstring& className);
		static void Destroy(Object* object);
		static void DestroyImmediate(Object* object);
	};

	typedef std::function<Object* (void)> ObjectCreateLambda;
	void SetObjectCreator(std::wstring className, ObjectCreateLambda lambda);
}