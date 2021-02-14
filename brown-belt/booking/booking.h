//
// Created by smarty on 27.10.2020.
//

#ifndef BOOKING_BOOKING_H
#define BOOKING_BOOKING_H
#include <utility>

namespace RAII {
    template <typename T>
    class Booking {
    private:
        T* provider_;
        int id_;
    public:
        Booking(T* provider, int counter)
        : provider_(provider)
        , id_(counter)
        {}

        Booking(const Booking&) = delete;
        Booking& operator=(const Booking&) = delete;

        Booking(Booking&& other) noexcept
        {
            provider_ = std::move(other.provider_);
            other.provider_ = nullptr;

            id_ = std::move(other.id_);
        }

        Booking& operator=(Booking&& other) noexcept
        {
            provider_ = std::move(other.provider_);
            other.provider_ = nullptr;
            id_ = std::move(other.id_);

            return *this;
        }

        ~Booking()
        {
            if (provider_) {
                provider_->CancelOrComplete(*this);
            }
        }
    };
}
#endif //BOOKING_BOOKING_H
