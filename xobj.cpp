﻿/*
* Copyright (C) 2017 YY Inc. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License"); 
* you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at
*
*	http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, 
* software distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and 
* limitations under the License.
*/


#include <time.h>
#include <vector>

#include "x2struct.hpp"
#include "xobj.hpp"

namespace x2struct {

using namespace ::std;

std::string XObj::hasa(const std::string&oname, const std::string&aname, bool &me)
{
    string allname;
    string strictname;

    vector<string> types;
    split(types, aname, ' ');
    for (size_t i=0; i<types.size(); ++i) {
        vector<string> tname;
        split(tname, types[i], ':');
        if (tname.size()==2 && tname[0]==_type) {
            strictname = tname[1];
            break;
        } else if (tname.size()==1) {
            allname = types[i];
        }
    }

    if (!strictname.empty()) {       // typename first
        vector<string> opts;
        split(opts, strictname, ',');
        if (has(opts[0])) {
            for (size_t i=1; i<opts.size(); ++i) {
                if (opts[i]==X2STRUCT_OPT_ME) {
                    me = true;
                    break;
                }
            }
            return opts[0];
        }
    }

    if (!allname.empty()) {         // then allname 
        vector<string> opts;
        split(opts, allname, ',');
        if (has(opts[0])) {
            for (size_t i=1; i<opts.size(); ++i) {
                if (opts[i]==X2STRUCT_OPT_ME) {
                    me = true;
                    break;
                }
            }
            return opts[0];
        }
    }

    if (has(oname)) {               // original last
        return oname;
    } else {
        return "";
    }
}

void XObj::set_path(const std::string&father, const std::string&key)
{
    if (!father.empty()) {
        _path.append(father);
        _path.append(".");
    }
    _path.append(key);
}

void XObj::set_path(const std::string&father, size_t index)
{
    _path.append(father);
    _path.append("[");
    _path.append(tostr(index));
    _path.append("]");
}

void XObj::me_exception(const std::string&key)
{
    std::string err="MUST EXIST node [";
    if (!_path.empty()) {
        err.append(_path);
        err.append(".");
    }
    err.append(key);
    err.append("] not exist");
    throw std::runtime_error(err);                                  \
}


}

