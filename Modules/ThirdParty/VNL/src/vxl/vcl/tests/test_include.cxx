#include <vcl_cassert.h>
#ifndef VCL_SGI_CC_720 //SGI7.2.1
#include <vcl_ciso646.h>
//#include <vcl_atomic_count.h> // ITK tests compilers this does not support
#endif
#include <vcl_csetjmp.h>
#include <vcl_cstdio.h>
#include <vcl_ctime.h>
#include <vcl_cctype.h>
#include <vcl_climits.h>
#include <vcl_csignal.h>
#include <vcl_cstdlib.h>
#ifndef __FreeBSD__ //FreeBSD4
#include <vcl_cwchar.h>
#ifndef __sun
#include <vcl_cwctype.h>
#endif
#endif
#include <vcl_cerrno.h>
#include <vcl_clocale.h>
#include <vcl_cstdarg.h>
#include <vcl_cstring.h>
#include <vcl_cmath.h>
#include <vcl_cfloat.h>
#include <vcl_cstddef.h>
#include <vcl_algorithm.h>
#include <vcl_iomanip.h>
#include <vcl_list.h>
#include <vcl_ostream.h>
#include <vcl_streambuf.h>
#ifndef VCL_EGCS //egcs
#include <vcl_bitset.h>
#endif
#include <vcl_ios.h>
#ifndef VCL_GCC_295 //gcc2.95
#include <vcl_locale.h>
#endif
#include <vcl_limits.h>
#include <vcl_queue.h>
#include <vcl_string.h>
#include <vcl_complex.h>
#include <vcl_iosfwd.h>
#include <vcl_map.h>
#include <vcl_set.h>
#if VCL_CXX_HAS_HEADER_TYPEINFO
#include <vcl_typeinfo.h>
#endif
#include <vcl_deque.h>
#include <vcl_iostream.h>
#include <vcl_istream.h>
#include <vcl_sstream.h>
#include <vcl_fstream.h>
#include <vcl_iterator.h>
#include <vcl_memory.h>
#include <vcl_utility.h>
#include <vcl_exception.h>
#include <vcl_new.h>
#include <vcl_stack.h>
#ifndef VCL_SGI_CC_720 //SGI7.2.1
#include <vcl_valarray.h>
#include <vcl_numeric.h>
#include <vcl_stdexcept.h>
#endif
#include <vcl_vector.h>
#include <vcl_functional.h>

#include <vcl_complex_fwd.h>
#include <vcl_stlfwd.h>
#include <vcl_where_root_dir.h>
#include <vcl_compiler.h>
#include <vcl_deprecated.h>
#define vcl_deprecated_header_h_ // to avoid deprecation warning in here
#include <vcl_deprecated_header.h>

int main() { return 0; }
