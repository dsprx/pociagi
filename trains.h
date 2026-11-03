#ifndef TRAINS_HEADER_
#define TRAINS_HEADER_

#include <cstdint>
#include <cstddef>
#include <ostream>

enum class WagonType : std::uint8_t {
  FIRST_CLASS = 54,
  SECOND_CLASS = 80,
  SLEEPER = 30,
  DINING = 32
};

class WagonSeries {
private:
  WagonType type_;
  std::size_t seats_;

  constexpr const char* type_to_string() const {
    switch (type_) {
      case WagonType::FIRST_CLASS:  return "1 klasa";
      case WagonType::SECOND_CLASS: return "2 klasa";
      case WagonType::SLEEPER:      return "sypialny";
      case WagonType::DINING:       return "restauracyjny";
    }

    return "";
  }

public:
  explicit constexpr WagonSeries(WagonType type, std::size_t seats)
    : type_(type), seats_(seats) {}

  constexpr WagonSeries(WagonType type)
    : WagonSeries(type, static_cast<std::size_t>(type)) {}

  constexpr WagonSeries(const WagonSeries&) = default;
  constexpr WagonSeries(WagonSeries&&) = default;
  constexpr WagonSeries& operator=(const WagonSeries&) = default;
  constexpr WagonSeries& operator=(WagonSeries&&) = default;

  constexpr WagonType type() const {
    return type_;
  }

  constexpr std::size_t seats() const {
    return seats_;
  }

  constexpr bool operator==(const WagonSeries& other) const {
    return (this->type_ == other.type_) && (this->seats_ == other.seats_);
  }

  constexpr bool operator!=(const WagonSeries& other) const {
    return !(*this == other);
  }

  friend std::ostream& operator<<(std::ostream& os, const WagonSeries& ws);
};

inline std::ostream& operator<<(std::ostream& os, const WagonSeries& ws) {
  os << "[" << ws.type_to_string() << ", miejsca: " << ws.seats() << "]";
  return os;
}

inline constexpr WagonSeries STANDARD_FIRST_CLASS(WagonType::FIRST_CLASS);
inline constexpr WagonSeries STANDARD_SECOND_CLASS(WagonType::SECOND_CLASS);
inline constexpr WagonSeries STANDARD_SLEEPER(WagonType::SLEEPER);
inline constexpr WagonSeries STANDARD_DINING(WagonType::DINING);

class Wagon {

};

class Locomotive {

};

class Train {

};

class Depot {

};

class Dispatcher {

};

#endif  // TRAINS_HEADER_
