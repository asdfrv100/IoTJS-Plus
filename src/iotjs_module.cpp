/* Copyright 2015-2016 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "iotjs_def.h"
#include "iotjs_module.h"


namespace iotjs {


static Module _modules[MODULE_COUNT];


#define DECLARE_MODULE_INITIALIZER(upper, Camel, lower) \
iotjs_jval_t Init ## Camel();

MAP_MODULE_LIST(DECLARE_MODULE_INITIALIZER)

#undef DECLARE_MODULE_INITIALIZER


#define INIT_MODULE_LIST(upper, Camel, lower) \
  _modules[MODULE_ ## upper].kind = MODULE_ ## upper; \
  _modules[MODULE_ ## upper].module = *iotjs_jval_get_undefined(); \
  _modules[MODULE_ ## upper].fn_register = Init ## Camel;

void InitModuleList() {
  MAP_MODULE_LIST(INIT_MODULE_LIST)
}

#undef INIT_MODULE_LIST


#define CLENUP_MODULE_LIST(upper, Camel, lower) \
  if (!iotjs_jval_is_undefined(&_modules[MODULE_ ## upper].module)) \
    iotjs_jval_destroy(&_modules[MODULE_ ## upper].module); \

void CleanupModuleList() {
  MAP_MODULE_LIST(CLENUP_MODULE_LIST)
}

#undef CLENUP_MODULE_LIST


Module* GetBuiltinModule(ModuleKind kind) {
  IOTJS_ASSERT(kind < MODULE_COUNT);
  return &_modules[kind];
}


} // namespace iotjs
