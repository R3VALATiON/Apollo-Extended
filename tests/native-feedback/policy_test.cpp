#include "../../src/native_feedback_policy.h"
#include <array>
#include <cassert>
#include <iostream>
int main() {
  using namespace native_feedback;
  lease_gate gate;
  assert(gate.allows(0)); // Existing unmodified clients retain existing behavior.
  std::array<std::uint8_t, 8> bytes {1, 1, 0x70, 0x17, 0x34, 0x12, 0, 0};
  auto req = parse(bytes);
  assert(req && req->enabled && req->lease_ms == 6000 && req->id == 0x1234);
  gate.apply(*req, 1000);
  assert(gate.allows(6999) && !gate.allows(7000));
  gate.apply(*req, 6000);
  assert(gate.allows(11999) && !gate.allows(12000));
  req->enabled = false; gate.apply(*req, 6500);
  assert(!gate.allows(6500));
  for (int i : {0, 1, 6, 7}) {
    auto invalid = bytes; invalid[i] = 99; assert(!parse(invalid));
  }
  assert(!parse(std::span(bytes).first(7)));
  bytes[2] = bytes[3] = 0; assert(!parse(bytes));
  bytes[2] = bytes[3] = 255; assert(!parse(bytes));
  std::cout << "PASS: native policy parser, malformed messages, off, renewal and lease expiry\n";
}
