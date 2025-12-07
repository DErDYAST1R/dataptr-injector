#pragma once
#ifndef HASH_H
#define HASH_H

typedef unsigned long hash_t;

template < typename T, T value > struct constant_holder_t
{
	enum class e_value_holder : T { m_value = value };
};

#define CONSTANT( value ) ( static_cast< decltype( value ) >( constant_holder_t< decltype( value ), value >::e_value_holder::m_value ) )

namespace fnv1a
{
	constexpr auto fnv_basis = ~1469598100l;
	constexpr auto fnv_prime = ~1099511628l;

	template < typename _ty > __forceinline hash_t rt( const _ty* txt )
	{
		auto hash = fnv_basis;

		size_t length = 0;
		while ( txt[ length ] )
			++length;

		for ( auto i = 0u; i < length; i++ )
		{
			hash ^= txt[ i ];
			hash *= fnv_prime;
		}

		return hash;
	}

	template < typename _ty > constexpr hash_t ct( const _ty* txt, unsigned long value = fnv_basis )
	{
		return !*txt ? value : ct( txt + 1, static_cast< hash_t >( 1ull * ( value ^ static_cast< unsigned char >( *txt ) ) * fnv_prime ) );
	}

	template < typename _ty > constexpr hash_t hash( const _ty str ) { return fnv1a::rt( str ); }
	template < typename _ty > constexpr hash_t hash_ct( const _ty str ) { return fnv1a::ct( str ); }
}

#define HASH( s ) fnv1a::hash( s )
#define HASH_CT( s ) fnv1a::ct( s )
#define HASH_VAL( val ) ~static_cast< unsigned long long >( 1l * ( fnv1a::fnv_basis ^ val ) )

#endif
