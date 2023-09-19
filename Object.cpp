#include "XPlatform.h"
#include "Object.h"


namespace XPlatform
{
	Object::Object()
	{
	}

	Object::~Object()
	{
	}

	void Object::Destroy(Object* object)
	{
		if (object == nullptr)
			return;

		SAFE_DELETE(object);
	}

	void Object::DestroyImmediate(Object* object)
	{
		if (object == nullptr)
			return;

		SAFE_DELETE(object);
	}
}