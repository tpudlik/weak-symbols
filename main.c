// Copyright 2023 The Pigweed Authors
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.
#include <stdio.h>
#include <stdint.h>

#include "weak.h"

void x_func() {
  printf("Calling A\n");
  A();

  printf("Querying a variable\n");

  printf("Variable address is %0lx\n", (intptr_t)(&variable));
  printf("Variable is %s\n", variable==42? "strong": variable==100? "weak":"undefined");

  printf("Calling a callback ...\n");
  Caller();
}

int main(void) { x_func(); }
