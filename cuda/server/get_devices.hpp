// Copyright (c)        2015 Patrick Diehl
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_CUDA_SERVER_GET_DEVICES_HPP_
#define HPX_CUDA_SERVER_GET_DEVICES_HPP_

#include <hpx/hpx.hpp>
#include <hpx/config.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/components/server/managed_component_base.hpp>
#include <hpx/runtime/components/server/locking_hook.hpp>

#include <cuda.h>
#include "../../cuda.hpp"
#include "../CudaErrorHandling.hpp"

#include "../fwd_declarations.hpp"

////////////////////////////////////////////////////////////////
namespace hpx {
namespace cuda {
namespace server {

// /////////////////////////////////////////////////////
//  Global cuda functions
//

// Returns the IDs of all devices on current host
std::vector<hpx::cuda::device>
get_devices(int major, int minor);

//[opencl_management_action_types
HPX_DEFINE_PLAIN_ACTION(get_devices, get_devices_action);
//]

}
}
}

#endif
