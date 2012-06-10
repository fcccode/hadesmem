// Copyright Joshua Boyce 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// This file is part of HadesMem.
// <http://www.raptorfactor.com/> <raptorfactor@raptorfactor.com>

#include "hadesmem/module_list.hpp"

#define BOOST_TEST_MODULE module_list
#include "hadesmem/detail/warning_disable_prefix.hpp"
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include "hadesmem/detail/warning_disable_suffix.hpp"

#include "hadesmem/error.hpp"
#include "hadesmem/module.hpp"
#include "hadesmem/process.hpp"
#include "hadesmem/detail/to_upper_ordinal.hpp"

// Boost.Test causes the following warning under GCC:
// error: base class 'struct boost::unit_test::ut_detail::nil_t' has a 
// non-virtual destructor [-Werror=effc++]
#if defined(HADESMEM_GCC)
#pragma GCC diagnostic ignored "-Weffc++"
#endif // #if defined(HADESMEM_GCC)

BOOST_AUTO_TEST_CASE(module_list)
{
  hadesmem::Process const process(::GetCurrentProcessId());
  
  hadesmem::ModuleList module_list_manual(process);
  auto iter = module_list_manual.begin();
  hadesmem::Module const this_mod(process, nullptr);
  BOOST_CHECK(iter != module_list_manual.end());
  BOOST_CHECK(*iter == this_mod);
  hadesmem::Module const ntdll_mod(process, L"NtDll.DlL");
  BOOST_CHECK(++iter != module_list_manual.end());
  BOOST_CHECK(*iter == ntdll_mod);
  hadesmem::Module const kernel32_mod(process, L"kernel32.dll");
  BOOST_CHECK(++iter != module_list_manual.end());
  BOOST_CHECK(*iter == kernel32_mod);
  
  hadesmem::ModuleList module_list_enum(process);
  std::for_each(std::begin(module_list_enum), std::end(module_list_enum), 
    [] (hadesmem::Module const& module)
    {
      BOOST_CHECK(module.GetHandle() != nullptr);
    });
  
  hadesmem::ModuleList module_list_find(process);
  BOOST_CHECK(std::find_if(std::begin(module_list_find), std::end(module_list_find), 
    [] (hadesmem::Module const& module)
    {
      return module.GetHandle() == GetModuleHandle(L"user32.dll");
    }) != std::end(module_list_find));
}