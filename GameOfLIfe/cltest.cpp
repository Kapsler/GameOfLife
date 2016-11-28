//// Author: Markus Schordan, 2011.
//
//#include "CL/cl.hpp"
//#include <malloc.h>
//#include <iostream>
//#include <string>
//#include <sstream>
//
//using namespace std;
//
//// list of error codes from "CL/cl.h"
//string cl_errorstring(cl_int err) {
//	switch (err) {
//	case CL_SUCCESS:                          return string("Success");
//	case CL_DEVICE_NOT_FOUND:                 return string("Device not found");
//	case CL_DEVICE_NOT_AVAILABLE:             return string("Device not available");
//	case CL_COMPILER_NOT_AVAILABLE:           return string("Compiler not available");
//	case CL_MEM_OBJECT_ALLOCATION_FAILURE:    return string("Memory object allocation failure");
//	case CL_OUT_OF_RESOURCES:                 return string("Out of resources");
//	case CL_OUT_OF_HOST_MEMORY:               return string("Out of host memory");
//	case CL_PROFILING_INFO_NOT_AVAILABLE:     return string("Profiling information not available");
//	case CL_MEM_COPY_OVERLAP:                 return string("Memory copy overlap");
//	case CL_IMAGE_FORMAT_MISMATCH:            return string("Image format mismatch");
//	case CL_IMAGE_FORMAT_NOT_SUPPORTED:       return string("Image format not supported");
//	case CL_BUILD_PROGRAM_FAILURE:            return string("Program build failure");
//	case CL_MAP_FAILURE:                      return string("Map failure");
//	case CL_MISALIGNED_SUB_BUFFER_OFFSET:     return string("Misaligned sub buffer offset");
//	case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST: return string("Exec status error for events in wait list");
//	case CL_INVALID_VALUE:                    return string("Invalid value");
//	case CL_INVALID_DEVICE_TYPE:              return string("Invalid device type");
//	case CL_INVALID_PLATFORM:                 return string("Invalid platform");
//	case CL_INVALID_DEVICE:                   return string("Invalid device");
//	case CL_INVALID_CONTEXT:                  return string("Invalid context");
//	case CL_INVALID_QUEUE_PROPERTIES:         return string("Invalid queue properties");
//	case CL_INVALID_COMMAND_QUEUE:            return string("Invalid command queue");
//	case CL_INVALID_HOST_PTR:                 return string("Invalid host pointer");
//	case CL_INVALID_MEM_OBJECT:               return string("Invalid memory object");
//	case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:  return string("Invalid image format descriptor");
//	case CL_INVALID_IMAGE_SIZE:               return string("Invalid image size");
//	case CL_INVALID_SAMPLER:                  return string("Invalid sampler");
//	case CL_INVALID_BINARY:                   return string("Invalid binary");
//	case CL_INVALID_BUILD_OPTIONS:            return string("Invalid build options");
//	case CL_INVALID_PROGRAM:                  return string("Invalid program");
//	case CL_INVALID_PROGRAM_EXECUTABLE:       return string("Invalid program executable");
//	case CL_INVALID_KERNEL_NAME:              return string("Invalid kernel name");
//	case CL_INVALID_KERNEL_DEFINITION:        return string("Invalid kernel definition");
//	case CL_INVALID_KERNEL:                   return string("Invalid kernel");
//	case CL_INVALID_ARG_INDEX:                return string("Invalid argument index");
//	case CL_INVALID_ARG_VALUE:                return string("Invalid argument value");
//	case CL_INVALID_ARG_SIZE:                 return string("Invalid argument size");
//	case CL_INVALID_KERNEL_ARGS:              return string("Invalid kernel arguments");
//	case CL_INVALID_WORK_DIMENSION:           return string("Invalid work dimension");
//	case CL_INVALID_WORK_GROUP_SIZE:          return string("Invalid work group size");
//	case CL_INVALID_WORK_ITEM_SIZE:           return string("Invalid work item size");
//	case CL_INVALID_GLOBAL_OFFSET:            return string("Invalid global offset");
//	case CL_INVALID_EVENT_WAIT_LIST:          return string("Invalid event wait list");
//	case CL_INVALID_EVENT:                    return string("Invalid event");
//	case CL_INVALID_OPERATION:                return string("Invalid operation");
//	case CL_INVALID_GL_OBJECT:                return string("Invalid OpenGL object");
//	case CL_INVALID_BUFFER_SIZE:              return string("Invalid buffer size");
//	case CL_INVALID_MIP_LEVEL:                return string("Invalid mip-map level");
//	case CL_INVALID_GLOBAL_WORK_SIZE:         return string("Invalid gloal work size");
//	case CL_INVALID_PROPERTY:                 return string("Invalid property");
//	default:                                  return string("Unknown error code");
//	}
//}
//
//void handle_clerror(cl_int err) {
//	if (err != CL_SUCCESS) {
//		cerr << "OpenCL Error: " << cl_errorstring(err) << string(".") << endl;
//		exit(EXIT_FAILURE);
//	}
//}
//
//void print_separation_line(string s, int empty = 0) {
//	for (int i = empty; i<0; i++) {
//		cout << endl;
//	}
//	int length = 79;
//	int n = length / s.size();
//	for (int i = 0; i<n; i++) {
//		cout << s;
//	}
//	int rest = length%s.size();
//	for (int i = 0; i<rest; i++) {
//		cout << s[i];
//	}
//	cout << endl;
//	for (int i = 0; i<empty; i++) {
//		cout << endl;
//	}
//}
//
//void print_name(string s, int fieldwidth) {
//	cout.setf(ios::left);
//	cout.width(fieldwidth);
//	cout << s << ": ";
//}
//void print_pname(string s) {
//	print_name(s, 20);
//}
//void print_dname(string s) {
//	print_name(s, 31);
//}
//
//int main(int argc, char **argv) {
//	cl_int err;
//	cl_uint numPlatforms;
//	cl_platform_id* platformIds;
//	cl_uint numDevices;
//	cl_device_id* deviceIds;
//
//	print_separation_line("=");
//	err = clGetPlatformIDs(0, nullptr, &numPlatforms);
//	handle_clerror(err);
//	cout << "Number of platforms: " << numPlatforms << endl;
//	platformIds = static_cast<cl_platform_id*>(alloca(sizeof(cl_platform_id) * numPlatforms));
//	err = clGetPlatformIDs(numPlatforms, platformIds, nullptr);
//
//	handle_clerror(err);
//
//	for (unsigned int i = 0; i<numPlatforms; i++) {
//		print_separation_line("=");
//		cout << "PLATFORM:" << i << endl;
//		print_separation_line("=");
//		print_pname("Platform ID"); cout << platformIds[i] << endl;
//		cl_platform_id id = platformIds[i];
//		size_t size;
//		err = clGetPlatformInfo(id, CL_PLATFORM_VENDOR, 0, nullptr, &size);
//		handle_clerror(err);
//		char* vendor = static_cast<char*>(alloca(sizeof(char) * size));
//		err = clGetPlatformInfo(id, CL_PLATFORM_VENDOR, size, vendor, nullptr);
//		handle_clerror(err);
//		print_pname("Vendor name"); cout << vendor << endl;
//
//		err = clGetPlatformInfo(id, CL_PLATFORM_NAME, 0, nullptr, &size);
//		handle_clerror(err);
//		char* pname = static_cast<char*>(alloca(sizeof(char) * size));
//		err = clGetPlatformInfo(id, CL_PLATFORM_NAME, size, pname, nullptr);
//		handle_clerror(err);
//		print_pname("Platform name"); cout << pname << endl;
//
//		err = clGetPlatformInfo(id, CL_PLATFORM_VERSION, 0, nullptr, &size);
//		handle_clerror(err);
//		char* version = static_cast<char*>(alloca(sizeof(char) * size));
//		err = clGetPlatformInfo(id, CL_PLATFORM_VERSION, size, version, nullptr);
//		handle_clerror(err);
//		print_pname("Platform version"); cout << version << endl;
//
//		err = clGetDeviceIDs(id, CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);
//		handle_clerror(err);
//		print_pname("Number of devices"); cout << numDevices << endl;
//		deviceIds = static_cast<cl_device_id*>(alloca(sizeof(cl_platform_id) * numDevices));
//		err = clGetDeviceIDs(id, CL_DEVICE_TYPE_ALL, numDevices, deviceIds, nullptr);
//		handle_clerror(err);
//
//		err = clGetPlatformInfo(id, CL_PLATFORM_EXTENSIONS, 0, nullptr, &size);
//		handle_clerror(err);
//		char* extensions = static_cast<char*>(alloca(sizeof(char) * size));
//		err = clGetPlatformInfo(id, CL_PLATFORM_EXTENSIONS, size, extensions, nullptr);
//		handle_clerror(err);
//		print_pname("Platform extensions"); cout << extensions << endl;
//
//		for (unsigned int j = 0; j<numDevices; j++) {
//			print_separation_line("-");
//			cout << "DEVICE:" << j << "  [PLATFORM:" << i << "]" << endl;
//			print_separation_line("-");
//			print_dname("  Device ID"); cout << deviceIds[j] << endl;
//			cl_device_id deviceId = deviceIds[j];
//
//			cl_uint maxComputeUnits = 0;
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &maxComputeUnits, nullptr);
//			handle_clerror(err);
//			print_dname("  Max compute units"); cout << maxComputeUnits << endl;
//
//			cl_uint maxWorkItemDimensions = 0;
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &maxWorkItemDimensions, nullptr);
//			handle_clerror(err);
//			print_dname("  Max work item dimensions"); cout << maxWorkItemDimensions << " ";
//
//			size_t* workItemSizes;
//			workItemSizes = static_cast<size_t*>(alloca(sizeof(size_t) * maxWorkItemDimensions));
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_MAX_WORK_ITEM_SIZES, maxWorkItemDimensions * sizeof(size_t), workItemSizes, nullptr);
//			handle_clerror(err);
//			cout << endl;
//
//			size_t maxWorkGroupSize = 0;
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &maxWorkGroupSize, nullptr);
//			handle_clerror(err);
//			print_dname("  Max work group size"); cout << maxWorkGroupSize << endl;
//
//			cl_int deviceVendorId = 0;
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_VENDOR_ID, sizeof(cl_uint), &deviceVendorId, nullptr);
//			handle_clerror(err);
//			print_dname("  Device vendor id"); cout << deviceVendorId << endl;
//
//			cl_uint maxClockFrequency = 0;
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &maxClockFrequency, nullptr);
//			handle_clerror(err);
//			print_dname("  Max clock frequency"); cout << maxClockFrequency << endl;
//
//			cl_uint deviceAddressBits = 0;
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &deviceAddressBits, nullptr);
//			handle_clerror(err);
//			print_dname("  Device address bits"); cout << deviceAddressBits << endl;
//
//			cl_ulong deviceMaxMemAllocSize = 0;
//			err = clGetDeviceInfo(deviceId, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &deviceMaxMemAllocSize, nullptr);
//			handle_clerror(err);
//			print_dname("  Device max memory alloc size"); cout << deviceMaxMemAllocSize << endl;
//		}
//		print_separation_line("-", 1);
//	}
//	print_separation_line("=");
//	return err;
//}
