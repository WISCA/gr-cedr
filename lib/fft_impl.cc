/* -*- c++ -*- */
/*
 * Copyright 2022 Arizona State University.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fft_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace cedr {

using input_type = gr_complex;
using output_type = gr_complex;
fft::sptr fft::make(bool direction, size_t vlen)
{
    return gnuradio::make_block_sptr<fft_impl>(direction, vlen);
}


/*
 * The private constructor
 */
fft_impl::fft_impl(bool direction, size_t vlen)
    : gr::sync_block("fft",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)*vlen),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)*vlen)),
    d_direction(direction),
    d_vlen(vlen)
{
}

/*
 * Our virtual destructor.
 */
fft_impl::~fft_impl() {}

int fft_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
	auto in = reinterpret_cast<const gr_complex*>(input_items[0]);
	auto out = reinterpret_cast<gr_complex*>(output_items[0]);

	int count = 0;
//  	printf("new work called with noutput_items: %d\n", noutput_items);

	while (count++ < noutput_items) {
	      /* Call out to the DASH_FFT Macro that will hook into CEDR
	       * complex(float) input and output,
	       * - d_vlen is size of the complex transform, true is forward, false is inverse */
	      DASH_FFT_flt((dash_cmplx_flt_type*)in, (dash_cmplx_flt_type*)out, d_vlen, d_direction);

	      in += d_vlen;
	      // The out pointer has already been moved forward appropriately by the output copy loop
	}
      // Tell runtime system how many output items we produced.
      return noutput_items;
}

} /* namespace cedr */
} /* namespace gr */
