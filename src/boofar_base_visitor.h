#ifndef BOOFAR_BASE_VISITOR_H_INCLUDED
#define BOOFAR_BASE_VISITOR_H_INCLUDED

namespace boofar
{
	namespace nodes
	{
		class generic;
		class identifier;
		class declaration;
		class literal;
		class decimal_literal;
		class float_literal;
		class hexadecimal_literal;
		class octal_literal;
	}

	namespace visitors
	{
		namespace detail
		{
			template <class R = void, class... T>
			struct base_factory
			{
			};

			template <class R, class T, class... Args>
			struct base_factory<R, T, Args...>
				: base_factory<R, Args...>
			{
				using base_factory<R, Args...>::visit;
				virtual R visit(T &)
				{
				}
			};

			template <class R, class T>
			struct base_factory<R, T>
				: base_factory<R>
			{
				virtual R visit(T &)
				{
				}
			};
		}

		template <class R = void>
		struct base
			: detail::base_factory<
			                       R,
			                       boofar::nodes::generic,
			                       boofar::nodes::identifier,
			                       boofar::nodes::declaration,
			                       boofar::nodes::literal,
			                       boofar::nodes::decimal_literal,
			                       boofar::nodes::float_literal,
			                       boofar::nodes::hexadecimal_literal,
			                       boofar::nodes::octal_literal
			                      >
		{
		};
	}
}

#endif
