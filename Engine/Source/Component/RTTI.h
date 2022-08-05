#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API RTTI
	{
	public:
		virtual const size_t& TypeIdInstance() const = 0;

		virtual RTTI* QueryInterface(const size_t id)
		{
			return nullptr;
		}

		virtual const RTTI* QueryInterface(const size_t id) const
		{
			return nullptr;
		}

		virtual bool Is(const size_t it) const
		{
			return false;
		}

		virtual bool Is(const std::string& name) const
		{
			return false;
		}

		template<typename T>
		T* As() const
		{
			if (Is(T::TypeIdClass()))
			{
				return (T*)this;
			}

			return nullptr;
		}

		template<typename T>
		const T* As() const
		{
			if (Is(T::TypeIdClass()))
			{
				return (T*)this;
			}

			return nullptr;
		}
	};

#define RTTI_DECLARATIONS(Type, ParentType)													\
	public:																					\
		static std::string TypeName() { return std::string(#Type); }						\
		virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
		static const size_t TypeIdClass()													\
		{																					\
			static int runTimeTypeId = 0;													\
			return (size_t)(&runTimeTypeId);												\
		}																					\
		virtual RTTI* QueryInterface(const size_t id)										\
		{																					\
			if (id == TypeIdClass())														\
			{ return (RTTI*)this; }															\
			else																			\
			{ return ParentType::QueryInterface(id); }										\
		}																					\
		virtual const RTTI* QueryInterface(const size_t id) const							\
		{																					\
			if (id == TypeIdClass())														\
			{ return (RTTI*)this; }															\
			else																			\
			{ return ParentType::QueryInterface(id); }										\
		}																					\
		virtual bool Is(const size_t id) const												\
		{																					\
			if (id == TypeIdClass())														\
			{ return true; }																\
			else { return ParentType::Is(id); }												\
		}																					\
		virtual bool Is(const std::string& name) const										\
		{																					\
			if (name == TypeName())															\
			{ return true; }																\
			else { return ParentType::Is(name); }											\
		}																					
}