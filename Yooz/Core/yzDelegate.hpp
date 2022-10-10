#pragma once

// C++ 11 Delegate Based on Don Clugston's FastDelegate

#include <yzSTD.hpp>

#if defined(_MSC_VER)
	#define FASTDLGT_MICROSOFT_MFP
#endif

namespace yz
{
namespace detail
{
	template<class OutputClass, class InputClass>
	inline OutputClass implicit_cast(InputClass input)
	{
		return input;
	}

	template<class OutputClass, class InputClass>
	union horrible_union
	{
		OutputClass out;
		InputClass  in;
	};

	template<class OutputClass, class InputClass>
	inline OutputClass horrible_cast(const InputClass input)
	{
		horrible_union<OutputClass, InputClass> u;

		static_assert(sizeof(InputClass) == sizeof(u) &&
		                      sizeof(InputClass) == sizeof(OutputClass),
		              "Cannot use horrible_cast<>");

		u.in = input;
		return u.out;
	}

	template<class OutputClass, class InputClass>
	inline OutputClass unsafe_horrible_cast(const InputClass input)
	{
		horrible_union<OutputClass, InputClass> u;
		u.in = input;
		return u.out;
	}

	using DefaultVoid = void;

	template<class T>
	struct DefaultVoidToVoid
	{
		using type = T;
	};

	template<>
	struct DefaultVoidToVoid<DefaultVoid>
	{
		using type = void;
	};

	template<class T>
	struct VoidToDefaultVoid
	{
		using type = T;
	};

	template<>
	struct VoidToDefaultVoid<void>
	{
		using type = DefaultVoid;
	};

#ifdef FASTDLGT_MICROSOFT_MFP
	class __single_inheritance GenericClass;
	class GenericClass
	{
	};
#else
	class GenericClass;
#endif

	const int SINGLE_MEMFUNCPTR_SIZE = sizeof(void(GenericClass::*)());

	template<int N>
	struct SimplifyMemFunc
	{
		template<class X, class XFuncType, class GenericMemFuncType>
		inline static GenericClass* Convert(X* pthis, XFuncType function_to_bind,
		                                    GenericMemFuncType& bound_func)
		{
			static_assert(N - 100,
			              "Unsupported member function pointer on this compiler");
			return 0;
		}
	};

	template<>
	struct SimplifyMemFunc<SINGLE_MEMFUNCPTR_SIZE>
	{
		template<class X, class XFuncType, class GenericMemFuncType>
		inline static GenericClass* Convert(X* pthis, XFuncType function_to_bind,
		                                    GenericMemFuncType& bound_func)
		{
			bound_func = reinterpret_cast<GenericMemFuncType>(function_to_bind);
			return reinterpret_cast<GenericClass*>(pthis);
		}
	};

#ifdef FASTDLGT_MICROSOFT_MFP
	template<>
	struct SimplifyMemFunc<SINGLE_MEMFUNCPTR_SIZE + sizeof(int)>
	{
		template<class X, class XFuncType, class GenericMemFuncType>
		inline static GenericClass* Convert(X* pthis, XFuncType function_to_bind,
		                                    GenericMemFuncType& bound_func)
		{
			union
			{
				XFuncType func;
				struct
				{
					GenericMemFuncType funcaddress;
					int                delta;
				} s;
			} u;

			static_assert(sizeof(function_to_bind) == sizeof(u.s),
			              "Cannot use horrible_cast<>");

			u.func     = function_to_bind;
			bound_func = u.s.funcaddress;

			return reinterpret_cast<GenericClass*>(reinterpret_cast<char*>(pthis) +
			                                       u.s.delta);
		}
	};

	struct MicrosoftVirtualMFP
	{
		void (GenericClass::*codeptr)();
		int delta;
		int vtable_index;
	};

	struct GenericVirtualClass: virtual public GenericClass
	{
		using ProbePtrType = GenericVirtualClass* (GenericVirtualClass::*)();
		GenericVirtualClass* GetThis() { return this; }
	};

	template<>
	struct SimplifyMemFunc<SINGLE_MEMFUNCPTR_SIZE + 2 * sizeof(int)>
	{
		template<class X, class XFuncType, class GenericMemFuncType>
		inline static GenericClass* Convert(X* pthis, XFuncType function_to_bind,
		                                    GenericMemFuncType& bound_func)
		{
			union
			{
				XFuncType func;
				GenericClass* (X::*ProbeFunc)();
				MicrosoftVirtualMFP s;
			} u;

			u.func     = function_to_bind;
			bound_func = reinterpret_cast<GenericMemFuncType>(u.s.codeptr);

			union
			{
				GenericVirtualClass::ProbePtrType virtfunc;
				MicrosoftVirtualMFP               s;
			} u2;

			static_assert(sizeof(function_to_bind) == sizeof(u.s) &&
			                      sizeof(function_to_bind) == sizeof(u.ProbeFunc) &&
			                      sizeof(u2.virtfunc) == sizeof(u2.s),
			              "Cannot use horrible_cast<>");

			u2.virtfunc = &GenericVirtualClass::GetThis;
			u.s.codeptr = u2.s.codeptr;

			return (pthis->*u.ProbeFunc)();
		}
	};

	template<>
	struct SimplifyMemFunc<SINGLE_MEMFUNCPTR_SIZE + 3 * sizeof(int)>
	{
		template<class X, class XFuncType, class GenericMemFuncType>
		inline static GenericClass* Convert(X* pthis, XFuncType function_to_bind,
		                                    GenericMemFuncType& bound_func)
		{
			union
			{
				XFuncType func;
				struct
				{
					GenericMemFuncType funcaddress;
					int                delta;
					int                vtordisp;
					int                vtable_index;
				} s;
			} u;

			static_assert(sizeof(XFuncType) == sizeof(u.s),
			              "Cannot use horrible_cast<>");

			u.func            = function_to_bind;
			bound_func        = u.s.funcaddress;
			int virtual_delta = 0;

			if(u.s.vtable_index)
			{
				const int* vtable = *reinterpret_cast<const int* const*>(
				        reinterpret_cast<const char*>(pthis) + u.s.vtordisp);

				virtual_delta = u.s.vtordisp +
				                *reinterpret_cast<const int*>(
				                        reinterpret_cast<const char*>(vtable) +
				                        u.s.vtable_index);
			}
			return reinterpret_cast<GenericClass*>(reinterpret_cast<char*>(pthis) +
			                                       u.s.delta + virtual_delta);
		};
	};

#endif
}  // namespace detail

class DelegateMemento
{
protected:
	using GenericMemFuncType = void (detail::GenericClass::*)();

	detail::GenericClass* m_pthis;
	GenericMemFuncType    m_pFunction;

public:
	DelegateMemento(): m_pthis(0), m_pFunction(0) {};
	void clear()
	{
		m_pthis     = 0;
		m_pFunction = 0;
	}

public:
	inline bool IsEqual(const DelegateMemento& x) const
	{
		return m_pthis == x.m_pthis && m_pFunction == x.m_pFunction;
	}

	inline bool IsLess(const DelegateMemento& right) const
	{
		if(m_pthis != right.m_pthis)
			return m_pthis < right.m_pthis;

		return std::memcmp(&m_pFunction, &right.m_pFunction, sizeof(m_pFunction)) <
		       0;
	}

	inline size_t Hash() const
	{
		return reinterpret_cast<size_t>(m_pthis) ^
		       detail::unsafe_horrible_cast<size_t>(m_pFunction);
	}

	inline bool operator!() const { return m_pthis == 0 && m_pFunction == 0; }

	inline bool empty() const { return m_pthis == 0 && m_pFunction == 0; }

public:
	DelegateMemento& operator=(const DelegateMemento& right)
	{
		SetMementoFrom(right);
		return *this;
	}

	inline bool operator<(const DelegateMemento& right) { return IsLess(right); }

	inline bool operator>(const DelegateMemento& right)
	{
		return right.IsLess(*this);
	}

	DelegateMemento(const DelegateMemento& right)
	        : m_pthis(right.m_pthis), m_pFunction(right.m_pFunction)
	{
	}

protected:
	void SetMementoFrom(const DelegateMemento& right)
	{
		m_pFunction = right.m_pFunction;
		m_pthis     = right.m_pthis;
	}
};

namespace detail
{
	template<class GenericMemFunc, class StaticFuncPtr, class UnvoidStaticFuncPtr>
	class ClosurePtr: public DelegateMemento
	{
	public:
		template<class X, class XMemFunc>
		inline void bindmemfunc(X* pthis, XMemFunc function_to_bind)
		{
			m_pthis = SimplifyMemFunc<sizeof(function_to_bind)>::Convert(
			        pthis, function_to_bind, m_pFunction);
		}

		template<class X, class XMemFunc>
		inline void bindconstmemfunc(const X* pthis, XMemFunc function_to_bind)
		{
			m_pthis = SimplifyMemFunc<sizeof(function_to_bind)>::Convert(
			        const_cast<X*>(pthis), function_to_bind, m_pFunction);
		}

		inline GenericClass*  GetClosureThis() const { return m_pthis; }
		inline GenericMemFunc GetClosureMemPtr() const
		{
			return reinterpret_cast<GenericMemFunc>(m_pFunction);
		}

		template<class DerivedClass>
		inline void CopyFrom(DerivedClass*, const DelegateMemento& right)
		{
			SetMementoFrom(right);
		}

		template<class DerivedClass, class ParentInvokerSig>
		inline void bindstaticfunc(DerivedClass*    pParent,
		                           ParentInvokerSig static_function_invoker,
		                           StaticFuncPtr    function_to_bind)
		{
			if(function_to_bind == 0)
			{  // cope with assignment to 0
				m_pFunction = 0;
			}
			else
			{
				bindmemfunc(pParent, static_function_invoker);
			}

			static_assert(sizeof(GenericClass*) == sizeof(function_to_bind),
			              "Cannot use evil method");

			m_pthis = horrible_cast<GenericClass*>(function_to_bind);
		}

		inline UnvoidStaticFuncPtr GetStaticFunction() const
		{
			static_assert(sizeof(UnvoidStaticFuncPtr) == sizeof(this),
			              "Cannot use evil method");
			return horrible_cast<UnvoidStaticFuncPtr>(this);
		}

		inline bool IsEqualToStaticFuncPtr(StaticFuncPtr funcptr)
		{
			if(funcptr == 0)
				return empty();
			else
				return funcptr ==
				       reinterpret_cast<StaticFuncPtr>(GetStaticFunction());
		}
	};
}  // namespace detail

template<typename R, typename... A>
class DelegateImpl
{
private:
	using DesiredRetType          = typename detail::DefaultVoidToVoid<R>::type;
	using StaticFunctionPtr       = DesiredRetType (*)(A...);
	using UnvoidStaticFunctionPtr = R (*)(A...);
	using GenericMemFn            = R (detail::GenericClass::*)(A...);
	using ClosureType = detail::ClosurePtr<GenericMemFn, StaticFunctionPtr,
	                                       UnvoidStaticFunctionPtr>;

	ClosureType m_Closure;

public:
	using type = DelegateImpl;

	DelegateImpl() { clear(); }
	DelegateImpl(const DelegateImpl& x) { m_Closure.CopyFrom(this, x.m_Closure); }

	inline void operator=(const DelegateImpl& x)
	{
		m_Closure.CopyFrom(this, x.m_Closure);
	}

	inline bool operator==(const DelegateImpl& x) const
	{
		return m_Closure.IsEqual(x.m_Closure);
	}

	inline bool operator!=(const DelegateImpl& x) const
	{
		return !m_Closure.IsEqual(x.m_Closure);
	}

	inline bool operator<(const DelegateImpl& x) const
	{
		return m_Closure.IsLess(x.m_Closure);
	}

	inline bool operator>(const DelegateImpl& x) const
	{
		return x.m_Closure.IsLess(m_Closure);
	}

	template<typename X, typename Y>
	DelegateImpl(Y* pthis, DesiredRetType (X::*function_to_bind)(A... args))
	{
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);
	}

	template<typename X, typename Y>
	inline void Bind(Y* pthis, DesiredRetType (X::*function_to_bind)(A... args))
	{
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(pthis), function_to_bind);
	}

	template<typename X, typename Y>
	DelegateImpl(const Y* pthis,
	             DesiredRetType (X::*function_to_bind)(A... args) const)
	{
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis),
		                           function_to_bind);
	}

	template<typename X, typename Y>
	inline void Bind(const Y* pthis,
	                 DesiredRetType (X::*function_to_bind)(A... args) const)
	{
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(pthis),
		                           function_to_bind);
	}

	template<typename X, typename Y>
	DelegateImpl(Y& pthis, DesiredRetType (X::*function_to_bind)(A... args))
	{
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(&pthis), function_to_bind);
	}

	template<typename X, typename Y>
	inline void Bind(Y& pthis, DesiredRetType (X::*function_to_bind)(A... args))
	{
		m_Closure.bindmemfunc(detail::implicit_cast<X*>(&pthis), function_to_bind);
	}

	template<typename X, typename Y>
	DelegateImpl(const Y& pthis,
	             DesiredRetType (X::*function_to_bind)(A... args) const)
	{
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(&pthis),
		                           function_to_bind);
	}

	template<typename X, typename Y>
	inline void Bind(const Y& pthis,
	                 DesiredRetType (X::*function_to_bind)(A... args) const)
	{
		m_Closure.bindconstmemfunc(detail::implicit_cast<const X*>(&pthis),
		                           function_to_bind);
	}

	DelegateImpl(DesiredRetType (*function_to_bind)(A... args))
	{
		Bind(function_to_bind);
	}

	void operator=(DesiredRetType (*function_to_bind)(A... args))
	{
		Bind(function_to_bind);
	}

	inline void Bind(DesiredRetType (*function_to_bind)(A... args))
	{
		m_Closure.bindstaticfunc(this, &DelegateImpl::InvokeStaticFunction,
		                         function_to_bind);
	}

	DelegateImpl(DesiredRetType (&function_to_bind)(A... args))
	{
		Bind(function_to_bind);
	}

	void operator=(DesiredRetType (&function_to_bind)(A... args))
	{
		Bind(function_to_bind);
	}

	inline void Bind(DesiredRetType (&function_to_bind)(A... args))
	{
		m_Closure.bindstaticfunc(this, &DelegateImpl::InvokeStaticFunction,
		                         &function_to_bind);
	}

	inline R operator()(A... args) const
	{
		return (m_Closure.GetClosureThis()->*(m_Closure.GetClosureMemPtr()))(
		        args...);
	}

private:
	struct SafeBoolStruct
	{
		int               a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	};

	using UselessTypedef        = SafeBoolStruct;
	using unspecified_bool_type = StaticFunctionPtr SafeBoolStruct::*;

public:
	operator unspecified_bool_type() const
	{
		return empty() ? 0 : &SafeBoolStruct::m_nonzero;
	}

	inline bool operator==(StaticFunctionPtr funcptr)
	{
		return m_Closure.IsEqualToStaticFuncPtr(funcptr);
	}

	inline bool operator!=(StaticFunctionPtr funcptr)
	{
		return !m_Closure.IsEqualToStaticFuncPtr(funcptr);
	}

	inline bool operator!() const { return !m_Closure; }

	inline bool empty() const { return !m_Closure; }
	void        clear() { m_Closure.clear(); }

	const DelegateMemento& GetMemento() const { return m_Closure; }
	void SetMemento(const DelegateMemento& any) { m_Closure.CopyFrom(this, any); }

private:
	inline R InvokeStaticFunction(A... args) const
	{
		return (*(m_Closure.GetStaticFunction()))(args...);
	}
};

template<typename Signature>
class Delegate;

template<typename R, typename... A>
class Delegate<R(A...)>: public DelegateImpl<R, A...>
{
public:
	using BaseType = DelegateImpl<R, A...>;
	using SelfType = Delegate;

	Delegate(): BaseType() {}

	template<typename X, typename Y>
	Delegate(Y* pthis, R (X::*function_to_bind)(A... args))
	        : BaseType(pthis, function_to_bind)
	{
	}

	template<typename X, typename Y>
	Delegate(const Y* pthis, R (X::*function_to_bind)(A... args) const)
	        : BaseType(pthis, function_to_bind)
	{
	}

	template<typename X, typename Y>
	Delegate(Y& pthis, R (X::*function_to_bind)(A... args))
	        : BaseType(pthis, function_to_bind)
	{
	}

	template<typename X, typename Y>
	Delegate(const Y& pthis, R (X::*function_to_bind)(A... args) const)
	        : BaseType(pthis, function_to_bind)
	{
	}

	Delegate(R (*function_to_bind)(A... args)): BaseType(function_to_bind) {}
	void operator=(const BaseType& x) { *static_cast<BaseType*>(this) = x; }
};

template<typename R, typename... A>
inline Delegate<R(A...)> MakeDelegate(R (*func)(A...))
{
	return Delegate<R(A...)>(func);
}

template<typename R, typename X, typename Y, typename... A>
inline Delegate<R(A...)> MakeDelegate(Y* x, R (X::*func)(A...))
{
	return Delegate<R(A...)>(x, func);
}

template<typename R, typename X, typename Y, typename... A>
inline Delegate<R(A...)> MakeDelegate(Y* x, R (X::*func)(A...) const)
{
	return Delegate<R(A...)>(x, func);
}

template<typename R, typename... A>
inline Delegate<R(A...)> MakeDelegate(R (&func)(A...))
{
	return Delegate<R(A...)>(func);
}

template<typename R, typename X, typename Y, typename... A>
inline Delegate<R(A...)> MakeDelegate(Y& x, R (X::*func)(A...))
{
	return Delegate<R(A...)>(x, func);
}

template<typename R, typename X, typename Y, typename... A>
inline Delegate<R(A...)> MakeDelegate(const Y& x, R (X::*func)(A...) const)
{
	return Delegate<R(A...)>(x, func);
}
}  // namespace yz
