/* -*- c++ -*- */
/*
 * Copyright 2022 Arizona State University.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CEDR_FFT_IMPL_H
#define INCLUDED_CEDR_FFT_IMPL_H

#include <gnuradio/cedr/fft.h>

namespace gr {
namespace cedr {

class fft_impl : public fft
{
private:
    // Nothing to declare in this block.

public:
    fft_impl(bool direction, size_t vlen);
    ~fft_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace cedr
} // namespace gr

#endif /* INCLUDED_CEDR_FFT_IMPL_H */
