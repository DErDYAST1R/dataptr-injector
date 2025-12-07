#pragma once

namespace fusion::pte
{
	struct mm_pte_t
	{
		union
		{
			uint64_t m_long;

			struct
			{
				uint64_t m_valid : 1;
				uint64_t m_dirty1 : 1;
				uint64_t m_owner : 1;
				uint64_t m_write_through : 1;
				uint64_t m_cache_disable : 1;
				uint64_t m_accessed : 1;
				uint64_t m_dirty : 1;
				uint64_t m_large_page : 1;
				uint64_t m_global : 1;
				uint64_t m_copy_on_write : 1;
				uint64_t m_unused : 1;
				uint64_t m_write : 1;
				uint64_t m_page_frame_number : 36;
				uint64_t m_reserved_for_hardware : 4;
				uint64_t m_reserved_for_software : 4;
				uint64_t m_wsle_age : 4;
				uint64_t m_wsle_protection : 3;
				uint64_t m_no_execute : 1;
			};
		};
	};

	mm_pte_t* get_pte_address( uint64_t virtual_address )
	{
		using fn = mm_pte_t * ( * )( void* );
		static fn fn_mi_get_pte_address = nullptr;

		if ( !fn_mi_get_pte_address )
		{
			fn_mi_get_pte_address = winapi::find_pattern<fn>( winapi::get_module_handle<void*>( _( "ntoskrnl.exe" ) ),
				_( "\x48\xC1\xE9\x09\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\x48\x23\xC8\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\x48\x03\xC1\xC3" ),
				_( "xxxxxx????????xxxxx????????xxxx" ) );

			if ( !fn_mi_get_pte_address )
				return nullptr;
		}

		return fn_mi_get_pte_address( reinterpret_cast< void* >( virtual_address ) );
	}

	uintptr_t allocate( size_t size )
	{
		uintptr_t allocated = 0;
		mm_pte_t* pte = 0;

		if ( size & 0xfff )
			size = ( ( size >> 12 ) << 12 ) + 0x1000;

		if ( NT_SUCCESS( imports::nt_allocate_virtual_memory( ( ( HANDLE ) ( LONG_PTR ) -1 ), reinterpret_cast< PVOID* >( &allocated ), 0, &size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE ) ) )
		{
			for ( uintptr_t i = allocated; i < ( ( allocated + size ) & 0xfffffffffffff000 ); i += 0x1000 )
			{
				*reinterpret_cast< uint8_t* >( i ) = 0;

				if ( ( pte = get_pte_address( i ) ) )
				{
					pte->m_no_execute = 0;
				}
				else
					TRACE( "pte not found" );
			}

		}
		return allocated;
	}

}