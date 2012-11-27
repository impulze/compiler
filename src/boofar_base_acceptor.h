#ifndef BOOFAR_BASE_ACCEPTOR_H_INCLUDED
#define BOOFAR_BASE_ACCEPTOR_H_INCLUDED

#include "boofar_base_visitor.h"
#include "boofar_code_generator.h"
#include "boofar_prettyprinter.h"

namespace boofar
{
	namespace acceptors
	{
		namespace detail
		{
			template <class R, class T>
			struct base_factory_single
			{
				virtual R accept(T &) const = 0;
			};

			template <class R = void, class... T>
			struct base_factory;

			template <class R, class T, class... Args>
			struct base_factory<R, T, Args...>
				: base_factory<R, Args...>,
				  virtual base_factory_single<R, T>
			{
				using base_factory<R, Args...>::accept;
				using base_factory_single<R, T>::accept;
			};

			template <class R, class T>
			struct base_factory<R, T>
				: virtual base_factory_single<R, T>
			{
				using base_factory_single<R, T>::accept;
			};

			template <class R>
			struct all_base_factory
				: base_factory<
			                       R,
			                       visitors::prettyprinter,
			                       visitors::code_generator
			                      >
			{
			};
		}

		template <class R = void>
		struct base
			: virtual detail::all_base_factory<R>
		{
		};

		template <class C, class R = void>
		struct implementation
			: virtual detail::all_base_factory<R>
		{
			R accept(visitors::prettyprinter &visitor) const override
			{
				visitor.visit(static_cast<C const &>(*this));
			}

			R accept(visitors::code_generator &visitor) const override
			{
				visitor.visit(static_cast<C const &>(*this));
			}
		};

	}
}

#endif
