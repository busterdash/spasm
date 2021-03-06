/*==============================================================================================
    
    preprocessor.hpp
    Copyright 2019-2021 Buster Schrader
    
    This file is part of SIASM.
    
    SIASM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    
    SIASM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with SIASM.  If not, see <https://www.gnu.org/licenses/>.
    
==============================================================================================

    Preprocessor
    5/17/18 - B.D.S.
    Purpose: Handles file inclusion.
    
==============================================================================================*/

#ifndef _PREPROCESSOR_HPP
#define _PREPROCESSOR_HPP

#include "bs_util.hpp"
#include <vector>

using namespace std;

class preprocessor
{
    string out;
    string filename;
    int line_num_in;                                  //the line number of the file we are reading in
    int line_num_out;                                 //the line number of the file we are writing out
    
    bool filter_comments(string &line);               //removes comments from each line in the instructions
    bool process_includes(string &line);              //checks lines for #include<file> and processes what it finds
    bool process_labels(string &line);                //checks lines for .labels, checks for repeats, and adds them to a list
    void display_error(int line_num, string err_msg); //to be called when an irrecoverrable error occurs.
    
    public:
        bool errors_exist;                            //funneled down between included documents to determine successful preprocessing
        vector<label*> labels;                        //list of label structures that we can pass to the assembler
        string export_to_str();                       //export instructions to be included in other documents
        void export_to_file(string file);             //export instructions for the assembler to handle
        preprocessor(string file);
        void cleanup();                               //delete all the labels we created earlier
};

#endif
