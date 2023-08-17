# Copyright 2023 TikTok Pte. Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(DUET_USE_STD_BYTE ${DUET_USE_CXX17})
set(DUET_USE_SHARED_MUTEX ${DUET_USE_CXX17})
set(DUET_USE_IF_CONSTEXPR ${DUET_USE_CXX17})
set(DUET_USE_MAYBE_UNUSED ${DUET_USE_CXX17})
set(DUET_USE_NODISCARD ${DUET_USE_CXX17})

if(DUET_USE_CXX17)
    set(DUET_LANG_FLAG "-std=c++17")
else()
    set(DUET_LANG_FLAG "-std=c++14")
endif()

set(DUET_USE_STD_FOR_EACH_N ${DUET_USE_CXX17})
# In some non-MSVC compilers std::for_each_n is not available even when compiling as C++17
if(DUET_USE_STD_FOR_EACH_N)
    cmake_push_check_state(RESET)
    set(CMAKE_REQUIRED_QUIET TRUE)
    if(NOT MSVC)
        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -O0 ${DUET_LANG_FLAG}")
        check_cxx_source_compiles("
            #include <algorithm>
            int main() {
                int a[1]{ 0 };
                volatile auto fun = std::for_each_n(a, 1, [](auto b) {});
                return 0;
            }"
            USE_STD_FOR_EACH_N
        )
        if(NOT USE_STD_FOR_EACH_N EQUAL 1)
            set(DUET_USE_STD_FOR_EACH_N OFF)
        endif()
        unset(USE_STD_FOR_EACH_N CACHE)
    endif()
    cmake_pop_check_state()
endif()
