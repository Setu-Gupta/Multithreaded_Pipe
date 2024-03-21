#include <condition_variable>
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

                        Pipe() {}
        };

        template<typename T, size_t N>
        void Pipe<T, N>::transmit_data(T&& data)
        {
                std::unique_lock lk(m);
                if(q.size() > N) // Wait for the queue to drain
                        cv_producer.wait(lk);

                q.push(data);
                cv_consumer.notify_all();
                // std::cout << "Sent " << data << std::endl;
        }

        template<typename T, size_t N>
        bool Pipe<T, N>::finish_transmission()
        {
                std::unique_lock lk(m);
                if(done) // Return false if the pipe was already closed
                        return false;
                done = true;
                cv_consumer.notify_all();
                return true;
        }

        template<typename T, size_t N>
        bool Pipe<T, N>::is_empty()
        {
                std::unique_lock lk(m);
                return q.size() == 0;
        }

        template<typename T, size_t N>
        std::optional<T> Pipe<T, N>::receive_data()
        {
                std::unique_lock lk(m);

                if(done && q.size() == 0)
                        return std::nullopt;

                if(!done && q.size() == 0) // Wait for the queue to fill up
                        cv_consumer.wait(lk);

                if(q.size() != 0)
                {
                        std::optional<T> ret = std::make_optional<T>(q.front());
                        q.pop();
                        cv_producer.notify_all();
                        return ret;
                }

                return std::nullopt;
        }

} // namespace multipipe
