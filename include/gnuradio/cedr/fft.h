/* -*- c++ -*- */
/*
 * Copyright 2022 Arizona State University.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CEDR_FFT_H
#define INCLUDED_CEDR_FFT_H

#include <gnuradio/cedr/api.h>
#include <gnuradio/sync_block.h>
#include <dash.h>

namespace gr {
namespace cedr {

/*!
 * \brief <+description of block+>
 * \ingroup cedr
 *
 */
class CEDR_API fft : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<fft> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of cedr::fft.
     *
     * To avoid accidental use of raw pointers, cedr::fft's
     * constructor is in a private implementation
     * class. cedr::fft::make is the public interface for
     * creating new instances.
     */
    static sptr make(bool direction, size_t vlen);
};

} // namespace cedr
} // namespace gr

#endif /* INCLUDED_CEDR_FFT_H */
