// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <atomic>
#include <cstdint>
#include <optional>
#include <span>

namespace native_feedback {
  struct request {
    bool enabled;
    std::uint16_t lease_ms;
    std::uint16_t id;
  };
  inline std::optional<request> parse(std::span<const std::uint8_t> data) {
    if (data.size() != 8 || data[0] != 1 || data[1] > 1 || data[6] || data[7]) return std::nullopt;
    const auto lease = static_cast<std::uint16_t>(data[2] | (data[3] << 8));
    if (lease < 1000 || lease > 10000) return std::nullopt;
    return request {data[1] == 1, lease, static_cast<std::uint16_t>(data[4] | (data[5] << 8))};
  }
  class lease_gate {
    std::atomic<std::uint64_t> deadline_ms {0};
    std::atomic_bool opted_in {false};
  public:
    void apply(const request &req, std::uint64_t now) {
      deadline_ms.store(req.enabled ? now + req.lease_ms : 0, std::memory_order_release);
      opted_in.store(true, std::memory_order_release);
    }
    bool allows(std::uint64_t now) const {
      // Preserve the existing Extended protocol for clients without policy negotiation.
      return !opted_in.load(std::memory_order_acquire) || now < deadline_ms.load(std::memory_order_acquire);
    }
  };
}
