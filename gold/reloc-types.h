// reloc-types.h -- CGC relocation templates for gold  -*- C++ -*-

// Copyright 2006, 2007, 2008 Free Software Foundation, Inc.
// Written by Ian Lance Taylor <iant@google.com>.

// This file is part of gold.

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
// MA 02110-1301, USA.

// This header files defines a few convenient templated types for use
// when handling CGC relocations.

#ifndef GOLD_RELOC_TYPES_H
#define GOLD_RELOC_TYPES_H

#include "cgccpp.h"

namespace gold
{

// Pick the CGC relocation accessor class and the size based on
// SH_TYPE, which is either cgccpp::SHT_REL or cgccpp::SHT_RELA.

template<int sh_type, int size, bool big_endian>
struct Reloc_types;

template<int size, bool big_endian>
struct Reloc_types<cgccpp::SHT_REL, size, big_endian>
{
  typedef typename cgccpp::Rel<size, big_endian> Reloc;
  typedef typename cgccpp::Rel_write<size, big_endian> Reloc_write;
  static const int reloc_size = cgccpp::Cgc_sizes<size>::rel_size;

  static inline typename cgccpp::Cgc_types<size>::Cgc_Swxword
  get_reloc_addend(const Reloc*)
  { gold_unreachable(); }

  static inline typename cgccpp::Cgc_types<size>::Cgc_Swxword
  get_reloc_addend_noerror(const Reloc*)
  { return 0; }

  static inline void
  set_reloc_addend(Reloc_write*,
		   typename cgccpp::Cgc_types<size>::Cgc_Swxword)
  { gold_unreachable(); }

  static inline void
  copy_reloc_addend(Reloc_write*, const Reloc*)
  { gold_unreachable(); }
};

template<int size, bool big_endian>
struct Reloc_types<cgccpp::SHT_RELA, size, big_endian>
{
  typedef typename cgccpp::Rela<size, big_endian> Reloc;
  typedef typename cgccpp::Rela_write<size, big_endian> Reloc_write;
  static const int reloc_size = cgccpp::Cgc_sizes<size>::rela_size;

  static inline typename cgccpp::Cgc_types<size>::Cgc_Swxword
  get_reloc_addend(const Reloc* p)
  { return p->get_r_addend(); }

  static inline typename cgccpp::Cgc_types<size>::Cgc_Swxword
  get_reloc_addend_noerror(const Reloc* p)
  { return p->get_r_addend(); }

  static inline void
  set_reloc_addend(Reloc_write* p,
		   typename cgccpp::Cgc_types<size>::Cgc_Swxword val)
  { p->put_r_addend(val); }

  static inline void
  copy_reloc_addend(Reloc_write* to, const Reloc* from)
  { to->put_r_addend(from->get_r_addend()); }
};

}; // End namespace gold.

#endif // !defined(GOLD_RELOC_TYPE_SH)
