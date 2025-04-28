#pragma once
#include <memory>

namespace Spyen {
	template<typename T>
	class weak_ptr {
	public:
		weak_ptr(std::weak_ptr<T> ptr) : m_Ptr(ptr) {};
		weak_ptr() : m_Ptr(nullptr) {};
		
		T* operator->() {
			m_LockedPtr = m_Ptr.lock();
			return m_LockedPtr.get();
		}

		operator bool() const {
			return !m_Ptr.expired();
		}

	private:
		std::weak_ptr<T> m_Ptr;
		mutable std::shared_ptr<T> m_LockedPtr;
	
	};
}