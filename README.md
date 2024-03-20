This library provides an implementation of a FIFO queue (aka Pipe) which can be used as a communication mechanism in multi-threaded applications. The producer thread can insert the data at one end of the pipe which can then be retrieved by the consumer thread at the other end of the pipe in FIFO order. Refer to the test case for an example instance.

# How to use
  1. Include the header into you code.
  2. Create an object of the Pipe class.
  3. Pass this object to both the producer and the consumer threads by reference.
  4. Interact with the Pipe using the API call described below.

# API details
  1. `Pipe<T, n>()`:
     Constructor for the pipe. `T` is the data type for the pipe. `n` is the maximum queue length uptil which the transmit calls should not block.
  
  2. `bool transmit_data(T&& data)`:    
     Inserts an element of type `T` in the pipe. This is a **blocking** call. `data`is the data element to be transmitted. Returns `true` if the transmission was successfull, `false` otherwise. Transmision will fail if `finish_transmission()` was called before the call to `transmit_data(T&& data)`.
       
  3. `bool finish_transmission()`:
     Closes the transmission end of the pipe. This is a **non-blocking** call. Returns `true` if the attempt to close the pipe was successfull, `false` otherwise. Will return false if `finish_transmission()` was already called once before this call.
  
  5. `bool is_empty()`:
     Returns `true` if the pipe is empty. This is a **non-blocking** call.
  
  6. `std::optional<T> receive_data()`:
     Retrieves an element of type `T` from the pipe in First-In-First-Out order. This is a **blocking** call. Returns an optional value of type `T`. The value is absent only if the pipe is empty _and_ it has been closed.
