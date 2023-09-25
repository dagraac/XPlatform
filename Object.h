#pragma once

#include"XPlatform.h"


/////////////////////////////////////////////////////////////////////////////
// @ ���� �ν��Ͻ� �����⿡ ������Ʈ�� ��ӹ��� ��ü�� �߰�.
/////////////////////////////////////////////////////////////////////////////
#define RegisterObject(CLASS)\
    namespace {\
        struct __##CLASS##Register__ {\
            __##CLASS##Register__() {\
				SetObjectCreator(L#CLASS, []() -> Object* { return new CLASS(); });\
            }\
        };\
    }\
    static __##CLASS##Register__ g_##CLASS##RegisterInstance;


/////////////////////////////////////////////////////////////////////////////
// @ ������Ʈ�� ��ӹ��� ��ü�� ����.
/////////////////////////////////////////////////////////////////////////////
//#define CreateInstance(CLASS) std::shared_ptr<CLASS>((CLASS*)Object::Instantiate(L#CLASS))
#define CreateInstance(CLASS) std::shared_ptr<CLASS>((CLASS*)Object::Instantiate(L#CLASS))
//#define DestroyInstance(INSTANCE) if (INSTANCE.)


namespace XPlatform
{
	/////////////////////////////////////////////////////////////////////////////
	// @ ������Ʈ : CreateInstance �� �����Ǵ� ��� ���̺귯�� ��ü���� �⺻ Ŭ����.
	/////////////////////////////////////////////////////////////////////////////
	class Object
	{
	private:
		uint64_t m_InstanceID;
		
	public:
		Object();
		virtual ~Object();

	protected:
		virtual void OnCreate();
		virtual void OnDestroy();

	public:
		//uint64_t GetReferenceCount();
		uint64_t GetInstanceID();

	public:
		static Object* Instantiate(const std::wstring& className);
		//static void DestroyImmediate(Object* object);

		template<typename T> static std::shared_ptr<T> Create(const std::wstring& className);
		template<typename T> static void Destroy(std::shared_ptr<T>* object);
	};

	typedef std::function<Object* (void)> ObjectCreateLambda;
	void SetObjectCreator(std::wstring className, ObjectCreateLambda lambda);

	template<typename T> inline std::shared_ptr<T> Object::Create(const std::wstring& className)
	{
		auto object = (T*)Object::Instantiate(className);
		return std::shared_ptr<T>(object);
	}

	template<typename T> inline void Object::Destroy(std::shared_ptr<T>* object)
	{
		object.reset();
		object = nullptr;
	}
}