#ifndef BOOFAR_BASE_VISITOR_H_INCLUDED
#define BOOFAR_BASE_VISITOR_H_INCLUDED

namespace boofar
{
	namespace nodes
	{
		class generic;
		class assignment;
		class binary_operation;
		class identifier;
		class declaration;
		class literal;
		class decimal_literal;
		class float_literal;
		class hexadecimal_literal;
		class octal_literal;
		class parameter_list;
	}

	namespace visitors
	{
		namespace detail
		{
			template <class R, class T>
			struct base_factory_single
			{
				virtual R visit(T &)
				{
				}
			};

			template <class R = void, class... T>
			struct base_factory;

			template <class R, class T, class... Args>
			struct base_factory<R, T, Args...>
				: base_factory<R, Args...>,
				  base_factory_single<R, T>
			{
				using base_factory<R, Args...>::visit;
				using base_factory_single<R, T>::visit;
			};

			template <class R, class T>
			struct base_factory<R, T>
				: base_factory_single<R, T>
			{
				using base_factory_single<R, T>::visit;
			};
		}

		template <class R = void>
		struct base
			: detail::base_factory<
			                       R,
			                       nodes::assignment,
			                       nodes::identifier,
			                       nodes::binary_operation,
			                       nodes::declaration,
			                       nodes::decimal_literal,
			                       nodes::float_literal,
			                       nodes::hexadecimal_literal,
			                       nodes::octal_literal,
			                       nodes::parameter_list
			                      >
		{
		};
	}
}

#endif
