# Raj's native feedback host changes

Base: `Taveszfito/Apollo-Extended`, commit `70ebba60a464e9769d1f800ac0ce669d62a0efdd`.

The base already implements native USB composite DualSense emulation on Windows through VIIPER/usbip-win2, including controller input, adaptive triggers, LEDs and native four-channel controller audio. This patch adds a bandwidth policy to that implementation; it does not claim to have created the existing backend.

The matching Android fork sends control packet `0x5506` over the existing authenticated/encrypted connection. Version 1 has eight bytes: version=1, enabled=0/1, lease milliseconds (little endian), request ID (little endian), two zero reserved bytes. A lease must be 1–10 seconds; the client uses six seconds and renews every two seconds. Invalid sizes, values, reserved bytes, unencrypted messages and messages from sessions without input permission are ignored.

The host acknowledges valid policy messages in the existing adaptive-trigger feedback envelope with an explicitly reserved marker (`event_flags=0x40`, types 'B'/'W', payload 'P', version, enabled, status, request ID). The Android fork consumes this marker before handling real adaptive-trigger effects.

After negotiation, disabled or expired policy drops controller PCM at capture/queue time and clears unsent packets. The sender does not transmit them. This reduces network traffic at the host, rather than merely discarding data on Android. Ordinary rumble, adaptive triggers, LEDs, touchpad, motion and the virtual controller's identity remain available. Capture remains initialized locally; this is a network-traffic switch, not a driver/audio-device teardown switch.

Unmodified Extended clients that never negotiate policy retain the base behavior. A patched client requires policy acknowledgement before playing native PCM. A client that connects to an older host cannot enforce source bandwidth suppression; the matching host patch is required.

## Verification

The isolated C++20 policy/parser/lease test passes with `-Wall -Wextra -Werror`. It checks parsing, malformed packets, off, renewal and expiry. The full Windows application and driver behavior have **not** been built/run in this Linux environment. The included GitHub Actions workflow is prepared for a Windows build after the fork exists; it has not run yet.

Follow the base project's `docs/building.md` for Windows/MSYS2 build requirements. This source does not install drivers while being built. Driver installation or replacement on the PC has not been performed.

The upstream Windows runtime is pinned in `third-party/windows-dualsense-runtime/README.md`. It is pre-release software and needs a separate hardware/driver validation pass before everyday use. Do not substitute an arbitrary USBip driver version: the upstream runtime explicitly pins its compatible set. A later usbip-win2 0.9.7.8 audio teardown race has a public issue and subsequent fixes; that report does not establish the pinned 0.9.7.7 set's status on this PC. Keep Secure Boot and existing protections in place while assessing compatibility.

No upstream pull request is part of this work.
