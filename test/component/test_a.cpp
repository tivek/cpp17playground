#include <cpp17playground/component/component_header.hpp>

using namespace cpp17playground;

int main() {
  component::B b{0, 0};
  if (component::bar(b) == 1) {
    return 0;
  } else {
    return 1;
  }
}
