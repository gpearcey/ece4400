# Copyright 2018 Jonathan Anderson
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

CXXFLAGS=	-std=c++14

all: avl-test
clean:
	rm -f *.o avl

avl-test: avl-test.o
	$(CXX) $(LDFLAGS) avl-test.o -o avl-test

acl-test.o: AVL.h