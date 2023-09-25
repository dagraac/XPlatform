#pragma once


namespace XPlatform
{
	/////////////////////////////////////////////////////////////////////////////
	// @ ���� Ŭ����.
	/////////////////////////////////////////////////////////////////////////////
	template<typename T> class SharedClass
	{
	protected:
		SharedClass() {}

	public:
		virtual ~SharedClass() {}

		static T* GetSharedInstance()
		{
			static T instance;
			return &instance;
		}

		SharedClass(const SharedClass&) = delete;
		void operator = (const SharedClass&) = delete;
	};
}