/* -*- c++ -*- */
/* 
 * Copyright 2015 <Nikos Kargas (nkargas@isc.tuc.gr)>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_RFID_READER_IMPL_H
#define INCLUDED_RFID_READER_IMPL_H

#include <rfid/reader.h>
#include <vector>
#include <queue>
#include <fstream>
#include <jsoncpp/json/json.h>

namespace gr {
    namespace rfid {

        class reader_impl : public reader {
        private:
            typedef uint16_t bit_order_16(uint16_t value);

            typedef uint8_t bit_order_8(uint8_t value);

            int s_rate, d_rate, n_cwquery_s, n_cwack_s, n_p_down_s;
            float sample_d, n_data0_s, n_data1_s, n_cw_s, n_pw_s, n_delim_s, n_trcal_s;
            std::vector<float> data_0, data_1, cw, cw_ack, cw_query, delim, frame_sync, preamble, rtcal, trcal, query_bits, ack_bits, query_rep, nak, query_adjust_bits, p_down;
            int q_change; // 0-> increment, 1-> unchanged, 2-> decrement
            // Command Waiting Time
            std::vector<float> wait_T4;

            void gen_query_adjust_bits();

            void crc_append(std::vector<float> &q);
            void crc16_append(std::vector<float> &rfid_input);
            void gen_query_bits();
            void gen_ack_bits(const float *in);

            //SELECT COMMAND
            struct select_command{
                int SELECT_ACTION[3];
                int SELECT_MEMBANK[2];
                int SELECT_POINTER[8];
                int SELECT_LENGTH[8];
                int SELECT_TRUNCATE[1];
                std::vector<int> SELECT_MASK;
            };
            std::vector<select_command> select_input_all;
            std::vector<std::vector<float>>select_output;
            //TEST
            std::vector<float> select_bits;
            const int SELECT_CODE[4] = {1, 0, 1, 0};
            const int SELECT_TARGET[3] = {1, 0, 0};
            const int SELECT_ACTION[3] = {0, 0, 0};
            const int SELECT_MEMBANK[2] = {0, 1};
            const int SELECT_POINTER[8] = {0, 0, 1, 0, 0, 0, 0, 0};
            const int SELECT_LENGTH[8] = {0, 0, 0, 0, 0, 0, 1, 1};
            const int SELECT_MASK[3] = {0, 0, 1};
            const int SELECT_TRUNCATE[1] = {1};
            void setting();

        public:

            void print_results();

            reader_impl(int sample_rate, int dac_rate);

            ~reader_impl();

            void forecast(int noutput_items, gr_vector_int &ninput_items_required);

            int general_work(int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items);
        };

    } // namespace rfid
} // namespace gr

#endif /* INCLUDED_RFID_READER_IMPL_H */

