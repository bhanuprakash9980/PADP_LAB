#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif
#define VECTOR_SIZE 1024

// OpenCL kernel which is run for every work item created.
const char* saxpy_kernel = "__kernel                                  "
                           "void saxpy_kernel(float alpha,            "
                           "                  __global float *A,      "
                           "                  __global float *B,      "
                           "                  __global float *C)      "
                           "{                                         "
                           "    //Get the index of the work-item      \n"
                           "    int index = get_global_id(0);         "
                           "    C[index] = alpha* A[index] + B[index];"
                           "}                                         ";

int main(int,char**)
{
    int i;
    // Allocate space for vectors A, B and C
    float alpha = 2.0;
    float* A = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    float* B = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    float* C = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    for (i = 0; i < VECTOR_SIZE; i++) {
        A[i] = i;
        B[i] = VECTOR_SIZE - i;
        C[i] = 0;
    }

    // Get platform and device information
    cl_platform_id* platforms = NULL;
    cl_uint num_platforms;
    // Set up the Platform
    cl_int clStatus = clGetPlatformIDs(0, NULL, &num_platforms);
    platforms = (cl_platform_id*)
        malloc(sizeof(cl_platform_id) * num_platforms);
    clStatus = clGetPlatformIDs(num_platforms, platforms, NULL);

    // Get the devices list and choose the device you want to run on
    cl_device_id* device_list = NULL;
    cl_uint num_devices;

    clStatus = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
    device_list = (cl_device_id*)
        malloc(sizeof(cl_device_id) * num_devices);
    clStatus = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, num_devices, device_list, NULL);

    // Create one OpenCL context for each device in the platform
    cl_context context;
    context = clCreateContext(NULL, num_devices, device_list, NULL, NULL, &clStatus);

    // Create a command queue
    cl_queue_properties clQueueOpts[] = { CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0 };

    cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, device_list[0], clQueueOpts, &clStatus);

    // Create memory buffers on the device for each vector
    cl_mem A_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY, VECTOR_SIZE * sizeof(float), NULL, &clStatus);
    cl_mem B_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY, VECTOR_SIZE * sizeof(float), NULL, &clStatus);
    cl_mem C_clmem = clCreateBuffer(context, CL_MEM_WRITE_ONLY, VECTOR_SIZE * sizeof(float), NULL, &clStatus);

    // Copy the Buffer A and B to the device
    clStatus = clEnqueueWriteBuffer(command_queue, A_clmem, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), A, 0, NULL, NULL);
    clStatus = clEnqueueWriteBuffer(command_queue, B_clmem, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&saxpy_kernel, NULL, &clStatus);

    // Build the program
    clStatus = clBuildProgram(program, 1, device_list, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "saxpy_kernel", &clStatus);

    // Set the arguments of the kernel
    clStatus = clSetKernelArg(kernel, 0, sizeof(float), (void*)&alpha);
    clStatus = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&A_clmem);
    clStatus = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&B_clmem);
    clStatus = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&C_clmem);

    // Execute the OpenCL kernel on the list
    size_t global_size = VECTOR_SIZE; // Process the entire lists
    size_t local_size = 64; // Process one item at a time
    cl_event event; // event listener
    clStatus = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, &event);

    // Read the cl memory C_clmem on device to the host variable C
    clStatus = clEnqueueReadBuffer(command_queue, C_clmem, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), C, 0, NULL, NULL);

    // Clean up and wait for all the comands to complete.
    clStatus = clFlush(command_queue);
    clStatus = clWaitForEvents(1, &event);
    clStatus = clFinish(command_queue);

    #pragma region timing calculations
    cl_ulong time_start;
    cl_ulong time_end;

    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

    double nanoSeconds = time_end - time_start;
    #pragma endregion

    // Display the result to the screen
    for (i = 0; i < VECTOR_SIZE; i++)
        printf("%f * %f + %f = %f\n", alpha, A[i], B[i], C[i]);

    printf("OpenCl Execution time is: %0.3f milliseconds \n", nanoSeconds / 1000000.0);

    // Finally release all OpenCL allocated objects and host buffers.
    clStatus = clReleaseKernel(kernel);
    clStatus = clReleaseProgram(program);
    clStatus = clReleaseMemObject(A_clmem);
    clStatus = clReleaseMemObject(B_clmem);
    clStatus = clReleaseMemObject(C_clmem);
    clStatus = clReleaseCommandQueue(command_queue);
    clStatus = clReleaseContext(context);
    free(A);
    free(B);
    free(C);
    free(platforms);
    free(device_list);
    return 0;
}