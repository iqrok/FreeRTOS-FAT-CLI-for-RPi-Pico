/* FreeRTOS_time.h
Copyright 2021 Carl John Kugler III

Licensed under the Apache License, Version 2.0 (the License); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at

   http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an AS IS BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
*/
#pragma once

#include <time.h>

#include "pico/util/datetime.h"

#ifdef __cplusplus
extern "C" {
#endif

extern time_t epochtime;

void FreeRTOS_time_init();
void setrtc(datetime_t *t);

#ifdef __cplusplus
}
#endif
