#include "XPlatform.h"
#include "Object.h"


namespace XPlatform
{
	/////////////////////////////////////////////////////////////////////////////
	// @ ������Ʈ �������� ��ȯ.
	/////////////////////////////////////////////////////////////////////////////
	auto& GetSharedAllObjects()
	{
		static std::vector<Object*> sharedAllObjects;
		return sharedAllObjects;
	}

	/////////////////////////////////////////////////////////////////////////////
	// @ ������Ʈ ������ ��ȯ.
	/////////////////////////////////////////////////////////////////////////////
	auto& GetSharedObjectCreator()
	{
		static std::map<std::wstring, ObjectCreateLambda> sharedObjectCreator;
		return sharedObjectCreator;
	}

	/////////////////////////////////////////////////////////////////////////////
	// @ ������Ʈ�� ��ӹ��� ��ü�� ���� �����Լ� ����.
	/////////////////////////////////////////////////////////////////////////////
	void SetObjectCreator(std::wstring className, ObjectCreateLambda lambda)
	{
		auto& sharedObjectCreator = GetSharedObjectCreator();
		auto it = sharedObjectCreator.find(className);

		if (it != sharedObjectCreator.end())
			return;

		sharedObjectCreator[className] = lambda;
	}

	void CheckAllReferences()
	{
		auto& sharedAllObjects = GetSharedAllObjects();
		auto it = sharedAllObjects.begin();
		while (it != sharedAllObjects.end())
		{	
			auto sharedObject = *it;
			if (sharedObject == nullptr)
			{
				it = sharedAllObjects.erase(it);
			}
			else if (sharedObject->GetReferenceCount() <= 0)
			{
				//sharedObject->OnDestroy();
				SAFE_DELETE(sharedObject);
				it = sharedAllObjects.erase(it);
			}

			++it;
		}
	}

	Object::Object()
	{
		m_ReferenceCount = 0;
		m_InstanceID = 0;
	}

	Object::~Object()
	{
		OnDestroy();
	}

	void Object::OnCreate()
	{
	}

	void Object::OnDestroy()
	{
	}

	uint64_t Object::GetReferenceCount()
	{
		return m_ReferenceCount;
	}

	uint64_t Object::GetInstanceID()
	{
		return m_InstanceID;
	}

	Object* Object::Instantiate(const std::wstring& className)
	{
		auto& sharedObjectCreator = GetSharedObjectCreator();
		auto& sharedAllObjects = GetSharedAllObjects();

		auto object = sharedObjectCreator[className]();
		sharedAllObjects.push_back(object);
		++object->m_ReferenceCount;
		object->OnCreate();
		return object;
	}

	void Object::Destroy(Object* object)
	{
		if (object == nullptr)
			return;

		--object->m_ReferenceCount;
		//SAFE_DELETE(object);
	}

	void Object::DestroyImmediate(Object* object)
	{
		if (object == nullptr)
			return;

		auto& sharedAllObjects = GetSharedAllObjects();
		sharedAllObjects.erase(std::remove(sharedAllObjects.begin(), sharedAllObjects.end(), object), sharedAllObjects.end());

		auto obj = std::make_shared<Object>();
		obj->OnDestroy();

		object->OnDestroy();
		SAFE_DELETE(object);
	}
}