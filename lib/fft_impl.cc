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
	      double *temp_in = new double[2*d_vlen];
	      double *temp_out = new double[2*d_vlen];
	      for (size_t i = 0; i < (size_t)d_vlen; i++){
		const gr_complex x = in[i]; // gr_complex is a type signature for std::complex<float>
		temp_in[2*i] = (double) x.real();
		temp_in[2*i+1] = (double) x.imag();
	      }

	      /* Call out to the DASH_FFT Macro that will hook into CEDR
	       * complex input and output,  input[2*i+0] = real, input[2*i+1] = imaginary
	       * - d_vlen is size of the complex transform, true is forward, false is inverse */
	      DASH_FFT(temp_in, temp_out, d_vlen, d_direction);

	      // Copy the temporary output buffer into the GR output buffer - and also cast back to float from double
	      for (size_t i = 0; i < (size_t)d_vlen; i++)
	      {
		gr_complex o = gr_complex(temp_out[2*i],temp_out[2*i+1]);
		*out++ = (gr_complex) o;
	      }


	      // Free the dynamically allocated temp buffers
	      delete[] temp_in;
	      delete[] temp_out;
	      // Move the pointer forward by FFT length
	      in += d_vlen;
	      // The out pointer has already been moved forward appropriately by the output copy loop
	}
      // Tell runtime system how many output items we produced.
      return noutput_items;
}

} /* namespace cedr */
} /* namespace gr */
