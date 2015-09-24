// Copyright (c)    2013 Damond Howard
//                  2015 Patrick Diehl
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#include <hpx/hpx.hpp>

#include <cuda.h>
#include <cuda_runtime.h>

#include <string>

#include "cuda/fwd_declarations.hpp"
#include "cuda/buffer.hpp"
#include "cuda/server/kernel.hpp"

using namespace hpx::cuda::server;

kernel::kernel() {
}

kernel::kernel(std::string kernel_name) {
	kernel_name = kernel_name;
}

kernel::kernel(intptr_t function) {
	this->function = reinterpret_cast<CUfunction>(function);
}

kernel::~kernel() {
}

void kernel::set_stream() {
	cuStreamCreate(&cu_stream, CU_STREAM_DEFAULT);
}

void kernel::set_grid_dim(unsigned int grid_x, unsigned int grid_y,
		unsigned int grid_z) {
	grid.x = grid_x;
	grid.y = grid_y;
	grid.z = grid_z;
}

void kernel::set_block_dim(unsigned int block_x, unsigned int block_y,
		unsigned int block_z) {
	block.x = block_x;
	block.y = block_y;
	block.z = block_z;
}

void kernel::load_module(std::string file_name) {
	module_name = file_name;
}

void kernel::load_kernel(std::string kernel_name) {
	kernel_name = kernel_name;
}

std::string kernel::get_function() {
	return kernel_name;
}

std::string kernel::get_module() {
	return module_name;
}

kernel::Dim3 kernel::get_grid() {
	return grid;
}

kernel::Dim3 kernel::get_block() {
	return block;
}

void kernel::set_arg(size_t size, hpx::cuda::buffer cu_buffer) {
	///sets a buffer component as the argument to a kernel
}

void kernel::run(std::vector<intptr_t> args) {

	void *args_pointer[args.size()];

	unsigned int i = 0;
	for (auto arg : args) {

		hpx::cuda::server::buffer* buffer_tmp =
				reinterpret_cast<hpx::cuda::server::buffer*>(&arg);
		CUdeviceptr dev_pointer = buffer_tmp->get_raw_pointer();
		args_pointer[i] = (void*)&dev_pointer;
	}
	cudaSetDevice(0);
	std::cout << function << std::endl;
	CUresult res = cuLaunchKernel(this->function, this->grid.x, this->grid.y, this->grid.y, // grid dim
			this->block.x, this->block.y, this->block.z,    // block dim
			0, NULL,             // shared mem and stream
			NULL, 0);   // arguments
	std::cout << res << std::endl;
	checkCudaError("Run kernel");
	cudaDeviceSynchronize();
	checkCudaError("Synchronize");
	std::cout << "execute kernel " << function << std::endl ;
}
