#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

namespace multipipe
{
        template<typename T, size_t N>
        class Pipe
        {
                private:
                        bool                    done = false; // This marks the end of transaction
                        std::queue<int>         q;            // The shared queue
                        std::mutex              m;            // Mutex used to access the queue
                        std::mutex              cvpm;         // Mutex for waking up the producer
                        std::condition_variable cv_producer;  // Conditional variable for waking up producer
                        std::condition_variable cv_consumer;  // Conditional variable for waking up consumer

                public:
                        void             transmit_data(T&& data); // Transmit data
                        bool             finish_transmission();   // Indicate end of transmission
                        bool             is_empty();              // Check if the pipe is empty
                        std::optional<T> receive_data();          // Receive data

                        // Delete copy constructor and assignment operator
                        Pipe(const Pipe&)            = delete;
                        Pipe& operator=(const Pipe&) = delete;

                        explicit Pipe();
                        ~Pipe();
        };

        template<typename T, size_t N>
        Pipe<T, N>::Pipe()
        {
                std::cout << "Constructed Pipe" << std::endl;
        }

        template<typename T, size_t N>
        void Pipe<T, N>::transmit_data(T&& data)
        {
                std::cout << "Transmitting " << data << std::endl;
        }

        template<typename T, size_t N>
        bool Pipe<T, N>::finish_transmission()
        {
                std::cout << "Terminating transmission" << std::endl;
                return false;
        }

        template<typename T, size_t N>
        bool Pipe<T, N>::is_empty()
        {
                std::cout << "Checking for data" << std::endl;
                return false;
        }

        template<typename T, size_t N>
        std::optional<T> Pipe<T, N>::receive_data()
        {
                std::cout << "Fetching data" << std::endl;
                return std::nullopt;
        }

        template<typename T, size_t N>
        Pipe<T, N>::~Pipe()
        {
                std::cout << "Destructed Pipe" << std::endl;
        }
} // namespace multipipe
