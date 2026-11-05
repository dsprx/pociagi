#ifndef TRAINS_HEADER_
#define TRAINS_HEADER_

#include <cstdint>
#include <cstddef>
#include <ostream>
#include <utility>
#include <compare>
#include <string>

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
public:
  using unique_id_t = std::size_t;

private:
  static inline constexpr unique_id_t EMPTY_NUMBER = 0;
  static inline constexpr WagonSeries DEFAULT_EMPTY_SERIES{WagonType::FIRST_CLASS};

  static inline constinit unique_id_t ever_built_ = 0;
  static inline constinit unique_id_t in_service_ = 0;

  unique_id_t number_;
  WagonSeries series_;

  static unique_id_t assign_number() {
    ++in_service_;
    return ++ever_built_;
  }

  void release() {
    if (*this) {
      --in_service_;
      number_ = EMPTY_NUMBER;
    }
  }

public:
  explicit Wagon(WagonSeries series) : number_(assign_number()), series_(series) {}

  constexpr Wagon() : number_(EMPTY_NUMBER), series_(DEFAULT_EMPTY_SERIES) {}

  Wagon(const Wagon& other)
    : number_((other) ? assign_number() : EMPTY_NUMBER),
      series_(other.series_) {}

  constexpr Wagon(Wagon&& other)
    : number_(std::exchange(other.number_, EMPTY_NUMBER)),
      series_(other.series_) {}

  ~Wagon() {
    release();
  }

  Wagon& operator=(const Wagon& other) {
    series_ = other.series_;

    if (!other) {
      release();
    } else if (!(*this)) {
      number_ = assign_number();
    }

    return *this;
  }

  Wagon& operator=(Wagon&& other) {
    if (this != &other) {
      release();

      number_ = std::exchange(other.number_, EMPTY_NUMBER);
      series_ = other.series_;
    }

    return *this;
  }

  constexpr unique_id_t number() const {
    return number_;
  }

  constexpr WagonSeries series() const {
    return series_;
  }

  constexpr operator WagonSeries() const {
    return series_;
  }

  explicit constexpr operator bool() const {
    return number_ != EMPTY_NUMBER;
  }

  constexpr bool operator==(const Wagon& other) const {
    return number_ == other.number_;
  }

  constexpr std::strong_ordering operator<=>(const Wagon& other) const {
    return number_ <=> other.number_;
  }

  static unique_id_t ever_built() {
    return ever_built_;
  }

  static unique_id_t in_service() {
    return in_service_;
  }
};

inline std::ostream& operator<<(std::ostream& os, const Wagon& wagon) {
  if (wagon) {
    os << "Wagon nr " << wagon.number() << " " << wagon.series();
  } else {
    os << "Wagon pusty";
  }

  return os;
}

class Locomotive {
private:
  static inline constexpr std::size_t EMPTY_MAX_WAGONS = 0;

  std::string designation_;
  std::size_t max_wagons_;

public:
  explicit Locomotive(std::string designation, std::size_t max_wagons)
    : designation_(designation.empty() ? "?" : std::move(designation)),
      max_wagons_(max_wagons) {}

  Locomotive() : designation_(), max_wagons_(EMPTY_MAX_WAGONS) {}

  Locomotive(const Locomotive&) = delete;
  Locomotive& operator=(const Locomotive&) = delete;

  Locomotive(Locomotive&& other)
    : designation_(std::exchange(other.designation_, std::string{})),
      max_wagons_(std::exchange(other.max_wagons_, EMPTY_MAX_WAGONS)) {}

  Locomotive& operator=(Locomotive&& other) {
    if (this != &other) {
      designation_ = std::exchange(other.designation_, std::string{});
      max_wagons_ = std::exchange(other.max_wagons_, EMPTY_MAX_WAGONS);
    }

    return *this;
  }

  const std::string& designation() const {
    return designation_;
  }

  std::size_t max_wagons() const {
    return max_wagons_;
  }

  explicit operator bool() const {
    return !designation_.empty();
  }
};

inline std::ostream& operator<<(std::ostream& os, const Locomotive& loc) {
  if (loc) {
    os << loc.designation() << " (uciąg: " << loc.max_wagons() << ")";
  } else {
    os << "brak lokomotywy";
  }

  return os;
}

class Train {

};

class Depot {

};

class Dispatcher {

};

#endif  // TRAINS_HEADER_
